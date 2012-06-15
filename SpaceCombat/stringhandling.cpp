#ifndef STRINGHANDLING_CPP_
#define STRINGHANDLING_CPP_
#include "stringhandling.h"
#include <stdlib.h>

string floatcharacters("-+1234567890.");



float getfloat(const string& String)
{
	size_t numberposition;
	float anwser=0.0;
	numberposition=String.find_first_of(floatcharacters);
	if (numberposition!=string::npos)
	{
		anwser=atof(String.substr(numberposition, string::npos).c_str());
	}
	//cout<<"getfloat of **"<<String<<"** equals to **"<<anwser<<"**"<<endl<<flush;
	return anwser;
}
float getfloatfromfilepath(const string& String)
{
	string tmp=String.substr(String.find_last_of('\\'), string::npos);
	size_t numberposition;
	float anwser=0.0;
	numberposition=tmp.find_first_of(floatcharacters);
	if (numberposition!=string::npos)
	{
		anwser=atof(tmp.substr(numberposition, string::npos).c_str());
	}
	//cout<<"getfloat of **"<<String<<"** equals to **"<<anwser<<"**"<<endl<<flush;
	return anwser;
}

int getint(const string& String)
{
	size_t numberposition;
	int anwser=0;
	numberposition=String.find_first_of(floatcharacters);
	if (numberposition!=string::npos)
	{
		anwser=atoi(String.substr(numberposition, string::npos).c_str());
	}
	//cout<<"getint of **"<<String<<"** equals to **"<<anwser<<"**"<<endl<<flush;
	return anwser;
}
vector<string> separatestrings(const string& String)
{
	size_t start=0, end=0;
	vector<string> anwser;
	do
	{
		end=String.find("\n", start+1);
		anwser.push_back(String.substr(start+1, end-(start+1)));
		start=end;
	}while(start!=string::npos);
	return anwser;
}
bool comparestringvestors(vector<string>&tmp1, vector<string>&tmp2)
{
	bool ok=true;
	if(tmp1.size()!=tmp2.size())
	{
		cout<<"tmp1.size()!=tmp2.size()"<<endl<<flush;
		cout<<tmp1.size()<<" vs "<<tmp2.size()<<endl<<flush;
		ok=false;
	}
	unsigned int i=0;
	for(i=0;(i<tmp1.size()&&i<tmp2.size());i++)
	{
		if(tmp1.at(i).compare(tmp2.at(i))!=0)
		{
			cout<<i<<" out of "<<tmp1.size()<<endl<<flush;
			cout<<"**"<<tmp1.at(i)<<"**"<<endl<<flush;
			cout<<"vs"<<endl<<flush;
			cout<<"**"<<tmp2.at(i)<<"**"<<endl<<flush;
			ok=false;
		}
	}
	if(i<tmp1.size())
	{
		cout<<"Excess tmp1:"<<endl<<flush;
		for(;i<tmp1.size();i++)
		{
			cout<<tmp1.at(i);
		}
	}
	if(i<tmp2.size())
	{
		cout<<"Excess tmp2:"<<endl<<flush;
		for(;i<tmp2.size();i++)
		{
			cout<<tmp2.at(i);
		}
	}
	return ok;
}

#endif //STRINGHANDLING_CPP_
