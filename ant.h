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
		bool* m_rules;
		int m_numrules;

		void printOver(int delay);
		void printColor(int color);
		void wrapEdges();
	public:
		Ant(int maxx, int maxy, int numrules, char* rulestring);
		~Ant();
	
		void animate(int until,int delay);
		
		void move();
		void print();
};

#endif
