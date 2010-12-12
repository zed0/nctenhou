#include "roomList.h"

roomList::roomList(WINDOW* parentWin)
{
	roomWin = derwin(parentWin, 0, 10, 0, 0);
	box(roomWin, 0, 0);
	wrefresh(roomWin);
	scrollok(roomWin, true);
}

int roomList::getWaiting(int type)
{
	return waiting.at(type);
}

int roomList::getInGame(int type)
{
	return inGame.at(type);
}

void roomList::updateWaiting(string waiting)
{
	waddstr(roomWin, ("waiting: "+waiting+"\n").c_str());
	wrefresh(roomWin);
}

void roomList::updateInGame(string inGame)
{
	waddstr(roomWin, ("Joined: "+inGame+"\n").c_str());
	wrefresh(roomWin);
}
