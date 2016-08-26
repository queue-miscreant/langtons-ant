#include "ant.h"

bool notmod2(int color) {
	return not color&1;
}

bool notmod3(int color) {
	return not not (color%3 - 1);
}

int main(int argc,char** argv) {
	//invalid arg count
	if (argc < 3 or argc > 5) {
		std::cout << "Invalid number of arguments" << std::endl;
		return -1;
	}
	//set initial args
	int maxx = std::atoi(argv[1]);
	int maxy = std::atoi(argv[2]);
	int delay = 10;
	int maxColor = 2;
	if (argc > 3)
		maxColor = std::atoi(argv[3]);
	if (argc > 4)
		delay = std::atoi(argv[4]);
	//invalid board size
	if (maxx < 1 || maxy < 1) {
		std::cout << "Invalid board size" << std::endl;
		return -2;
	}
	
	Ant langton (maxx,maxy,maxColor,delay);
	langton.animate(notmod3,2e4);
}


