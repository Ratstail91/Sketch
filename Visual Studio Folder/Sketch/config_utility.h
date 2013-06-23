/* File Name: config_utility.h
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
 *     Load and process configuration values from a file.
*/
#ifndef KR_CONFIGUTILITY_H_
#define KR_CONFIGUTILITY_H_ 2012062703

#include <map>
#include <string>

class ConfigUtility {
public:
	/* Public access members */
	void Load		(const char* szFileName);

	std::string String		(const char* szKey);
	const char* Cstring		(const char* szKey);
	int Integer				(const char* szKey);
	double Real				(const char* szKey);
	bool Boolean			(const char* szKey);

	std::string operator[]	(const char* szKey);
	std::string operator[]	(std::string sKey);

	std::map<std::string, std::string>* GetMap();

private:
	/* Private access members */
	std::map<std::string, std::string> m_vValues;
};

#endif
