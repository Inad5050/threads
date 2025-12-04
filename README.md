# Threads

This program generates random numbers and classifies them into positive or negative lists, then it sorts and prints them. It uses multiple threads and synchronizes them with mutexes. Its focal point is to minimize thread contention. In order to do so, it employs several strategies:

- **Pre-allocation:** We don't know how many positive or negative numbers we will need to store. However, from the start we know the total numbers of integers. We allocate the lists upfront in order to prevent several costly calls to `realloc`.
- **Batching:** To minimize mutex contention we do not lock them for every single number. We fill a local buffer (default size: 1000 integers), and flush it into the shared list in a single operation. 
- **Writing:** We minimize operations during the lock of each mutex. We reserve space by advancing the shared index of each of the two lists. Then each thread writes in the reserved positions while running in parallel.

## Compilation

To compile the project use the provided Makefile:

```bash
make
```

## Usage

```bash
./threads <number_of_threads> <numbers_per_thread>
```

- **number_of_threads:** How many threads will be used.

- **numbers_per_thread:** How many numbers each thread will generate.

### Example

```bash
./threads 6 10000
```
Generates 60000 numbers using 6 threads.


## Testing
To run basic tests:

```bash
./test/parsing.sh
```

- **Note:** requires Valgrind.

```bash
./test/performance.sh
```

- **Note:** some of the tests in performance.sh are designed to stress the program. Since we just want to measure thread performance and in order to save time, we will compile with **make test**, which won't print numbers.
