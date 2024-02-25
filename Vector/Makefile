all: main.o Vector.o
	g++ Vector.o main.o -o run 
main.o: main.cpp Vector.h
	g++ -c main.cpp -o main.o
BigInteger.o: Vector.h
	g++ -o Vector.o
clean:
	rm -rf *.o run *.exe