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

struct menuBarEntry {
	int index;
	Button button;
	std::vector<Button> dropButtons;
};

class MenuBar {
public:
	MenuBar() = default;
	~MenuBar() = default;

	void LoadSurfaces(std::string bgName, std::string fgName);
	void DrawTo(SDL_Surface* const dest);

	Button::State MouseMotion(SDL_MouseMotionEvent const&, int* entryIndex = nullptr, int* dropButtonIndex = nullptr);
	Button::State MouseButtonDown(SDL_MouseButtonEvent const&, int* entryIndex = nullptr, int* dropButtonIndex = nullptr);
	Button::State MouseButtonUp(SDL_MouseButtonEvent const&, int* entryIndex = nullptr, int* dropButtonIndex = nullptr);

	//call when the menu is created
	int NewButton(std::string text);
	int NewDropButton(int entryIndex, std::string text);

	//clean up
	void ClearButtons();
	void ClearDropButtons(int entryIndex);

private:
	std::vector<menuBarEntry> buttons;
	Image bgImage, fgImage;
};

#endif
