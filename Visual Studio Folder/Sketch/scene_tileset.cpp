/* File Name: scene_tileset.cpp
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
#include "scene_tileset.h"

#include "colors.h"
#include "lua_util.h"

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

SceneTileset::SceneTileset(lua_State* L):
m_pLuaVM(L)
{
	m_cam.x = 0;
	m_cam.y = 0;
}

SceneTileset::~SceneTileset() {
	//
}

//-------------------------
//Frame loop members
//-------------------------

void SceneTileset::Head() {
	//
}

void SceneTileset::Tail() {
	//
}

void SceneTileset::Update() {
	//
}

void SceneTileset::Render(SDL_Surface* const pScreen) {
	//zero the background
	SDL_FillRect(pScreen, NULL, MapRGB(pScreen->format, colors[C_BLACK]));

	//render the tileset
	SDL_Rect dclip = m_cam;

	SDL_BlitSurface(GetTileset(m_pLuaVM)->GetSurface(), NULL, pScreen, &dclip);
}

//-------------------------
//Input loop members
//-------------------------

void SceneTileset::MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	if (rMotion.state & SDL_BUTTON_RMASK) {
		m_cam.x += rMotion.xrel;
		m_cam.y += rMotion.yrel;
	}
}

void SceneTileset::MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	//
}

void SceneTileset::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	//select the tile
	if (rButton.button != SDL_BUTTON_LEFT ||
		rButton.x - m_cam.x < 0 ||
		rButton.y - m_cam.y < 0 ||
		rButton.x - m_cam.x > GetTileset(m_pLuaVM)->GetSurface()->w ||
		rButton.y - m_cam.y > GetTileset(m_pLuaVM)->GetSurface()->h
		)
	{
		return;
	}

	//get the tile index
	Uint32 tx = rButton.x / GetTileset(m_pLuaVM)->GetWidth();
	Uint32 ty = rButton.y / GetTileset(m_pLuaVM)->GetHeight();
	Uint32 t = ty * GetTileset(m_pLuaVM)->GetXCount() + tx;

	//set the tile
	DoString(m_pLuaVM, "settile(%d)", t+1);

	//return to the editor
	SetNextScene(SCENE_EDITOR);
}

void SceneTileset::KeyDown(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			DoString(m_pLuaVM, "settile(0)");
			SetNextScene(SCENE_EDITOR);
			break;

		case SDLK_TAB:
			SetNextScene(SCENE_EDITOR);
			break;

		case SDLK_SPACE:
			DoString(m_pLuaVM, "settile(0)");
			SetNextScene(SCENE_EDITOR);
			break;
	};
}

void SceneTileset::KeyUp(SDL_KeyboardEvent const& rKey) {
	//
}

//-------------------------
//Members
//-------------------------

//...

