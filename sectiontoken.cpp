/*
 * sectiontoken.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: sawan
 */

#include "sectiontoken.h"
#include <string>
using namespace std;



SectionToken::SectionToken(string str, secType_t tempType){
	text = str;
	type = tempType;
}

secType_t SectionToken:: getType() const{
	return type;
}


