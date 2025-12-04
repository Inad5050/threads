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
	indThread *ind		= (indThread *)arg;
	Threads *t			= ind->main;
	unsigned int seed	= t->randSeed + ind->index;
	int	nmb;

	for (int i = 0; i < t->nmbsPerThread && !sigFlag; i++)
	{
		nmb = get_rand_int(&seed);
		if (nmb >= 0)
		{
			pthread_mutex_lock(&(t->posList->mutex));
			t->posList->array[t->posList->index] = nmb;
			t->posList->index;
			pthread_mutex_unlock(&(t->posList->mutex));
		}
		else
		{
			pthread_mutex_lock(&(t->negList->mutex));
			t->negList->array[t->negList->index] = nmb;
			t->negList->index;
			pthread_mutex_unlock(&(t->negList->mutex));
		}
	}
	return (NULL);	
}

int get_rand_int(unsigned int *seed)
{
	int nmb = 
}