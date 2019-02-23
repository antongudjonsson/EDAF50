# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS =  -std=c++11 -I.
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++11 
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS =   -L.
#LDLIBS = -llab1
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
PROGS = tagremover primes

all: $(PROGS)

test: date_test tagremover_Test primes_test tostring_test

# Targets rely on implicit rules for compiling and linking
#date: date.o
date_test: date.o
tagremover_Test: tagremover.o
tagremover: tagremover.o
primes: primes.o
primes_test: primes.o
tostring_test: date.o

# Phony targets
.PHONY: all test clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS) *.enc *.dec

distclean: clean
	rm *.d

run: all
	 ./date_test


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
