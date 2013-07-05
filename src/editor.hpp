#ifndef EXAMPLE_HPP_
#define EXAMPLE_HPP_

#include "base_scene.hpp"

#include "map.hpp"
#include "tileset.hpp"
#include "surface_manager.hpp"
#include "vector2.hpp"

class Editor : public BaseScene {
public:
	//Public access members
	Editor();
	~Editor();

protected:
	//Frame loop
	void FrameStart();
	void Update(double delta);
	void FrameEnd();
	void Render(SDL_Surface* const);

	//Event handlers
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&);
	void KeyDown(SDL_KeyboardEvent const&);
	void KeyUp(SDL_KeyboardEvent const&);

	//members
	Map map;
	SurfaceManager surfMgr;
	Vector2 cam;
};

#endif
