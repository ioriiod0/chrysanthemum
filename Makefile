


all: test2

test2: test2.cc tuple_serialization.h sequential.h parsers.h data_holder.h
	gcc test2.cc -o test2 -std=c++0x

clean: 
	rm -f *.o
