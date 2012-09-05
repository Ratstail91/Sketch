/* File Name: scene_mgr.h
 * Author: Kayne Ruse
 * Date: 31/8/2012
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
#ifndef KR_SCENEMGR_H_
#define KR_SCENEMGR_H_

#include "base_scene_mgr.h"
#include "base_scene.h"
#include "scene_list.h"

#include "lua.h"

class SceneMgr : public BaseSceneMgr {
public:
	/* Public access members */
	SceneMgr();
//	virtual ~SceneMgr();

	virtual void Init();
//	virtual void Proc();
	virtual void Quit();

protected:
	/* Protected access members */
	virtual void LoadScene();

	lua_State* m_pLuaVM;
};

#endif
