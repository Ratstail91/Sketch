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

void MenuBar::LoadSurfaces(std::string bgName, std::string fgName) {
	bgImage.LoadSurface(bgName);
	fgImage.LoadSurface(fgName);
}

void MenuBar::DrawTo(SDL_Surface* const dest) {
	//TODO
	for (auto& i : buttons) {
		i.button.DrawTo(dest);
		for (auto& j : i.dropButtons) {
			j.DrawTo(dest);
		}
	}
}

Button::State MenuBar::MouseMotion(SDL_MouseMotionEvent const&, int* entryIndex, int* dropButtonIndex) {
	//TODO
}

Button::State MenuBar::MouseButtonDown(SDL_MouseButtonEvent const&, int* entryIndex, int* dropButtonIndex) {
	//TODO
}

Button::State MenuBar::MouseButtonUp(SDL_MouseButtonEvent const&, int* entryIndex, int* dropButtonIndex) {
	//TODO
}

int MenuBar::NewButton(std::string text) {
	menuBarEntry entry;
	entry.index = buttons.size();

	//setup the button
	entry.button.Setup(
		entry.index * bgImage.GetSurface()->w,
		0,
		bgImage.GetSurface(),
		fgImage.GetSurface(),
		text
	);

	buttons.push_back(entry);

	return buttons.size() - 1;
}

int MenuBar::NewDropButton(int entryIndex, std::string text) {
	if (entryIndex > buttons.size()) {
		throw(std::logic_error("No buttons with that index"));
	}

	Button button(
		entryIndex * bgImage.GetSurface()->w,
		buttons[entryIndex].dropButtons.size() * bgImage.GetSurface()->h/3 + bgImage.GetSurface()->h/3,
		bgImage.GetSurface(),
		fgImage.GetSurface(),
		text
	);

	buttons[entryIndex].dropButtons.push_back(button);

	return buttons[entryIndex].dropButtons.size() - 1;
}

void MenuBar::ClearButtons() {
	buttons.clear();
}

void MenuBar::ClearDropButtons(int entryIndex) {
	//TODO
}
