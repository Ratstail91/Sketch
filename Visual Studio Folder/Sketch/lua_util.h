#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void Error(lua_State* L, const char* fmt, ...);

void DoFile		(lua_State* L, const char* fname);
void DoString	(lua_State* L, const char* str);
void DoCall		(lua_State* L, const char* func, const char* sig, ...);

void SetRegister			(lua_State* L, const char* key, void* udata);
void PushRegister			(lua_State* L, const char* key);
void* GetRegisterUserData	(lua_State* L, const char* key);

#define REG_REGION "region"
#define REG_TERMINAL "terminal"
#define REG_TILESET "tileset"

/*

error

dofile
dostring
docall

-pushtablestring
-pushtablenumber

setregister
pushregister
getregisteruserdata

*/

#endif
