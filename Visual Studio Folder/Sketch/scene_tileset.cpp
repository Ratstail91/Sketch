/* File Name: scene_tileset.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include <iostream>
#include "scene_tileset.h"
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
	//
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
	//
}

//-------------------------
//Input loop members
//-------------------------

void SceneTileset::MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	//
}

void SceneTileset::MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	//
}

void SceneTileset::MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	//
}

void SceneTileset::KeyDown(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
			break;

		//...
	};
}

void SceneTileset::KeyUp(SDL_KeyboardEvent const& rKey) {
	//
}

//-------------------------
//Members
//-------------------------

//...

