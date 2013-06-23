/* File Name: camera_2d_utility.cpp
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
 *     Allow for dynamic (and smooth) movement of the camera on  2D plane.
*/
#include <exception>
#include "camera_2d_utility.h"

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_ORIGIN2D_H_ != 2012062701
#error Origin2D version is incompatible with Camera2DUtility
#endif

//-------------------------
//Public access members
//-------------------------

Camera2DUtility::Camera2DUtility() {
	m_eMode = NORMAL;
	m_iScreenW = 0;
	m_iScreenH = 0;
}

int Camera2DUtility::GetCamX() {
	switch(m_eMode) {
		case NORMAL: return -(int)GetOriginX();
		case CENTER: return -((int)GetOriginX() - (m_iScreenW/2));
//		case TARGET: //unknown
		case DISABLE: return 0;
		default: throw(std::exception("Invalid Camera Mode found"));
	}
}

int Camera2DUtility::GetCamY() {
	switch(m_eMode) {
		case NORMAL: return -(int)GetOriginY();
		case CENTER: return -((int)GetOriginY() - (m_iScreenH/2));
//		case TARGET: //unknown
		case DISABLE: return 0;
		default: throw(std::exception("Invalid Camera Mode found"));
	}
}

//-------------------------
//Mode
//-------------------------

Camera2DUtility::Mode Camera2DUtility::SetMode(Camera2DUtility::Mode eMode) {
	//possibility for a "position correction" here, that would prevent the "jump" when the mode is changed
	if (eMode <= _BEGIN || eMode >= _END) throw(std::exception("Invalid Camera Mode"));
	return m_eMode = eMode;
}

Camera2DUtility::Mode Camera2DUtility::GetMode() {
	return m_eMode;
}

//-------------------------
//Screen size
//-------------------------

void Camera2DUtility::SetScreenSize(int w, int h) {
	m_iScreenW = w;
	m_iScreenH = h;
}

int Camera2DUtility::SetScreenWidth(int w) {
	return m_iScreenW = w;
}

int Camera2DUtility::SetScreenHeight(int h) {
	return m_iScreenH = h;
}

int Camera2DUtility::GetScreenWidth() {
	return m_iScreenW;
}

int Camera2DUtility::GetScreenHeight() {
	return m_iScreenH;
}
