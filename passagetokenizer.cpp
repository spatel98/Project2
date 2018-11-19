/*
 * passagetokenizer.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: sawan
 */

#include <iostream>
#include <string>
using namespace std;

#include "passagetokenizer.h"


PassageTokenizer::PassageTokenizer(string str){
	passage = passage + str;
	currLoc = passage.find(">") + 1;
}

bool PassageTokenizer:: hasNextSection(){
	if(passage.find("[[", currLoc) != string::npos){
		return true;
	}else if(passage.find("(set:", currLoc) != string::npos){
		return true;
	}else if(passage.find("(if:", currLoc) != string::npos){
		return true;
	}else if(passage.find("(else:", currLoc) != string::npos){
		return true;
	}else if(passage.find("(else-if:", currLoc) != string::npos){
		return true;
	}else if(passage.find("(go-to:", currLoc) != string::npos){
		return true;
	}else if(passage.substr(currLoc, 1) != "<"){
		return true;
	}else{
		return false;
	}
}

SectionToken PassageTokenizer:: nextSection(){
	int tempLoc;
	secType_t tempType;

	if(passage.substr(currLoc, 2) == "[["){
		tempType = LINK;
		tempLoc = currLoc;
		currLoc = passage.find("]]", tempLoc) + 2;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.substr(currLoc, 5) == "(set:"){
		tempType = SET;
		tempLoc = currLoc;
		currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.substr(currLoc, 4) == "(if:"){
		tempType = IF;
		tempLoc = currLoc;
		currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.substr(currLoc, 6) == "(else:"){
		tempType = ELSE;
		tempLoc = currLoc;
		currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.substr(currLoc, 9) == "(else-if:"){
		tempType = ELSEIF;
		tempLoc = currLoc;
		currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.substr(currLoc, 7) == "(go-to:"){
		tempType = GOTO;
		tempLoc = passage.find("(go-to:", currLoc);
		currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else if((passage.substr(currLoc, 1) != "(") && (passage.substr(currLoc, 1) != "[")){
		tempType = TEXT;
		tempLoc = currLoc;
		if ((passage.find("(", currLoc) == string::npos) && (passage.find("[", currLoc) == string::npos)){
			currLoc = passage.find("<", currLoc);
		}else if(passage.find("(", currLoc) < passage.find("[", currLoc)){
			currLoc = passage.find("(", currLoc);
		}else{
			currLoc = passage.find("[", currLoc);
		}
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}else{
		tempType = BLOCK;
		tempLoc = currLoc;
		while(passage.find("[[", currLoc) != string::npos && (passage.find("[[", currLoc) < passage.find("]", currLoc))){
			currLoc = passage.find("]]", currLoc) + 2;
			while((passage.find("(if:", currLoc) < passage.find("]", currLoc) && passage.find("(if:", currLoc) != string::npos) || (passage.find("(else-if:", currLoc) < passage.find("]", currLoc) && passage.find("else-if:", currLoc) != string::npos) || (passage.find("(else:", currLoc) < passage.find("]", currLoc) && passage.find("else:", currLoc) != string::npos)){
				currLoc = passage.find("[", currLoc) + 1;
				while(passage.find("[[", currLoc) != string::npos && (passage.find("[[", currLoc) < passage.find("]", currLoc))){
					currLoc = passage.find("]]", currLoc) + 2;
				}
				currLoc = passage.find("]", currLoc) + 1;
			}
		}
		while((passage.find("(if:", currLoc) < passage.find("]", currLoc) && passage.find("(if:", currLoc) != string::npos) || (passage.find("(else-if:", currLoc) < passage.find("]", currLoc) && passage.find("else-if:", currLoc) != string::npos) || (passage.find("(else:", currLoc) < passage.find("]", currLoc) && passage.find("else:", currLoc) != string::npos)){
			currLoc = passage.find("[", currLoc) + 1;
			while(passage.find("[[", currLoc) != string::npos && (passage.find("[[", currLoc) < passage.find("]", currLoc))){
				currLoc = passage.find("]]", currLoc) + 2;
			}
			currLoc = passage.find("]", currLoc) + 1;
			while(passage.find("[[", currLoc) != string::npos && (passage.find("[[", currLoc) < passage.find("]", currLoc))){
				currLoc = passage.find("]]", currLoc) + 2;
			}
		}
		
		currLoc = passage.find("]", currLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, currLoc - tempLoc), tempType);
		return obj;
	}
}

//********************************************************ROUGH WORK**************************************************************

