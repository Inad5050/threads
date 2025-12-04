#include "../include/threads.h"

int get_rand_int(unsigned int *seed)
{
	return (rand_r(seed) - RAND_MAX / 2);
}

void print_numbers(Threads *t)
{
	qsort(t->posList->array, t->posList->index, sizeof(int), compare_ints);
	qsort(t->negList->array, t->negList->index, sizeof(int), compare_ints);
	printf("-----NEGATIVE-----\n");
	for (int i = 0; i < t->negList->index && !sigFlag; i++)
		printf("[%d]:	%d\n", i, t->negList->array[i]);
	printf("-----POSITIVE-----\n");
	for (int i = 0; i < t->posList->index && !sigFlag; i++)
		printf("[%d]:	%d\n", i, t->posList->array[i]);
}

int compare_ints(const void *nmbA, const void *nmbB)
{
	return (*(int *)nmbA - *(int *)nmbB);
}
