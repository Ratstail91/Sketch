/* File Name: scene_editor.cpp
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
m_pLuaVM(L), m_bShowTerminal(true)
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

	if (m_bShowTerminal) {
		//draw the terminal
		SDL_Rect rect = {0, pScreen->h-100, pScreen->w, 100};
		TerminalDraw(m_pLuaVM, pScreen, rect, 5);
	}
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
		TerminalPrintf(m_pLuaVM, "Error: check console");
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
		TerminalPrintf(m_pLuaVM, "Error: check console");
		cerr << "Brush Error: " << e.what() << endl;
	}

	//set the brush size
	try {
		if (rButton.button == SDL_BUTTON_WHEELUP) {
			DoString(m_pLuaVM, "setsize(getsize()+1)");
		}
		if (rButton.button == SDL_BUTTON_WHEELDOWN) {
			DoString(m_pLuaVM, "setsize(getsize()-1)");
		}
	}
	catch(exception& e) {
		TerminalPrintf(m_pLuaVM, "Error: check console");
		cerr << "Size Error: " << e.what() << endl;
	}
}

void SceneEditor::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		DoString(m_pLuaVM, "brush.mousebuttonup(%d, %d, %d)",
			rButton.button, rButton.x-m_cam.x, rButton.y-m_cam.y);
	}
	catch(exception& e) {
		TerminalPrintf(m_pLuaVM, "Error: check console");
		cerr << "Brush Error: " << e.what() << endl;
	}
}

void SceneEditor::KeyDown(SDL_KeyboardEvent const& rKey) {
	if (rKey.keysym.sym == SDLK_ESCAPE) {
		QuitEvent();
		return;
	}

	if (rKey.keysym.sym == SDLK_TAB && !(rKey.keysym.mod & KMOD_SHIFT)) {
		SetNextScene(SCENE_TILESET);
		return;
	}

	if (rKey.keysym.sym == SDLK_TAB && (rKey.keysym.mod & KMOD_SHIFT)) {
		m_bShowTerminal = !m_bShowTerminal;
		return;
	}

	//up & down keys control layers
	try {
		if (rKey.keysym.sym == SDLK_UP) {
			DoString(m_pLuaVM, "setlayer(getlayer()+1)");
		}
		if (rKey.keysym.sym == SDLK_DOWN) {
			DoString(m_pLuaVM, "setlayer(getlayer()-1)");
		}
	}
	catch(exception& e) {
		TerminalPrintf(m_pLuaVM, "Error: check console");
		cerr << "Keypress Error: " << e.what() << endl;
	}

	if (m_bShowTerminal) {
		GetTerminal(m_pLuaVM)->KeyDown(rKey.keysym);

		if (rKey.keysym.sym == SDLK_RETURN) {
			TerminalDoString(m_pLuaVM);
		}
	}
}

void SceneEditor::KeyUp(SDL_KeyboardEvent const& rKey) {
	if (m_bShowTerminal) {
		GetTerminal(m_pLuaVM)->KeyUp(rKey.keysym);
	}
}

//-------------------------
//Members
//-------------------------

//...