/*
 PassageTokenizer::PassageTokenizer(string str){
	passage = str;
	set_currLoc = 0;
	link_currLoc = 0;
	if_currLoc = 0;
	else_currLoc = 0;
	elseif_currLoc = 0;
	goto_currLoc = 0;
	text_currLoc = passage.find(">") + 1;
	block_currLoc = passage.find(">") + 1;
}

bool PassageTokenizer:: hasNextSection(){
	if(passage.find("[[", link_currLoc) != string::npos){
		return true;
	}else if(passage.find("(set:", set_currLoc) != string::npos){
		return true;
	}else if(passage.find("(if:", if_currLoc) != string::npos){
		return true;
	}else if(passage.find("(else:", else_currLoc) != string::npos){
		return true;
	}else if(passage.find("(else-if:", elseif_currLoc) != string::npos){
		return true;
	}else if(passage.find("(go-to:", goto_currLoc) != string::npos){
		return true;
	}else if(passage.substr(text_currLoc, 1) != "<"){
		return true;
	}else if(passage.substr(block_currLoc, 1) != "<"){
		return true;
	}else{
		return false;
	}
}

SectionToken PassageTokenizer:: nextSection(){
	int tempLoc;
	secType tempType;
	SectionToken emptyObj("", EMPTY);

	if(passage.find("[[", link_currLoc) != string::npos){
		tempType = LINK;
		tempLoc = passage.find("[[", link_currLoc);
		link_currLoc = passage.find("]]", tempLoc) + 2;
		SectionToken obj(passage.substr(tempLoc, link_currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.find("(set:", set_currLoc) != string::npos){
		tempType = SET;
		tempLoc = passage.find("(set:", set_currLoc);
		set_currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, set_currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.find("(if:", if_currLoc) != string::npos){
		tempType = IF;
		tempLoc = passage.find("(if:", if_currLoc);
		if_currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, if_currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.find("(else:", else_currLoc) != string::npos){
		tempType = ELSE;
		tempLoc = passage.find("(else:", else_currLoc);
		else_currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, else_currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.find("(else-if:", elseif_currLoc) != string::npos){
		tempType = ELSEIF;
		tempLoc = passage.find("(else-if:", elseif_currLoc);
		elseif_currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, elseif_currLoc - tempLoc), tempType);
		return obj;
	}else if(passage.find("(go-to:", goto_currLoc) != string::npos){
		tempType = ELSE;
		tempLoc = passage.find("(go-to:", goto_currLoc);
		goto_currLoc = passage.find(")", tempLoc) + 1;
		SectionToken obj(passage.substr(tempLoc, goto_currLoc - tempLoc), tempType);
		return obj;
	}
	
	while((passage.substr(text_currLoc, 1) == "(") || (passage.substr(text_currLoc, 1) == "[")){
		tempType = TEXT;
		if(passage.substr(text_currLoc, 5) == "(set:"){
			tempLoc = passage.find("(set:", text_currLoc);
			text_currLoc = passage.find(")", tempLoc) + 1;
		}else if(passage.substr(text_currLoc, 7) == "(go-to:"){
			tempLoc = passage.find("(go-to:", text_currLoc);
			text_currLoc = passage.find(")", tempLoc) + 1;
		}else if (passage.substr(text_currLoc, 4) == "(if:"){
			tempLoc = passage.find("(if:", text_currLoc);
			text_currLoc = passage.find(")", tempLoc) + 1;
		}else if (passage.substr(text_currLoc, 9) == "(else-if:"){
			tempLoc = passage.find("(else-if:", text_currLoc);
			text_currLoc = passage.find(")", tempLoc) + 1;
		}else if (passage.substr(text_currLoc, 6) == "(else:"){
			tempLoc = passage.find("(else:", text_currLoc);
			text_currLoc = passage.find(")", tempLoc) + 1;
		}else if (passage.substr(text_currLoc, 2) == "[["){
			tempLoc = passage.find("[[", text_currLoc);
			text_currLoc = passage.find("]]", tempLoc) + 2;
		}
	}
	
	if((passage.substr(text_currLoc, 1) != "(") && (passage.substr(text_currLoc, 1) != "[")){
			tempType = TEXT;
			tempLoc = text_currLoc;
			if((passage.find("(", text_currLoc) == string::npos) && (passage.find("[", text_currLoc) == string::npos)){
				text_currLoc = passage.find("<", text_currLoc);
			}else if(passage.find("(", text_currLoc) < passage.find("[", text_currLoc)){
				text_currLoc = passage.find("(", text_currLoc);
			}else{
				text_currLoc = passage.find("[", text_currLoc);
			}
			SectionToken obj(passage.substr(tempLoc, text_currLoc - tempLoc), tempType);
			return obj;
	}
	
	else{
		return emptyObj;
	}
}
*/
