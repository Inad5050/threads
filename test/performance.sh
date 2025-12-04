#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

tester()
{
	THREADS=$1
	NMBS=$2

	echo "=== threads: $THREADS,	nmbsPerThread: $NMBS,	totalNmbs: $(($THREADS * $NMBS)) ==="
	/usr/bin/time -f "%e" -o .tmpTest ./threads $THREADS $NMBS > /dev/null
	TIME=$(cat .tmpTest)
	SPEED=$(awk "BEGIN {printf \"%.2f\", ($THREADS * $NMBS) / $TIME / 1000000}")
	echo -e "Time: ${TIME}s | Speed: ${SPEED} MillionNumbers/s\n"
}

echo "======================================"
echo "             SPEED TEST               "
echo "======================================"

make re

echo "One thread"
tester 1 40000000
echo "Less threads than cores"
tester 4 10000000
echo "One thread per core"
tester 6 6666666
echo "High thread density"
tester 50 800000
echo "Thread number is a multiple of core number"
tester 60 666666
echo "Too many threads"
tester 2000 20000


echo "======================================"
echo "                END                   "
echo "======================================"