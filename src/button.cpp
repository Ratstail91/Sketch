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
#include "button.hpp"

#include <stdexcept>

Button::Button(std::string bgname, std::string fname, std::string t, Sint16 _x, Sint16 _y) {
	LoadSurface(bgname);
	LoadFontSurface(fname);
	SetText(t);
	SetX(x);
	SetY(y);
}

Button::Button(SDL_Surface* bg, SDL_Surface* f, std::string t, Sint16 _x, Sint16 _y) {
	SetSurface(bg);
	SetFontSurface(f);
	SetText(t);
	SetX(x);
	SetY(y);
}

SDL_Surface* Button::LoadSurface(std::string s) {
	image.LoadSurface(s);
	image.SetClipH(image.GetClipH()/3); //3 phases, vertical storage
	SetText(text); //reset textX & textY
	return image.GetSurface();
}

SDL_Surface* Button::LoadFontSurface(std::string s) {
	font.LoadSurface(s);
	SetText(text); //reset textX & textY
	return font.GetSurface();
}

SDL_Surface* Button::SetSurface(SDL_Surface* p) {
	image.SetSurface(p);
	image.SetClipH(image.GetClipH()/3); //3 phases, vertical storage
	SetText(text); //reset textX & textY
	return image.GetSurface();
}

SDL_Surface* Button::SetFontSurface(SDL_Surface* p) {
	font.SetSurface(p);
	SetText(text); //reset textX & textY
	return font.GetSurface();
}

Button::State Button::MouseMotion(SDL_MouseMotionEvent const& motion) {
	return CalcState(motion.x, motion.y, motion.state & SDL_BUTTON_LMASK);
}

Button::State Button::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	if (button.button == SDL_BUTTON_LEFT) {
		return CalcState(button.x, button.y, true);
	}
	return state;
}

Button::State Button::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	if (button.button == SDL_BUTTON_LEFT) {
		return CalcState(button.x, button.y, false);
	}
	return state;
}

void Button::DrawTo(SDL_Surface* const dest) {
	image.DrawTo(dest, x, y);
	font.DrawStringTo(text, dest, textX + x, textY + y);
}

std::string Button::SetText(std::string t) {
	//one line, cache the position
	text = t;
	textX = (image.GetClipW() / 2) - (font.GetCharW() * text.size() / 2);
	textY = (image.GetClipH() / 2) - (font.GetCharH() / 2);
	return text;
}

Button::State Button::CalcState(Sint16 i, Sint16 j, bool leftPressed) {
	if (i < x || i > (x + image.GetClipW()) ||
		j < y || j > (y + image.GetClipH())
		) {
		image.SetClipY(0);
		return state = State::NORMAL;
	}
	if (leftPressed) {
		image.SetClipY(image.GetClipH()*2);
		return state = State::PRESSED;
	}
	else {
		image.SetClipY(image.GetClipH());
		return state = State::HOVER;
	}
}
