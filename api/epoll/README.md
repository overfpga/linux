
## epoll数据结构

### epoll用户空间数据结构

    typedef union epoll_data  /* epoll_data 是用户数据，内核不会处理，只是与fd绑定，当fd事件到来时，epoll_wait会返回，用户会继续处理*/
    {
      void *ptr;
      int fd;
      uint32_t u32;
      uint64_t u64;
    } epoll_data_t;

    struct epoll_event
    {
      uint32_t events;	/* Epoll events 事件类型，EPOLLIN或EPOLLOUT等*/
      epoll_data_t data;	/* User data variable */
    } __EPOLL_PACKED;

## epoll函数

### epoll_ctl

    SYSCALL_DEFINE4(epoll_ctl, int, epfd, int, op, int, fd,
        struct epoll_event __user *, event)
    {
      int error;
      int full_check = 0;
      struct fd f, tf;
      struct eventpoll *ep;
      struct epitem *epi;
      struct epoll_event epds;
      struct eventpoll *tep = NULL;

      error = -EFAULT;
      if (ep_op_has_event(op) &&
          copy_from_user(&epds, event, sizeof(struct epoll_event)))
        goto error_return;

      error = -EBADF;
      f = fdget(epfd);
      if (!f.file)
        goto error_return;

      /* Get the "struct file *" for the target file */
      tf = fdget(fd);
      if (!tf.file)
        goto error_fput;

      /* The target file descriptor must support poll */
      error = -EPERM;
      if (!file_can_poll(tf.file))
        goto error_tgt_fput;

      /* Check if EPOLLWAKEUP is allowed */
      if (ep_op_has_event(op))
        ep_take_care_of_epollwakeup(&epds);

      error = -EINVAL;
      if (f.file == tf.file || !is_file_epoll(f.file))
        goto error_tgt_fput;


      if (ep_op_has_event(op) && (epds.events & EPOLLEXCLUSIVE)) {
        if (op == EPOLL_CTL_MOD)
          goto error_tgt_fput;
        if (op == EPOLL_CTL_ADD && (is_file_epoll(tf.file) ||
            (epds.events & ~EPOLLEXCLUSIVE_OK_BITS)))
          goto error_tgt_fput;
      }

      /*
      * At this point it is safe to assume that the "private_data" contains
      * our own data structure.
      */
      ep = f.file->private_data;

      mutex_lock_nested(&ep->mtx, 0);
      if (op == EPOLL_CTL_ADD) {
        if (!list_empty(&f.file->f_ep_links) ||
                is_file_epoll(tf.file)) {
          full_check = 1;
          mutex_unlock(&ep->mtx);
          mutex_lock(&epmutex);
          if (is_file_epoll(tf.file)) {
            error = -ELOOP;
            if (ep_loop_check(ep, tf.file) != 0) {
              clear_tfile_check_list();
              goto error_tgt_fput;
            }
          } else
            list_add(&tf.file->f_tfile_llink,
                  &tfile_check_list);
          mutex_lock_nested(&ep->mtx, 0);
          if (is_file_epoll(tf.file)) {
            tep = tf.file->private_data;
            mutex_lock_nested(&tep->mtx, 1);
          }
        }
      }

      epi = ep_find(ep, tf.file, fd);

      error = -EINVAL;
      switch (op) {
      case EPOLL_CTL_ADD:
        if (!epi) {
          epds.events |= EPOLLERR | EPOLLHUP;
          error = ep_insert(ep, &epds, tf.file, fd, full_check);
        } else
          error = -EEXIST;
        if (full_check)
          clear_tfile_check_list();
        break;
      case EPOLL_CTL_DEL:
        if (epi)
          error = ep_remove(ep, epi);
        else
          error = -ENOENT;
        break;
      case EPOLL_CTL_MOD:
        if (epi) {
          if (!(epi->event.events & EPOLLEXCLUSIVE)) {
            epds.events |= EPOLLERR | EPOLLHUP;
            error = ep_modify(ep, epi, &epds);
          }
        } else
          error = -ENOENT;
        break;
      }
      if (tep != NULL)
        mutex_unlock(&tep->mtx);
      mutex_unlock(&ep->mtx);

    error_tgt_fput:
      if (full_check)
        mutex_unlock(&epmutex);

      fdput(tf);
    error_fput:
      fdput(f);
    error_return:

      return error;
    }













