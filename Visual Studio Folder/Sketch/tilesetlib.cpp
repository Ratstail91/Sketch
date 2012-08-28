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

	reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->Load(fname, w, h);

	return 0;
}

int tileset_Unload(lua_State* L) {
	CHECK_GTHAN(L, 0);
	reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->Unload();
	return 0;
}

int tileset_IsLoaded(lua_State* L) {
	CHECK_GTHAN(L, 0);
	if (reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->IsLoaded()) {
		lua_pushboolean(L, 1);
	}
	else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

int tileset_GetFileName(lua_State* L) {
	CHECK_GTHAN(L, 0);
	std::string str = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetFileName();
	lua_pushstring(L, str.c_str());
	return 1;
}

int tileset_GetXCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetXCount();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetYCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetYCount();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetWidth(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetWidth();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetHeight(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetHeight();
	lua_pushnumber(L, ret);
	return 1;
}

int tileset_GetCount(lua_State* L) {
	CHECK_GTHAN(L, 0);
	double ret = reinterpret_cast<Tileset*>(GetRegisterUserData(L, REG_TILESET))->GetCount();
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