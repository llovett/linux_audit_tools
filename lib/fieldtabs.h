/* This is a generated file, see Makefile.am for its inputs. */
static const char field_strings[] = "a0\0a1\0a2\0a3\0arch\0auid\0devmajor\0devminor\0dir\0egid\0"
	"euid\0exit\0filetype\0fsgid\0fsuid\0gid\0inode\0key\0loginuid\0msgtype\0"
	"obj_lev_high\0obj_lev_low\0obj_role\0obj_type\0obj_user\0path\0perm\0pers\0pid\0ppid\0"
	"sgid\0subj_clr\0subj_role\0subj_sen\0subj_type\0subj_user\0success\0suid\0uid";
static const unsigned field_s2i_s[] = {
	0,3,6,9,12,17,22,31,40,44,
	49,54,59,68,74,80,84,90,94,103,
	111,124,136,145,154,163,168,173,178,182,
	187,192,201,211,220,230,240,248,253,
};
static const int field_s2i_i[] = {
	200,201,202,203,11,9,100,101,107,6,
	2,103,108,8,4,5,102,210,9,12,
	23,22,20,21,19,105,106,10,0,18,
	7,17,14,16,15,13,104,3,1,
};
static int field_s2i(const char *s, int *value) {
	size_t len, i;
	len = strlen(s);
	{ char copy[len + 1];
	for (i = 0; i < len; i++) {
		char c = s[i];
		copy[i] = GT_ISUPPER(c) ? c - 'A' + 'a' : c;
	}
	copy[i] = 0;
	return s2i__(field_strings, field_s2i_s, field_s2i_i, 39, copy, value);
	}
}
static const int field_i2s_i[] = {
	0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,21,22,23,100,101,102,103,104,105,
	106,107,108,200,201,202,203,210,
};
static const unsigned field_i2s_s[] = {
	178,253,49,248,74,80,44,187,68,17,
	173,12,103,230,201,220,211,192,182,154,
	136,145,124,111,22,31,84,54,240,163,
	168,40,59,0,3,6,9,90,
};
static const char *field_i2s(int v) {
	return i2s_bsearch__(field_strings, field_i2s_i, field_i2s_s, 38, v);
}
