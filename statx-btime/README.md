# statx and btime

Creation time of a file (aka birth time or `btime`) is not among [unix file
timestamps](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html)
(`atime`, `mtime` and `ctime`) as defined by POSIX.

That said, some Linux filesystems such as ext4 or btrfs implements it, and
since Linux 4.11, `btime` is available via [`statx(2)`
syscall](http://man7.org/linux/man-pages/man2/statx.2.html).

## References and timeline

* 2010 [File creation times](https://lwn.net/Articles/397442) (lwn.net)
* 2016 [statx](https://lwn.net/Articles/685791) (lwn.net)
* 2017 [statx merged](https://lwn.net/Articles/718222/), available since [Linux
  4.11](https://kernelnewbies.org/Linux_4.11#statx.282.29.2C_a_modern_stat.282.29_alternative)
* 2017 [statx glibc wrapper
  merged](https://sourceware.org/bugzilla/show_bug.cgi?id=21297), available
  since [glibc
  2.28](https://www.sourceware.org/ml/libc-alpha/2018-08/msg00003.html) (2018)
* 2018 `statx` is still not used in gnulib or gnu coreutils (stat, ls)
