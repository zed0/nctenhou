#ifndef LOBBY_H
#define LOBBY_H

#include "stringUtils.h"
#include "roomList.h"
#include "chatBox.h"
#include <iostream>

class lobby
{
	private:
		WINDOW* lobbyWin;
		roomList* rooms;
		chatBox* chat;
	public:
		lobby(WINDOW*);
		void updateChat(string chat);
		void updateRooms(string rooms);
};

#endif
