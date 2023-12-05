
## epoll数据结构

### epoll用户空间数据结构

    typedef union epoll_data
    {
      void *ptr;
      int fd;
      uint32_t u32;
      uint64_t u64;
    } epoll_data_t;

    struct epoll_event
    {
      uint32_t events;	/* Epoll events */
      epoll_data_t data;	/* User data variable */
    } __EPOLL_PACKED;