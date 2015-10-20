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
#include <sqlite3.h>

using namespace std;

string getInput();
vector<string> inputFormatter(string);
void inputParser(vector<string>);

int main()
{
	bool userLeaving = false;
	vector<string> userMessage;

	cout << "Hello world, I am cbot!" << endl;
	cout << "I have been designed to enjoy conversations, say whatever's on your mind!" << endl;

	do
	{
		//Get the user input, and format the input into a vector dividing words and punctuation
		userMessage = inputFormatter(getInput());

		//Function to parse input here
		inputParser(userMessage);

		//Function to structure a response here

		//Function to output a response here
		for(unsigned i = 0; i < userMessage.size(); i++)
		{
			cout << userMessage[i] << ' ';
		}
	}while(!userLeaving);

	return 0;
}

string getInput()
{
	string inputString;

	getline(cin, inputString);

	return inputString;
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

void inputParser(vector<string> input)
{

}
