/* File Name: font.h
 * Author: Kayne Ruse
 * Date: 31/8/2012
 * Copyright: (c) Kayne Ruse 2012
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
 *
 * Description:
 *     ...
*/
#ifndef KR_FONT_H_
#define KR_FONT_H_

#include "SDL.h"

class Font {
public:
	Font();
	~Font();

	void Load(const char* fName, SDL_Rect fmt);
	void Unload();
	bool IsLoaded();

	void DrawString(SDL_Surface* pDest, const char* str, SDL_Rect pos);

	//OO breakers
	SDL_Surface* GetSurface() { return m_pSurface; }
	SDL_Rect* GetFormat() { return &m_fmt; }

private:
	SDL_Surface* m_pSurface;
	SDL_Rect m_fmt;
};

#endif
