/******Developer notes******

Cbot is an *intelligent* chatting bot. Cbot is designed to make conversation based on sentence structure utilizing a knowledge database.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sqlite3.h>
#include <dbasemanager.h>
#include <converse.h>

using namespace std;

void sentenceParser(vector<string>);

//Used to place sql query results into wordTypes
static int parserCallback(void *data, int argc, char **argv, char **azColName);
vector<string> wordTypes;

int main()
{
	bool userLeaving = false;
	vector<string> userMessage;

	cout << "Hello world, I am cbot!" << endl;
	cout << "I have been designed to enjoy conversations, say whatever's on your mind!" << endl;

	do
	{
	    //Place the user sentence into vector userMessage
        userMessage = createVector(getUserSentence());
        wordTypes.resize(userMessage.size());

		//Determine the sentence type utilizing a database of vocabulary
		sentenceParser(userMessage);

		//Function to structure a response here

		//Function to output a response here


        userMessage.clear();
        wordTypes.clear();
	}while(!userLeaving);

	return 0;
}

void sentenceParser(vector<string> userMessage)
{
	sqlite3 *db;
    char *sql;
    char *zErrMsg = 0;
    int rc;
    const char* data;
    string word, queryStatement;

	//Connect to the database, limited to old style c code by the sqlite header file
	//sqlite_open returns true if it fails...
	if(sqlite3_open("vocabulary.db", &db))
	{
		cout << "Cant open database" << endl;
	}
	else
	{
		cout << "Opened database successfully" << endl;

		//Create a vector, for which the word position in the sentence correlates to the grammatic type
		for(int i = 0; i < userMessage.size(); i++)
        {
            word = userMessage.at(i);

            if(!ispunct(word.at(0)))
            {
                //query database tables for the word, and set the vector element = to the positive matches for type
                queryStatement = "SELECT    Type   FROM    Grammar  WHERE    Word =  '" + word + "'";
                //Create cstring version of sql statement so it can pass into the sql arguement
                int length = queryStatement.length() + 1;
                char charSQl[length];
                strcpy(charSQl, queryStatement.c_str());
                sql = charSQl;

                //Execute sql statement
                rc = sqlite3_exec(db, sql, parserCallback , (void*)data, &zErrMsg);
            }

            //Generate database from words.txt on special case that user input contains "GENDATA"
			if(word == "GENDATA")
            {
                generateDatabase();
            }
        }

	}

	sqlite3_close(db);
}

//Used to place sql query results into wordTypes
static int parserCallback(void *data, int argc, char **argv, char **azColName)
{
    int i;

    for(i=0; i<argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        wordTypes.at(i) = argv[i];
        cout << wordTypes.at(i) << endl;
    }

    return 0;
}
