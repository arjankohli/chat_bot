#ifndef DBASEMANAGER_H_INCLUDED
#define DBASEMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

struct sentence
{
    vector<string> word;
    vector<string> type;
};

void verifySql(int rc, char *errorMsg);
void generateDatabase();
void execSelectQuery(sqlite3* db, sentence &Sentence);

#endif // DBASEMANAGER_H_INCLUDED
