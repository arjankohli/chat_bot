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

string getUserSentence();
void createVector(string _string_userMessage, vector<string> &vector_userMessage);
void sentenceParser(vector<string>);

static int callback(void *data, int argc, char **argv, char **azColName);
void verifySql(int rc, char *zErrMsg);
void generateDatabase();

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
		createVector(getUserSentence(), userMessage);

		//Determine the sentence type utilizing a database of vocabulary
		sentenceParser(userMessage);

		//Function to structure a response here

		//Function to output a response here
		for(unsigned i = 0; i < userMessage.size(); i++)
		{
			cout << userMessage[i] << ' ';
		}

	}while(!userLeaving);

	return 0;
}

string getUserSentence()
{
	string inputString;

	getline(cin, inputString);
	cin.ignore();

	return inputString;
}

//Given an input sentence, this function creates a vector from that sentence so it can be easily parsed.
void createVector(string string_userMessage, vector<string> &vector_userMessage)
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

void sentenceParser(vector<string> userMessage)
{
	sqlite3 *db;
    char *sql;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";
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
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                verifySql(rc, zErrMsg);
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


//This callback function is used to get data from sql SELECT statements
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

//Returns the status of the sql statement to the console screen
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

//Generates a database from words.txt
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
            insertStatement = "INSERT  INTO    Grammar VALUES('" + word + "', '" + type + "')";

            //Create cstring version of sql statement so it can pass into the sql arguement
            int length = insertStatement.length() + 1;
            char charSQl[length];
            strcpy(charSQl, insertStatement.c_str());
            sql = charSQl;

            //Execute sql statement
            rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            verifySql(rc, zErrMsg);
        }

        sqlite3_close(db);
    }
}
