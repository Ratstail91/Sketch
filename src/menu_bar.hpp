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
#ifndef MENUBAR_HPP_
#define MENUBAR_HPP_

#include "image.hpp"
#include "button.hpp"

#include <vector>

//TODO: Separate this into it's own module
class DropDownMenu {
public:
	DropDownMenu() = default;
	~DropDownMenu() = default;

	void DrawTo(SDL_Surface* const dest);

	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	int MouseButtonUp(SDL_MouseButtonEvent const&);

private:
	Button mainButton;

	std::vector<Button> dropButtons;
	bool open = false;

	friend class MenuBar;
};

class MenuBar {
public:
	MenuBar() = default;
	~MenuBar() = default;

	void LoadSurfaces(std::string bgName, std::string fgName);
	void DrawTo(SDL_Surface* const dest);

	//TODO: Stop this from interfering with the map
	Button::State MouseMotion(SDL_MouseMotionEvent const&);
	Button::State MouseButtonDown(SDL_MouseButtonEvent const&);
	Button::State MouseButtonUp(SDL_MouseButtonEvent const&, int* menu = nullptr, int* button = nullptr);

	//call when the menu is created
	int NewMenu(std::string text);
	int NewButton(int index, std::string text);

	//clean up
	void ClearMenus() { menuButtons.clear(); }
	void ClearButtons(int menuIndex);

	//accessors & mutators
//	Image* GetBGImage() { return &bgImage; }
//	Image* GetFGImage() { return &fgImage; }

//	std::vector<DropDownMenu>* GetMenuButtons() { return &menuButtons; }

private:
	std::vector<DropDownMenu> menuButtons;
	Image bgImage, fgImage;
};

#endif
