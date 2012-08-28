#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdarg.h>

#include "lua.hpp"

#include "colors.h"
#include "lua_util.h"

#include "terminal_util.h"

using namespace std;

//-------------------------
//Utilities
//-------------------------

void TerminalDraw(Terminal* pTerminal, SDL_Surface* pDest, SDL_Rect* pRect, TTF_Font* pFont, unsigned int uiHeight, unsigned int uiLines) {
	SDL_Rect sclip = {0, 0, pRect->w, pRect->h}, dclip = *pRect;

	//fill the background
	SDL_FillRect(pDest, &dclip, MapRGB(pDest->format, colors[C_MGREY]));

	//prepeare these
	SDL_Surface* pMsg = NULL;
	unsigned int uiStart = ((pTerminal->GetLines()->size() > uiLines) ? pTerminal->GetLines()->size() - uiLines : 0);

	//draw the x most recent lines
	for (unsigned int i = uiStart; i < pTerminal->GetLines()->size(); i++) {
		//reset dclip
		dclip = *pRect;
		dclip.y += (i-uiStart)*uiHeight;
		dclip.h = uiHeight;

		//render line
		pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetLine(i).c_str(), colors[C_WHITE]);
		SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
		SDL_FreeSurface(pMsg);
	}

	//if there isn't an input string, end here
	if (pTerminal->GetInput()->size() == 0) return;

	//reset dclip: draw the line at the bottom if the rect
	dclip = *pRect;
	dclip.y += dclip.h - uiHeight;
	dclip.h = uiHeight;

	//render line
	pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetInput()->c_str(), colors[C_LGREY]);

	//scroll tweak
	if ( Uint16(pMsg->w) > pRect->w) {
		dclip.x -= Uint16(pMsg->w) - pRect->w;
		sclip.w += Uint16(pMsg->w) - pRect->w;
	}

	SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
	SDL_FreeSurface(pMsg);
}

void TerminalDoString(Terminal* pTerminal, lua_State* L, const char* prompt) {
	//if the most recent line is valid, execute it as a lua script

	try {
		if (pTerminal->GetLines()->size() &&
			pTerminal->GetLine(-1).size() &&
			!strncmp(pTerminal->GetLine(-1).c_str(), prompt, strlen(prompt))
			)
		{
			//pop the most recent line, and execute it
			string s = pTerminal->GetLine(-1);
			pTerminal->GetLines()->pop_back();
			DoString(L, s.c_str()+strlen(prompt));
		}
	}
	catch(exception& e) {
		TerminalPrintf(pTerminal, "Error: check console");
		cout << "Prompt Error: " << e.what() << endl;
	}
}

void TerminalPrintf(Terminal* pTerminal, const char* fmt, ...) {
	//get the formatted string
	va_list argp;

	va_start(argp, fmt);

	char buf[1024];
	vsprintf(buf, fmt, argp);

	va_end(argp);

	pTerminal->Push(buf);
}

//-------------------------
//Glue Functions
//-------------------------

//TODO: Move these into their own module

int l_TerminalPrint(lua_State* L) {
	//print to the terminal, but only one line
	Terminal* pTerminal = NULL;
	const char* str = NULL;
	int argc = lua_gettop(L);

	//get the terminal
	if ( (pTerminal = (Terminal*)GetRegisterUserData(L, REG_TERMINAL)) == NULL) {
		throw(exception("Failed to get terminal pointer from the registry"));
	}

	for (int i = 0; i < argc; i++) {
		if ( (str = lua_tostring(L, -argc+i)) == NULL) {
			throw(exception("Failed to print line to the terminal"));
		}

		TerminalPrintf(pTerminal, str);
	}

	lua_pop(L, argc);

	return 0;
}

//-------------------------
//Lua Interface Functions
//-------------------------

int luaopen_terminal(lua_State* L) {
	//this should be moved to it's own module, but I won't worry for now
	lua_pushcfunction(L, l_TerminalPrint);
	lua_setglobal(L, REG_TERMINAL);
	return 0;
}
