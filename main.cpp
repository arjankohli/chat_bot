/******Developer notes******

Cbot is an *intelligent* chatting bot. Cbot is designed to make conversation based on sentence structure utilizing a knowledge database.

First an input string is grabbed, formatted, broken into word segments and encased in sentence containers.
The sentences are then logically interpreted by  first matching the sentences to common sentence structures in English,
and then applying the words in context to develop a sentence meaning.
Then a response is formulated based on the sentence interpretation

Remember KISS
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <sqlite3>

using namespace std;

//vector< vector<string> > inputFormatter(string);
vector<string> inputFormatter(string);

//Move this elsewhere ASAP
bool userLeaving = false;

int main()
{
	string userInputStr;
	vector<string> formattedInput;

	cout << "Hello world, I am cbot!" << endl;
	cout << "I have been designed to enjoy conversations, say whatever's on your mind!" << endl;

	do
	{
		getline(cin, userInputStr);

		//Function to format the input into something usable here
		formattedInput = inputFormatter(userInputStr);

		//Function to parse input here
		//inputParser(formattedInput);

		//Function to structure a response here

		//Function to output a response here
		for(unsigned i = 0; i < formattedInput.size(); i++)
		{
			cout << formattedInput[i] << ' ';
		}
	}while(!userLeaving);

	return 0;
}

vector<string> inputFormatter(string userInputStr)
{
	vector<string> formattedInput(1);

	for(unsigned charPos = 0, wordPos = 0; charPos < userInputStr.length(); charPos++)
	{
		if(isalnum(userInputStr.at(charPos)))
		{
			formattedInput.at(wordPos).push_back(userInputStr.at(charPos));
		}
		else if(isspace(userInputStr.at(charPos)))
		{
			wordPos++;
			formattedInput.resize(wordPos + 1);
		}
		else if(ispunct(userInputStr.at(charPos)))
		{
			wordPos++;
			formattedInput.resize(wordPos + 1);
			formattedInput.at(wordPos).push_back(userInputStr.at(charPos));
		}
	}

	return formattedInput;
}
