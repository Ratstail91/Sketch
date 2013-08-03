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
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "image.hpp"
#include "raster_font.hpp"

#include <string>

//3-phases, no toggle, centred text
class Button {
public:
	enum class State {
		NORMAL, HOVER, PRESSED
	};

	Button() = default;
	Button(std::string bgname, std::string fontname, std::string t = "", Sint16 x = 0, Sint16 y = 0);
	Button(SDL_Surface* background, SDL_Surface* font, std::string t = "", Sint16 x = 0, Sint16 y = 0);
	~Button() = default;

	//graphics
	SDL_Surface* LoadSurface(std::string);
	SDL_Surface* LoadFontSurface(std::string);
	SDL_Surface* SetSurface(SDL_Surface*);
	SDL_Surface* SetFontSurface(SDL_Surface*);
	SDL_Surface* GetSurface() const { return image.GetSurface(); }
	SDL_Surface* GetFontSurface() const { return font.GetSurface(); }
	void FreeSurface() { image.FreeSurface(); }
	void FreeFontSurface() { font.FreeSurface(); }

	//handle input
	State MouseMotion(SDL_MouseMotionEvent const&);
	State MouseButtonDown(SDL_MouseButtonEvent const&);
	State MouseButtonUp(SDL_MouseButtonEvent const&);
	State SetState(State s) { return state = s; }
	State GetState() const { return state; }

	//yet another draw function
	void DrawTo(SDL_Surface* const);

	//text string
	std::string SetText(std::string);
	std::string GetText() const { return text; }

	//position
	Sint16 SetX(Sint16 i) { return x = i; }
	Sint16 SetY(Sint16 i) { return y = i; }
	Sint16 GetX() const { return x; }
	Sint16 GetY() const { return y; }

	//OO Breakers
	Image* GetImage() { return &image; }
	RasterFont* GetFont() { return &font; }

	Sint16 SetTextX(Sint16 i) { return textX = i; }
	Sint16 SetTextY(Sint16 i) { return textY = i; }
	Sint16 GetTextX() const { return textX; }
	Sint16 GetTextY() const { return textY; }
private:
	State CalcState(Sint16 x, Sint16 y, bool leftPressed);

	Sint16 x = 0, y = 0;
	Sint16 textX = 0, textY = 0; //prevent recalc every loop
	Image image;
	RasterFont font; //TODO: cache this?
	State state = State::NORMAL;
	std::string text;
};

#endif
