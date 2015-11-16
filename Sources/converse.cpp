#include <converse.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Gets an input string from the console and
    creates a vector from that sentence so it can be easily parsed.
*/
void getUserSentence(vector<word> &sentence)
{
	string inputString;

	getline(cin, inputString);

	sentence.resize(1);

	for(unsigned strPos = 0, vectPos = 0; strPos < inputString.length(); strPos++)
	{
		if(isalnum(inputString.at(strPos)))
		{
			sentence.at(vectPos).name.push_back(tolower(inputString.at(strPos)));
		}
		else if(isspace(inputString.at(strPos)))
		{
		    vectPos++;
			sentence.resize(vectPos + 1);
		}
		else if(ispunct(inputString.at(strPos)))
		{
		    vectPos++;
			sentence.resize(vectPos + 1);
			sentence.at(vectPos).name.push_back(inputString.at(strPos));
		}
	}
}
