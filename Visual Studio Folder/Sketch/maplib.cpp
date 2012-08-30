#include <exception>
#include "lua.hpp"
#include "lua_util.h"
#include "sketch_lib.h"

#include "region.h"

//preprocessor

#define CHECK_LTHAN(L, i) if (lua_gettop(L) < i) throw(std::exception("Too few arguments"));
#define CHECK_GTHAN(L, i) if (lua_gettop(L) > i) throw(std::exception("Too many arguments"));

//glue functions
int map_Load(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	GetRegion(L)->Load(x, y, l);

	return 0;
}

int map_Unload(lua_State* L) {
	CHECK_GTHAN(L, 0);
	GetRegion(L)->Unload();
	return 0;
}

int map_IsLoaded(lua_State* L) {
	CHECK_GTHAN(L, 0);
	if (GetRegion(L)->IsLoaded()) {
		lua_pushboolean(L, 1);
	}
	else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

int map_GetXCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetRegion(L)->GetXCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_GetYCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetRegion(L)->GetYCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_GetLCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = GetRegion(L)->GetLCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_GetTile(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	double v = GetRegion(L)->GetTile(x-1, y-1, l-1);

	lua_pushnumber(L, v);

	return 1;
}

int map_SetTile(lua_State* L) {
	CHECK_LTHAN(L, 4);
	CHECK_GTHAN(L, 4);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);
	double v = lua_tonumber(L, 4);

	GetRegion(L)->SetTile(x-1, y-1, l-1, v);

	return 0;
}

//library
static const luaL_Reg maplib[] = {
	{"load", map_Load},
	{"unload", map_Unload},
	{"isloaded", map_IsLoaded},
	{"getxcount", map_GetXCount},
	{"getycount", map_GetYCount},
	{"getlcount", map_GetLCount},
	{"gettile", map_GetTile},
	{"settile", map_SetTile},
	{NULL, NULL},
};

int sketchopen_maplib(lua_State* L) {
	luaL_newlib(L, maplib);
	return 1;
}
