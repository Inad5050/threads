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

// init
int		check_argument(char *argStr);
Threads	*init_struct(int threadNmb, int nmbsPerThread);
void	init_individual_threads(Threads *t);
void	init_nmb_struct(nmbList **n, Threads *t);

// signals
void	set_signals(void);
void	sig_handler();

// exit
void error_exit(char *str, Threads *t);
void free_everything(Threads *t);

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
