/* File Name: base_scene_mgr.cpp
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
#include <exception>
#include <iostream>
#include "base_scene_mgr.h"
using namespace std;

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENE_H_ != 2012062701
#error BaseScene version is incompatible with BaseSceneMgr
#endif

//-------------------------
//Public access members
//-------------------------

void BaseSceneMgr::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw(exception("Failed to initialise SDL"));

	BaseScene::SetScreen(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
}

void BaseSceneMgr::Proc() {
	try {
		LoadScene();
		m_iNext = m_pScene->GetNextScene();

		while(m_iNext != BaseScene::SCENE_QUIT) {
			if (m_iNext != BaseScene::SCENE_NULL) {
				UnloadScene();
				LoadScene();
			}

			m_pScene->RunFrame();
			m_iNext = m_pScene->GetNextScene();
		}
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	catch(int& i) {
		cerr << "Error code: " << i << endl;
	}
	catch(...) {
		cerr << "Unhandled exception thrown" << endl;
	}

	UnloadScene();
}

void BaseSceneMgr::Quit() {
	SDL_Quit();
}

//-------------------------
//Protected access members
//-------------------------

BaseSceneMgr::BaseSceneMgr() {
	m_pScene = NULL;
	m_iNext = BaseScene::SCENE_FIRST;
}

BaseSceneMgr::~BaseSceneMgr() {
	//
}

//-------------------------
//Accessors and mutators
//-------------------------

BaseScene* BaseSceneMgr::SetScene(BaseScene* pScene) {
	return m_pScene = pScene;
}

BaseScene* BaseSceneMgr::GetScene() {
	return m_pScene;
}

int BaseSceneMgr::SetNext(int iNext) {
	return m_iNext = iNext;
}

int BaseSceneMgr::GetNext() {
	return m_iNext;
}
//-------------------------
//Scene management members
//-------------------------

void BaseSceneMgr::UnloadScene() {
	delete m_pScene;
	m_pScene = NULL;
}
