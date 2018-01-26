#
# Student makefile for Cache Lab
# Note: requires a 64-bit x86-64 system
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all:  csim test-shift tracegen
	# Generate a handin tar file each time you compile
	-tar -cvf ${USER}-handin.tar  csim.c shift.c

csim: csim.c cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o csim csim.c cachelab.c -lm

test-shift: test-shift.c shift.o cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o test-shift test-shift.c cachelab.c shift.o

tracegen: tracegen.c shift.o cachelab.c
	$(CC) $(CFLAGS) -O0 -o tracegen tracegen.c shift.o cachelab.c

shift.o: shift.c
	$(CC) $(CFLAGS) -O0 -c shift.c

#
# Clean the src dirctory
#
clean:
	rm -rf *.o
	rm -f csim
	rm -f test-shift tracegen
	rm -f trace.all trace.f*
	rm -f .csim_results .marker
