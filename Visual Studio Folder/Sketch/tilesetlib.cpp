/* File Name: tilesetlib.cpp
 * Author: Kayne Ruse
 * Date: 31/8/2012
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
#include <exception>
#include "lua.hpp"
#include "lua_util.h"
#include "sketch_lib.h"

#include "region.h"
#include "tileset.h"

//preprocessor

#define CHECK_LTHAN(L, i) if (lua_gettop(L) < i) throw(std::exception("Too few arguments"));
#define CHECK_GTHAN(L, i) if (lua_gettop(L) > i) throw(std::exception("Too many arguments"));

//glue functions
int tileset_Load(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	const char* fname = lua_tostring(L, 1);
	double w = lua_tonumber(L, 2);
	double h = lua_tonumber(L, 3);

	GetTileset(L)->Load(fname, w, h);

	return 0;
}

int tileset_Unload(lua_State* L) {
	CHECK_GTHAN(L, 0);
	GetTileset(L)->Unload();
	return 0;
}

int tileset_IsLoaded(lua_State* L) {
	CHECK_GTHAN(L, 0);
	if (GetTileset(L)->IsLoaded()) {
		lua_pushboolean(L, 1);
	}
	else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

int tileset_GetFileName(lua_State* L) {
	CHECK_GTHAN(L, 0);
	std::string str = GetTileset(L)->GetFileName();
	lua_pushstring(L, str.c_str());
	return 1;
}

int tileset_GetXCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetTileset(L)->GetXCount();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetYCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetTileset(L)->GetYCount();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetWidth(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetTileset(L)->GetWidth();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetHeight(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetTileset(L)->GetHeight();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetTileset(L)->GetCount();
	lua_pushnumber(L, ret);
	return 1;
}

//library
static const luaL_Reg tilesetlib[] = {
	{"load", tileset_Load},
	{"unload", tileset_Unload},
	{"isloaded", tileset_IsLoaded},
	{"getfname", tileset_GetFileName},
	{"getxcount", tileset_GetXCount},
	{"getycount", tileset_GetYCount},
	{"getwidth", tileset_GetWidth},
	{"getheight", tileset_GetHeight},
	{"getcount", tileset_GetCount},
	{NULL, NULL},
};

int sketchopen_tilesetlib(lua_State* L) {
	luaL_newlib(L, tilesetlib);
	return 1;
}