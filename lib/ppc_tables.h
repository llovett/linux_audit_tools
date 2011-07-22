/* This is a generated file, see Makefile.am for its inputs. */
static const char ppc_syscall_strings[] = "_llseek\0_newselect\0_sysctl\0accept\0accept4\0access\0acct\0add_key\0adjtimex\0afs_syscall\0"
	"alarm\0bdflush\0bind\0break\0brk\0capget\0capset\0chdir\0chmod\0chown\0"
	"chroot\0clock_getres\0clock_gettime\0clock_nanosleep\0clock_settime\0clone\0close\0connect\0creat\0create_module\0"
	"delete_module\0dup\0dup2\0dup3\0epoll_create\0epoll_create1\0epoll_ctl\0epoll_pwait\0epoll_wait\0eventfd\0"
	"eventfd2\0execve\0exit\0exit_group\0faccessat\0fadvise64\0fadvise64_64\0fallocate\0fanotify_init\0fanotify_mark\0"
	"fchdir\0fchmod\0fchmodat\0fchown\0fchownat\0fcntl\0fcntl64\0fdatasync\0fgetxattr\0flistxattr\0"
	"flock\0fork\0fremovexattr\0fsetxattr\0fstat\0fstat64\0fstatat\0fstatfs\0fstatfs64\0fsync\0"
	"ftime\0ftruncate\0ftruncate64\0futex\0futimesat\0get_kernel_syms\0get_robust_list\0getcpu\0getcwd\0getdents\0"
	"getdents64\0getegid\0geteuid\0getgid\0getgroups\0getitimer\0getpeername\0getpgid\0getpgrp\0getpid\0"
	"getpmsg\0getppid\0getpriority\0getresgid\0getresuid\0getrlimit\0getrusage\0getsid\0getsockname\0getsockopt\0"
	"gettid\0gettimeofday\0getuid\0getxattr\0gtty\0idle\0init_module\0inotify_add_watch\0inotify_init\0inotify_init1\0"
	"inotify_rm_watch\0io_cancel\0io_destroy\0io_getevents\0io_setup\0io_submit\0ioctl\0ioperm\0iopl\0ioprio_get\0"
	"ioprio_set\0ipc\0kexec_load\0keyctl\0kill\0lchown\0lgetxattr\0link\0linkat\0listen\0"
	"listxattr\0llistxattr\0lock\0lookup_dcookie\0lremovexattr\0lseek\0lsetxattr\0lstat\0lstat64\0madvise\0"
	"mincore\0mkdir\0mkdirat\0mknod\0mknodat\0mlock\0mlockall\0mmap\0mmap2\0modify_ldt\0"
	"mount\0move_pages\0mprotect\0mpx\0mq_getsetattr\0mq_notify\0mq_open\0mq_timedreceive\0mq_timedsend\0mq_unlink\0"
	"mremap\0msync\0multiplexer\0munlock\0munlockall\0munmap\0nanosleep\0nfsservctl\0nice\0oldfstat\0"
	"oldlstat\0oldolduname\0oldstat\0olduname\0open\0openat\0pause\0pciconfig_iobase\0pciconfig_read\0pciconfig_write\0"
	"perf_counter_open\0personality\0pipe\0pipe2\0pivot_root\0poll\0ppoll\0prctl\0pread\0preadv\0"
	"prlimit64\0prof\0profil\0pselect6\0ptrace\0putpmsg\0pwrite\0pwritev\0query_module\0quotactl\0"
	"read\0readahead\0readdir\0readlink\0readlinkat\0readv\0reboot\0recv\0recvfrom\0recvmmsg\0"
	"recvmsg\0remap_file_pages\0removexattr\0rename\0renameat\0request_key\0rmdir\0rt_sigaction\0rt_sigpending\0rt_sigprocmask\0"
	"rt_sigqueueinfo\0rt_sigreturn\0rt_sigsuspend\0rt_sigtimedwait\0rt_tgsigqueueinfo\0rtas\0sched_get_priority_max\0sched_get_priority_min\0sched_getaffinity\0sched_getparam\0"
	"sched_getscheduler\0sched_rr_get_interval\0sched_setaffinity\0sched_setparam\0sched_setscheduler\0sched_yield\0select\0send\0sendfile\0sendfile64\0"
	"sendmsg\0sendto\0set_robust_list\0set_tid_address\0setdomainname\0setfsgid\0setfsuid\0setgid\0setgroups\0sethostname\0"
	"setitimer\0setpgid\0setpriority\0setregid\0setresgid\0setresuid\0setreuid\0setrlimit\0setsid\0setsockopt\0"
	"settimeofday\0setuid\0setxattr\0sgetmask\0shutdown\0sigaction\0sigaltstack\0signal\0signalfd\0signalfd4\0"
	"sigpending\0sigprocmask\0sigreturn\0sigsuspend\0socket\0socketcall\0socketpair\0splice\0spu_create\0spu_run\0"
	"ssetmask\0stat\0stat64\0statfs\0statfs64\0stime\0stty\0subpage_prot\0swapcontext\0swapoff\0"
	"swapon\0symlink\0symlinkat\0sync\0sync_file_range2\0sysfs\0sysinfo\0syslog\0tee\0tgkill\0"
	"time\0timer_create\0timer_delete\0timer_getoverrun\0timer_gettime\0timer_settime\0timerfd\0timerfd_gettime\0timerfd_settime\0times\0"
	"tkill\0truncate\0truncate64\0tuxcall\0ugetrlimit\0ulimit\0umask\0umount\0umount2\0uname\0"
	"unlink\0unlinkat\0unshare\0uselib\0ustat\0utime\0utimensat\0utimes\0vfork\0vhangup\0"
	"vm86\0vmsplice\0wait4\0waitid\0waitpid\0write\0writev";
