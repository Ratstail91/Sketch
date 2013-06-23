/* File Name: base_scene.h
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
#ifndef KR_BASESCENE_H_
#define KR_BASESCENE_H_ 2012062701

#include "SDL.h"

class BaseScene {
public:
	/* Scene list */
	enum {
		SCENE_QUIT = -1, //close the program
		SCENE_NULL = 0, //do nothing
		SCENE_FIRST = 1 //first scene to open
	};

	/* Static members */
	static SDL_Surface* SetScreen(int w, int h, int bpp, int iFlags);
	static SDL_Surface* GetScreen();

	/* Public access members */
	BaseScene();
	virtual ~BaseScene();

	/* Program control members */
	virtual void RunFrame();
	virtual int GetNextScene();

protected:
	/* Frame loop members */
	virtual void Head	() {}
	virtual void Tail	() {}
	virtual void Input	();
	virtual void Update	() {}
	virtual void Render	(SDL_Surface* const) =0;

	/* Input loop members */
	virtual void QuitEvent			() { SetNextScene(SCENE_QUIT); }
	virtual void MouseMotion		(SDL_MouseMotionEvent const&) {}
	virtual void MouseButtonDown	(SDL_MouseButtonEvent const&) {}
	virtual void MouseButtonUp		(SDL_MouseButtonEvent const&) {}
	virtual void KeyDown			(SDL_KeyboardEvent const&) {}
	virtual void KeyUp				(SDL_KeyboardEvent const&) {}
//	virtual void UnknownEvent		(SDL_Event const&) {}

	/* Program control members */
	virtual int SetNextScene(int);

private:
	static SDL_Surface* ms_pScreen;
	int m_iNextScene;
};

#endif
