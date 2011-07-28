/* This is a generated file, see Makefile.am for its inputs. */
static const char type_strings[] = "a0\0a1\0a2\0acct\0addr\0arch\0auid\0cap_fi\0cap_fp\0cap_pe\0"
	"cap_pi\0cap_pp\0capability\0cgroup\0cmd\0comm\0cwd\0data\0device\0dir\0"
	"egid\0euid\0exe\0exit\0family\0file\0flags\0fsgid\0fsuid\0gid\0"
	"icmptype\0id\0igid\0inode_gid\0inode_uid\0iuid\0key\0mode\0name\0new-disk\0"
	"new_gid\0oauid\0ogid\0old-disk\0old_prom\0ouid\0path\0perm\0perm_mask\0prom\0"
	"proto\0res\0result\0saddr\0sauid\0ses\0sgid\0sig\0suid\0syscall\0"
	"uid\0vm\0watch";
static const unsigned type_s2i_s[] = {
	0,3,6,9,14,19,24,29,36,43,
	50,57,64,75,82,86,91,95,100,107,
	111,116,121,125,130,137,142,148,154,160,
	164,173,176,181,191,201,206,210,215,220,
	229,237,243,248,257,266,271,276,281,291,
	296,302,306,313,319,325,329,334,338,343,
	351,355,358,
};
static const int type_s2i_i[] = {
	14,15,16,6,25,4,1,21,21,21,
	21,21,12,6,6,6,6,19,6,6,
	2,1,6,5,22,6,10,2,1,2,
	23,1,2,2,1,1,6,8,6,6,
	2,1,2,6,11,1,6,7,7,11,
	24,13,13,9,1,20,2,17,1,3,
	1,6,6,
};
static int type_s2i(const char *s, int *value) {
	return s2i__(type_strings, type_s2i_s, type_s2i_i, 63, s, value);
}
