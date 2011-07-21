/* This is a generated file, see Makefile.am for its inputs. */
static const char i386_syscall_strings[] = "_llseek\0_newselect\0_sysctl\0access\0acct\0add_key\0adjtimex\0afs_syscall\0alarm\0bdflush\0"
	"break\0brk\0capget\0capset\0chdir\0chmod\0chown\0chown32\0chroot\0clock_getres\0"
	"clock_gettime\0clock_nanosleep\0clock_settime\0clone\0close\0creat\0create_module\0delete_module\0dup\0dup2\0"
	"dup3\0epoll_create\0epoll_create1\0epoll_ctl\0epoll_pwait\0epoll_wait\0eventfd\0eventfd2\0execve\0exit\0"
	"exit_group\0faccessat\0fadvise64\0fadvise64_64\0fallocate\0fanotify_init\0fanotify_mark\0fchdir\0fchmod\0fchmodat\0"
	"fchown\0fchown32\0fchownat\0fcntl\0fcntl64\0fdatasync\0fgetxattr\0flistxattr\0flock\0fork\0"
	"fremovexattr\0fsetxattr\0fstat\0fstat64\0fstatat64\0fstatfs\0fstatfs64\0fsync\0ftime\0ftruncate\0"
	"ftruncate64\0futex\0futimesat\0get_kernel_syms\0get_mempolicy\0get_robust_list\0get_thread_area\0getcpu\0getcwd\0getdents\0"
	"getdents64\0getegid\0getegid32\0geteuid\0geteuid32\0getgid\0getgid32\0getgroups\0getgroups32\0getitimer\0"
	"getpgid\0getpgrp\0getpid\0getpmsg\0getppid\0getpriority\0getresgid\0getresgid32\0getresuid\0getresuid32\0"
	"getrlimit\0getrusage\0getsid\0gettid\0gettimeofday\0getuid\0getuid32\0getxattr\0gtty\0idle\0"
	"init_module\0inotify_add_watch\0inotify_init\0inotify_init1\0inotify_rm_watch\0io_cancel\0io_destroy\0io_getevents\0io_setup\0io_submit\0"
	"ioctl\0ioperm\0iopl\0ioprio_get\0ioprio_set\0ipc\0keyctl\0kill\0lchown\0lchown32\0"
	"lgetxattr\0link\0linkat\0listxattr\0llistxattr\0lock\0lookup_dcookie\0lremovexattr\0lseek\0lsetxattr\0"
	"lstat\0lstat64\0madvise\0madvise1\0mbind\0migrate_pages\0mincore\0mkdir\0mkdirat\0mknod\0"
	"mknodat\0mlock\0mlockall\0mmap\0mmap2\0modify_ldt\0mount\0move_pages\0mprotect\0mpx\0"
	"mq_getsetattr\0mq_notify\0mq_open\0mq_timedreceive\0mq_timedsend\0mq_unlink\0mremap\0msync\0munlock\0munlockall\0"
	"munmap\0nanosleep\0nfsservctl\0nice\0oldfstat\0oldlstat\0oldolduname\0oldstat\0olduname\0open\0"
	"openat\0pause\0perf_event_open\0personality\0pipe\0pipe2\0pivot_root\0poll\0ppoll\0prctl\0"
	"pread64\0preadv\0prlimit64\0prof\0profil\0pselect6\0ptrace\0putpmsg\0pwrite64\0pwritev\0"
	"query_module\0quotactl\0read\0readahead\0readdir\0readlink\0readlinkat\0readv\0reboot\0recvmmsg\0"
	"remap_file_pages\0removexattr\0rename\0renameat\0request_key\0restart_syscall\0rmdir\0rt_sigaction\0rt_sigpending\0rt_sigprocmask\0"
	"rt_sigqueueinfo\0rt_sigreturn\0rt_sigsuspend\0rt_sigtimedwait\0rt_tgsigqueueinfo\0sched_get_priority_max\0sched_get_priority_min\0sched_getaffinity\0sched_getparam\0sched_getscheduler\0"
	"sched_rr_get_interval\0sched_setaffinity\0sched_setparam\0sched_setscheduler\0sched_yield\0select\0sendfile\0sendfile64\0set_mempolicy\0set_robust_list\0"
	"set_thread_area\0set_tid_address\0setdomainname\0setfsgid\0setfsgid32\0setfsuid\0setfsuid32\0setgid\0setgid32\0setgroups\0"
	"setgroups32\0sethostname\0setitimer\0setpgid\0setpriority\0setregid\0setregid32\0setresgid\0setresgid32\0setresuid\0"
	"setresuid32\0setreuid\0setreuid32\0setrlimit\0setsid\0settimeofday\0setuid\0setuid32\0setxattr\0sgetmask\0"
	"sigaction\0sigaltstack\0signal\0signalfd\0signalfd4\0sigpending\0sigprocmask\0sigreturn\0sigsuspend\0socketcall\0"
	"splice\0ssetmask\0stat\0stat64\0statfs\0statfs64\0stime\0stty\0swapoff\0swapon\0"
	"symlink\0symlinkat\0sync\0sync_file_range\0sys_kexec_load\0sysfs\0sysinfo\0syslog\0tee\0tgkill\0"
	"time\0timer_create\0timer_delete\0timer_getoverrun\0timer_gettime\0timer_settime\0timerfd\0timerfd_gettime\0timerfd_settime\0times\0"
	"tkill\0truncate\0truncate64\0ugetrlimit\0ulimit\0umask\0umount\0umount2\0uname\0unlink\0"
	"unlinkat\0unshare\0uselib\0ustat\0utime\0utimensat\0utimes\0vfork\0vhangup\0vm86\0"
	"vm86old\0vmsplice\0vserver\0wait4\0waitid\0waitpid\0write\0writev";
