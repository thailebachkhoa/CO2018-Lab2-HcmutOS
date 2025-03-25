CC = gcc
CFLAGS = -Wall -O2 -pthread

all: sum_serial sum_multithread

sum_serial: sum_serial.c
	$(CC) $(CFLAGS) -o sum_serial sum_serial.c

sum_multithread: sum_multithread.c
	$(CC) $(CFLAGS) -o sum_multithread sum_multithread.c

clean:
	rm -f sum_serial sum_multithread
