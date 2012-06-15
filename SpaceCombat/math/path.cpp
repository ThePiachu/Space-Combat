#include "path.h"


	bool path::unittest()
	{
		vector <point> tmppoints;
		tmppoints.push_back(point(0.0, 0.0, 0.0));
		tmppoints.push_back(point(0.0, 1.0, 0.0));
		tmppoints.push_back(point(0.0, 0.0, 1.0));
		tmppoints.push_back(point(1.0, 0.0, 0.0));
		path testedpath(tmppoints);
		path testedpath2;
		testedpath2.addpoint(tmppoints.at(0));
		testedpath2.addpoint(tmppoints.at(1));
		testedpath2.addpoint(tmppoints.at(2));
		testedpath2.addpoint(tmppoints.at(3));

		point a, b;
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			a=testedpath.popfrontpoint();
			b=testedpath2.popfrontpoint();
			if (a==b)
			{
				//cout<<"popfrontpoint from initializations OK"<<endl<<flush;
			}
			else
			{
				cout<<"popfrontpoint initializations not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"popfrontpoint from initializations OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		testedpath.addpoints(tmppoints);
		testedpath2.addpoints(tmppoints);
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			a=testedpath.popfrontpoint();
			b=testedpath2.popfrontpoint();
			if (a==b)
			{
				//cout<<"popfrontpoint from addpoints OK"<<endl<<flush;
			}
			else
			{
				cout<<"popfrontpoint from addpoints not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"popfrontpoint from addpoints OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		testedpath.addpoints(tmppoints);
		testedpath2=-testedpath;
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			b=testedpath2.popfrontpoint();
			if (tmppoints.at(tmppoints.size()-1-i)==b)
			{
				//cout<<"popfrontpoint from -path OK"<<endl<<flush;
			}
			else
			{
				cout<<"popfrontpoint from -path not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"popfrontpoint from -path OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		line la, lb;
		testedpath.addpoints(tmppoints);
		testedpath2.addpoints(tmppoints);
		for (unsigned int i=0;i<tmppoints.size()-1;i++)//minus 1, since the last line popped will be a one point loop
		{
			la=testedpath.popfrontline();
			lb=line(tmppoints.at(i), tmppoints.at((i+1)%tmppoints.size()));
			if (la==lb)
			{
				//cout<<"popfrontline OK"<<endl<<flush;
			}
			else
			{
				cout<<"popfrontline not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"popfrontline OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		testedpath(tmppoints);
		testedpath2.addpoints(tmppoints);
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			a=testedpath.popfrontpoint();
			b=testedpath2.popfrontpoint();
			if (a==b)
			{
				//cout<<"operator() and addpoints OK"<<endl<<flush;
			}
			else
			{
				cout<<"operator() or addpoints not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"operator() and addpoints OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();


		testedpath(tmppoints);
		testedpath2(tmppoints);
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			la=testedpath.giveline(i);
			lb=line(tmppoints.at(i), tmppoints.at((i+1)%tmppoints.size()));
			if (la==lb)
			{

			}
			else
			{
				cout<<"giveline not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"giveline OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		testedpath(tmppoints);
		testedpath2(tmppoints);
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			la=testedpath.giveline(i);
			lb=testedpath.givelineloop(i+tmppoints.size());
			if (la==lb)
			{

			}
			else
			{
				cout<<"givelineloop not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"givelineloop OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		pathsegment sa, sb;
		testedpath(tmppoints);
		testedpath2(tmppoints);
		for (unsigned int i=0;i<tmppoints.size();i++)
		{
			sa=testedpath.givesegment(i);
			sb=testedpath.givesegmentloop(i+tmppoints.size());
			if (sa==sb)
			{

			}
			else
			{
				cout<<"givesegmentloop not OK"<<endl<<flush;
				return false;
			}
		}
		cout<<"givesegmentloop OK"<<endl<<flush;
		testedpath.clear();
		testedpath2.clear();

		cout<<"All OK"<<endl<<flush;
		return true;
	}
