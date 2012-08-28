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
int map_generate(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->Load(x, y, l);

	return 0;
}

int map_clear(lua_State* L) {
	CHECK_GTHAN(L, 0);
	reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->Unload();
	return 0;
}

int map_getxcount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->GetXCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_getycount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->GetYCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_getlcount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->GetLCount();
	lua_pushnumber(L, ret);
	return 1;
}

int map_gettile(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	double v = reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->GetTile(x-1, y-1, l-1);

	lua_pushnumber(L, v);

	return 1;
}

int map_settile(lua_State* L) {
	CHECK_LTHAN(L, 4);
	CHECK_GTHAN(L, 4);

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);
	double v = lua_tonumber(L, 4);

	reinterpret_cast<Region*>(GetRegisterUserData(L, REG_REGION))->SetTile(x-1, y-1, l-1, v);

	return 0;
}

int map_loadtileset(lua_State* L) {
	CHECK_LTHAN(L, 3);
	CHECK_GTHAN(L, 3);

	const char* fname = lua_tostring(L, 1);
	double w = lua_tonumber(L, 2);
	double h = lua_tonumber(L, 3);

	reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->Load(fname, w, h);

	return 0;
}

//library
static const luaL_Reg maplib[] = {
	{"generate", map_generate},
	{"clear", map_clear},
	{"getxcount", map_getxcount},
	{"getycount", map_getycount},
	{"getlcount", map_getlcount},
	{"gettile", map_gettile},
	{"settile", map_settile},
	{"loadtileset", map_loadtileset},
	{NULL, NULL},
};

int sketchopen_maplib(lua_State* L) {
	luaL_newlib(L, maplib);
	return 1;
}
