/*
 * storytokenizer.h
 *
 *  Created on: Sep 13, 2018
 *      Author: sawan
 */

#ifndef STORYTOKENIZER_H_
#define STORYTOKENIZER_H_

#include "sectiontoken.h"
#include "passagetokenizer.h"
#include "passagetoken.h"
#include <string>
#include <vector>
using namespace std;

class StoryTokenizer{
	public:
		StoryTokenizer(string str);
		bool hasNextPassage();
		PassageToken nextPassage();

	private:
		string story = "";
		int currLoc;
};

#endif /* STORYTOKENIZER_H_ */
