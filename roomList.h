#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <ncursesw/ncurses.h>
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class roomList
{
	private:
		WINDOW* roomWin;
		vector<int> waiting;
		vector<int> inGame;
	public:
		roomList(WINDOW*);
		int getWaiting(int type);
		int getInGame(int type);
		void updateWaiting(string waiting);
		void updateInGame(string inGame);
};

#endif
