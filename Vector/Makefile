all: clean main.o Vector.o
	g++ Vector.o main.o -o run 
main.o: main.cpp Vector.h
	g++ -c main.cpp -o main.o
Vector.o: Vector.h
	g++ -c Vector.h -o Vector.o
clean:
	rm -rf *.o run *.exe