#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void Error(lua_State* L, const char* fmt, ...);

void DoFile		(lua_State* L, const char* fname);
void DoString	(lua_State* L, const char* str);
void DoCall		(lua_State* L, const char* func, const char* sig, ...);

/*

error

dofile
dostring
docall

//overload these
pushtablestring
pushtablenumber

*/

#endif
