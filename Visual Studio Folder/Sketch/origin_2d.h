/* File Name: origin_2d.h
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
 *     Handle position and motion on a 2D plane.
*/
#ifndef KR_ORIGIN2D_H_
#define KR_ORIGIN2D_H_ 2012062701

class Origin2D {
public:
	/* Public access members */
	Origin2D(float x = 0, float y = 0);

	virtual void Update(int iDelta);

	/* Positon in 2D */
	void SetOriginPosition		(float x, float y);
	float SetOriginX			(float x);
	float SetOriginY			(float y);

	void ShiftOriginPosition	(float x, float y);
	float ShiftOriginX			(float x);
	float ShiftOriginY			(float y);

	float GetOriginX			();
	float GetOriginY			();

	/* Motion in 2D */
	void SetMotion		(float x, float y);
	float SetMotionX	(float x);
	float SetMotionY	(float y);

	void ShiftMotion	(float x, float y);
	float ShiftMotionX	(float x);
	float ShiftMotionY	(float y);

	float GetMotionX	();
	float GetMotionY	();

	void StopMotion		();

private:
	/* Private access members */
	float m_fOriginX;
	float m_fOriginY;
	float m_fMotionX;
	float m_fMotionY;
};

#endif
