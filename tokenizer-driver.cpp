//============================================================================
// Name        : Project1.cpp
// Author      : Sawan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "storytokenizer.h"
#include <fstream>
#include <unordered_map>
#include <map>
using namespace std;

int main()
{
  string line, story;

  ifstream input;

  input.open("if2.html");

  if (!input.is_open())
  {
	  cout << "Could not open if.html";
	  return 1;
  }

  getline(input, line);
  while (input && line != "</html>")
  {
    story += line + '\n';
    getline(input, line);
  }
  unordered_map<string, bool> sets;

  unordered_map<string, PassageToken> passages;

  string firstPassage;

  StoryTokenizer st(story);
  int pass = 0;
  while (st.hasNextPassage())
  {
    PassageToken ptok = st.nextPassage();
    pass++;
    cout << "Passage " << pass << ":  " << ptok.getName() <<endl;

	passages.emplace(ptok.getName(), ptok);

	if (pass == 1)
		firstPassage = ptok.getName();

    PassageTokenizer pt(ptok.getText());
    while (pt.hasNextSection())
    {

      SectionToken stok = pt.nextSection();
      switch (stok.getType())
      {
      case LINK:
        cout << "  Link:  ";
        break;
      case SET:
	  {
		  cout << "  Set:  ";

		  string name = stok.getText().substr(6, stok.getText().find(' ',6) - 6);

		  int f = stok.getText().find("true");

		  bool c;
		  
		  if (f != string::npos)
		  {
			  c = true;
		  }
		  else
		  {
			  c = false;
		  }

		  sets.emplace(name, c);

		  break;
	  }
      case GOTO:
        cout << "  Go-to:  ";
        break;
      case IF:
        cout << "  If:  ";
        break;
      case ELSEIF:
        cout << "  Else-if:  ";
        break;
      case ELSE:
        cout << "  Else:  ";
        break;
      case BLOCK:
        cout << "  Block:  ";
        break;
      case TEXT:
        cout << "  Text:  ";
        break;
      default:
        cout << "  Unknown token:  ";
      }
      cout << stok.getText() << endl;
    }

  }

  PassageToken current = passages.at(firstPassage);

  PassageTokenizer t = PassageTokenizer(current.getText());

  while (t.hasNextSection())
  {
	  SectionToken s = t.nextSection();


  }



  for (auto it = passages.begin(); it != passages.end(); ++it)
  {
	  cout << it->first << "  " << it->second.getName() << endl;
  }

  while (true);
  return 0;
}
