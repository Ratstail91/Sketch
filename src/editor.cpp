#include "editor.hpp"

//-------------------------
//Public access members
//-------------------------

Editor::Editor() {
	//
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
	//
}

//-------------------------
//Event handlers
//-------------------------

void Editor::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void Editor::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//
}

void Editor::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void Editor::KeyDown(SDL_KeyboardEvent const& key) {
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
			break;
	}
}

void Editor::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
