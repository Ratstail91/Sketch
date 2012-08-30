/* File Name: scene_editor.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include <iostream>
#include "scene_editor.h"

#include "lua.hpp"
#include "lua_util.h"

#include "colors.h"
#include "terminal.h"
#include "terminal_util.h"

#include "region.h"
#include "tileset.h"

using namespace std;

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENE_H_ != 2012062701 //27/6/2012, revision 1
#error BaseScene version is incompatible with this scene
#endif

//-------------------------
//Public access members
//-------------------------

SceneEditor::SceneEditor(lua_State* L):
m_pLuaVM(L)
{
	m_cam.x = 0;
	m_cam.y = 0;
}

SceneEditor::~SceneEditor() {
	//
}

//-------------------------
//Frame loop members
//-------------------------

void SceneEditor::Head() {
	//
}

void SceneEditor::Tail() {
	//
}

void SceneEditor::Update() {
	//
}

void SceneEditor::Render(SDL_Surface* const pScreen) {
	//zero the background
	SDL_FillRect(pScreen, NULL, MapRGB(pScreen->format, colors[C_BLACK]));

	//draw the map
	if (GetRegion(m_pLuaVM)->IsLoaded() && GetTileset(m_pLuaVM)->IsLoaded()) {
		SDL_Rect sclip, dclip;

		//setup sclip
		sclip.w = GetTileset(m_pLuaVM)->GetWidth();
		sclip.h = GetTileset(m_pLuaVM)->GetHeight();

		for (unsigned int i = 0; i < GetRegion(m_pLuaVM)->GetXCount(); i++) {
			for (unsigned int j = 0; j < GetRegion(m_pLuaVM)->GetYCount(); j++) {
				for (unsigned int k = 0; k < GetRegion(m_pLuaVM)->GetLCount(); k++) {
					//set dclip
					dclip.x = i * GetTileset(m_pLuaVM)->GetWidth() + m_cam.x;
					dclip.y = j * GetTileset(m_pLuaVM)->GetHeight() + m_cam.y;

					//set sclip
					sclip.x = (GetRegion(m_pLuaVM)->GetTile(i, j, k)-1) % GetTileset(m_pLuaVM)->GetXCount() * GetTileset(m_pLuaVM)->GetWidth();
					sclip.y = (GetRegion(m_pLuaVM)->GetTile(i, j, k)-1) / GetTileset(m_pLuaVM)->GetXCount() * GetTileset(m_pLuaVM)->GetHeight();

					//blit the surface
					SDL_BlitSurface(GetTileset(m_pLuaVM)->GetSurface(), &sclip, pScreen, &dclip);
				}//l
			}//y
		}//x
	}//if

//	//draw the terminal
//	if (g_bTerminalActive) {
//		SDL_Rect rect = {0, pScreen->h-100, pScreen->w, 100};
//		TerminalDraw(&g_terminal, pScreen, &rect, g_pFont, 16, 5);
//	}
}

//-------------------------
//Input loop members
//-------------------------

void SceneEditor::MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	if (rMotion.state & SDL_BUTTON_RMASK) {
		m_cam.x += rMotion.xrel;
		m_cam.y += rMotion.yrel;
	}

	try {
		//run the brush script
		lua_getglobal(m_pLuaVM, "brush");
		lua_getfield(m_pLuaVM, -1, "active");
		lua_getfield(m_pLuaVM, -1, "mousemotion");
		lua_pushnumber(m_pLuaVM, rMotion.state);
		lua_pushnumber(m_pLuaVM, rMotion.x-m_cam.x);
		lua_pushnumber(m_pLuaVM, rMotion.y-m_cam.y);
		lua_pushnumber(m_pLuaVM, rMotion.xrel);
		lua_pushnumber(m_pLuaVM, rMotion.yrel);
		lua_pcall(m_pLuaVM, 5, 0, 0);
		lua_pop(m_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		lua_getglobal(m_pLuaVM, "brush");
		lua_getfield(m_pLuaVM, -1, "active");
		lua_getfield(m_pLuaVM, -1, "mousebuttondown");
		lua_pushnumber(m_pLuaVM, rButton.button);
		lua_pushnumber(m_pLuaVM, rButton.x-m_cam.x);
		lua_pushnumber(m_pLuaVM, rButton.y-m_cam.y);
		lua_pcall(m_pLuaVM, 3, 0, 0);
		lua_pop(m_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		lua_getglobal(m_pLuaVM, "brush");
		lua_getfield(m_pLuaVM, -1, "active");
		lua_getfield(m_pLuaVM, -1, "mousebuttonup");
		lua_pushnumber(m_pLuaVM, rButton.button);
		lua_pushnumber(m_pLuaVM, rButton.x-m_cam.x);
		lua_pushnumber(m_pLuaVM, rButton.y-m_cam.y);
		lua_pcall(m_pLuaVM, 3, 0, 0);
		lua_pop(m_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::KeyDown(SDL_KeyboardEvent const& rKey) {
	GetTerminal(m_pLuaVM)->KeyDown(rKey.keysym);

	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
			break;

		case SDLK_RETURN:
			TerminalDoString(m_pLuaVM);
			break;
	};
}

void SceneEditor::KeyUp(SDL_KeyboardEvent const& rKey) {
	GetTerminal(m_pLuaVM)->KeyUp(rKey.keysym);
}

//-------------------------
//Members
//-------------------------

//...

