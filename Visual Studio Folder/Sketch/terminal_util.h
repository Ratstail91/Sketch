#ifndef KR_TERMINALUTIL_H_
#define KR_TERMINALUTIL_H_

#include "SDL.h"

#include "lua.h"

#include "terminal.h"

//utilities
void TerminalDraw		(lua_State* L, SDL_Surface* pDest, SDL_Rect rect, int lines);
void TerminalDoString	(lua_State* L, const char* prompt = "");
void TerminalPrintf		(lua_State* L, const char* fmt, ...);

//lua interface functions
int luaopen_terminal	(lua_State* L);

#endif
