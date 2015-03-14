all:
	g++ -o ./example/main.exe ./example/main8.cpp -std=c++11 -I./src

dox:
	doxygen doxygen.config

sta:
	cloc --by-file ./src ./test > ./statics/cloc_$(shell date +"%Y-%m-%d_%H-%M-%S").txt
