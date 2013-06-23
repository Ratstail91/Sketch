/* File Name: config_utility.cpp
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
//#define _CRT_SECURE_NO_WARNINGS
#include <exception>
#include <fstream>
#include "config_utility.h"
using namespace std;

//-------------------------
//Public access members
//-------------------------

void ConfigUtility::Load(const char* szFileName) {
	ifstream is(szFileName);

	if (!is.is_open()) {
		string sWhat = "Failed to open config file for reading: ";
		sWhat += szFileName;
		throw(exception(sWhat.c_str()));
	}

	string sBufferOne;
	string sBufferTwo;

	for (;;) { //forever
		//discard newlines/blank lines w/ whitespace
		while(
				is.peek() == '\r' ||
				is.peek() == '\n' ||
				is.peek() == '\t' ||
				is.peek() == ' '
			)
			is.ignore();

		//end of file
		if (is.eof())
			break;

		//skip comment lines
		if (is.peek() == '#') {
			while( !(is.peek() == '\r' || is.peek() == '\n' || is.eof()) )
				is.ignore();
			continue;
		}

		//read in the pair
		getline(is, sBufferOne,'=');
		getline(is, sBufferTwo);

		//trim the strings at the start & end
		while(sBufferOne[0] == '\t' || sBufferOne[0] == ' ')
			sBufferOne.erase(0, 1); //probably not needed
		while(sBufferTwo[0] == '\t' || sBufferTwo[0] == ' ')
			sBufferTwo.erase(0, 1);
		while(sBufferOne[sBufferOne.size()-1] == '\t' || sBufferOne[sBufferOne.size()-1] == ' ')
			sBufferOne.erase(sBufferOne.end()-1);
		while(sBufferTwo[sBufferTwo.size()-1] == '\t' || sBufferTwo[sBufferTwo.size()-1] == ' ')
			sBufferTwo.erase(sBufferTwo.end()-1);

		//save the pair
		m_vValues[sBufferOne] = sBufferTwo;
	}

	is.close();
}

string ConfigUtility::String(const char* szKey) {
	return m_vValues[szKey];
}

const char* ConfigUtility::Cstring(const char* szKey) {
	return m_vValues[szKey].c_str();
}

int ConfigUtility::Integer(const char* szKey) {
	return atoi(m_vValues[szKey].c_str());
}

double ConfigUtility::Real(const char* szKey) {
	return atof(m_vValues[szKey].c_str());
}

bool ConfigUtility::Boolean(const char* szKey) {
	if (! _stricmp( m_vValues[szKey].c_str() , "true") )
		return true;

	if (! _stricmp( m_vValues[szKey].c_str() , "false") )
		return false;

	string sWhat = "Unknown boolean argument. Key: ";
	sWhat += szKey;
	sWhat += ", value: ";
	sWhat += m_vValues[szKey];
	throw(exception(sWhat.c_str()));
}

string ConfigUtility::operator[](const char* szKey) {
	return String(szKey);
}

string ConfigUtility::operator[](string sKey) {
	return String(sKey.c_str());
}

map<string, string>* ConfigUtility::GetMap() {
	return &m_vValues;
}
