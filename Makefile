all:
	g++ -g -o ./bin/main.exe ./example/example01.cpp -std=c++11 -I./src

test: ./bin/test01.exe

./bin/test01.exe: ./test/test01.cpp ./src/tree.hpp
	g++ -o ./bin/test01.exe ./test/test01.cpp -std=c++11 -I./src

dox:
	doxygen doxygen.config

sta:
	cloc --by-file ./src ./test > ./statics/cloc_$(shell date +"%Y-%m-%d_%H-%M-%S").txt
