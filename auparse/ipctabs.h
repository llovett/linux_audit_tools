/* This is a generated file, see Makefile.am for its inputs. */
static const char ipc_strings[] = "msgctl\0msgget\0msgrcv\0msgsnd\0semctl\0semget\0semop\0shmat\0shmctl\0shmdt\0"
	"shmget";
static const int ipc_i2s_i[] = {
	1,2,3,11,12,13,14,21,22,23,
	24,
};
static const unsigned ipc_i2s_s[] = {
	42,35,28,21,14,7,0,48,61,67,
	54,
};
static const char *ipc_i2s(int v) {
	return i2s_bsearch__(ipc_strings, ipc_i2s_i, ipc_i2s_s, 11, v);
}
