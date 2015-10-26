/******Developer notes******

Cbot is an *intelligent* chatting bot. Cbot is designed to make conversation based on sentence structure utilizing a knowledge database.

First an input string is grabbed, formatted, broken into word segments and encased in sentence containers.
The sentences are then logically interpreted by  first matching the sentences to common sentence structures in English,
and then applying the words in context to develop a sentence meaning.
Then a response is formulated based on the sentence interpretation

Remember KISS

For development in codeblocks use:
#include <C:\Users\Arjan\codeblocks\sqlite3\sqlite3.h>
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

	for(unsigned strPos = 0, vectPos = 0; strPos < userInputStr.length(); strPos++)
	{
		if(isalnum(userInputStr.at(strPos)))
		{
			formattedInput.at(vectPos).push_back(userInputStr.at(strPos));
		}
		else if(isspace(userInputStr.at(strPos)))
		{
			vectPos++;
			formattedInput.resize(vectPos + 1);
		}
		else if(ispunct(userInputStr.at(strPos)))
		{
			vectPos++;
			formattedInput.resize(vectPos + 1);
			formattedInput.at(vectPos).push_back(userInputStr.at(strPos));
		}
	}

	return formattedInput;
}

void inputParser(vector<string> input)
{
	//Connect to the database, limited to old style c code by the sqlite header file
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("vocabulary.db", &db);
	if(rc)
	{
		cout << "Cant open database:" << sqlite3_errmsg(db);
	}
	else
	{
		cout << "Opened database successfully" << endl;
		


	}
	//Close the connection now that we are done with it.
	sqlite3_close(db);
}
