
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