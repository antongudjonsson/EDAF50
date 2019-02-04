# The following rule means: "if ltest does not exist, or
# is older than ltest.o or list.o,
# then link ltest".
ltest: ltest.o list.o
	g++ -o ltest ltest.o list.o

# Rules to create the object files.
ltest.o: ltest.cc list.h
	g++ -c ltest.cc -std=c++11
list.o: list.cc list.h
	g++ -c list.cc -std=c++11

print_argv: print_argv.o
	g++ -o print_argv print_argv.o
print_argv.o: print_argv.cc
	g++ -c print_argv.cc -std=c++11
