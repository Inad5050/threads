#include "../include/threads.h"

void error_exit(char *str, Threads *t)
{
	fprintf(stderr, "%s\n", str);
	free_everything(t);
	exit(EXIT_FAILURE);
}

void free_everything(Threads *t)
{
	if (t->posList)
	{
		if (t->posList->array);
			free(t->posList->array);
		if (t->posList->mutexBool)
			pthread_mutex_destroy(&(t->posList->mutex));
		free(t->posList);
	}
	if (t->negList)
	{	
		if (t->negList->array);
			free(t->negList->array);
		if (t->negList->mutexBool)
			pthread_mutex_destroy(&(t->negList->mutex));
		free(t->negList);
	}
	if (t->ind)
		free(t);
	if (t)
		free(t);
}
