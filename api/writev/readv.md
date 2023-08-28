#写文件
函数write从文件的当前偏移写文件，调用进程把要写入的数据存放在一个缓冲区
ssize_t write(int fd, const void *buf, size_t count);

函数pwrite64从指定偏移开始写文件
ssize_t pwrite64(int fd, const void *buf, size_t count, off_t offset);

功能：将数据从文件描述符读到分散的内存块中，即分散读
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

功能：将多块分散的内存数据一并写入文件描述符中，即集中写
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

函数pwritev从指定偏移开始写文件，调用进程把要写入的数据存放在多个分散的缓冲区
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);


函数pwritev2在函数pwritev的基础上增加了参数“int flags
ssize_t pwritev2(int fd, const struct iovec *iov, int iovcnt, off_t offset, int flags);
其中pwritev和pwritev2是Linux内核私有的系统调用



#glibc库封装的I/O写函数


size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);




#把内存中所有修改过的文件元数据和文件数据写回到存储设备

sync把内存中所有修改过的文件元数据和文件数据写回到存储设备
    void sync(void);


syncfs把文件描述符fd引用的文件所属的文件系统写回到存储设备
    int syncfs(int fd);


fsync把文件描述符fd引用的文件修改过的元数据和数据写回到存储设备
    int fsync(int fd);

fdatasync把文件描述符fd引用的文件修改过的数据写回到存储设备，还会把检索这些数据需要的元数据写回到存储设备
    int fdatasync(int fd);


把数据从用户空间缓冲区写到内核的标准I/O流函数
    int fflush(FILE *stream);



#写回存储设备情况
（1）周期回写。 默认5秒回写一次
（2）当脏页的数量达到限制的时候，强制回写。
（3）进程调用sync和syncfs等系统调用



#读文件
进程读文件的方式有3种。
（1）调用内核提供的读文件的系统调用。
（2）调用glibc库封装的读文件的标准I/O流函数。
（3）创建基于文件的内存映射，把文件的一个区间映射到进程的虚拟地址空间，然后直接读内存
第2种方式在用户空间创建了缓冲区，能减少系统调用的次数，提高性能。第3种方式可以避免系统调用，性能最高



系统调用read从文件的当前偏移读文件，把数据存放在一个缓冲区
    ssize_t read(int fd, void *buf, size_t count);


系统调用pread64从指定偏移开始读文件
    ssize_t pread64(int fd, void *buf, size_t count, off_t offset);


系统调用readv从文件的当前偏移读文件，把数据存放在多个分散的缓冲区
    ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

系统调用preadv从指定偏移开始读文件，把数据存放在多个分散的缓冲区
    ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);

系统调用preadv2在系统调用preadv的基础上增加了参数“int flags”
    ssize_t preadv2(int fd, const struct iovec *iov, int iovcnt, off_t offset, int flags);

其中preadv和preadv2是Linux内核私有的系统调用














