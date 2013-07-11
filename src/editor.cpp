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
#include "editor.hpp"

#include <iostream>
using namespace std;

//-------------------------
//Public access members
//-------------------------

Editor::Editor(lua_State* L) {
	luaState = L;

	tileset.LoadSurface("tileset.bmp", 32, 32);

	//debug: generate 1 visible layer, and push 7 invisible layers on top
	map->Generate(1, 40, 40, 0);
//	for (int i = 0; i < 7; i++) {
//		map.InsertLayer(i+1);
//	}
}

Editor::~Editor() {
	//
}

//-------------------------
//Frame loop
//-------------------------

void Editor::FrameStart() {
	//
}

void Editor::Update(double delta) {
	//
}

void Editor::FrameEnd() {
	//
}

void Editor::Render(SDL_Surface* const screen) {
//	map.DrawTo(screen, cam.x, cam.y);
	for (int i = 0; i < map->GetLayerCount(); i++) {
		map->DrawLayerTo(screen, &tileset, i, cam.x, cam.y);
	}
//	tileset.DrawTileTo(screen, 14, cam.x, cam.y);
}

//-------------------------
//Event handlers
//-------------------------

void Editor::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//TODO: lua hook

	if (motion.state & SDL_BUTTON_LMASK) {
		//left button: apply to the map
	}

	if (motion.state & SDL_BUTTON_RMASK) {
		//right button: scroll the map
		cam.x += motion.xrel;
		cam.y += motion.yrel;
	}
}

void Editor::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//TODO: lua hook

	if (button.button == SDL_BUTTON_LEFT) {
		//left button: ???
	}

	if (button.button == SDL_BUTTON_RIGHT) {
		//right button: ???
	}
}

void Editor::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//TODO: lua hook
}

void Editor::KeyDown(SDL_KeyboardEvent const& key) {
	//info can be found here:
	//http://en.wikipedia.org/wiki/Keyboard_shortcut

	//TODO: lua hook

	//HOTKEYS: control and shift modifiers
	if (key.keysym.mod & KMOD_CTRL && key.keysym.mod & KMOD_SHIFT) {
		//do nothing
	}

	//HOTKEYS: control modifier
	else if (key.keysym.mod & KMOD_CTRL) {
		switch(key.keysym.sym) {
			case SDLK_s:
				//TODO: save the map to a specified file
			break;

			case SDLK_l:
				//TODO: load the map from a specified file
			break;

			case SDLK_n:
				//TODO: create a "blank" map
			break;

			case SDLK_z:
				//TODO: undo changes (change cache)
			break;

			case SDLK_y:
				//TODO: redo changes (change cache)
			break;
		}
	}

	//HOTKEYS: shift modifier
	else if (key.keysym.mod & KMOD_SHIFT) {
		//
	}

	//HOTKEYS: no recognized modifier
	else {
		switch(key.keysym.sym) {
			case SDLK_ESCAPE:
				QuitEvent();
			break;
		}
	}
}

void Editor::KeyUp(SDL_KeyboardEvent const& key) {
	//TODO: lua hook
}
