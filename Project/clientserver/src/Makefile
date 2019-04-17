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
LDFLAGS =   -g
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets

PROGS = newsserver newsserverMem newsclient

all: libclientserver.a $(PROGS) 

# Create the library; ranlib is for Darwin (OS X) and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: connection.o server.o messagehandler.o
	ar rv libclientserver.a  connection.o server.o messagehandler.o
	ranlib libclientserver.a
newsserver: newsserver.o connection.o server.o messagehandler.o article.o newsgroup.o memorydB.o database.o
newsserverMem: newsserverMem.o connection.o server.o messagehandler.o article.o newsgroup.o memorydB.o database.o
newsclient: newsclient.o connection.o server.o messagehandler.o


# Phony targets
.PHONY: all clean distclean

SRC = $(wildcard *.cc)

# Standard clean
clean:
	rm $(SRC:.cc=.o) $(PROGS)

distclean: clean
	-rm libclientserver.a
	-rm $(SRC:.cc=.d) 

runserver: newsserver newsclient
	./newsserver 3000

runserverDB: newsserverMem newsclient
	./newsserverMem 3000

runclient: newsserver newsclient
	./newsclient localhost 3000

reset:
	rm -r database.db

install:
	cp newsserver newsclient newsserverMem ../bin


# Include the *.d files
-include $(SRC:.cc=.d)
