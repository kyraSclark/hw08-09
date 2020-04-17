all: stringtest-ours

stringtest-ours: stringtest-ours.o
	clang++ -o stringtest-ours -ltestinglogger stringtest-ours.o

stringtest-ours.o: stringtest-ours.cpp chunkystring.hpp chunkylist.hpp chunkylist-private.hpp
	clang++ -c -std=c++1z -Wall -Wextra -pedantic stringtest-ours.cpp

clean:
	rm stringtest-ours *.o
