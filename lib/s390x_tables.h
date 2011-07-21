/* This is a generated file, see Makefile.am for its inputs. */
static const char s390x_syscall_strings[] = "_sysctl\0access\0acct\0add_key\0adjtimex\0afs_syscall\0alarm\0bdflush\0brk\0capget\0"
	"capset\0chdir\0chmod\0chown\0chroot\0clock_getres\0clock_gettime\0clock_nanosleep\0clock_settime\0clone\0"
	"close\0creat\0create_module\0delete_module\0dup\0dup2\0dup3\0epoll_create\0epoll_create1\0epoll_ctl\0"
	"epoll_pwait\0epoll_wait\0eventfd\0eventfd2\0execve\0exit\0exit_group\0faccessat\0fadvise64\0fallocate\0"
	"fanotify_init\0fanotify_mark\0fchdir\0fchmod\0fchmodat\0fchown\0fchownat\0fcntl\0fdatasync\0fgetxattr\0"
	"flistxattr\0flock\0fork\0fremovexattr\0fsetxattr\0fstat\0fstatfs\0fstatfs64\0fsync\0ftruncate\0"
	"futex\0futimesat\0get_kernel_syms\0get_robust_list\0getcpu\0getcwd\0getdents\0getegid\0geteuid\0getgid\0"
	"getgroups\0getitimer\0getpgid\0getpgrp\0getpid\0getpmsg\0getppid\0getpriority\0getresgid\0getresuid\0"
	"getrlimit\0getrusage\0getsid\0gettid\0gettimeofday\0getuid\0getxattr\0idle\0init_module\0inotify_add_watch\0"
	"inotify_init\0inotify_init1\0inotify_rm_watch\0io_cancel\0io_destroy\0io_getevents\0io_setup\0io_submit\0ioctl\0ioprio_get\0"
	"ioprio_set\0ipc\0kexec_load\0keyctl\0kill\0lchown\0lgetxattr\0link\0linkat\0listxattr\0"
	"llistxattr\0lremovexattr\0lseek\0lsetxattr\0lstat\0madvise\0mincore\0mkdir\0mkdirat\0mknod\0"
	"mknodat\0mlock\0mlockall\0mmap\0mount\0mprotect\0mq_getsetattr\0mq_notify\0mq_open\0mq_timedreceive\0"
	"mq_timedsend\0mq_unlink\0mremap\0msync\0munlock\0munlockall\0munmap\0nanosleep\0newfstatat\0nfsservctl\0"
	"nice\0open\0openat\0pause\0perf_event_open\0personality\0pipe\0pipe2\0pivot_root\0poll\0"
	"ppoll\0prctl\0pread\0preadv\0prlimit64\0pselect6\0ptrace\0putpmsg\0pwrite\0pwritev\0"
	"query_module\0quotactl\0read\0readahead\0readdir\0readlink\0readlinkat\0readv\0reboot\0remap_file_pages\0"
	"removexattr\0rename\0renameat\0request_key\0rmdir\0rt_sigaction\0rt_sigpending\0rt_sigprocmask\0rt_sigqueueinfo\0rt_sigreturn\0"
	"rt_sigsuspend\0rt_sigtimedwait\0rt_tgsigqueueinfo\0sched_get_priority_max\0sched_get_priority_min\0sched_getaffinity\0sched_getparam\0sched_getscheduler\0sched_rr_get_interval\0sched_setaffinity\0"
	"sched_setparam\0sched_setscheduler\0sched_yield\0select\0sendfile\0set_robust_list\0set_tid_address\0setdomainname\0setfsgid\0setfsuid\0"
	"setgid\0setgroups\0sethostname\0setitimer\0setpgid\0setpriority\0setregid\0setresgid\0setresuid\0setreuid\0"
	"setrlimit\0setsid\0settimeofday\0setuid\0setxattr\0sigaction\0sigaltstack\0signal\0signalfd\0signalfd4\0"
	"sigpending\0sigprocmask\0sigreturn\0sigsuspend\0socketcall\0splice\0stat\0statfs\0statfs64\0swapoff\0"
	"swapon\0symlink\0symlinkat\0sync\0sync_file_range\0sysfs\0sysinfo\0syslog\0tee\0tgkill\0"
	"timer_create\0timer_delete\0timer_getoverrun\0timer_gettime\0timer_settime\0timerfd\0timerfd_create\0timerfd_gettime\0timerfd_settime\0times\0"
	"tkill\0truncate\0umask\0umount\0umount2\0uname\0unlink\0unlinkat\0unshare\0uselib\0"
	"ustat\0utime\0utimensat\0utimes\0vfork\0vhangup\0vmsplice\0wait4\0waitid\0write\0"
	"writev";
