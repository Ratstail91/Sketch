/* File Name: region.h
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
#ifndef KR_REGION_H_
#define KR_REGION_H_

#include "SDL.h"

class Region {
public:
	Region();
	~Region();

	void Load		(Uint32 x, Uint32 y, Uint32 l);
	void Unload		();
	bool IsLoaded	();

	Uint32 GetTile(Uint32 x, Uint32 y, Uint32 l);
	Uint32 SetTile(Uint32 x, Uint32 y, Uint32 l, Uint32 v);

	Uint32 GetXCount();
	Uint32 GetYCount();
	Uint32 GetLCount();

private:
	void GenArray();
	void ClrArray();

	Uint32 m_iXCount;
	Uint32 m_iYCount;
	Uint32 m_iLCount;

	Uint32*** m_pArray;
};

#endif
