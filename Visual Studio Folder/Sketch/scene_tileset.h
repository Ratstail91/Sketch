/* File Name: scene_tileset.h
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#ifndef KR_SCENETILESET_H_
#define KR_SCENETILESET_H_

#include "SDL.h"
#include "base_scene.h"
#include "scene_list.h"

#include "lua.hpp"

class SceneTileset : public BaseScene {
public:
	/* Public access members */
	SceneTileset(lua_State* L);
	virtual ~SceneTileset();

protected:
	/* Frame loop members */
	virtual void Head	();
	virtual void Tail	();
	virtual void Update	();
	virtual void Render	(SDL_Surface* const);

	/* Input loop members */
	virtual void QuitEvent			() { SetNextScene(SCENE_EDITOR); } //hack
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
