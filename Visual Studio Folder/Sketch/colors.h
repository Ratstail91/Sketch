/* File Name: colors.h
 * Author: Kayne Ruse
 * Date: 5/9/2012
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
#ifndef KR_COLORS_H_
#define KR_COLORS_H_

#include "SDL.h"

enum {
	//standard colours
	C_BLACK,
	C_WHITE,
	C_RED,
	C_GREEN,
	C_BLUE,

	//non-standard colours
	C_DGREY,
	C_MGREY,
	C_LGREY,

	C_HOTPINK,
	C_BEIGE,
};

extern SDL_Color colors[];

#define MapRGB(format, color) SDL_MapRGB(format, color.r, color.g, color.b)

#endif
