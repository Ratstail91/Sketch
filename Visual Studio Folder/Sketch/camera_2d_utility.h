/* File Name: camera_2d_utility.h
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
#ifndef KR_CAMERA2DUTILITY_H_
#define KR_CAMERA2DUTILITY_H_ 2012062701

#include "origin_2d.h"

class Camera2DUtility : public Origin2D {
public:
	/* Mode enum */
	enum Mode {
		_BEGIN = 0, //bounding

		NORMAL,
		CENTER,
//		TARGET,
		DISABLE,

		_END //bounding
	};

	/* Public access members */
	Camera2DUtility();

	int GetCamX();
	int GetCamY();

	/* Mode */
	Mode SetMode(Mode eMode);
	Mode GetMode();

	/* Screen size */
	void SetScreenSize	(int w, int h);
	int SetScreenWidth	(int w);
	int SetScreenHeight	(int h);

	int GetScreenWidth	();
	int GetScreenHeight	();

private:
	/* Private access members */
	Mode m_eMode;

	int m_iScreenW;
	int m_iScreenH;
};

#endif
