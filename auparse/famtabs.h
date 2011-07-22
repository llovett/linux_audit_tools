/* This is a generated file, see Makefile.am for its inputs. */
static const char fam_strings[] = "appletalk\0ash\0atmpvc\0atmsvc\0ax25\0bluetooth\0bridge\0decnet\0econet\0inet\0"
	"inet6\0ipx\0irda\0key\0local\0netbeui\0netlink\0netrom\0packet\0pppox\0"
	"rose\0security\0sna\0wanpipe\0x25";
static const unsigned fam_i2s_direct[] = {
	88,64,28,75,0,110,43,14,156,69,
	130,50,94,135,84,102,117,10,57,21,
	-1u,144,79,124,148,-1u,-1u,-1u,-1u,-1u,
	33,
};
static const char *fam_i2s(int v) {
	return i2s_direct__(fam_strings, fam_i2s_direct, 1, 31, v);
}
