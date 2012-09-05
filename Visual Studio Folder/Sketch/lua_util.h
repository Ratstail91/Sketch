/* File Name: lua_util.h
 * Author: Kayne Ruse
 * Date: 3/9/2012
 * Copyright: (c) Kayne Ruse 2012
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * Description:
 *     ...
*/
#ifndef KR_LUAUTIL_H_
#define KR_LUAUTIL_H_

#include "lua.h"

void Error(lua_State* L, const char* fmt, ...);

void DoFile		(lua_State* L, const char* fname);
void DoString	(lua_State* L, const char* fmt, ...);
void DoCall		(lua_State* L, const char* func, const char* sig, ...);

//register system
void SetRegister			(lua_State* L, const char* key, void* udata);
void PushRegister			(lua_State* L, const char* key);
void* GetRegisterUserData	(lua_State* L, const char* key);

//register keys
#define REG_REGION "region"
#define REG_TERMINAL "terminal"
#define REG_TILESET "tileset"
#define REG_FONT "font"

//register object pointers
#define GetRegion(L) (reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION)))
#define GetTerminal(L) (reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL)))
#define GetTileset(L) (reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET)))
#define GetFont(L) (reinterpret_cast<Font*>(GetRegisterUserData(L, REG_FONT)))

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
