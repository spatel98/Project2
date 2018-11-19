/*
 * sectiontoken.h
 *
 *  Created on: Sep 19, 2018
 *      Author: sawan
 */

#ifndef SECTIONTOKEN_H_
#define SECTIONTOKEN_H_

#include <string>
#include "passagetoken.h"
using namespace std;

enum secType_t{LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT, EMPTY};

class SectionToken : public PassageToken{
	public:
		SectionToken(string str, secType_t tempType);
		secType_t getType() const;
		
	private:
		//string section;
		secType_t type;
};

#endif /* SECTIONTOKEN_H_ */
