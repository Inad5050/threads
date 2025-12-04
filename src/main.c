#include "../include/threads.h"

volatile sig_atomic_t sigFlag = false;

int main(int argc, char **argv)
{
	if (argc != 3)
		return (fprintf(stderr, ARG_NUM));
	int threadNmb = check_argument(argv[1]);
	int nmbsPerThread = check_argument(argv[2]);

	set_signals();

	Threads *t = init_struct(threadNmb, nmbsPerThread);

	return (0);
}
