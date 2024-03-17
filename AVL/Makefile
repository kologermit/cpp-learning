all: clean build
	./run
run: clean build
	./run
build:
	g++ main.cpp -o ./run
clean:
	rm -rf *.exe run test
test: clean
	g++ -Wall -Wno-warning -Wno-notes test.cpp -o test
	./test