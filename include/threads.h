#ifndef THREADS_H
#define THREADS_H

#define DEFAULT_BUFFER_SIZE 1000
#include "messages.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>

extern volatile sig_atomic_t sigFlag;

typedef struct s_individualThreads indThread;
typedef struct
{
	int				*array;
	int				index;
	pthread_mutex_t	mutex;
	bool			mutexBool;
} nmbList;

typedef struct
{
	int			threadNmb;
	int			nmbsPerThread;
	nmbList		*posList;
	nmbList		*negList;
	indThread	*ind;
	int			randSeed;
} Threads;

struct s_individualThreads
{
	pthread_t	thread;
	int			index;
	Threads		*main;
};

// main
void *routine(void *arg);

// init
int		check_argument(char *argStr);
Threads	*init_struct(int threadNmb, int nmbsPerThread);
void	init_individual_threads(Threads *t);
void	init_nmb_struct(nmbList **n, Threads *t);

// signals
void	set_signals(void);
void	sig_handler();

// exit
void	error_exit(char *str, Threads *t);
void	free_everything(Threads *t);

// utils
int		get_rand_int(unsigned int *seed);
void	print_numbers(Threads *t);
int		compare_ints(const void *nmbA, const void *nmbB);

#endif
