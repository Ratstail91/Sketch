/* File Name: fps_utility.cpp
 * Author: Kayne Ruse
 * Date: 27/6/2012
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
 *     To calculate framerate and regulate game speed.
*/
#include <time.h>
#include "fps_utility.h"

//-------------------------
//Static members
//-------------------------

int FPSUtility::ms_iFrameRate = 0;
int FPSUtility::ms_iLastFrameRate = 0;
int FPSUtility::ms_iFrameTick = 0;
int FPSUtility::ms_iDeltaTime = 0;
int FPSUtility::ms_iDeltaTick = 0;

//-------------------------
//Public access members
//-------------------------

int FPSUtility::CalcFrameRate() {
	if (clock() - ms_iFrameTick >= CLOCKS_PER_SEC) {
		ms_iLastFrameRate = ms_iFrameRate;
		ms_iFrameRate = 0;
		ms_iFrameTick = clock();
	}
	ms_iFrameRate++;
	return ms_iLastFrameRate;
}

int FPSUtility::CalcDeltaTime() {
	ms_iDeltaTime = clock() - ms_iDeltaTick;
	ms_iDeltaTick = clock();
	return ms_iDeltaTime;
}

int FPSUtility::GetFrameRate() {
	return ms_iLastFrameRate;
}

int FPSUtility::GetDeltaTime() {
	return ms_iDeltaTime;
}
