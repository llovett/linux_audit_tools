/* This is a generated file, see Makefile.am for its inputs. */
static const char cap_strings[] = "audit_control\0audit_write\0chown\0dac_override\0dac_read_search\0fowner\0fsetid\0ipc_lock\0ipc_owner\0kill\0"
	"lease\0linux_immutable\0mac_admin\0mac_override\0mknod\0net_admin\0net_bind_service\0net_broadcast\0net_raw\0setfcap\0"
	"setgid\0setpcap\0setuid\0sys_admin\0sys_boot\0sys_chroot\0sys_module\0sys_nice\0sys_pacct\0sys_ptrace\0"
	"sys_rawio\0sys_resource\0sys_time\0sys_tty_config\0syslog";
static const unsigned cap_i2s_direct[] = {
	26,32,45,61,68,94,207,222,214,105,
	160,177,150,191,75,84,259,300,248,289,
	279,229,239,270,310,323,332,144,99,14,
	0,199,131,121,347,
};
static const char *cap_i2s(int v) {
	return i2s_direct__(cap_strings, cap_i2s_direct, 0, 34, v);
}
