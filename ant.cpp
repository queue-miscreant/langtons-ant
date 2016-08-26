#include "ant.h"

Ant::Ant(int maxx, int maxy, int maxcolor, int delay) {
	m_maxx = maxx;
	m_maxy = maxy;
	m_size = maxx*maxy;

	m_xpos = maxx/2;
	m_ypos = maxy/2;
	// 0
	//3 1
	// 2
	m_orientation = 0;

	m_board = new int[m_size];
	for (int i = 0; i < m_size; i++) {
		m_board[i] = 0;
	}
	m_generation = 0;
	m_maxcolor = maxcolor;
	m_delay = delay*1000;
}

Ant::Ant(int maxx, int maxy) {
	Ant(maxx, maxy, 2, 500);
}

Ant::~Ant() {
	delete [] m_board;
}

void Ant::printColor(int color) {
	int bold = (color<8) ? 22 : 1;
	int colorMod = color%8;
	int trueColor;
	if (not colorMod)
		trueColor = 7;
	else if (colorMod == 7)
		trueColor = 0;
	else
		trueColor = colorMod;
	std::printf("\x1b[4%d;%dm",trueColor,bold);
}

void Ant::print() {
	int lastColor = -1;
	for (int i = 0; i < m_size; i++) {
		int thisColor = m_board[i];
		if (thisColor != lastColor)
			printColor(thisColor);
		lastColor = thisColor;
		std::cout << ' ';
		if (i % m_maxx == m_maxx-1) {
			std::printf("\x1b[m\n");
			lastColor = -1;
		}
	}
	std::cout << "Generation: " << m_generation << std::endl;
}

void Ant::printOver() {
	print();
	usleep(m_delay);
	std::printf("\x1b[%dF",m_maxy+1);
}

//direction(int) is called on color
void Ant::animate(bool direction(int),int until) {
	for (m_generation = 0; m_generation < until; m_generation++) {
		move(direction);
		printOver();
	}
	print();
}

void Ant::move(bool direction(int)) {
	int pos = m_xpos+m_maxx*m_ypos;
	if (direction(m_board[pos])) {	//turn right
		m_orientation += 1;
		if (m_orientation == 4) m_orientation = 0;
	} else {						//turn left
		m_orientation -= 1;
		if (m_orientation == -1) m_orientation = 3;
	}
	//increment the color
	m_board[pos] += 1;
	m_board[pos] %= m_maxcolor;
	//go to the next cell
	if (m_orientation&1) {	//1 or 3 (left right)
		m_xpos += m_orientation-2;
		//connect the sides
		if (m_xpos < 0) m_xpos = m_maxx-1;
		else if (m_xpos >= m_maxx) m_xpos = 0;
	} else {				//0 or 2 (up down)
		m_ypos += m_orientation-1;
		//connect the sides
		if (m_ypos < 0) m_ypos = m_maxy-1;
		else if (m_ypos >= m_maxy) m_ypos = 0;
	}
}
