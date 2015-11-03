/******Developer notes******

Cbot is an *intelligent* chatting bot. Cbot is designed to make conversation based on sentence structure utilizing a knowledge database.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <C:\Users\Arjan\codeblocks\sqlite3\sqlite3.h>

using namespace std;

string getInput();
vector<string> inputFormatter(string);
void inputParser(vector<string>);
static int callback(void *data, int argc, char **argv, char **azColName);
void verifySql(int rc, char *zErrMsg);
void generateDatabase();

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

		//Parse the input by determining the sentence type utilizing a database of vocabulary
		inputParser(userMessage);

		//Function to structure a response here

		//Function to output a response here
		for(unsigned i = 0; i < userMessage.size(); i++)
		{
			cout << userMessage[i] << ' ';
			if(userMessage[i] == "GENDATA")
            {
                generateDatabase();
            }
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

//Format the input into a vector
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

	//sqlite_open returns true if it fails...
	if(sqlite3_open("vocabulary.db", &db))
	{
		cout << "Cant open database" << endl;
	}
	else
	{
		cout << "Opened database successfully" << endl;


	}
	//Close the connection now that we are done with it.
	sqlite3_close(db);
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}

void verifySql(int rc, char *zErrMsg)
{
    if( rc != SQLITE_OK )
    {
        cout << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        cout << "Operation done successfully" << endl;
    }
}

void generateDatabase()
{
    //Variables needed to make sql_lite statements
    //*limited to c-strings by the sqlite header files
    sqlite3 *db;
    char *sql;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";

    ifstream inputFile;
    inputFile.open("words.txt");
    string word, type, insertStatement;

    //Connect to the database
    if(sqlite3_open("vocabulary.db", &db))
    {
        cout << "Cant open database!" << endl;
    }
    else if(!inputFile)
    {
        cout << "Input File not found!" << endl;
    }
    else
    {
        cout << "Opened database successfully" << endl;
        cout << "Writing files into the database!" << endl;

        //Create table if it does not exist.
        sql = "CREATE TABLE IF NOT EXISTS Grammar(Word TEXT PRIMARY KEY    NOT NULL,Type TEXT    NOT NULL)";
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
        verifySql(rc, zErrMsg);

        //proper nouns, nouns, pronouns, verbs, adjectives, adverbs, prepositions, articles
        while(inputFile >> word >> type)
        {
            //Check for if the word + type exists, and if not create an entry for that word + type
            insertStatement = "INSERT  INTO    Grammar VALUES ('" + word + "', '" + type + "')";

            //Create cstring version of sql statement so it can pass into the sql arguement
            int length = insertStatement.length() + 1;
            char charSQl[length];
            strcpy(charSQl, insertStatement.c_str());
            sql = charSQl;

            //Execute sql statement
            rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            verifySql(rc, zErrMsg);
        }

        //Close the connection now that we are done with it.
        sqlite3_close(db);
    }
}
