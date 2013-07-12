/* Copyright: (c) Kayne Ruse 2013
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
*/
#include "custom_libraries.hpp"

#include "map.hpp"

//-------------------------
//define the glue wrapper functons
//-------------------------

static int generate(lua_State* l) {
	//default value
	while (lua_gettop(l) < 4) {
		lua_pushnumber(l, TILE_NONE);
	}

	Map::GetSingletonPtr()->Generate(
		lua_tonumber(l, 1),
		lua_tonumber(l, 2),
		lua_tonumber(l, 3),
		lua_tonumber(l, 4)
		);

	return 0;
}

static int clear(lua_State* l) {
	Map::GetSingletonPtr()->Clear();
	return 0;
}

static int insertLayer(lua_State* l) {
	Map::GetSingletonPtr()->InsertLayer(lua_tonumber(l, 1), lua_tonumber(l, 2));
	return 0;
}

static int deleteLayer(lua_State* l) {
	Map::GetSingletonPtr()->DeleteLayer(lua_tonumber(l, 1));
	return 0;
}

static int setTile(lua_State* l) {
	lua_pushnumber(l, Map::GetSingletonPtr()->SetTile(
		lua_tonumber(l, 1),
		lua_tonumber(l, 2),
		lua_tonumber(l, 3),
		lua_tonumber(l, 4)
		));
	return 1;
}

static int getTile(lua_State* l) {
	lua_pushnumber(l, Map::GetSingletonPtr()->GetTile(
		lua_tonumber(l, 1),
		lua_tonumber(l, 2),
		lua_tonumber(l, 3)
		));
	return 1;
}

static int getLayerCount(lua_State* l) {
	lua_pushnumber(l, Map::GetSingletonPtr()->GetLayerCount());
	return 1;
}

static int getWidth(lua_State* l) {
	lua_pushnumber(l, Map::GetSingletonPtr()->GetWidth());
	return 1;
}

static int getHeight(lua_State* l) {
	lua_pushnumber(l, Map::GetSingletonPtr()->GetHeight());
	return 1;
}

static int getTileMax(lua_State* l) {
	lua_pushnumber(l, TILE_MAX);
	return 1;
}

static int getTileNone(lua_State* l) {
	lua_pushnumber(l, TILE_NONE);
	return 1;
}

//-------------------------
//register  the functions
//-------------------------

static const luaL_Reg libs[] = {
	{"Generate", generate},
	{"Clear", clear},
	{"InsertLayer", insertLayer},
	{"DeleteLayer", deleteLayer},
	{"SetTile", setTile},
	{"GetTile", getTile},
	{"GetLayerCount", getLayerCount},
	{"GetWidth", getWidth},
	{"GetHeight", getHeight},
	{"GetTileMax", getTileMax},
	{"GetTileNone", getTileNone},
	{nullptr, nullptr}
};

void openMapLib(lua_State* l) {
	luaL_newlib(l, libs);
	lua_setglobal(l, "map");
}