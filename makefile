CC = g++
CFLAGS = -Wall

all: sender receiver

sender: sender.cc
	$(CC) $(CFLAGS) sender.cc -o sender

receiver: receiver.cc
	$(CC) $(CFLAGS) receiver.cc -o receiver

clean:
	rm -f sender receiver