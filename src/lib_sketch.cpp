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

#include <iostream>
using namespace std;

//-------------------------
//define the glue wrapper functons
//-------------------------

static int save(lua_State* l) {
	return 0;
}

static int load(lua_State* l) {
	return 0;
}

//-------------------------
//register  the functions
//-------------------------

static const luaL_Reg libs[] = {
	{"Save", save},
	{"Load", load},
	{nullptr, nullptr}
};

void openSketchLib(lua_State* l) {
	luaL_newlib(l, libs);
	lua_setglobal(l, "sketch");
}