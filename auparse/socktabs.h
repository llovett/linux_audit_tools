/* This is a generated file, see Makefile.am for its inputs. */
static const char sock_strings[] = "accept\0bind\0connect\0getpeername\0getsockname\0getsockopt\0listen\0recv\0recvfrom\0recvmsg\0"
	"send\0sendmsg\0sendto\0setsockopt\0shutdown\0socket\0socketpair";
static const unsigned sock_i2s_direct[] = {
	124,7,12,55,0,32,20,131,84,62,
	97,67,115,104,44,89,76,
};
static const char *sock_i2s(int v) {
	return i2s_direct__(sock_strings, sock_i2s_direct, 1, 17, v);
}
