/* File Name: base_scene.cpp
 * Author: Kayne Ruse
 * Date: 27/6/2012
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
 *     The abstract base class for implementing scenes in the scene framework.
*/
#include <exception>
#include "base_scene.h"

//-------------------------
//Static members
//-------------------------

SDL_Surface* BaseScene::ms_pScreen = NULL;

SDL_Surface* BaseScene::SetScreen(int w, int h, int bpp, int iFlags) {
	//SDL video
	ms_pScreen = SDL_SetVideoMode(w, h, bpp, iFlags);

	if (ms_pScreen == NULL)
		throw(std::exception("Failed to initialise the screen surface"));

	return ms_pScreen;
}

SDL_Surface* BaseScene::GetScreen() {
	return ms_pScreen;
}

//-------------------------
//Public access members
//-------------------------

BaseScene::BaseScene() {
	m_iNextScene = SCENE_NULL;
}

BaseScene::~BaseScene() {
	//
}

//-------------------------
//Program control members
//-------------------------

void BaseScene::RunFrame() {
	Head();

	Input();
	Update();
	Render(ms_pScreen);

	SDL_Flip(ms_pScreen);

	Tail();
}

int BaseScene::GetNextScene() {
	return m_iNextScene;
}

int BaseScene::SetNextScene(int i) {
	return m_iNextScene = i;
}

//-------------------------
//Input loop
//-------------------------

void BaseScene::Input() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				QuitEvent();
				break;

			case SDL_VIDEORESIZE:
				SetScreen(event.resize.w, event.resize.h, 0, ms_pScreen->flags);
				break;

			case SDL_MOUSEMOTION:
				MouseMotion(event.motion);
				break;

			case SDL_MOUSEBUTTONDOWN:
				MouseButtonDown(event.button);
				break;

			case SDL_MOUSEBUTTONUP:
				MouseButtonUp(event.button);
				break;

			case SDL_KEYDOWN:
				KeyDown(event.key);
				break;

			case SDL_KEYUP:
				KeyUp(event.key);
				break;

//			default:
//				UnknownEvent(event);
//				break;
		}
	}
}
