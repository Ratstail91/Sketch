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

#include "font.h"

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

	//draw the terminal
	SDL_Rect rect = {0, pScreen->h-100, pScreen->w, 100};
	TerminalDraw(m_pLuaVM, pScreen, rect, 5);
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
		DoString(m_pLuaVM, "brush.mousemotion(%d, %d, %d, %d, %d)",
			rMotion.state, rMotion.x-m_cam.x, rMotion.y-m_cam.y, rMotion.xrel, rMotion.yrel);
	}
	catch(exception& e) {
		cerr << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		DoString(m_pLuaVM, "brush.mousebuttondown(%d, %d, %d)",
			rButton.button, rButton.x-m_cam.x, rButton.y-m_cam.y);
	}
	catch(exception& e) {
		cerr << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		DoString(m_pLuaVM, "brush.mousebuttonup(%d, %d, %d)",
			rButton.button, rButton.x-m_cam.x, rButton.y-m_cam.y);
	}
	catch(exception& e) {
		cerr << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::KeyDown(SDL_KeyboardEvent const& rKey) {
	if (rKey.keysym.sym == SDLK_ESCAPE) {
		QuitEvent();
		return;
	}

	if (rKey.keysym.sym == SDLK_TAB) {
		SetNextScene(SCENE_TILESET);
		return;
	}

	//up & down keys control layers

	GetTerminal(m_pLuaVM)->KeyDown(rKey.keysym);

	if (rKey.keysym.sym == SDLK_RETURN) {
		TerminalDoString(m_pLuaVM);
	}
}

void SceneEditor::KeyUp(SDL_KeyboardEvent const& rKey) {
	GetTerminal(m_pLuaVM)->KeyUp(rKey.keysym);
}

//-------------------------
//Members
//-------------------------

//...

