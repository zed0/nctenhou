#include "roomList.h"

roomList::roomList(WINDOW* parentWin)
{
	roomWin = derwin(parentWin, 0, 10, 0, 0);
	box(roomWin, 0, 0);
	wrefresh(roomWin);
	scrollok(roomWin, true);
	waiting.resize(12);
	inGame.resize(12);
}

int roomList::getWaiting(int type)
{
	return waiting.at(type);
}

int roomList::getInGame(int type)
{
	return inGame.at(type);
}

void roomList::updateWaiting(string waitingString)
{
	setWaiting(waitingString);
	wclear(roomWin);
	for(int i=0; i<waiting.size(); ++i)
	{
		waddstr(roomWin, (stringUtils::toString<int>(i) + ": " + stringUtils::toString<int>(waiting.at(i))+"\n").c_str());
	}
	//waddstr(roomWin, ("waiting: "+waitingString+"\n").c_str());
	wrefresh(roomWin);
}

void roomList::updateInGame(string inGameString)
{
	//waddstr(roomWin, ("Joined: "+inGameString+"\n").c_str());
	wrefresh(roomWin);
}

void roomList::setWaiting(string waitingString)
{
	for(int i=0; i<waiting.size(); ++i)
	{
		waiting.at(i) = 0;
	}
	int currentType = 0;
	int total = 0;
	for(int i=0; i<waitingString.length(); ++i)
	{
		if(waitingString.at(i) >= 'A')
		{
			currentType += total;
			total = 0;
			waiting.at(gameType(currentType)) = waitingString.at(i) - 'A';
		}
		else if(waitingString.at(i) >= '0' && waitingString.at(i) <= '9')
		{
			if(total != 0)
			{
				total *= 10;
			}
			total += waitingString.at(i) - '0';
		}
	}
}

int roomList::gameType(int gameType)
{
	switch(gameType)
	{
		case 3:
			return 0;
		case 1:
			return 1;
		case 0:
			return 2;
		case 8:
			return 3;
		case 64:
			return 4;
		case 72:
			return 5;

		case 7:
			return 6;
		case 5:
			return 7;
		case 4:
			return 8;
		case 12:
			return 9;
		case 65:
			return 10;
		case 73:
			return 11;
	}
}
