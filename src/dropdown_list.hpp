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
#ifndef DROPDOWNLIST_HPP_
#define DROPDOWNLIST_HPP_

#include "button.hpp"

#include <vector>

class DropdownList {
public:
	DropdownList() = default;
	~DropdownList() = default;

	void LoadSurfaces(std::string bgName, std::string fgName);
	void SetSurfaces(SDL_Surface* bg, SDL_Surface* fg);
	void FreeSurfaces();

	void DrawTo(SDL_Surface* const dest);

	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	int MouseButtonUp(SDL_MouseButtonEvent const&);

	//simple accessors and mutators
	Sint16 SetX(Sint16 i) { return x = i; }
	Sint16 SetY(Sint16 i) { return y = i; }
	Sint16 GetX() const { return x; }
	Sint16 GetY() const { return y; }

	Button* GetMainButton() { return &mainButton; }

	int NewButton(std::string text);
	int EraseButton(int index);
	int GetButtonCount() const { return dropButtons.size(); }

	Image* GetBGImage() { return &bgImage; }
	Image* GetFGImage() { return &fgImage; }

private:
	Sint16 x = 0, y = 0;
	Button mainButton;
	std::vector<Button> dropButtons;
	Image bgImage, fgImage;
	bool open = false;
};

#endif
