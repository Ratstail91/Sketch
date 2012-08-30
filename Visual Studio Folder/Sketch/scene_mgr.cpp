/* File Name: scene_mgr.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
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

	BaseScene::SetScreen(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	//

	//open the libraries
	luaL_openlibs(m_pLuaVM);

	//register the globals for lua
	SetRegister(m_pLuaVM, REG_TERMINAL, new Terminal());
	SetRegister(m_pLuaVM, REG_REGION, new Region());
	SetRegister(m_pLuaVM, REG_TILESET, new Tileset());
	SetRegister(m_pLuaVM, REG_FONT, new Font());

	SDL_Rect fmt = {16, 16, 16, 16};
	GetFont(m_pLuaVM)->Load("pokemon_dark_font.bmp", fmt);

	try {
		DoFile(m_pLuaVM, "startup.lua");
	}
	catch(exception& e) {
		cerr << "Startup Error: " << e.what() << endl;
		TerminalPrintf(m_pLuaVM, "Error: check console");
	}

	//debugging...
	//...
}

//void SceneMgr::Proc() {
//	//
//}

void SceneMgr::Quit() {
	try {
		DoFile(m_pLuaVM, "shutdown.lua");
	}
	catch(exception& e) {
		cerr << "Shutdown Error: " << e.what() << endl;
		TerminalPrintf(m_pLuaVM, "Error: check console");
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
	SceneMgr app;

	app.Init();
	app.Proc();
	app.Quit();

	return 0;
}
