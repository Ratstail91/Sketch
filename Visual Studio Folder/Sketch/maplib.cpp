#include <exception>
#include "lua.hpp"
#include "lua_util.h"
#include "sketch_lib.h"

#include "region.h"

//TODO this needs to be split into several modules:
//region, mapframe, tileset, etc.

//glue functions

int l_gettile(lua_State* L) {
	if (lua_gettop(L) > 3) {
		throw(std::exception("Too many arguments"));
	}

	if (lua_gettop(L) < 3) {
		throw(std::exception("Too few arguments"));
	}

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	GetRegister(L, "region");

	double v = reinterpret_cast<Region*>(lua_touserdata(L, -1))->GetTile(x-1, y-1, l-1);

	lua_pushnumber(L, v);

	return 1;
}

int l_settile(lua_State* L) {
	if (lua_gettop(L) > 4) {
		throw(std::exception("Too many arguments"));
	}

	if (lua_gettop(L) < 4) {
		throw(std::exception("Too few arguments"));
	}

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);
	double v = lua_tonumber(L, 4);

	GetRegister(L, "region");

	reinterpret_cast<Region*>(lua_touserdata(L, -1))->SetTile(x-1, y-1, l-1, v);

	return 0;
}

int l_getxcount(lua_State* L) {
	if (lua_gettop(L) != 0) {
		throw(std::exception("Too many arguments"));
	}

	GetRegister(L, "region");

	double ret = reinterpret_cast<Region*>(lua_touserdata(L, 1))->GetXCount();

	lua_pushnumber(L, ret);

	return 1;
}

int l_getycount(lua_State* L) {
	if (lua_gettop(L) != 0) {
		throw(std::exception("Too many arguments"));
	}

	GetRegister(L, "region");

	double ret = reinterpret_cast<Region*>(lua_touserdata(L, 1))->GetYCount();

	lua_pushnumber(L, ret);

	return 1;
}

int l_getlcount(lua_State* L) {
	if (lua_gettop(L) != 0) {
		throw(std::exception("Too many arguments"));
	}

	GetRegister(L, "region");

	double ret = reinterpret_cast<Region*>(lua_touserdata(L, 1))->GetLCount();

	lua_pushnumber(L, ret);

	return 1;
}

int l_newregion(lua_State* L) {
	if (lua_gettop(L) > 3) {
		throw(std::exception("Too many arguments"));
	}

	if (lua_gettop(L) < 3) {
		throw(std::exception("Too few arguments"));
	}

	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	double l = lua_tonumber(L, 3);

	//delete the existing region
	DoCall(L, "deletemap", ">");

	SetRegister(L, "region", new Region(x, y, l));

	return 0;
}

int l_deleteregion(lua_State* L) {
	if (lua_gettop(L) != 0) {
		throw(std::exception("Too many arguments"));
	}

	GetRegister(L, "region");

	delete lua_touserdata(L, -1);

	SetRegister(L, "region", NULL);

	return 0;
}

//library
static const luaL_Reg maplib[] = {
	{"gettile", l_gettile},
	{"settile", l_settile},
	{"getxcount", l_getxcount},
	{"getycount", l_getycount},
	{"getlcount", l_getlcount},
//	{"newmap", l_newregion},
//	{"deletemap", l_deleteregion},
	{NULL, NULL},
};

int sketchopen_maplib(lua_State* L) {
	luaL_newlib(L, maplib);
	return 1;
}
