#include "editor.hpp"

//-------------------------
//Public access members
//-------------------------

Editor::Editor() {
	surfMgr.Load("tileset", "tileset.bmp");
	map.Generate(8, 400, 400, 0);
	map.GetLayer(0)->GetTileset()->SetOrigSurface(surfMgr.Get("tileset"), 32, 32);
}

Editor::~Editor() {
	surfMgr.FreeAll();
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
	for (int i = 0; i < map.GetLayers(); i++) {
		map.DrawLayerTo(screen, i, cam.x, cam.y);
	}
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
