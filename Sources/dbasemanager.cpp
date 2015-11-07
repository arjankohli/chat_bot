#include <dbasemanager.h>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

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
