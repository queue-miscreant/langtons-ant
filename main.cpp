#include "ant.h"

int main(int argc,char** argv) {
	//invalid arg count
	if (argc < 4 or argc > 6) {
		std::cout << "Invalid number of arguments" << std::endl;
		return -1;
	}
	//set initial args
	int maxx = std::atoi(argv[1]);
	int maxy = std::atoi(argv[2]);
	//invalid board size
	if (maxx < 1 || maxy < 1) {
		std::cout << "Invalid board size" << std::endl;
		return -2;
	}
	if (argv[4] == nullptr) {
		char temp[] = "torus";
		argv[4] = temp;
	}
	Ant langton (maxx,maxy,argv[3],argv[4]);
	int delay = 10;
	if (argc > 5) {
		delay = std::atoi(argv[5]);
	}
	langton.animate(delay);
}
