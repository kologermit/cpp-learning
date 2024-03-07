run: clean build
	./run
build:
	g++ main.cpp -o ./run
clean:
	rm -rf *.exe run test
test: clean
	g++ test.cpp -o test
	./test