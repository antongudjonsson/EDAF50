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
PROGS = simplebitset bitset bitreference

all: $(PROGS)

test: simplebitsettest bitsettest1 bitsettest2

# Targets rely on implicit rules for compiling and linking
#date: date.o
simplebitset: simplebitset.o
simplebitsettest: simplebitset.o
bitset: bitset.o bitreference.o
bitreference: bitset.o bitreference.o
bitsettest1: bitset.o bitreference.o
bitsettest2: bitset.o bitreference.o



# Phony targets
.PHONY: all test clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS)

distclean: clean
	rm *.d

run: all
	 


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
