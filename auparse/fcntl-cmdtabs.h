/* This is a generated file, see Makefile.am for its inputs. */
static const char fcntl_strings[] = "F_DUPFD\0F_GETFD\0F_GETFL\0F_GETLEASE\0F_GETLK\0F_GETLK64\0F_GETOWN\0F_GETSIG\0F_NOTIFY\0F_SETFD\0"
	"F_SETFL\0F_SETLEASE\0F_SETLK\0F_SETLK64\0F_SETLKW\0F_SETLKW64\0F_SETOWN\0F_SETSIG";
static const int fcntl_i2s_i[] = {
	0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,1024,1025,1026,
};
static const unsigned fcntl_i2s_s[] = {
	0,8,80,16,88,35,107,125,145,53,
	154,62,43,115,134,96,24,71,
};
static const char *fcntl_i2s(int v) {
	return i2s_bsearch__(fcntl_strings, fcntl_i2s_i, fcntl_i2s_s, 18, v);
}
