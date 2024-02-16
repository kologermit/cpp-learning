all: main.o BigInteger.o
	g++ BigInteger.o main.o -o run 
main.o: main.cpp BigInteger.h
	g++ -c main.cpp -o main.o
BigInteger.o: BigInteger.cpp BigInteger.h
	g++ -c BigInteger.cpp -o BigInteger.o
clean:
	rm -rf *.o run *.exe