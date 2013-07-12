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
#ifndef TILESET_HPP_
#define TILESET_HPP_

#include "map_tile.hpp"

#include "SDL/SDL.h"

#include <vector>
#include <string>

class Tileset {
public:
	Tileset() = default;
	~Tileset() { FreeSurface(); }
	Tileset(SDL_Surface* s, Uint16 w, Uint16 h) { SetSurface(s, w, h); }

	void DrawTileTo(SDL_Surface* const dest, tile_t index, Sint16 x, Sint16 y);
	void DrawVectorTo(SDL_Surface* const dest, std::vector<std::vector<MapTile>>&, Sint16 x, Sint16 y);

	void LoadSurface(std::string s, Uint16 w, Uint16 h);
	void FreeSurface();

	//accessors and mutators
	SDL_Surface* SetSurface(SDL_Surface*, Uint16 w, Uint16 h);
	SDL_Surface* GetSurface() const { return surface; };

	Uint16 GetWidth() const { return width; };
	Uint16 GetHeight() const { return height; };

	std::string SetFileName(std::string s) { return fileName = s; }
	std::string GetFileName() const { return fileName; }

private:
	SDL_Surface* surface = nullptr;
	Uint16 width = 0, height = 0;
	std::string fileName;
};

#endif
