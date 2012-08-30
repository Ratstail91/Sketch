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
