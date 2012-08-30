#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdarg.h>

#include "lua.hpp"

#include "colors.h"
#include "lua_util.h"

#include "terminal_util.h"
#include "font.h"

using namespace std;

//-------------------------
//Utilities
//-------------------------

void TerminalDraw(lua_State* L, SDL_Surface* pDest, SDL_Rect rect, int lines) {
	SDL_Rect sclip = {0, 0, rect.w, rect.h}, dclip = rect;

	//fill the background
	SDL_FillRect(pDest, &dclip, MapRGB(pDest->format, colors[C_WHITE]));

	//prepeare these
	int start = ((GetTerminal(L)->GetLines()->size() > lines) ? GetTerminal(L)->GetLines()->size() - lines : 0);

	//draw the x most recent lines
	for (int i = start; i < GetTerminal(L)->GetLines()->size(); i++) {
		//reset dclip
		dclip = rect;
		dclip.y += (i-start)* GetFont(L)->GetFormat()->h;
		dclip.h = GetFont(L)->GetFormat()->h;

		//render line
		GetFont(L)->DrawString(pDest, GetTerminal(L)->GetLine(i).c_str(), dclip);
	}

	//if there isn't an input string, end here
	if (GetTerminal(L)->GetInput()->size() == 0) return;

	//reset dclip: draw the line at the bottom if the rect
	dclip = rect;
	dclip.y += dclip.h - GetFont(L)->GetFormat()->h;
	dclip.h = GetFont(L)->GetFormat()->h;

	//scroll tweak
	//...

	GetFont(L)->DrawString(pDest, GetTerminal(L)->GetInput()->c_str(), dclip);
}

void TerminalDoString(lua_State* L, const char* prompt) {
	//if the most recent line is valid, execute it as a lua script

	try {
		if (GetTerminal(L)->GetLines()->size() &&
			GetTerminal(L)->GetLine(-1).size() &&
			!strncmp(GetTerminal(L)->GetLine(-1).c_str(), prompt, strlen(prompt))
			)
		{
			//pop the most recent line, and execute it
			string s = GetTerminal(L)->GetLine(-1);
			GetTerminal(L)->GetLines()->pop_back();
			DoString(L, s.c_str()+strlen(prompt));
		}
	}
	catch(exception& e) {
		TerminalPrintf(L, "Error: check console");
		cout << "Prompt Error: " << e.what() << endl;
	}
}

void TerminalPrintf(lua_State* L, const char* fmt, ...) {
	//get the formatted string
	va_list argp;

	va_start(argp, fmt);

	char buf[1024];
	vsprintf(buf, fmt, argp);

	va_end(argp);

	GetTerminal(L)->Push(buf);
}
