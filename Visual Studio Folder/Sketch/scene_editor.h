/* File Name: scene_editor.h
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
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
};

#endif
