# define compliation commands
CC = gcc
CXX = g++
AR = ar
ARFLAGS = rcs

# define compilation flags
CFLAGS += -g -Wall -Wextra -Wpedantic -I. -O0
LDFLAGS = -L. -levolver
CPPUNITFLAGS = -L./gtest -lgtest

# define common dependencies
OBJS = Reaction.o Network.o Configs.o
HEADERS = Reaction.h Network.h Configs.h
TESTOBJS = test_configs.o test_suite.o
TESTHEADERS = test_configs.h test_reaction.h

# compile everything
all: test_suite

test_suite: $(TESTOBJS) $(TESTHEADERS) libevolver.a
	$(CXX) $(CFLAGS) -o $@ $(TESTOBJS) $(CPPUNITFLAGS) $(LDFLAGS)

libevolver.a: $(OBJS) $(HEADERS)
	$(AR) $(ARFLAGS) libevolver.a $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -std=c11 -c $<

%.o: %.cc $(HEADERS)
	$(CXX) $(CFLAGS) -std=c++11 -c $<


clean:
	/bin/rm -rf *.o evolver *.dSYM .*.swp
