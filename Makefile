# define compliation commands
CC = gcc
CXX = g++

# define compilation flags
CFLAGS += -g -Wall -Wextra -Wpedantic -std=c11 -O0

# define common dependencies
OBJS = Reaction.o Network.o Configs.o
HEADERS = Reaction.h Network.h Configs.h
TESTOBJS = test_configs.o test_reaction.o
TESTHEADERS = test_configs.h test_reaction.h

# compile everything
all: test_configs

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	/bin/rm -rf *.o evolver *.dSYM .*.swp
