#include "../include/threads.h"

void set_signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		perror(CNOT_SIGNAL);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGTERM, sig_handler) == SIG_ERR)
	{
		perror(CNOT_SIGNAL);
		exit(EXIT_FAILURE);
	}
}

void sig_handler()
{
	sigFlag = true;
}
