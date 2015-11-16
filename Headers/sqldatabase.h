#ifndef DBASEMANAGER_H_INCLUDED
#define DBASEMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

void verifySql(int rc, char *errorMsg);
void generateDatabase();

#endif // DBASEMANAGER_H_INCLUDED
