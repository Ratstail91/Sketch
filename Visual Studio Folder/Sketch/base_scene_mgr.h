/* File Name: base_scene_mgr.h
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
 *     The base class for managing a series of classes derived from BaseScene.
*/
#ifndef KR_BASESCENEMGR_H_
#define KR_BASESCENEMGR_H_ 2012062701

#include "base_scene.h"

class BaseSceneMgr {
public:
	/* Public access members */
	virtual void Init();
	virtual void Proc();
	virtual void Quit();

protected:
	/* Protected access members */
	BaseSceneMgr();
	virtual ~BaseSceneMgr();

	/* Accessors and mutators */
	BaseScene* SetScene(BaseScene*);
	BaseScene* GetScene();
	int SetNext(int);
	int GetNext();

	/* Scene management members */
	virtual void LoadScene() =0;
	virtual void UnloadScene();

private:
	BaseScene* m_pScene;
	int m_iNext;
};

#endif