static const unsigned s390x_syscall_s2i_s[] = {
	0,8,15,20,28,37,49,55,63,67,
	74,81,87,93,99,106,119,133,149,163,
	169,175,181,195,209,213,218,223,236,250,
	260,272,283,291,300,307,312,323,333,343,
	353,367,381,388,395,404,411,420,426,436,
	446,457,463,468,481,491,497,505,515,521,
	531,537,547,563,579,586,593,602,610,618,
	625,635,645,653,661,668,676,684,696,706,
	716,726,736,743,750,763,770,779,784,796,
	814,827,841,858,868,879,892,901,911,917,
	928,939,943,954,961,966,973,983,988,995,
	1005,1016,1029,1035,1045,1051,1059,1067,1073,1081,
	1087,1095,1101,1110,1115,1121,1130,1144,1154,1162,
	1178,1191,1201,1208,1214,1222,1233,1240,1250,1261,
	1272,1277,1282,1289,1295,1311,1323,1328,1334,1345,
	1350,1356,1362,1368,1375,1385,1394,1401,1409,1416,
	1424,1437,1446,1451,1461,1469,1478,1489,1495,1502,
	1519,1531,1538,1547,1559,1565,1578,1592,1607,1623,
	1636,1650,1666,1684,1707,1730,1748,1763,1782,1804,
	1822,1837,1856,1868,1875,1884,1900,1916,1930,1939,
	1948,1955,1965,1977,1987,1995,2007,2016,2026,2036,
	2045,2055,2062,2075,2082,2091,2101,2113,2120,2129,
	2139,2150,2162,2172,2183,2194,2201,2206,2213,2222,
	2230,2237,2245,2255,2260,2276,2282,2290,2297,2301,
	2308,2321,2334,2351,2365,2379,2387,2402,2418,2434,
	2440,2446,2455,2461,2468,2476,2482,2489,2498,2506,
	2513,2519,2525,2535,2542,2548,2556,2565,2571,2578,
	2584,
};
static const int s390x_syscall_s2i_i[] = {
	149,33,51,278,124,137,27,134,45,184,
	185,12,15,212,61,261,260,262,259,120,
	6,8,127,129,41,63,326,249,327,250,
	312,251,318,323,11,1,248,300,253,314,
	332,333,133,94,299,207,291,55,148,229,
	232,143,2,235,226,108,100,266,118,93,
	238,292,130,305,311,183,141,202,201,200,
	205,105,132,65,20,188,64,96,211,209,
	191,77,147,236,78,199,227,112,128,285,
	284,324,286,247,244,245,243,246,54,283,
	282,117,277,280,37,198,228,9,296,230,
	231,234,19,225,107,219,218,39,289,14,
	290,150,152,90,21,125,276,275,271,274,
	273,272,163,144,151,153,91,162,293,169,
	34,5,288,29,331,136,42,325,217,168,
	302,172,180,328,334,301,26,189,181,329,
	167,131,3,222,89,85,298,145,88,267,
	233,38,295,279,40,174,176,175,178,173,
	179,177,330,159,160,240,155,157,161,239,
	154,156,158,142,187,304,252,121,216,215,
	214,206,74,104,57,97,204,210,208,203,
	75,66,79,213,224,67,186,48,316,322,
	73,126,119,72,102,306,106,99,265,115,
	87,83,297,36,307,135,116,103,308,241,
	254,258,257,256,255,317,319,321,320,43,
	237,92,60,22,52,122,10,294,303,86,
	62,30,315,313,190,111,309,114,281,4,
	146,
};
static int s390x_syscall_s2i(const char *s, int *value) {
	size_t len, i;
	len = strlen(s);
	{ char copy[len + 1];
	for (i = 0; i < len; i++) {
		char c = s[i];
		copy[i] = GT_ISUPPER(c) ? c - 'A' + 'a' : c;
	}
	copy[i] = 0;
	return s2i__(s390x_syscall_strings, s390x_syscall_s2i_s, s390x_syscall_s2i_i, 271, copy, value);
	}
}
static const unsigned s390x_syscall_i2s_direct[] = {
	307,463,1446,2578,1277,169,-1u,175,983,2482,
	300,81,-1u,1081,87,-1u,-1u,-1u,1029,661,
	1115,2461,-1u,-1u,-1u,1394,49,-1u,1289,2519,
	-1u,-1u,8,1272,-1u,2255,961,1531,1067,1559,
	209,1323,2434,-1u,63,-1u,-1u,2113,-1u,-1u,
	15,2468,-1u,911,420,-1u,1987,-1u,-1u,2455,
	99,2513,213,676,653,2055,2091,-1u,-1u,-1u,
	-1u,2172,2139,1965,2045,-1u,726,750,2062,-1u,
	-1u,-1u,2237,-1u,1469,2506,2230,1495,1461,1110,
	1233,2446,521,388,-1u,684,1995,-1u,2206,497,
	-1u,2183,2290,1977,635,2201,1045,491,-1u,-1u,
	2548,779,-1u,2565,2222,2282,939,515,2162,163,
	1916,2476,-1u,28,1121,2150,181,784,195,547,
	1437,645,381,55,2276,1311,37,-1u,-1u,-1u,
	593,1868,457,1208,1489,2584,736,426,0,1095,
	1214,1101,1222,1822,1748,1837,1763,1856,1684,1707,
	1782,1240,1201,-1u,-1u,-1u,1424,1345,1261,-1u,
	-1u,1356,1623,1565,1592,1578,1650,1607,1636,1362,
	1409,-1u,586,67,74,2101,1875,668,1401,2542,
	716,-1u,-1u,-1u,-1u,-1u,-1u,966,763,618,
	610,602,2036,2007,625,1955,404,2026,706,2016,
	696,93,2075,1948,1939,1930,1334,1059,1051,-1u,
	-1u,1451,-1u,2082,1035,481,770,973,436,995,
	1005,446,1519,1016,468,743,2440,531,1804,1730,
	2301,-1u,892,868,879,901,858,312,223,250,
	272,1900,333,2308,2365,2351,2334,2321,149,119,
	106,133,-1u,-1u,2213,505,1502,-1u,-1u,-1u,
	1154,1191,1178,1162,1144,1130,943,20,1547,954,
	2571,928,917,814,796,841,-1u,1282,1073,1087,
	411,537,1250,2489,1538,988,2245,1478,395,323,
	1385,1350,2498,1884,563,2194,2260,2297,2556,-1u,
	579,260,2535,343,2525,2120,2379,283,2387,2418,
	2402,2129,291,827,1328,218,236,1368,1416,1666,
	1295,353,367,1375,
};
static const char *s390x_syscall_i2s(int v) {
	return i2s_direct__(s390x_syscall_strings, s390x_syscall_i2s_direct, 1, 334, v);
}
