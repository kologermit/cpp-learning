all: clean main.o
	g++ main.o -o run
main.o: main.s
	g++ -c main.s -o main.o
main.s: main.ii
	g++ -S main.ii -o main.s
main.ii: main.cpp
	g++ -E main.cpp -o main.ii
clean:
	rm -rf *.o run *.exe *.ii *.s
run: all
	./run