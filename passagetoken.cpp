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

string PassageToken::getName() const
{
	int s = getText().find("name=\"")+6;
	
	int e = getText().find("\" ", s);

	

	return getText().substr(s,e-s);
}
