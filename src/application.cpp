/* Copyright: (c) Kayne Ruse 2013
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
*/
#include "application.hpp"

#include "custom_libraries.hpp"
#include "map.hpp"

#include <stdexcept>
#include <chrono>

//-------------------------
//Scene headers
//-------------------------

//Add the custom scene headers here
#include "splash_screen.hpp"
#include "editor.hpp"

//-------------------------
//Public access members
//-------------------------

Application::Application() {
	//
}

Application::~Application() {
	//
}

void Application::Init() {
	//initialize the APIs
	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw(std::runtime_error("Failed to initialize SDL"));
	}

	if (!(luaState = luaL_newstate())) {
		throw(std::runtime_error("Failed to initialize lua"));
	}

	//open the lua libraries
	luaL_openlibs(luaState);
	openCustomLibraries(luaState);

	luaL_dofile(luaState, "rsc\\init.lua");

	//create the "global" objects
	lua_pushlightuserdata(luaState, reinterpret_cast<void*>(new Map()));
	lua_setfield(luaState, LUA_REGISTRYINDEX, "sketch-map");

	//TODO: tileset manager

	//create the screen
	BaseScene::SetScreen(800, 600);
}

void Application::Proc() {
	LoadScene(SceneList::FIRST);

	//prepare the time system
	typedef std::chrono::steady_clock Clock;

	Clock::duration delta(16 * Clock::duration::period::den / std::milli::den);
	Clock::time_point simTime = Clock::now();
	Clock::time_point realTime;

	//The main loop
	while(activeScene->GetNextScene() != SceneList::QUIT) {
		//switch scenes when necessary
		if (activeScene->GetNextScene() != SceneList::CONTINUE) {
			LoadScene(activeScene->GetNextScene());
			continue;
		}

		//update the current time
		realTime = Clock::now();

		//simulate game time
		while (simTime < realTime) {
			//call each user defined function
			activeScene->RunFrame(double(delta.count()) / Clock::duration::period::den);
			simTime += delta;
		}

		//draw the game to the screen
		activeScene->RenderFrame();

		//give the computer a break
		SDL_Delay(10);
	}

	UnloadScene();
}

void Application::Quit() {
	//delete the "global" objects
	lua_getfield(luaState, LUA_REGISTRYINDEX, "sketch-map");
	delete reinterpret_cast<Map*>(lua_touserdata(luaState, -1));
	lua_pop(luaState, 1);

	//clean up the APIs
	lua_close(luaState);
	SDL_Quit();
}

//-------------------------
//Private access members
//-------------------------

void Application::LoadScene(SceneList sceneIndex) {
	UnloadScene();

	switch(sceneIndex) {
		//add scene creation calls here
		case SceneList::FIRST:
		case SceneList::SPLASHSCREEN:
			activeScene = new SplashScreen(luaState);
		break;

		case SceneList::EDITOR:
			activeScene = new Editor(luaState);
		break;

		default:
			throw(std::logic_error("Failed to recognize the scene index"));
	}
}

void Application::UnloadScene() {
	delete activeScene;
	activeScene = nullptr;
}
