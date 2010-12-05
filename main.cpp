#include <ncursesw/ncurses.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "network.h"

using namespace std;

void *mainThread(void *tid);
void *pingThread(void *tid);
string japaneseNum(int n);
string wideNum(int n);
void renderTile(int y, int x, string tile);
template<class T> T fromString(const string& s);
template<class T> string toString(const T& t);
int charToInt(char a);

static WINDOW *mainWin;
static WINDOW *debugCont;
static WINDOW *debugWin;

network tenhouNet("112.78.204.226", "80");
//network tenhouNet("localhost", "9001");

int main()
{
	string name = "ID30EA6C7C-8YS42EDV";
	string lobby = "4567";
	setlocale(LC_CTYPE, "");
	mainWin = initscr();
	refresh();
	debugCont = newwin(20, COLS, 0, 0);
	debugWin = subwin(debugCont, 18, COLS-2, 1, 1);
	//tenhouNet = new network("112.78.204.226", "80");
	//network tenhouNet("localhost", "9001");

	scrollok(debugWin, true);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	box(debugCont, ACS_VLINE, ACS_HLINE);
	wrefresh(debugCont);
	wrefresh(debugWin);
	tenhouNet.sendMsg("<Z />");
	//say hi
	tenhouNet.sendMsg("<HELO name=\"" + name + "\" tid=\"" + lobby + "\" sx=\"C\" />");
	//join game queues
	//tenhouNet.sendMsg("<JOIN t=\"" + lobby + ",9\" />");
	tenhouNet.sendMsg("<JOIN t=\"" + lobby + ",7\" />");
	tenhouNet.sendMsg("<JOIN t=\"" + lobby + ",3\" />");
	tenhouNet.sendMsg("<JOIN t=\"" + lobby + ",1\" />");
	tenhouNet.sendMsg("<JOIN t=\"" + lobby + ",65\" />");

	pthread_t mainLoop;
	pthread_t pingLoop;
	int threadNum = 0;
	pthread_create(&mainLoop, NULL, mainThread, (void *)threadNum);
	threadNum++;
	pthread_create(&pingLoop, NULL, pingThread, (void *)threadNum);
	pthread_exit(NULL);
	/*
	for(int i=1; i<=9; ++i)
	{
		renderTile(1, i*3, toString<int>(i) + "m");
		renderTile(4, i*3, toString<int>(i) + "p");
		renderTile(7, i*3, toString<int>(i) + "s");
	}
	renderTile(10, 3, "1e");
	renderTile(10, 6, "1o");
	renderTile(10, 9, "1w");
	renderTile(10, 12, "1r");
	renderTile(10, 15, "1g");
	renderTile(10, 18, "1d");
	renderTile(10, 21, "1i");
	*/

	//move(20, 20);
	getch();
	delwin(debugWin);
	endwin();
	return 0;
}

void *mainThread(void *tid)
{
	string buffer;
	bool disconnected = false;
	while(!disconnected)
	{
		buffer = "";
		//tenhouNet.sendMsg("<Z />");
		int status = tenhouNet.recieveMsg(buffer);
		if(status == 0)
		{
			disconnected = true;
		}
		else if(status > 0)
		{
			waddstr(debugWin, (buffer + "\n").c_str());
			wrefresh(debugWin);
			if(buffer != "")
			{
				//cout << buffer << endl;
			}
		}
	}
}

void *pingThread(void *tid)
{
	while(true)
	{
		tenhouNet.sendMsg("<Z />");
		//waddstr(debugWin, (buffer + "\n").c_str());
		sleep(14);
	}
}

