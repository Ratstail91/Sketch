/* File Name: scene_mgr.h
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
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
