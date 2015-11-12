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
    sentence Sentence;
    bool userLeaving = false;

    //Initial greeting, maybe move this into converse.h
    cout << "Hello world, I am cbot!" << endl;
    cout << "I have been designed to enjoy conversations, say whatever's on your mind!" << endl;

    do
    {
        //Get the user sentence and place into vector
        Sentence.word = createVector(getUserSentence());

        ///PLACE THIS SOMEWHERE ELSE, IT IS UGLY!!!
        Sentence.type.resize(Sentence.word.size());

        //Determine the sentence type utilizing a database of vocabulary
        parseSentence(Sentence);

        //Function to structure a response here

        //Function to output a response here

        ///PLACE THIS SOMEWHERE ELSE, IT IS UGLY!!!
        Sentence.word.clear();
        Sentence.type.clear();

    }
    while(!userLeaving);

    return 0;
}
