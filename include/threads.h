#ifndef THREADS_H
#define THREADS_H

#include "messages.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>

extern volatile sig_atomic_t sigFlag;

int		check_argument(char *argStr);
void	set_signals(void);
void	sig_handler(void);
Threads	*init_struct(int threadNmb, int nmbsPerThread);
void	error_exit(char *str, Threads *t);
void	init_nmb_struct(nmbList **n, Threads *t);
void	init_individual_threads(Threads *t);
void	init_mutexs(Threads *t);

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
} Threads;

struct s_individualThreads
{
	pthread_t	thread;
	int			index;
	Threads		*main;
};

#endif
