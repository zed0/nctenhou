#ifndef CHATBOX_H
#define CHATBOX_H

#include <ncursesw/ncurses.h>
#include <iostream>
#include "stringUtils.h"

class chatBox
{
	private:
		WINDOW* chatWin;
	public:
		chatBox(WINDOW*);
		void update(string uname, string text);
};

#endif
