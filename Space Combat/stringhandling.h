#ifndef STRINGHANDLING_H_
#define STRINGHANDLING_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

float getfloat(const string&);
int getint(const string&);
vector<string> separatestrings(const string&);
float getfloatfromfilepath(const string&);
bool comparestringvestors(vector<string>&tmp1, vector<string>&tmp2);


#endif /* STRINGHANDLING_H_ */