void renderTile(int y, int x, string tile)
{
	if(tile.at(1) == 'm') //Man
	{
		attron(COLOR_PAIR(5)|A_BOLD);
		mvaddstr(y, x, japaneseNum(charToInt(tile.at(0))).c_str());
		attroff(COLOR_PAIR(5)|A_BOLD);
		attron(COLOR_PAIR(2));
		mvaddstr(y+1, x, "萬");
		attroff(COLOR_PAIR(2));
	}
	else if(tile.at(1) == 's') //Sou
	{
		int num = charToInt(tile.at(0));
		if(num == 2 || num == 3 || num == 4 || num == 6 || num == 8)
		{
			attron(COLOR_PAIR(7));
			mvaddstr(y, x, wideNum(charToInt(tile.at(0))).c_str());
			attroff(COLOR_PAIR(7));
			attron(COLOR_PAIR(3));
			mvaddstr(y+1, x, "║ ");
			attroff(COLOR_PAIR(3));
		}
		else
		{
			attron(COLOR_PAIR(7));
			mvaddstr(y, x, wideNum(charToInt(tile.at(0))).c_str());
			//mvaddstr(y+1, x, "鳥");
			mvaddstr(y+1, x, "║ ");
			attroff(COLOR_PAIR(7));
		}
	}
	else if(tile.at(1) == 'p') //Pin
	{
		attron(COLOR_PAIR(6));
		mvaddstr(y, x, wideNum(charToInt(tile.at(0))).c_str());
		mvaddstr(y+1, x, "◎∙");
		attroff(COLOR_PAIR(6));
	}
	else if(tile.at(1) == 'e') //East?
	{
		attron(COLOR_PAIR(5)|A_BOLD);
		mvaddstr(y, x, "Ｅ");
		mvaddstr(y+1, x, "東");
		attroff(COLOR_PAIR(5)|A_BOLD);
	}
	else if(tile.at(1) == 'o') //South?
	{
		attron(COLOR_PAIR(5)|A_BOLD);
		mvaddstr(y, x, "Ｓ");
		mvaddstr(y+1, x, "南");
		attroff(COLOR_PAIR(5)|A_BOLD);
	}
	else if(tile.at(1) == 'w') //West?
	{
		attron(COLOR_PAIR(5)|A_BOLD);
		mvaddstr(y, x, "Ｗ");
		mvaddstr(y+1, x, "西");
		attroff(COLOR_PAIR(5)|A_BOLD);
	}
	else if(tile.at(1) == 'r') //North?
	{
		attron(COLOR_PAIR(5)|A_BOLD);
		mvaddstr(y, x, "Ｎ");
		mvaddstr(y+1, x, "北");
		attroff(COLOR_PAIR(5)|A_BOLD);
	}
	else if(tile.at(1) == 'g') //Green Dragon?
	{
		attron(COLOR_PAIR(8));
		mvaddstr(y, x, "Ｇ");
		attroff(COLOR_PAIR(8));
		attron(COLOR_PAIR(3));
		mvaddstr(y+1, x, "發");
		attroff(COLOR_PAIR(3));
	}
	else if(tile.at(1) == 'd') //Red Dragon?
	{
		attron(COLOR_PAIR(8));
		mvaddstr(y, x, "Ｒ");
		attroff(COLOR_PAIR(8));
		attron(COLOR_PAIR(2));
		mvaddstr(y+1, x, "中");
		attroff(COLOR_PAIR(2));
	}
	else if(tile.at(1) == 'i') //White Dragon?
	{
		attron(COLOR_PAIR(8));
		mvaddstr(y, x, "Ｗ");
		attroff(COLOR_PAIR(8));
		attron(COLOR_PAIR(8)|A_BOLD);
		mvaddstr(y+1, x, "白");
		attroff(COLOR_PAIR(8)|A_BOLD);
	}
}

string japaneseNum(int n)
{
	switch(n)
	{
		case 1:
			return "一";
		case 2:
			return "二";
		case 3:
			return "三";
		case 4:
			return "四";
		case 5:
			return "五";
		case 6:
			return "六";
		case 7:
			return "七";
		case 8:
			return "八";
		case 9:
			return "九";
		default:
			return "Error";
	}
}

string wideNum(int n)
{
	switch(n)
	{
		case 1:
			return "１";
		case 2:
			return "２";
		case 3:
			return "３";
		case 4:
			return "４";
		case 5:
			return "５";
		case 6:
			return "６";
		case 7:
			return "７";
		case 8:
			return "８";
		case 9:
			return "９";
		case 0:
			return "０";
		default:
			return "Error";
	}
}

//converts from a string to an arbitray numerical format
template<class T> T fromString(const string& s)
{
	istringstream stream(s);
	T t;
	stream >> t;
	return t;
}
//converts to a string from an arbitrary numerical format
template<class T> string toString(const T& t)
{
	ostringstream stream;
	stream << t;
	return stream.str();
}

int charToInt(char a)
{
	return a - '0';
}
