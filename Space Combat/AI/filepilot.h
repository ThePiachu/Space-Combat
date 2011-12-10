#ifndef FILEPILOT_H_
#define FILEPILOT_H_

#define NAMEHASHLENGTH 10

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "steeringpreferences.h"
#include "steering.h"
#include "steeringcontrol.h"
#include "pilot.h"

#define FILEPILOTSPEAK false

class filepilot
{
	random* myrandom;
	string tmppilot;
	vector<string> tmppilotv;
	float minscore;//minimum score the agent needs to get before it is saved
	string subfolder;//a string representing a subfolder that will be used by a particular mothership
public:
	filepilot(const float& MinScore=0.0):
		myrandom(random::getinstance()),
		tmppilot(),
		tmppilotv(),
		minscore(MinScore),
		subfolder("")
	{
	}
	~filepilot()
	{
	}


	pilot makepilotfromstring(const string& FilePilot)
	{
		return pilot(separatestrings(FilePilot));
	}


	string generatepilotname(const pilot* Pilot)
	{
		char Chars[100];
		string anwser;
		sprintf(Chars, "%f", Pilot->score);
		anwser+=Chars+string(" ");
		for(unsigned int i=0;i<NAMEHASHLENGTH;i++)
		{
			anwser+=myrandom->randomlowercasechar();
		}
		return anwser;
	}
	string generatepilotname(const pilot& Pilot)
	{
		char Chars[100];
		string anwser;
		sprintf(Chars, "%f", Pilot.score);
		anwser+=Chars+string(" ");
		for(unsigned int i=0;i<NAMEHASHLENGTH;i++)
		{
			anwser+=myrandom->randomlowercasechar();
		}
		return anwser;
	}
	/*void savepilot(const pilot& Pilot, const bool& PilotIsHarvester=false)
	{
		//cout<<"Saving pilot"<<endl<<flush;
		if(Pilot.score>minscore)
		{
			string path;

			fstream pathfile;
			pathfile.open("path.txt");
			if(pathfile.is_open())
			{
				getline(pathfile, path);
				pathfile.close();


				string filename=generatepilotname(Pilot)+string(".txt");
				ofstream pilotfile;
				pilotfile.open((path+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+filename).c_str(), ios::trunc);

				if(pilotfile.is_open())
				{
					pilotfile<<Pilot.print();
					//pilotfile<<string("foo");

					pilotfile.close();
					//pilotfile.open((path+string("bar.txt")).c_str(), ios::trunc);
					//pilotfile<<string("foo");
					//pilotfile.close();
				}
			}
		}
	}*/
	void savepilot(const pilot* Pilot, const bool& PilotIsHarvester=false)
	{
		if(FILEPILOTSPEAK)cout<<"filepilot::savepilot(const pilot* Pilot, const bool& PilotIsHarvester=false)"<<endl<<flush;
		if(Pilot!=NULL)if(Pilot->score>minscore)
		{
			if(FILEPILOTSPEAK)cout<<"if(Pilot!=NULL)if(Pilot->score>minscore)"<<endl<<flush;
			string path;

			fstream pathfile;
			pathfile.open("path.txt");
			if(pathfile.is_open())
			{
				if(FILEPILOTSPEAK)cout<<"if(pathfile.is_open())"<<endl<<flush;
				getline(pathfile, path);
				pathfile.close();

				string filename=generatepilotname(Pilot)+string(".txt");
				ofstream pilotfile;
				pilotfile.open((path+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+filename).c_str(), ios::trunc);

				if(pilotfile.is_open())
				{
					if(FILEPILOTSPEAK)cout<<"if(pilotfile.is_open())"<<endl<<flush;
					pilotfile<<Pilot->print();
					if(FILEPILOTSPEAK)cout<<"pilotfile<<Pilot->print();"<<endl<<flush;

					pilotfile.close();
				}
			}
		}
	}

