#ifndef THINK_H_INCLUDED
#define THINK_H_INCLUDED

#include <vector>
#include <string>
#include <wordstruct.h>

using namespace std;

void parseSentence(vector<word> &sentence);
static int select_callback(void* sentence, int argc, char **argv, char **azColName);

#endif // THINK_H_INCLUDED
