#include "lobby.h"

lobby::lobby(WINDOW* parentWin)
{
	lobbyWin = derwin(parentWin, 30, 40, 10, 10);
	rooms = new roomList(lobbyWin);
	chat = new chatBox(lobbyWin);
	box(lobbyWin, 0, 0);
	wrefresh(lobbyWin);
}

void lobby::updateChat(string chatString)
{
	string uname = stringUtils::getXMLAttr(chatString, "uname");
	string text = stringUtils::getXMLAttr(chatString, "text");
	chat->update(uname, text);
	wrefresh(lobbyWin);
}

void lobby::updateRooms(string roomString)
{
	string waiting = stringUtils::getXMLAttr(roomString, "j");
	string inGame = stringUtils::getXMLAttr(roomString, "g");
	rooms->updateWaiting(waiting);
	rooms->updateInGame(inGame);
	wrefresh(lobbyWin);
}
