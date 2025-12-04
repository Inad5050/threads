#include "../include/threads.h"

volatile sig_atomic_t sigFlag = false;

int main(int argc, char **argv)
{
	if (argc != 3)
		return (fprintf(stderr, ARG_NUM));
	int threadNum = check_argument(argv[1]);
	int nmbsPerThread = check_argument(argv[2]);

	set_signals();

	return (0);
}

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