static const unsigned i386_syscall_s2i_s[] = {
	0,8,19,27,34,39,47,56,68,74,
	82,88,92,99,106,112,118,124,132,139,
	152,166,182,196,202,208,214,228,242,246,
	251,256,269,283,293,305,316,324,333,340,
	345,356,366,376,389,399,413,427,434,441,
	450,457,466,475,481,489,499,509,520,526,
	531,544,554,560,568,578,586,596,602,608,
	618,630,636,646,662,676,692,708,715,722,
	731,742,750,760,768,778,785,794,804,816,
	826,834,842,849,857,865,877,887,899,909,
	921,931,941,948,955,968,975,984,993,998,
	1003,1015,1033,1046,1060,1077,1087,1098,1111,1120,
	1130,1136,1143,1148,1159,1170,1174,1181,1186,1193,
	1202,1212,1217,1224,1234,1245,1250,1265,1278,1284,
	1294,1300,1308,1316,1325,1331,1345,1353,1359,1367,
	1373,1381,1387,1396,1401,1407,1418,1424,1435,1444,
	1448,1462,1472,1480,1496,1509,1519,1526,1532,1540,
	1551,1558,1568,1579,1584,1593,1602,1614,1622,1631,
	1636,1643,1649,1665,1677,1682,1688,1699,1704,1710,
	1716,1724,1731,1741,1746,1753,1762,1769,1777,1786,
	1794,1807,1816,1821,1831,1839,1848,1859,1865,1872,
	1881,1898,1910,1917,1926,1938,1954,1960,1973,1987,
	2002,2018,2031,2045,2061,2079,2102,2125,2143,2158,
	2177,2199,2217,2232,2251,2263,2270,2279,2290,2304,
	2320,2336,2352,2366,2375,2386,2395,2406,2413,2422,
	2432,2444,2456,2466,2474,2486,2495,2506,2516,2528,
	2538,2550,2559,2570,2580,2587,2600,2607,2616,2625,
	2634,2644,2656,2663,2672,2682,2693,2705,2715,2726,
	2737,2744,2753,2758,2765,2772,2781,2787,2792,2800,
	2807,2815,2825,2830,2846,2861,2867,2875,2882,2886,
	2893,2898,2911,2924,2941,2955,2969,2977,2993,3009,
	3015,3021,3030,3041,3052,3059,3065,3072,3080,3086,
	3093,3102,3110,3117,3123,3129,3139,3146,3152,3160,
	3165,3173,3182,3190,3196,3203,3211,3217,
};
static const int i386_syscall_s2i_i[] = {
	140,142,149,33,51,286,124,137,27,134,
	17,45,184,185,12,15,182,212,61,266,
	265,267,264,120,6,8,127,129,41,63,
	330,254,329,255,319,256,323,328,11,1,
	252,307,250,272,324,338,339,133,94,306,
	95,207,298,55,221,148,231,234,143,2,
	237,228,108,197,300,100,269,118,35,93,
	194,240,299,130,275,312,244,318,183,141,
	220,50,202,49,201,47,200,80,205,105,
	132,65,20,188,64,96,171,211,165,209,
	76,77,147,224,78,24,199,229,32,112,
	128,292,291,332,293,249,246,247,245,248,
	54,101,110,290,289,117,288,37,16,198,
	230,9,303,232,233,53,253,236,19,227,
	107,196,219,219,274,294,218,39,296,14,
	297,150,152,90,192,123,21,317,125,56,
	282,281,277,280,279,278,163,144,151,153,
	91,162,169,34,28,84,59,18,109,5,
	295,29,336,136,42,331,217,168,309,172,
	180,333,340,44,98,308,26,189,181,334,
	167,131,3,225,89,85,305,145,88,337,
	257,235,38,302,287,0,40,174,176,175,
	178,173,179,177,335,159,160,242,155,157,
	161,241,154,156,158,82,187,239,276,311,
	243,258,121,139,216,138,215,46,214,81,
	206,74,104,57,97,71,204,170,210,164,
	208,70,203,75,66,79,23,213,226,68,
	67,186,48,321,327,73,126,119,72,102,
	313,69,106,195,99,268,25,31,115,87,
	83,304,36,314,283,135,116,103,315,270,
	13,259,263,262,261,260,322,326,325,43,
	238,92,193,191,58,60,22,52,122,10,
	301,310,86,62,30,320,271,190,111,166,
	113,316,273,114,284,7,4,146,
};
static int i386_syscall_s2i(const char *s, int *value) {
	size_t len, i;
	len = strlen(s);
	{ char copy[len + 1];
	for (i = 0; i < len; i++) {
		char c = s[i];
		copy[i] = GT_ISUPPER(c) ? c - 'A' + 'a' : c;
	}
	copy[i] = 0;
	return s2i__(i386_syscall_strings, i386_syscall_s2i_s, i386_syscall_s2i_i, 338, copy, value);
	}
}
static const unsigned i386_syscall_i2s_direct[] = {
	1938,340,526,1816,3211,1631,202,3203,208,1212,
	3086,333,106,2893,1367,112,1186,82,1614,1278,
	842,1418,3065,2600,968,2781,1762,68,1584,1643,
	3123,2787,993,27,1579,602,2825,1181,1910,1353,
	1954,242,1677,3009,1741,88,2406,778,2656,760,
	742,34,3072,1245,1130,475,1444,2466,3052,1602,
	3059,132,3117,246,857,834,2580,2634,2625,2744,
	2550,2486,2715,2682,2444,2570,921,931,955,2587,
	794,2422,2263,2807,1593,1839,3110,2800,1865,1831,
	1396,1551,3021,608,434,450,865,2474,1746,2765,
	578,1136,2726,2875,2456,816,2753,1294,554,1622,
	1143,3152,998,3165,3190,2792,2867,1170,596,2705,
	196,2352,3080,1407,47,1435,2693,214,1003,228,
	646,1807,826,427,74,2861,1665,56,2386,2366,
	0,722,8,520,1526,1859,3217,941,489,19,
	1381,1532,1387,1540,2217,2143,2232,2158,2251,2079,
	2102,2177,1558,1519,2528,899,3160,1794,1699,1568,
	2506,877,1710,2018,1960,1987,1973,2045,2002,2031,
	1716,1777,118,715,92,99,2644,2270,849,1769,
	3146,3041,1401,3030,618,2758,1300,560,1193,975,
	785,768,750,2559,2495,804,2432,457,2538,909,
	2516,887,124,2607,2413,2395,2375,1688,1345,1308,
	731,481,-1u,-1u,948,1821,2616,1284,544,984,
	1202,499,1224,1234,509,1898,1265,531,3015,2279,
	630,2199,2125,2320,692,1111,1087,1098,1120,1077,
	366,-1u,345,1250,256,283,305,1881,2336,2898,
	2955,2941,2924,2911,182,152,139,166,2772,586,
	2886,3139,376,3182,1325,662,2290,1472,1509,1496,
	1480,1462,1448,2846,3196,-1u,39,1926,1174,1159,
	1148,1033,1015,1060,1331,1636,1359,1373,466,636,
	568,3093,1917,1217,2815,1848,441,356,1753,1704,
	3102,2304,676,2737,2830,2882,3173,1424,708,293,
	3129,2663,2969,316,389,2993,2977,2672,324,269,
	251,1682,1046,1724,1786,2061,1649,1872,399,413,
	1731,
};
static const char *i386_syscall_i2s(int v) {
	return i2s_direct__(i386_syscall_strings, i386_syscall_i2s_direct, 0, 340, v);
}
