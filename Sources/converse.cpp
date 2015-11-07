#include <converse.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string getUserSentence()
{
	string inputString;

	getline(cin, inputString);
	cin.ignore();

	return inputString;
}

//Given an input sentence, this function creates a vector from that sentence so it can be easily parsed.
void createVector(string string_userMessage, vector<string> vector_userMessage)
{
    vector_userMessage.clear();
    vector_userMessage.resize(1);

	for(unsigned strPos = 0, vectPos = 0; strPos < string_userMessage.length(); strPos++)
	{
		if(isalnum(string_userMessage.at(strPos)))
		{
			vector_userMessage.at(vectPos).push_back(string_userMessage.at(strPos));
		}
		else if(isspace(string_userMessage.at(strPos)))
		{
		    vectPos++;
			vector_userMessage.resize(vectPos + 1);
		}
		else if(ispunct(string_userMessage.at(strPos)))
		{
		    vectPos++;
			vector_userMessage.resize(vectPos + 1);
			vector_userMessage.at(vectPos).push_back(string_userMessage.at(strPos));
		}
	}
}
