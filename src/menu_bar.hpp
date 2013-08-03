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

#include <string>
#include <vector>

class MenuBar {
public:
	MenuBar() = default;
	MenuBar(std::string bgname, std::string fontname, std::vector<std::vector<std::string>> info);
	MenuBar(SDL_Surface* background, SDL_Surface* font, std::vector<std::vector<std::string>> info);
	~MenuBar() = default;

	//graphics
	SDL_Surface* LoadSurface(std::string);
	SDL_Surface* LoadFontSurface(std::string);
	SDL_Surface* SetSurface(SDL_Surface*);
	SDL_Surface* SetFontSurface(SDL_Surface*);
	SDL_Surface* GetSurface() const { return image.GetSurface(); }
	SDL_Surface* GetFontSurface() const { return fontImage.GetSurface(); }
	void FreeSurface() { image.FreeSurface(); }
	void FreeFontSurface() { fontImage.FreeSurface(); }

	//yet another draw function
	void DrawTo(SDL_Surface* const dest);

	//user inputs
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&, int* entry = nullptr, int* button = nullptr);

	//manage the entries & buttons
	void SetEntries(std::vector<std::vector<std::string>> info);
	void Clear() { entries.clear(); }

	//OO breakers
	int NewEntry(std::vector<std::string>);
	void EraseEntry(int index);
	int GetEntryCount();

	int NewButton(int entry, std::string text);
	void EraseButton(int entry, int button);
	void ClearButtons(int entry);
	int GetButtonCount(int entry);

	Image* GetImage() { return &image; }
	Image* GetFontImage() { return &fontImage; }

private:
	void ResetPositions();
	void ResetSurfaces();

	class MenuBarEntry;

	std::vector<MenuBarEntry> entries;
	Image image, fontImage;
};

class MenuBar::MenuBarEntry {
public:
	MenuBarEntry() = default;
	~MenuBarEntry() = default;

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

#endif
