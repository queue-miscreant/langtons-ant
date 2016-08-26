#ifndef ANT_H
#include <iostream>
#include <unistd.h>  

class Ant {
	private:
		int* m_board;
		int m_maxx;
		int m_maxy;
		int m_size;

		int m_xpos;
		int m_ypos;
		int m_orientation;

		int m_generation;
		int m_maxcolor;

		int m_delay;

		void printOver();
		void printColor(int color);
	public:
		Ant(int maxx, int maxy);
		Ant(int maxx, int maxy, int maxcolor, int delay);
		~Ant();
	
		void animate(bool direction(int),int until);
		
		void move(bool direction(int));
		void print();
};

#endif
