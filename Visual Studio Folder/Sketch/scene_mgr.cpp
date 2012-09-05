/* File Name: scene_mgr.cpp
 * Author: Kayne Ruse
 * Date: 5/9/2012
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
#include <stdexcept>
#include <iostream>

#include "SDL.h"
#include "lua.hpp"

#include "lua_util.h"

#include "colors.h"
#include "terminal.h"
#include "terminal_util.h"

#include "scene_mgr.h"

#include "region.h"
#include "tileset.h"
#include "font.h"

using namespace std;

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENEMGR_H_ != 2012062701 //27/6/2012, revision 1
#error BaseSceneMgr version is incompatible with SceneMgr
#endif

//-------------------------
//Scene headers
//-------------------------

#include "scene_editor.h"
#include "scene_tileset.h"

//-------------------------
//Public access members
//-------------------------

SceneMgr::SceneMgr() {
	m_pLuaVM = NULL;
}

//SceneMgr::~SceneMgr() {
//	//
//}

void SceneMgr::Init() {
	//init the libraries
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(-1);
	if ( (m_pLuaVM = luaL_newstate()) == NULL)
		exit(-2);

	//open the libraries
	luaL_openlibs(m_pLuaVM);

	//register the globals to lua
	SetRegister(m_pLuaVM, REG_TERMINAL, new Terminal());
	SetRegister(m_pLuaVM, REG_REGION, new Region());
	SetRegister(m_pLuaVM, REG_TILESET, new Tileset());
	SetRegister(m_pLuaVM, REG_FONT, new Font());

	try {
		//run the startup script
		DoFile(m_pLuaVM, "rsc\\scripts\\startup.lua");

		//load the font from lua (yes, it's messy)

		lua_getglobal(m_pLuaVM, "terminal");
		lua_getfield(m_pLuaVM, -1, "font");

		lua_getfield(m_pLuaVM, -1, "fname");
		lua_getfield(m_pLuaVM, -2, "x");
		lua_getfield(m_pLuaVM, -3, "y");
		lua_getfield(m_pLuaVM, -4, "w");
		lua_getfield(m_pLuaVM, -5, "h");

		SDL_Rect fmt;

		fmt.x = lua_tonumber(m_pLuaVM, -4);
		fmt.y = lua_tonumber(m_pLuaVM, -3);
		fmt.w = lua_tonumber(m_pLuaVM, -2);
		fmt.h = lua_tonumber(m_pLuaVM, -1);

		GetFont(m_pLuaVM)->Load(lua_tostring(m_pLuaVM, -5), fmt);

		lua_pop(m_pLuaVM, 7);

		//setup the screen
		lua_getglobal(m_pLuaVM, "screen");
		lua_getfield(m_pLuaVM, -1, "w");
		lua_getfield(m_pLuaVM, -2, "h");
		lua_getfield(m_pLuaVM, -3, "fullscreen");

		int w = lua_tonumber(m_pLuaVM, -3);
		int h = lua_tonumber(m_pLuaVM, -2);
		int f = lua_toboolean(m_pLuaVM, -1);

		lua_pop(m_pLuaVM, 4);

		if (w < 300 || h < 200) {
			//minimum screen size
			throw(exception("Specified screen size is too small"));
		}

		int flags = SDL_HWSURFACE|SDL_DOUBLEBUF;

		if (f) {
			flags |= SDL_FULLSCREEN;
		}

		BaseScene::SetScreen(w, h, SDL_GetVideoInfo()->vfmt->BitsPerPixel, flags);
	}
	catch(exception& e) {
		cerr << "Startup Error: " << e.what() << endl;
		throw(1);
	}

	//debugging...
	//...
}

//void SceneMgr::Proc() {
//	//
//}

void SceneMgr::Quit() {
	try {
		DoFile(m_pLuaVM, "rsc\\scripts\\shutdown.lua");
	}
	catch(exception& e) {
		cerr << "Shutdown Error: " << e.what() << endl;
		throw(1);
	}

	GetFont(m_pLuaVM)->Unload();

	//delete the pointers
	delete GetTerminal(m_pLuaVM);
	delete GetRegion(m_pLuaVM);
	delete GetTileset(m_pLuaVM);
	delete GetFont(m_pLuaVM);

	lua_close(m_pLuaVM);
	SDL_Quit();
}

//-------------------------
//Protected access members
//-------------------------

void SceneMgr::LoadScene() {
	delete GetScene();

	switch(GetNext()) {
		case BaseScene::SCENE_FIRST: //this is always the first scene in the game

		case SCENE_EDITOR:
			SetScene( new SceneEditor(m_pLuaVM) );
			break;

		case SCENE_TILESET:
			SetScene( new SceneTileset(m_pLuaVM) );
			break;
	}
}

//-------------------------
//SDL_main()
//-------------------------

#include <iostream>
using namespace std;

int SDL_main(int, char**) {
	try {
		SceneMgr app;

		app.Init();
		app.Proc();
		app.Quit();
	}
	catch(int& i) {
		return i;
	}

	return 0;
}
