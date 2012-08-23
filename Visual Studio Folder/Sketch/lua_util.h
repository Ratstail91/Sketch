#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void Error(lua_State* L, const char* fmt, ...);

void DoFile		(lua_State* L, const char* fname);
void DoString	(lua_State* L, const char* str);
void DoCall		(lua_State* L, const char* func, const char* sig, ...);

void SetRegister(lua_State* L, const char* key, void* udata);
void GetRegister(lua_State* L, const char* key);

/*

error

dofile
dostring
docall

-pushtablestring
-pushtablenumber

setregister
getregister

*/

#endif
