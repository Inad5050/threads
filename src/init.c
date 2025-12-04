#include "../include/threads.h"

int check_argument(char *argStr)
{
	char *endptr;
	long argNmb = strtol(argStr, endptr, 10);
	if (endptr != '\0' || argStr == endptr)
	{
		fprintf(stderr, ARG_INVALID);
		exit(EXIT_FAILURE);
	}
	if (argNmb <= 0)
	{
		fprintf(stderr, ARG_ZERO);
		exit(EXIT_FAILURE);
	}
	if (argNmb > __INT_MAX__)
	{
		fprintf(stderr, ARG_MAX_INT);
		exit(EXIT_FAILURE);
	}
}

Threads *init_struct(int threadNmb, int nmbsPerThread)
{
	Threads *t = calloc(1, sizeof(Threads));
	if (!t)
	{
		fprintf(stderr, CNOT_ALLOC);
		exit(EXIT_FAILURE);
	}
	t->threadNmb = threadNmb;
	t->nmbsPerThread = nmbsPerThread;
	init_nmb_struct(&(t->posList), t);
	init_nmb_struct(&(t->negList), t);
	init_individual_threads(t);
	t->randSeed = time(NULL);
	return (t);
}

void init_individual_threads(Threads *t)
{
	t->ind = calloc(t->threadNmb, sizeof(indThread));
	if (!t->ind)
		error_exit(CNOT_ALLOC, t);
	for (int i = 0; i < t->threadNmb; i++)
	{
		t->ind[i].index = i;
		t->ind[i].main = t;
	}
}

void init_nmb_struct(nmbList **n, Threads *t)
{
	*n = calloc(1, sizeof(nmbList));
	if (!(*n))
		error_exit(CNOT_ALLOC, t);
	(*n)->array = calloc(t->threadNmb * t->nmbsPerThread, sizeof(int));
	if (!(*n)->array)
		error_exit(CNOT_ALLOC, t);
	if (pthread_mutex_init(&((*n)->mutex), NULL))
		error_exit(CNOT_MUTEX, t);
	(*n)->mutexBool = true;
}
