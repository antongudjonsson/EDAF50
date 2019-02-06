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
PROGS =  ltest test_coding print_argv encode decode

all: $(PROGS)

test: test_coding
	./test_coding

# Targets rely on implicit rules for compiling and linking
ltest: ltest.o list.o
#ltest: liblab1.a ltest.o
test_coding: test_coding.o coding.o
print_argv: print_argv.o
encode: encode.o coding.o
#encode: encode.o liblab1.a
decode: decode.o coding.o
#decode: decode.o liblab1.a
liblab1.a: coding.o list.o
	ar crv liblab1.a coding.o list.o

# Phony targets
.PHONY: all test clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS) *.enc *.dec

distclean: clean
	rm *.d


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
