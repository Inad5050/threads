#ifndef THREADS_H
#define THREADS_H

#include "messages.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

extern volatile sig_atomic_t sigFlag;

int check_argument(char *argStr);
void set_signals(void);
void sig_handler(void);


#endif