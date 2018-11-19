/*
 * storytokenizer.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: sawan
 */

#include <iostream>
#include <string>
using namespace std;

#include "storytokenizer.h"

StoryTokenizer::StoryTokenizer(string str){
	story = story + str;
	currLoc = 0;
}

bool StoryTokenizer:: hasNextPassage(){
	if(story.find("<tw-passagedata", currLoc) != string::npos){
		return true;
	}else{
		return false;
	}
}

PassageToken StoryTokenizer:: nextPassage(){
	int tempLoc;

	tempLoc = story.find("<tw-passagedata", currLoc);
	currLoc = story.find("</tw-passagedata", tempLoc) + 16;

	PassageToken obj(story.substr(tempLoc, currLoc - tempLoc));
	return obj;
}

