/*
 * passagetoken.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: sawan
 */

#include <iostream>
#include <string>
using namespace std;

#include "passagetoken.h"

PassageToken::PassageToken()
{
}

PassageToken::PassageToken(string str){
	text = str;
}

string PassageToken::getText() const{
	return text;
}
