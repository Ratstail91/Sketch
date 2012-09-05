/* File Name: tileset.h
 * Author: Kayne Ruse
 * Date: 28/8/2012
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
#ifndef KR_TILESET_H_
#define KR_TILESET_H_

#include <string>
#include "SDL.h"

//This is a basic file loading class

class Tileset {
public:
	Tileset();
	~Tileset();

	void Load		(std::string fname, Uint32 w, Uint32 h);
	void Unload		();
	bool IsLoaded	();

	std::string GetFileName();
	SDL_Surface* GetSurface();

	Uint32 GetXCount();
	Uint32 GetYCount();
	Uint32 GetWidth();
	Uint32 GetHeight();

	Uint32 GetCount();

private:
	std::string m_sFileName;
	SDL_Surface* m_pSurface;

	Uint32 m_iXCount;
	Uint32 m_iYCount;
	Uint32 m_iWidth;
	Uint32 m_iHeight;
};

#endif
