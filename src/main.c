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

	for (int i = 0; i < t->threadNmb; i++)
		if (pthread_create(&t->ind[i].thread, NULL, &routine, &(t->ind[i])))
			error_exit(CNOT_THREAD_CREATE, t);
	for (int i = 0; i < t->threadNmb; i++)
		if (pthread_join(&t->ind[i].thread, NULL))
			error_exit(CNOT_THREAD_JOIN, t);

	if (sigFlag)
		fprintf(stderr, SIG_END);
	free_everything(t);
	return (0);
}

void *routine(void *arg)
{

}
