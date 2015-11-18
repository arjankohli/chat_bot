#include <converse.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Gets an input string from the console and
    creates a vector from that sentence so it can be easily parsed.
*/
void getUserSentence(vector<word> &sentence)
{
	string inputString;
    int pos1, pos2;
    pos1 = pos2 = 0;
    word buffer;

    sentence.clear();

    getline(cin, inputString);

    while(pos1 < inputString.length())
    {
        pos2 = inputString.find(' ', pos1 + 1);

        if(pos2 == -1)
        {
            pos2 = inputString.length();i
        }

        buffer.name = inputString.substr(pos1, pos2 - pos1);

        if(buffer.name.find(' ') == -1)
        {
            sentence.push_back(buffer);
        }

        pos1 = pos2 + 1;
    }
}
