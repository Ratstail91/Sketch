/* File Name: image.h
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
 *     A wrapper for SDL_Surface, and it's rendering functionality.
*/
#ifndef KR_IMAGE_H_
#define KR_IMAGE_H_ 2012062701

#include "SDL.h"

class Image {
public:
	/* Public access members */
	Image();
	Image(const char* szFileName, int x=0, int y=0, int w=0, int h=0);
	Image(SDL_Surface* pSurface,  int x=0, int y=0, int w=0, int h=0);
	virtual ~Image();

	void LoadImage(const char* szFileName, int x=0, int y=0, int w=0, int h=0);
	void LoadImage(SDL_Surface* pSurface,  int x=0, int y=0, int w=0, int h=0);
	void UnloadImage();

	void SetColorKey(int iRed=255, int iGreen=0, int iBlue=255);
	void ClearColorKey();

	virtual void DrawTo(SDL_Surface* const, int iCamX=0, int iCamY=0);

	/* Accessors and mutators */
	void SetImagePosition(int x, int y);

	int SetImageX(int);
	int SetImageY(int);
	int SetImageW(int);
	int SetImageH(int);

	int GetImageX();
	int GetImageY();
	int GetImageW();
	int GetImageH();

	int SetSheetX(int);
	int SetSheetY(int);

	int GetSheetX();
	int GetSheetY();
	int GetSheetW();
	int GetSheetH();

	bool IsLoadedImage();
	bool IsLocalImage();

protected:
	/* Protected access members */
	SDL_Surface* SetSurface(SDL_Surface*);
	SDL_Surface* GetSurface();

private:
	/* Private access members */
	void Init();

	SDL_Rect m_sclip;
	SDL_Rect m_dclip;
	SDL_Surface* m_pSurface;
	bool m_bLocal;
};

#endif
