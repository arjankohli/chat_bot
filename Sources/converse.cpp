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
vector<string> createVector(string string_userMessage)
{
    vector<string> vector_userMessage(1);

	for(unsigned strPos = 0, vectPos = 0; strPos < string_userMessage.length(); strPos++)
	{
		if(isalnum(string_userMessage.at(strPos)))
		{
			vector_userMessage.at(vectPos).push_back(tolower(string_userMessage.at(strPos)));
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

	return vector_userMessage;
}
