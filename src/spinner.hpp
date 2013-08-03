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
#ifndef SPINNER_HPP_
#define SPINNER_HPP_

#include "button.hpp"
#include "raster_font.hpp"
#include "image.hpp"

#include <array>
#include <string>

class Spinner {
public:
	Spinner() = default;
	~Spinner() = default;

	void LoadSurfaces(std::string bgName, std::string fgName);
	void SetSurfaces(SDL_Surface* fgSurface, SDL_Surface* bgSurface);
	void FreeSurfaces();

	void DrawTo(SDL_Surface* const dest);

	//user inputs
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&);

	//accessors and mutators
	int SetMin(int i);
	int SetMax(int i);
	int GetMin();
	int GetMax();
	int GetValue();
private:
	std::array<Button, 6> buttons;
	std::string text;
	int min = 0, max = 0, value = 0;
};

#endif
