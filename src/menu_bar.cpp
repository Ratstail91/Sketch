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
#include <sstream>

MenuBar::MenuBar(std::string bgname, std::string fontname, std::vector<std::vector<std::string>> info) {
	LoadSurface(bgname);
	LoadFontSurface(fontname);
	SetEntries(info);
}

MenuBar::MenuBar(SDL_Surface* background, SDL_Surface* font, std::vector<std::vector<std::string>> info) {
	SetSurface(background);
	SetFontSurface(font);
	SetEntries(info);
}

SDL_Surface* MenuBar::LoadSurface(std::string s) {
	image.LoadSurface(s);
	ResetSurfaces();
	return image.GetSurface();
}

SDL_Surface* MenuBar::LoadFontSurface(std::string s) {
	fontImage.LoadSurface(s);
	ResetSurfaces();
	return fontImage.GetSurface();
}

SDL_Surface* MenuBar::SetSurface(SDL_Surface* p) {
	image.SetSurface(p);
	ResetSurfaces();
	return image.GetSurface();
}

SDL_Surface* MenuBar::SetFontSurface(SDL_Surface* p) {
	fontImage.SetSurface(p);
	ResetSurfaces();
	return fontImage.GetSurface();
}

void MenuBar::DrawTo(SDL_Surface* const dest) {
	for (auto& i : entries) {
		i.DrawTo(dest);
	}
}

void MenuBar::MouseMotion(SDL_MouseMotionEvent const& motion) {
	for (auto& i : entries) {
		i.MouseMotion(motion);
	}
}

void MenuBar::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	for (auto& i : entries) {
		i.MouseButtonDown(button);
	}
}

void MenuBar::MouseButtonUp(SDL_MouseButtonEvent const& button, int* entry, int* butt) {
	int ret = -1;
	for (auto& i : entries) {
		ret = i.MouseButtonUp(button);

		if (ret != -1 && entry && butt) {
			*entry = (&i - entries.data());
			*butt = ret;
		}
	}
}

void MenuBar::SetEntries(std::vector<std::vector<std::string>> info) {
	entries.clear();
	for (auto& i : info) {
		NewEntry(i);
	}
	ResetPositions();
}

int MenuBar::NewEntry(std::vector<std::string> info) {
	if (info.size() < 1) {
		std::ostringstream msg;
		msg << "Cannot create a menu entry without information for it";
		throw(std::logic_error(msg.str()));
	}

	//create the entry itself
	MenuBarEntry e;
	e.mainButton.SetSurface(image.GetSurface());
	e.mainButton.SetFontSurface(fontImage.GetSurface());
	e.mainButton.SetText(info[0]);
	e.mainButton.SetX(entries.size() * image.GetClipW());
	e.mainButton.SetY(0);

	//push the entry onto the menu bar
	info.erase(info.begin());
	entries.push_back(e);

	//create each button
	for (auto& i : info) {
		NewButton(entries.size()-1, i);
	}

	return entries.size() -1;
}

void MenuBar::EraseEntry(int entry) {
	if (entry >= entries.size()) {
		std::ostringstream msg;
		msg << "No menu entry of index " << entry;
		throw(std::out_of_range(msg.str()));
	}
	entries.erase(entries.begin()+entry);
	ResetPositions();
}

int MenuBar::GetEntryCount() {
	return entries.size();
}

int MenuBar::NewButton(int entry, std::string text) {
	if (entry >= entries.size()) {
		std::ostringstream msg;
		msg << "No menu entry of index " << entry;
		throw(std::out_of_range(msg.str()));
	}

	//may the programmer gods forgive my sins
	entries[entry].dropButtons.push_back(
		Button(
			image.GetSurface(),
			fontImage.GetSurface(),
			text,
			entry * image.GetClipW(), //x
			(entries[entry].dropButtons.size() +1) * (image.GetClipH()/3) //y, +1 to account for the main button's position
		)
	);
}

void MenuBar::EraseButton(int entry, int button) {
	if (entry >= entries.size()) {
		std::ostringstream msg;
		msg << "No menu entry of index " << entry;
		throw(std::out_of_range(msg.str()));
	}
	if (button >= entries[entry].dropButtons.size()) {
		std::ostringstream msg;
		msg << "No button of index " << button << " present in menu entry index " << entry;
		throw(std::out_of_range(msg.str()));
	}
	entries[entry].dropButtons.erase(entries[entry].dropButtons.begin()+button);
	ResetPositions();
}

void MenuBar::ClearButtons(int entry) {
	if (entry >= entries.size()) {
		std::ostringstream msg;
		msg << "No menu entry of index " << entry;
		throw(std::out_of_range(msg.str()));
	}
	entries[entry].dropButtons.clear();
	ResetPositions();
}

int MenuBar::GetButtonCount(int entry) {
	if (entry >= entries.size()) {
		std::ostringstream msg;
		msg << "No menu entry of index " << entry;
		throw(std::out_of_range(msg.str()));
	}
	return entries[entry].dropButtons.size();
}

void MenuBar::ResetPositions() {
	for (int i = 0; i < entries.size(); i++) {
		entries[i].mainButton.SetX(i * image.GetClipW());
		entries[i].mainButton.SetY(0);

		for (int j = 0; j < entries[i].dropButtons.size(); j++) {
			entries[i].dropButtons[j].SetX(i * image.GetClipW());
			entries[i].dropButtons[j].SetY((j+1) * (image.GetClipH()/3));
		}
	}
}

void MenuBar::ResetSurfaces() {
	for (auto& i : entries) {
		i.mainButton.SetSurface(image.GetSurface());
		i.mainButton.SetFontSurface(fontImage.GetSurface());

		for (auto& j : i.dropButtons) {
			j.SetSurface(image.GetSurface());
			j.SetFontSurface(fontImage.GetSurface());
		}
	}
}

void MenuBar::MenuBarEntry::DrawTo(SDL_Surface* const dest) {
	//only draw the dropButtons in the user has this menu open
	mainButton.DrawTo(dest);

	if (!open) {
		return;
	}

	for (auto& i : dropButtons) {
		i.DrawTo(dest);
	}
}

void MenuBar::MenuBarEntry::MouseMotion(SDL_MouseMotionEvent const& motion) {
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

void MenuBar::MenuBarEntry::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//open the menu
	if (!(open = mainButton.MouseButtonDown(button) == Button::State::PRESSED)) {
		return;
	}

	//update the others anyway
	for (auto& i : dropButtons) {
		i.MouseButtonDown(button);
	}
}

int MenuBar::MenuBarEntry::MouseButtonUp(SDL_MouseButtonEvent const& button) {
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
