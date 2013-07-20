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
#include "menu_bar.hpp"

#include <stdexcept>

void DropDownMenu::DrawTo(SDL_Surface* const dest) {
	//only draw the dropButtons in the user has this menu open
	mainButton.DrawTo(dest);

	if (!open) {
		return;
	}

	for (auto& i : dropButtons) {
		i.DrawTo(dest);
	}
}

void DropDownMenu::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//open the menu
	bool o = mainButton.MouseMotion(motion) == Button::State::PRESSED;

	if (!(open |= o)) {
		return;
	}

	for (auto& i : dropButtons) {
		//dragging down the menu
		o |= i.MouseMotion(motion) == Button::State::PRESSED;
	}

	open = o;
}

void DropDownMenu::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//open the menu
	if (!(open = mainButton.MouseButtonDown(button) == Button::State::PRESSED)) {
		return;
	}

	//update the others anyway
	for (auto& i : dropButtons) {
		i.MouseButtonDown(button);
	}
}

int DropDownMenu::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	int ret = -1;
	mainButton.MouseButtonUp(button);

	for (auto& i : dropButtons) {
		//the user just released this button
		if (i.GetState() != i.MouseButtonUp(button) && i.GetState() == Button::State::HOVER && open) {
			//get this button's index
			ret = (&i - dropButtons.data());
		}
	}

	open = false;
	return ret;
}

//-------------------------

void MenuBar::LoadSurfaces(std::string bgName, std::string fgName) {
	bgImage.LoadSurface(bgName);
	fgImage.LoadSurface(fgName);
}

void MenuBar::DrawTo(SDL_Surface* const dest) {
	//TODO: a full bar across the screen
	for (auto& i : menuButtons) {
		i.DrawTo(dest);
	}
}

Button::State MenuBar::MouseMotion(SDL_MouseMotionEvent const& mouseMotion) {
	for (auto& i : menuButtons) {
		i.MouseMotion(mouseMotion);
	}
}

Button::State MenuBar::MouseButtonDown(SDL_MouseButtonEvent const& mouseButton) {
	for (auto& i : menuButtons) {
		i.MouseButtonDown(mouseButton);
	}
}

Button::State MenuBar::MouseButtonUp(SDL_MouseButtonEvent const& mouseButton, int* menuIndex, int* buttonIndex) {
	for (auto& i : menuButtons) {
		i.MouseButtonUp(mouseButton);
	}
}

int MenuBar::NewMenu(std::string text) {
	DropDownMenu ddMenu;

	//setup the button
	ddMenu.mainButton.Setup(
		menuButtons.size() * bgImage.GetSurface()->w,
		0,
		bgImage.GetSurface(),
		fgImage.GetSurface(),
		text
	);

	menuButtons.push_back(ddMenu);

	return menuButtons.size() - 1;
}

int MenuBar::NewButton(int menuIndex, std::string text) {
	if (menuIndex > menuButtons.size()) {
		throw(std::logic_error("No drop down menu with that index"));
	}

	Button button(
		menuIndex * bgImage.GetSurface()->w,
		menuButtons[menuIndex].dropButtons.size() * bgImage.GetSurface()->h/3 + bgImage.GetSurface()->h/3,
		bgImage.GetSurface(),
		fgImage.GetSurface(),
		text
	);

	menuButtons[menuIndex].dropButtons.push_back(button);

	return menuButtons[menuIndex].dropButtons.size() - 1;
}

void MenuBar::ClearButtons(int i) {
	if (i > menuButtons.size()) {
		throw(std::logic_error("No drop down menu with that index"));
	}
	menuButtons[i].dropButtons.clear();
}
