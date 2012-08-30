#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void Error(lua_State* L, const char* fmt, ...);

void DoFile		(lua_State* L, const char* fname);
void DoString	(lua_State* L, const char* str);
void DoCall		(lua_State* L, const char* func, const char* sig, ...);

//register system
void SetRegister			(lua_State* L, const char* key, void* udata);
void PushRegister			(lua_State* L, const char* key);
void* GetRegisterUserData	(lua_State* L, const char* key);

//register keys
#define REG_REGION "region"
#define REG_TERMINAL "terminal"
#define REG_TILESET "tileset"

//register object pointers
#define GetRegion(L) (reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION)))
#define GetTerminal(L) (reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL)))
#define GetTileset(L) (reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET)))

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
