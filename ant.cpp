#include "ant.h"

Ant::Ant(int maxx, int maxy, char* rulestring, char* manifold) {
	m_maxx = maxx;
	m_maxy = maxy;
	m_size = maxx*maxy;

	m_xpos = maxx/2;
	m_ypos = maxy/2;
	// 0
	//3 1
	// 2
	m_orientation = 0;
	m_invert = false;
	m_generation = 0;

	m_board = new int[m_size];
	for (int i = 0; i < m_size; i++)
		m_board[i] = 0;
	
	for (m_numrules = 0; rulestring[m_numrules] != 0; m_numrules++);
	m_rules = new bool[m_numrules];
	for (int i = 0; i < m_numrules; i++)
		if (rulestring[i] == 48 or rulestring[i] == 49) //0 or 1 only
			m_rules[i] = rulestring[i]-48;
		else
			m_rules[i] = 0;
	
	if (strcmp(manifold,"torus") == 0)
		m_xwrap = false,m_ywrap = false;
	else if (strcmp(manifold,"klein") == 0)
		m_xwrap = true,m_ywrap = false;
	else if (strcmp(manifold,"turnklein") == 0)
		m_xwrap = false,m_ywrap = true;
	else if (strcmp(manifold,"projective") == 0)
		m_xwrap = true,m_ywrap = true;
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
			std::printf("\x1b[m\r\n");
			lastColor = -1;
		}
	}
}

void Ant::printOver(int delay) {
	print();
	std::cout << "Generation: " << m_generation;
	if (delay) usleep(delay * 1000);
	std::printf("\r\x1b[%dA",m_maxy+1);
}

//direction(int) is called on color
void Ant::animate(int delay) {
	WINDOW* win = initscr();
	char input;
	bool go = true;
	bool loop = true;

	cbreak();
	noecho();
	nodelay(win,true);
	while (loop) {
		if (go) {
			printOver(delay);
			move();
			m_generation++;
		}
		input = (char) getch();
		if (input != ERR) {
			if (input == ' ')
				go = not go;
			else if (input == 'q')
				loop = false;
		}
	}
	nocbreak();
	echo();
	nodelay(win,false);

	delwin(win);
	endwin();
	refresh();

	for (int i = 0; i <= m_maxy+1; i++)
		std::printf("\x1b[K\n");
	std::printf("\x1b[%dA",m_maxy+2);
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
	if (m_orientation&1) 	//1 or 3 (left right)
		if (m_invert)
			m_xpos -= m_orientation-2;
		else
			m_xpos += m_orientation-2;
	else					//0 or 2 (up down)
		if (m_invert)
			m_ypos -= m_orientation-1;
		else
			m_ypos += m_orientation-1;
	wrapEdges();
}

void Ant::wrapEdges() {
	if (m_ypos < 0) {
		m_ypos = m_maxy-1;
		if (m_ywrap)
			m_xpos = m_maxx-1-m_xpos, m_invert = not m_invert;
	} else if (m_ypos >= m_maxy) {
		m_ypos = 0;
		if (m_ywrap)
			m_xpos = m_maxx-1-m_xpos, m_invert = not m_invert;
	}

	if (m_xpos < 0) {
		m_xpos = m_maxx-1;
		//orientation = 00: orientation -> 10
		//orientation = 10: orientation -> 00
		if (m_xwrap) 
			m_ypos = m_maxy-1-m_ypos, m_invert = not m_invert;
	} else if (m_xpos >= m_maxx) {
		m_xpos = 0;
		if (m_xwrap)
			m_ypos = m_maxy-1-m_ypos, m_invert = not m_invert;
	}
}
