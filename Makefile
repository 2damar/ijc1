CC=gcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -pedantic
LIBS=-lm
DFLAGS=-DUSE_INLINE

all: primes primes-i steg-decode

primes:	primes.o eratosthenes.o error.o
	$(CC) -o primes primes.o eratosthenes.o error.o $(CFLAGS) $(LIBS)

primes-i: primes-i.o eratosthenes-i.o error.o 
	$(CC) -o primes-i primes-i.o eratosthenes-i.o error.o $(CFLAGS) $(LIBS) $(DFLAGS)

steg-decode: steg-decode.o eratosthenes.o ppm.o error.o
	$(CC) -o steg-decode steg-decode.o eratosthenes.o ppm.o error.o $(CFLAGS) $(LIBS)

ppm.o: ppm.c error.c
	$(CC) -c ppm.c -o ppm.o $(CFLAGS) 

eratosthenes.o: eratosthenes.c
	$(CC) -c eratosthenes.c -o eratosthenes.o $(CFLAGS) $(LIBS)

eratosthenes-i.o: eratosthenes.c 
	$(CC) -c eratosthenes.c -o eratosthenes-i.o $(CFLAGS) $(LIBS) $(DFLAGS)

primes-i.o: primes.c eratosthenes.c error.c
	$(CC) -c primes.c -o primes-i.o $(CFLAGS) $(DFLAGS)

steg-decode.o: steg-decode.c eratosthenes.c ppm.c error.c
	$(CC) -c steg-decode.c -o steg-decode.o $(CFLAGS) 

.PHONY: clean

clean: 
	rm -f *.o

run: 
	time ./primes;	time ./primes-i


