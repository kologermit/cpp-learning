all: clean build
	./run
run: clean build
	./run
build:
	g++ -Wall -g main.cpp -o ./run
clean:
	rm -rf *.exe run test
test_build: clean
	g++ -Wall -g test.cpp -o test
test: clean test_build
	./test
valgrind: build
	valgrind --leak-check=yes --log-file="./valgrind.txt" ./run > ./result.txt
valgrind_test: test_build
	valgrind --leak-check=yes ./test