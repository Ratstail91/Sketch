/* File Name: scene_editor.h
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
#ifndef KR_SCENEEDITOR_H_
#define KR_SCENEEDITOR_H_

#include "SDL.h"
#include "base_scene.h"
#include "scene_list.h"

#include "lua.hpp"

class SceneEditor : public BaseScene {
public:
	/* Public access members */
	SceneEditor(lua_State* L);
	virtual ~SceneEditor();

protected:
	/* Frame loop members */
	virtual void Head	();
	virtual void Tail	();
	virtual void Update	();
	virtual void Render	(SDL_Surface* const);

	/* Input loop members */
	virtual void MouseMotion		(SDL_MouseMotionEvent const&);
	virtual void MouseButtonDown	(SDL_MouseButtonEvent const&);
	virtual void MouseButtonUp		(SDL_MouseButtonEvent const&);
	virtual void KeyDown			(SDL_KeyboardEvent const&);
	virtual void KeyUp				(SDL_KeyboardEvent const&);

	/* Members */
	lua_State* m_pLuaVM;
	SDL_Rect m_cam;
	bool m_bShowTerminal;
};

#endif