static const unsigned ppc_syscall_s2i_s[] = {
	0,8,19,27,34,42,49,54,62,71,
	83,89,97,102,108,112,119,126,132,138,
	144,151,164,178,194,208,214,220,228,234,
	248,262,266,271,276,289,303,313,325,336,
	344,353,360,365,376,386,396,409,419,433,
	447,454,461,470,477,486,492,500,510,520,
	531,537,542,555,565,571,579,587,595,605,
	611,617,627,639,645,655,671,687,694,701,
	710,721,729,737,744,754,764,776,784,792,
	799,807,815,827,837,847,857,867,874,886,
	897,904,917,924,933,938,943,955,973,986,
	1000,1017,1027,1038,1051,1060,1070,1076,1083,1088,
	1099,1110,1114,1125,1132,1137,1144,1154,1159,1166,
	1173,1183,1194,1199,1214,1227,1233,1243,1249,1257,
	1265,1273,1279,1287,1293,1301,1307,1316,1321,1327,
	1338,1344,1355,1364,1368,1382,1392,1400,1416,1429,
	1439,1446,1452,1464,1472,1483,1490,1500,1511,1516,
	1525,1534,1546,1554,1563,1568,1575,1581,1598,1613,
	1629,1647,1659,1664,1670,1681,1686,1692,1698,1704,
	1711,1721,1726,1733,1742,1749,1757,1764,1772,1785,
	1794,1799,1809,1817,1826,1837,1843,1850,1855,1864,
	1873,1881,1898,1910,1917,1926,1938,1944,1957,1971,
	1986,2002,2015,2029,2045,2063,2068,2091,2114,2132,
	2147,2166,2188,2206,2221,2240,2252,2259,2264,2273,
	2284,2292,2299,2315,2331,2345,2354,2363,2370,2380,
	2392,2402,2410,2422,2431,2441,2451,2460,2470,2477,
	2488,2501,2508,2517,2526,2535,2545,2557,2564,2573,
	2583,2594,2606,2616,2627,2634,2645,2656,2663,2674,
	2682,2691,2696,2703,2710,2719,2725,2730,2743,2755,
	2763,2770,2778,2788,2793,2810,2816,2824,2831,2835,
	2842,2847,2860,2873,2890,2904,2918,2926,2942,2958,
	2964,2970,2979,2990,2998,3009,3016,3022,3029,3037,
	3043,3050,3059,3067,3074,3080,3086,3096,3103,3109,
	3117,3122,3131,3137,3144,3152,3158,
};
static const int ppc_syscall_s2i_i[] = {
	140,142,149,330,344,33,51,269,124,137,
	27,134,327,17,45,183,184,12,15,181,
	61,247,246,248,245,120,6,328,8,127,
	129,41,63,316,236,315,237,303,238,307,
	314,11,1,234,298,233,254,309,323,324,
	133,94,297,95,289,55,204,148,214,217,
	143,2,220,211,108,197,291,100,253,118,
	35,93,194,221,290,130,299,302,182,141,
	202,50,49,47,80,105,332,132,65,20,
	187,64,96,170,165,76,77,147,331,340,
	207,78,24,212,32,112,128,276,275,318,
	277,231,228,229,227,230,54,101,110,274,
	273,117,268,271,37,16,213,9,294,329,
	215,216,53,235,219,19,210,107,196,205,
	206,39,287,14,288,150,152,90,192,123,
	21,301,125,56,267,266,262,265,264,263,
	163,144,201,151,153,91,162,168,34,28,
	84,59,18,109,5,286,29,200,198,199,
	319,136,42,317,203,167,281,171,179,320,
	325,44,98,280,26,188,180,321,166,131,
	3,191,89,85,296,145,88,336,337,343,
	342,239,218,38,293,270,40,173,175,174,
	177,172,178,176,322,255,159,160,223,155,
	157,161,222,154,156,158,82,334,186,226,
	341,335,300,232,121,139,138,46,81,74,
	104,57,97,71,169,164,70,75,66,339,
	79,23,209,68,338,67,185,48,305,313,
	73,126,119,72,326,102,333,283,279,278,
	69,106,195,99,252,25,31,310,249,115,
	87,83,295,36,308,135,116,103,284,250,
	13,240,244,243,242,241,306,312,311,43,
	208,92,193,225,190,58,60,22,52,122,
	10,292,282,86,62,30,304,251,189,111,
	113,285,114,272,7,4,146,
};
static int ppc_syscall_s2i(const char *s, int *value) {
	size_t len, i;
	len = strlen(s);
	{ char copy[len + 1];
	for (i = 0; i < len; i++) {
		char c = s[i];
		copy[i] = GT_ISUPPER(c) ? c - 'A' + 'a' : c;
	}
	copy[i] = 0;
	return s2i__(ppc_syscall_strings, ppc_syscall_s2i_s, ppc_syscall_s2i_i, 337, copy, value);
	}
}
static const unsigned ppc_syscall_i2s_direct[] = {
	360,537,1794,3152,1563,214,3144,228,1154,3043,
	353,126,2842,1287,132,1137,102,1546,1227,792,
	1338,3022,2501,917,2719,1742,83,1516,1575,3080,
	2725,933,42,1511,611,2788,1132,1910,1273,1938,
	262,1659,2958,1721,108,2363,737,2557,729,721,
	49,3029,1194,1070,486,1364,2402,3009,1534,3016,
	144,3074,266,807,784,2470,2535,2517,2682,2451,
	2422,2616,2583,2380,2460,847,857,904,2488,744,
	2370,2252,2770,1525,1817,3067,2763,1843,1809,1316,
	1483,2970,617,454,470,815,2410,1726,2703,587,
	1076,2634,2824,2392,754,2691,1243,565,1554,1083,
	3109,938,3117,3131,2755,2816,1110,605,2606,208,
	2331,3037,1327,62,1355,2594,234,943,248,655,
	1785,776,447,89,2810,1647,71,2354,2345,0,
	701,8,531,1446,1837,3158,867,500,19,1301,
	1464,1307,1472,2206,2132,2221,2147,2240,2068,2091,
	2166,1490,1439,2441,837,1772,1681,1500,2431,827,
	1692,2002,1944,1971,1957,2029,1986,2015,1698,1757,
	138,694,112,119,2545,2264,799,1749,3103,2998,
	1799,1321,2979,627,2696,1249,571,1598,1613,1581,
	1452,710,1670,492,1257,1265,897,2964,2508,1233,
	555,924,1144,510,1173,1183,520,1898,1214,542,
	639,2188,2114,-1u,2990,2273,1051,1027,1038,1060,
	1017,2315,386,365,1199,276,303,325,1881,2847,
	2904,2890,2873,2860,194,164,151,178,2743,2835,
	3096,2710,595,396,2063,-1u,-1u,-1u,-1u,-1u,
	-1u,1392,1429,1416,1400,1382,1368,1114,54,1926,
	1125,3137,1099,1088,973,955,1000,2674,2663,1733,
	1686,3059,2656,2831,3122,1568,1279,1293,477,645,
	579,3050,1917,1159,2778,1826,461,376,671,2299,
	1344,687,313,3086,2564,2918,336,2793,409,2730,
	2942,2926,2573,344,289,271,1664,986,1629,1704,
	1764,2045,419,433,1711,2627,97,220,1166,27,
	874,764,2645,2259,2292,1850,1855,2526,2477,886,
	2284,1873,1864,34,
};
static const char *ppc_syscall_i2s(int v) {
	return i2s_direct__(ppc_syscall_strings, ppc_syscall_i2s_direct, 1, 344, v);
}
