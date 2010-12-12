#include "chatBox.h"

chatBox::chatBox(WINDOW* parentWin)
{
	chatWin = derwin(parentWin, 0, 0, 0, 10);
	box(chatWin, 0, 0);
	wrefresh(chatWin);
	scrollok(chatWin, true);
}

void chatBox::update(string uname, string text)
{
	waddstr(chatWin, (stringUtils::ASCIIToStr(uname) + ": " + stringUtils::ASCIIToStr(text) + "\n").c_str());
	wrefresh(chatWin);
}