	void testsavepilot()
	{
		pilot tmp=pilot::examplepilot();
		savepilot(&tmp);
	}
	vector<pilot>getxtoppilots(const unsigned int& NumberOfPilots=1, const bool& PilotIsHarvester=false)
	{
		vector<pilot>anwser;
		char Char[100];
		string tmp;
		fstream pathfile;
		ifstream listfile;
		string pilotpath;
		pathfile.open("path.txt");
		if(pathfile.is_open())
		{
			pathfile.getline(Char, 100);
			pilotpath+=Char;
			pathfile.close();
			//cout<<pilotpath<<endl<<flush;

			string batch1("@echo off");
			string batch2("del "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+"list.txt");
			string batch3("for /R "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+
					" %A in (*) do echo %A >> "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+"list.txt");


			system(batch1.c_str());
			system(batch2.c_str());
			system(batch1.c_str());
			system(batch3.c_str());

			listfile.open((pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+string("list.txt")).c_str());

			if(listfile.is_open())
			{

				if(listfile.eof())cout<<"No"<<endl<<flush;

				vector<pair<float, string> > pilotlist;

				getline(listfile,tmp);
				while(!listfile.eof())
				{
					pilotlist.push_back(pair<float, string>(getfloatfromfilepath(tmp), tmp));
					//cout<<pilotlist.back().first<<"**"<<tmp<<endl<<flush;
					getline(listfile,tmp);
				}
				listfile.close();
				sort(pilotlist.begin(), pilotlist.end());

				unsigned int end=NumberOfPilots;
				if (end>pilotlist.size())end=pilotlist.size();

				ifstream pilotfile;
				vector<string> pilotv;
				for(unsigned int i=0;i<end;i++)
				{
					pilotv.clear();
					pilotfile.clear();
					pilotfile.open(pilotlist.at(i).second.c_str());
					getline(pilotfile,tmp);
					while(!pilotfile.eof())
					{
						pilotv.push_back(tmp);
						getline(pilotfile,tmp);
					}
					pilotfile.close();
					//cout<<"pilotv.size() "<<pilotv.size()<<endl<<flush;
					anwser.push_back(pilot(pilotv));
				}
			}
		}
		return anwser;
	}
	bool unittest()
	{

		pilot tmp=pilot::examplepilot();


		if(tmp==makepilotfromstring(tmp.print()))
		{
			return true;
		}
		tmp.printme();
		makepilotfromstring(tmp.print()).printme();
		return false;
	}
	void setsubfolder(const unsigned int& ScenarioNumber, const unsigned int& R, const unsigned int& G, const unsigned int& B)
	{//a function that takes mothership's colour and uses it as a subfolder for storing private boids
		char Chars[10];
		subfolder="";
		itoa(ScenarioNumber, Chars, 10);
		subfolder+=string("scenario")+Chars;
		subfolder+="\\";
		switch(R)
		{
		case 0:
			subfolder+="0";
			break;
		case 1:
			subfolder+="1";
			break;
		case 2:
			subfolder+="2";
			break;
		}
		switch(G)
		{
		case 0:
			subfolder+="0";
			break;
		case 1:
			subfolder+="1";
			break;
		case 2:
			subfolder+="2";
			break;
		}
		switch(B)
		{
		case 0:
			subfolder+="0";
			break;
		case 1:
			subfolder+="1";
			break;
		case 2:
			subfolder+="2";
			break;
		}
		subfolder+="\\";
	}
	void compiledata(const bool& PilotIsHarvester=false)
	{//a function that gathers all data gathered into a single file
		vector<vector<string> >pilotsdata;

		char Char[100];
		string tmp;
		fstream pathfile;
		ifstream listfile;
		string pilotpath;
		pathfile.open("path.txt");
		if(pathfile.is_open())
		{
			pathfile.getline(Char, 100);
			pilotpath+=Char;
			pathfile.close();
			//cout<<pilotpath<<endl<<flush;

			string batch1("@echo off");
			string batch2("del "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+"list.txt");
			string batch3("for /R "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+
					" %A in (*) do echo %A >> "+pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+"list.txt");


			system(batch1.c_str());
			system(batch2.c_str());
			system(batch1.c_str());
			system(batch3.c_str());

			listfile.open((pilotpath+subfolder+(PilotIsHarvester?string("1\\"):string("0\\"))+string("list.txt")).c_str());

			if(listfile.is_open())
			{

				if(listfile.eof())cout<<"No"<<endl<<flush;

				getline(listfile,tmp);
				string tmppilotstring;
				vector<string> pilotlist;
				while(!listfile.eof())
				{
					pilotlist.push_back(tmp);
					getline(listfile,tmp);
				}
				listfile.close();


				ifstream pilotfile;
				vector<string> pilotv;
				if(pilotlist.size()>0)
				//for(unsigned int i=0;i<pilotlist.size();i++)
				{//getting labels for the data once
					pilotsdata.push_back(vector<string>());//creates a new entry for a pilot
					pilotv.clear();
					pilotfile.clear();
					pilotfile.open(pilotlist.at(0).c_str());
					getline(pilotfile,tmp);
					while(!pilotfile.eof())
					{//gathers pilot data
						//if (pilotsdata.back().empty())pilotsdata.back().push_back("\t");//making sure the data is properly aligned
						//else
						pilotsdata.back().push_back(string("\t")+tmp.substr(0, tmp.find('\t', 0)));
						getline(pilotfile,tmp);
					}
					pilotfile.close();
				}
				for(unsigned int i=0;i<pilotlist.size();i++)
				{
					pilotsdata.push_back(vector<string>());//creates a new entry for a pilot
					pilotv.clear();
					pilotfile.clear();
					pilotfile.open(pilotlist.at(i).c_str());
					getline(pilotfile,tmp);
					size_t tabposition;
					while(!pilotfile.eof())
					{//gathers pilot data
						tabposition=tmp.find('\t', 0);
						if (tabposition!=string::npos)
						{
							pilotsdata.back().push_back(tmp.substr(tabposition, string::npos));
						}
						else pilotsdata.back().push_back(string("\t"));
						getline(pilotfile,tmp);
					}
					pilotfile.close();
				}
				if(pilotsdata.size()>0)
				{
					ofstream anwserfile;
					anwserfile.open((pilotpath+subfolder+(PilotIsHarvester?string("1 - "):string("0 - "))+string(" report.txt")).c_str(), ios::trunc);

					if(anwserfile.is_open())
					{//saving all data together
						for(unsigned int j=0;j<pilotsdata.size();j++)
						{
							for(unsigned int i=0;i<pilotsdata.at(0).size();i++)
								anwserfile<<pilotsdata.at(j).at(i);
							anwserfile<<string("\n");
						}

						anwserfile.close();
					}
					else cout<<"!if(anwserfile.is_open())"<<endl<<flush;
				}
			}
		}
	}
};

#endif /* FILEPILOT_H_ */
