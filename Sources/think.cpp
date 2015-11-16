#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sqlite3.h>
#include <sqldatabase.h>
#include <think.h>

/*
    Tests words in the sentence against the database to identify word types,
    test word types against conditionals to identify type of sentence,
    passover to a function that handles response.
*/
void parseSentence(vector<word> &sentence)
{
    sqlite3 *db;
    char *sql;
    int length;
    int rc;
    char *errorMsg = 0;
    string sql_selectStatement;
    void* point_Sentence = &sentence;

    //Connect to the database
    if(sqlite3_open("vocabulary.db", &db))
    {
        cout << "Cant open database \"vocabulary.db\"" << endl;
    }
    else
    {
        //Create a vector which models the grammatic types of the sentence
        for(unsigned i = 0; i < sentence.size(); i++)
        {
            if(sentence.at(i).name == "GENDATA")
            {
                generateDatabase();
            }
            else if(sentence.at(i).name != "." && sentence.at(i).name != "!" && sentence.at(i).name != "?")
            {
                sql_selectStatement = "SELECT Type FROM Grammar WHERE Word = '" + sentence.at(i).name + "'";
                //Create a cstring version of the sql statement so it can be passed to sqlite.h functions
                length = sql_selectStatement.length() + 1;
                char charSQl[length];
                strcpy(charSQl, sql_selectStatement.c_str());
                sql = charSQl;

                //Execute sql statement
                sqlite3_exec(db, sql, select_callback, point_Sentence, &errorMsg);

               // sentence.at(i).type = sql_selectStatement;
            }
        }

        //Perform logic conditionals against the sentence types
    }

    sqlite3_close(db);
}

static int select_callback(void* sentence, int argc, char **argv, char **azColName)
{
   int i;
   vector<word> Sentence = *((vector<word>*)sentence);

   //Sentence.at(i).type = argv[i];
   for(i=0; i<argc; i++){
      cout << azColName[i] << " " << argv[i];
   }

   return 0;
}
