#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sqlite3.h>
#include <sqldatabase.h>

using namespace std;

/*
    Generates a sql database of words and their types from a text file.
    Types consist of:
        proper nouns, nouns, pronouns, verbs, adjectives, adverbs, prepositions, articles
*/
void generateDatabase()
{
    ifstream inputFile;
    inputFile.open("words.txt");

    string word, type, sql_insertStatement;

    sqlite3 *db;
    char *sql;
    char *errorMsg = 0;
    int rc;

    if(!inputFile)
    {
        cout << "Input file not found!" << endl;
    }
    else if(sqlite3_open("vocabulary.db", &db))
    {
        cout << "Can't open database!" << endl;
    }
    else
    {
        cout << "Opened database successfully" << endl;
        cout << "Writing files into the database!" << endl;

        //Create table inside database.
        sql = "CREATE TABLE IF NOT EXISTS Grammar(Word TEXT PRIMARY KEY    NOT NULL,Type TEXT    NOT NULL)";
        rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);
        verifySql(rc, errorMsg);

        //Populate the table with words and types
        while(inputFile >> word >> type)
        {
            sql_insertStatement = "INSERT  INTO    Grammar VALUES('" + word + "', '" + type + "')";

            //Create a cstring version of the sql statement so it can be passed to sqlite.h functions
            int length = sql_insertStatement.length() + 1;
            char charSQl[length];
            strcpy(charSQl, sql_insertStatement.c_str());
            sql = charSQl;

            //Execute sql statement
            rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);
        }

        sqlite3_close(db);
    }
}

/*
    Executes sql select statements against the vocabulary database and
    gets the corresponding type for the word.
*/
void execSelectQuery(sqlite3* db, sentence &Sentence)
{
    char *sql;
    char *errorMsg = 0;
    int rc;
    sqlite3_stmt *stmt;

    //Execute sql statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        throw string(sqlite3_errmsg(db));
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
    {
        string errmsg(sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        throw errmsg;
    }

    //Sentence.word[i] = reinterpret_cast< const char* >(sqlite3_column_text(stmt, 0));
    //Sentence.type[i] = reinterpret_cast< const char* >(sqlite3_column_text(stmt, 1));

    sqlite3_finalize(stmt);
}

//Displays the status of the sql statement to the console screen
void verifySql(int rc, char *errorMsg)
{
    if(rc != SQLITE_OK)
    {
        cout << "SQL Error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    else
    {
        cout << "Operation done successfully!" << endl;
    }
}
