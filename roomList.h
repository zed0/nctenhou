#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <ncursesw/ncurses.h>
#include <iostream>
#include <string>
#include "stringUtils.h"
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
		void updateWaiting(string waitingString);
		void updateInGame(string inGameString);
		void setWaiting(string waitingString);
		int gameType(int gameType);
};

#endif
