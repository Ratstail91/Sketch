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
#ifndef MAPTILE_HPP_
#define MAPTILE_HPP_

/* TODO: allow this to be modified (at runtime?), to allow *massive* maps
 * Could use a macro TILE_INVISIBLE defined as the maximum value for "value"'s type,
 * and thread it into the existing code. That way, this could be an unsigned char,
 * or even have a non-standard size (bit fields).
*/

struct MapTile {
	int value;
	//other metadata
};

#endif
