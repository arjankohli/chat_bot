#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sqlite3.h>
#include <sqldatabase.h>
#include <think.h>

void parseSentence(sentence &Sentence)
{
    sqlite3 *db;
    char *sql;
    char *errorMsg = 0;
    int length;
    string queryStatement;

    //Connect to the database
    if(sqlite3_open("vocabulary.db", &db))
    {
        cout << "Cant open database \"vocabulary.db\"" << endl;
    }
    else
    {
        //Create a vector which models the grammatic types of the sentence
        for(unsigned i = 0; i < Sentence.word.size(); i++)
        {
            if(Sentence.word.at(i) == "GENDATA")
            {
                generateDatabase();
            }
            else if(!ispunct(Sentence.word.at(i).at(0)))
            {
                //query database tables for the word
                queryStatement = "SELECT    Type   FROM    Grammar  WHERE    Word =  '" + Sentence.word.at(i) + "'";
                //Create cstring version of sql statement so it can pass into the sql arguement
                length = queryStatement.length() + 1;
                char charSQl[length];
                strcpy(charSQl, queryStatement.c_str());
                sql = charSQl;

                //Execute sql statement

            }
        }
    }

    sqlite3_close(db);
}
