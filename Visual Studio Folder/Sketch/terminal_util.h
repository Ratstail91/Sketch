#ifndef KR_TERMINALUTIL_H_
#define KR_TERMINALUTIL_H_

#include "SDL.h"
#include "SDL_ttf.h"

#include "lua.h"

#include "terminal.h"

//utilities
void TerminalDraw		(Terminal* pTerminal, SDL_Surface* pDest, TTF_Font* pFont, int iSize, SDL_Rect* pRect, unsigned int lines);
void TerminalDoString	(Terminal* pTerminal, lua_State* L, const char* prompt = "");
void TerminalPrintf		(Terminal* pTerminal, const char* fmt, ...);

//lua interface functions
int luaopen_terminal	(lua_State* L);

#endif
