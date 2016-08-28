#ifndef ANT_H
#include <iostream>
#include <unistd.h>  
#include <string.h>
#include <curses.h>

class Ant {
	private:
		int* m_board;
		int m_maxx;
		int m_maxy;
		int m_size;

		int m_xpos;
		int m_ypos;
		int m_orientation;
		bool m_invert;
		bool m_xwrap;
		bool m_ywrap;

		int m_generation;
		bool* m_rules;
		int m_numrules;

		void printOver(int delay);
		void printColor(int color);
		void wrapEdges();
	public:
		Ant(int maxx, int maxy, char* rulestring, char* manifold);
		~Ant();
	
		void animate(int delay);
		
		void move();
		void print();
};

#endif
