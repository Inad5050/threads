#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

pass()
{
	echo -e "${GREEN}[OK]${NC}";
}

fail()
{
	echo -e "${GREEN}[FAIL]${NC}";
}

echo "======================================"
echo "           PARSING TEST               "
echo "======================================"

make re

echo "No arguments"
! ./threads >/dev/null 2>&1 && pass || fail
echo "Non-numeric argument"
! ./threads 4 patata >/dev/null 2>&1 && pass || fail
echo "Negative number"
! ./threads 4 -100 >/dev/null 2>&1 && pass || fail
echo "Zero threads"
! ./threads 0 100 >/dev/null 2>&1 && pass || fail
echo "Check memory leaks"
valgrind -q --leak-check=full --error-exitcode=1 ./threads 4 50 >/dev/null 2>&1 && pass || fail
echo "Check data races"
valgrind -q --tool=helgrind --error-exitcode=1 ./threads 4 50 >/dev/null 2>&1 && pass || fail

echo "======================================"
echo "                END                   "
echo "======================================"
