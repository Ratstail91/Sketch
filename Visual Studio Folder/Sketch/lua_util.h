#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void error(lua_State* L, const char* fmt, ...);

void dofile		(lua_State* L, const char* fname);
void dostring	(lua_State* L, const char* str);
void docall		(lua_State* L, const char* func, const char* sig, ...);

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
