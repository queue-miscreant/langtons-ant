#include "ant.h"

Ant::Ant(int maxx, int maxy, int numrules, char* rulestring) {
	m_maxx = maxx;
	m_maxy = maxy;
	m_size = maxx*maxy;

	m_xpos = maxx/2;
	m_ypos = maxy/2;
	// 0
	//3 1
	// 2
	m_orientation = 0;
	m_generation = 0;

	m_board = new int[m_size];
	for (int i = 0; i < m_size; i++)
		m_board[i] = 0;

	m_numrules = numrules;
	m_rules = new bool[numrules];
	for (int i = 0; i < numrules; i++) {
		m_rules[i] = rulestring[i]-48;
	}

	/*
	char buff[2];
	for (int i = 0; rulestring[i] != 0; i++) {
		if (isdigit(rulestring[i])) {
			int loc;
			i++; //check the next (number?)
			if (isdigit(rulestring[i])) {
				buff[0] = rulestring[i-1];
				buff[1] = rulestring[i];
				std::sprintf(buff,"%d",loc);
			} else
				loc = std::atoi(&rulestring[i-1]);
			m_rules[loc] = 1;
		}
	}
	*/
}

Ant::~Ant() {
	delete [] m_board;
	delete [] m_rules;
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
}

void Ant::printOver(int delay) {
	print();
	std::cout << "Generation: " << m_generation << std::endl;
	if (delay) usleep(delay * 1000);
	std::printf("\x1b[%dF",m_maxy+1);
}

//direction(int) is called on color
void Ant::animate(int until,int delay) {
	for (m_generation = 0; m_generation < until; m_generation++) {
		printOver(delay);
		move();
	}
	print();
}

void Ant::move() {
	int pos = m_xpos+m_maxx*m_ypos;
	if (m_rules[m_board[pos]]) {	//turn right
		m_orientation += 1;
		if (m_orientation == 4) m_orientation = 0;
	} else {						//turn left
		m_orientation -= 1;
		if (m_orientation == -1) m_orientation = 3;
	}
	//increment the color
	m_board[pos] += 1;
	m_board[pos] %= m_numrules;
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

void Ant::wrapEdges() {
}
