# define compliation commands
CC = gcc
CXX = g++
AR = ar
ARFLAGS = rcs

# define compilation flags
CFLAGS += -g -Wall -Wextra -Wpedantic -I. -O0
LDFLAGS = -L. -L./cvode_libs -levolver -lsundials_cvode -lsundials_nvecserial
CPPUNITFLAGS = -L./gtest -lgtest

# define common dependencies
OBJS = Reaction.o Network.o Configs.o Cvode_Utils.o
HEADERS = Reaction.h Network.h Configs.h Cvode_Utils.h
TESTOBJS = test_configs.o test_Reaction.o test_network.o test_suite.o test_cvode_utils.o
TESTHEADERS = test_configs.h test_Reaction.h test_network.h test_cvode_utils.h

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
