/* File Name: sketch_lib.h
 * Author: Kayne Ruse
 * Date: 29/8/2012
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
#ifndef KR_SKETCHLIB_H_
#define KR_SKETCHLIB_H_

#include "lua.h"

#define SKETCH_MAPLIBNAME "map"
LUAMOD_API int sketchopen_maplib(lua_State* L);

#define SKETCH_TILESETLIBNAME "tileset"
LUAMOD_API int sketchopen_tilesetlib(lua_State* L);

#define SKETCH_TERMINALLIBNAME "terminal"
LUAMOD_API int sketchopen_terminallib(lua_State* L);

//tileset manager...

//map frame...

#endif
