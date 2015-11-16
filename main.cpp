/******Developer notes******

Cbot is an *intelligent* chatting bot. Cbot is designed to make conversation based on sentence structure utilizing a knowledge database.

*/

/// TODO: Create logic conditionals for the sentence types in think.cpp ...

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sqlite3.h>
#include <sqldatabase.h>
#include <converse.h>
#include <think.h>

using namespace std;

int main()
{
    vector<word> sentence;
    bool userLeaving = false;

    //Initial greeting, maybe move this into converse.h
    cout << "Hello world, I am cbot!" << endl;
    cout << "I have been designed to enjoy conversations, say whatever's on your mind!" << endl;

    do
    {
        //Get the user sentence and place into vector
        getUserSentence(sentence);

        cout << sentence.size();

        ///Determine the sentence type utilizing a database of vocabulary
        parseSentence(sentence);

        //Function to structure a response here

        //Function to output a response here
        /*
        for(int i = 0; i < sentence.size(); i++)
        {
            cout << sentence.at(i).type;
        }
        */

        ///PLACE THIS SOMEWHERE ELSE, IT IS UGLY!!!
        sentence.clear();
    }
    while(!userLeaving);

    return 0;
}
