# define compliation commands
CC = gcc
CXX = g++

# define compilation flags
CFLAGS += -g -Wall -Wextra -Wpedantic -I. -O0
CPPUNITFLAGS = -L./gtest -lgtest

# define common dependencies
OBJS = Reaction.o Network.o Configs.o
HEADERS = Reaction.h Network.h Configs.h
TESTOBJS = test_configs.o test_reaction.o
TESTHEADERS = test_configs.h test_reaction.h

# compile everything
all: test_suite

test_suite: $(TESTOBJS) $(TESTHEADERS)
	$(CXX) $(CFLAGS) -o $@ $(TESTOBJS) $(CPPUNITFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -std=c11 -c $<

%.o: %.cc $(HEADERS)
	$(CXX) $(CFLAGS) -std=c++11 -c $<


clean:
	/bin/rm -rf *.o evolver *.dSYM .*.swp
