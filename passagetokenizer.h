/*
 * passagetokenizer.h
 *
 *  Created on: Sep 19, 2018
 *      Author: sawan
 */

#ifndef PASSAGETOKENIZER_H_
#define PASSAGETOKENIZER_H_

#include "sectiontoken.h"
#include <string>
using namespace std;


class PassageTokenizer{
	public:
		PassageTokenizer(string str);
		bool hasNextSection();
		SectionToken nextSection();
	private:
		string passage = "";
		int currLoc;
};



#endif /* PASSAGETOKENIZER_H_ */
