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
		if (pthread_join(t->ind[i].thread, NULL))
			error_exit(CNOT_THREAD_JOIN, t);

	if (!sigFlag)
		print_numbers(t);

	if (sigFlag)
		printf(SIG_END);
	free_everything(t);
	return (0);
}

void *routine(void *arg)
{
	indThread *ind = (indThread *)arg;
	Threads *t = ind->main;
	unsigned int seed = t->randSeed + ind->index;
	int maxbufferSize = DEFAULT_BUFFER_SIZE > t->nmbsPerThread ? t->nmbsPerThread : DEFAULT_BUFFER_SIZE;
	int remaining = t->nmbsPerThread;
	int bufferPos[maxbufferSize];
	int bufferPosIndex = 0;
	int bufferNeg[maxbufferSize];
	int bufferNegIndex = 0;
	int nmb;
	int initialPosListIndex;
	int initialNegListIndex;

	while (remaining > 0 && !sigFlag)
	{
		int currentForNumbers = remaining < maxbufferSize ? remaining : maxbufferSize;
		for (int i = 0; i < currentForNumbers && !sigFlag; i++)
		{
			nmb = get_rand_int(&seed);
			if (nmb >= 0)
				bufferPos[bufferPosIndex++] = nmb;
			else
				bufferNeg[bufferNegIndex++] = nmb;
		}

		pthread_mutex_lock(&(t->posList->mutex));
		initialPosListIndex = t->posList->index;
		t->posList->index += bufferPosIndex;
		pthread_mutex_unlock(&(t->posList->mutex));
		for (int i = 0; i < bufferPosIndex; i++)
			t->posList->array[initialPosListIndex++] = bufferPos[i];

		pthread_mutex_lock(&(t->negList->mutex));
		initialNegListIndex = t->negList->index;
		t->negList->index += bufferNegIndex;
		pthread_mutex_unlock(&(t->negList->mutex));
		for (int i = 0; i < bufferNegIndex; i++)
			t->negList->array[initialNegListIndex++] = bufferNeg[i];

		remaining = remaining - bufferPosIndex - bufferNegIndex;
		bufferPosIndex = 0;
		bufferNegIndex = 0;
	}
	return (NULL);
}
