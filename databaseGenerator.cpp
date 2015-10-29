#include <iostream>
#include <string>
#include <C:\Users\Arjan\codeblocks\sqlite3\sqlite3.h>
#include <fstream>
using namespace std;

void databaseGenerator();

int makeDatabase()
{
	databaseGenerator();
	return 0;
}

void databaseGenerator()
{
        //Connect to the database, limited to old style c code by the sqlite
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
		cout << "Writing files into the database!" << endl;

		ifstream inputFile;
		inputFile.open("input.txt");

                //nouns, pronouns, verbs, adjectives, adverbs, prepositions$


        }
        //Close the connection now that we are done with it.
        sqlite3_close(db);

}
