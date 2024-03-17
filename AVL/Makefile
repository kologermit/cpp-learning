all: clean build
	./run
run: clean build
	./run
build:
	g++ -Wall -g main.cpp -o ./run
clean:
	rm -rf *.exe run test
test: clean
	g++ -Wall -g test.cpp -o test
	./test
valgrind: build
	valgrind --leak-check=yes --log-file="./valgrind.txt" ./run > ./result.txt