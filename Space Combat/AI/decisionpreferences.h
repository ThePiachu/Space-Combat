#ifndef DECISIONPREFERENCES_H_
#define DECISIONPREFERENCES_H_

#include "../math.h"
#include "../stringhandling.h"

class decisionpreferences
{//function to hold all preferences for decision making of the boid
public:
	float minloadp,//minimum load the boid will take before returning to base
			maxloadp;//load at which the boid will definately return to base
	float asteroidcolourweight,//how important is the colour of the asteroid
			asteroiddistanceweight,//how important is the distance to the asteroid
				maxboidsququetoasteroid,//the max number of boids that can dock the same asteroid
					infiniteasteroidweight;//whether the boid will prefer to mine infiniteasteroids or not
	float maxboidsququetoenemy,//how many boids does the agent think is enough to kill an enemy
			maxboidsququetoharvester;

	decisionpreferences
	(
		const float& MinLoad=0.3,
		const float& MaxLoad=0.8,
		const float& AsteroidColourWeight=-0.5,
		const float& AsteroidDistanceWeight=-0.5,
		const float& MaxBoidsQueueToAsteroid=3.0,
		const float& InfiniteAsteroidWeight=1.0,
		const float& MaxBoidsQueueToEnemy=5.0,
		const float& MaxBoidsQueueToHarvester=5.0
	):
		minloadp(MinLoad),
		maxloadp(MaxLoad),
		asteroidcolourweight(AsteroidColourWeight),
		asteroiddistanceweight(AsteroidDistanceWeight),
		maxboidsququetoasteroid(MaxBoidsQueueToAsteroid),
		infiniteasteroidweight(InfiniteAsteroidWeight),
		maxboidsququetoenemy(MaxBoidsQueueToEnemy),
		maxboidsququetoharvester(MaxBoidsQueueToHarvester)
	{
	}
	decisionpreferences
	(
		const decisionpreferences& Parent,
		const bool& Evolve=false
	):
		minloadp(evolve(Parent.minloadp, Evolve)),
		maxloadp(evolve(Parent.maxloadp, Evolve)),
		asteroidcolourweight(evolve(Parent.asteroidcolourweight, Evolve)),
		asteroiddistanceweight(evolve(Parent.asteroiddistanceweight, Evolve)),
		maxboidsququetoasteroid(evolve(Parent.maxboidsququetoasteroid, Evolve)),
		infiniteasteroidweight(evolve(Parent.infiniteasteroidweight, Evolve)),
		maxboidsququetoenemy(evolve(Parent.maxboidsququetoenemy, Evolve)),
		maxboidsququetoharvester(evolve(Parent.maxboidsququetoharvester, Evolve))
	{
	}
	decisionpreferences
	(
		const decisionpreferences& Parent,
		const bool& Evolve,
		const bool& SpecialEvolve
	)://function for selective evolution
		minloadp(evolve(Parent.minloadp, Evolve)),
		maxloadp(evolve(Parent.maxloadp, Evolve)),
		asteroidcolourweight(evolve(Parent.asteroidcolourweight, Evolve)),
		asteroiddistanceweight(evolve(Parent.asteroiddistanceweight, Evolve)),
		maxboidsququetoasteroid(evolve(Parent.maxboidsququetoasteroid, Evolve)),
		infiniteasteroidweight(evolve(Parent.infiniteasteroidweight, Evolve)),
		maxboidsququetoenemy(evolve(Parent.maxboidsququetoenemy, Evolve)),
		maxboidsququetoharvester(evolve(Parent.maxboidsququetoharvester, Evolve))
	{
	}
	decisionpreferences
	(
		const vector<string>& FileDecitionPreferences
	):
		minloadp(0.0),
		maxloadp(0.0),
		asteroidcolourweight(0.0),
		asteroiddistanceweight(0.0),
		maxboidsququetoasteroid(0.0),
		infiniteasteroidweight(0.0),
		maxboidsququetoenemy(0.0),
		maxboidsququetoharvester(0.0)
	{
		for(unsigned int i=0;i<FileDecitionPreferences.size();i++)
		{
			if(FileDecitionPreferences.at(i).find("minloadp")==0)
				minloadp=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("maxloadp")==0)
				maxloadp=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("asteroidcolourweight")==0)
				asteroidcolourweight=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("asteroiddistanceweight")==0)
				asteroiddistanceweight=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("maxboidsququetoasteroid")==0)
				maxboidsququetoasteroid=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("infiniteasteroidweight")==0)
				infiniteasteroidweight=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("maxboidsququetoenemy")==0)
				maxboidsququetoenemy=getfloat(FileDecitionPreferences.at(i));
			if(FileDecitionPreferences.at(i).find("maxboidsququetoharvester")==0)
				maxboidsququetoharvester=getfloat(FileDecitionPreferences.at(i));
		}
	}
	~decisionpreferences()
	{
	}
	decisionpreferences& operator()(const decisionpreferences& Parent,const bool& Evolve=false)
	{
		minloadp=evolve(Parent.minloadp, Evolve);
		maxloadp=evolve(Parent.maxloadp, Evolve);
		asteroidcolourweight=evolve(Parent.asteroidcolourweight, Evolve);
		asteroiddistanceweight=evolve(Parent.asteroiddistanceweight, Evolve);
		maxboidsququetoasteroid=evolve(Parent.maxboidsququetoasteroid, Evolve);
		infiniteasteroidweight=evolve(Parent.infiniteasteroidweight, Evolve);
		maxboidsququetoenemy=evolve(Parent.maxboidsququetoenemy, Evolve);
		maxboidsququetoharvester=evolve(Parent.maxboidsququetoharvester, Evolve);
		return *this;
	}
	string print()const
	{
		char Chars[100];
		string anwser("\ndecisionpreferences");

		sprintf(Chars, "%f", minloadp);
		anwser+=string("\nminloadp\t")+Chars;
		sprintf(Chars, "%f", maxloadp);
		anwser+=string("\nmaxloadp\t")+Chars;
		sprintf(Chars, "%f", asteroidcolourweight);
		anwser+=string("\nasteroidcolourweight\t")+Chars;
		sprintf(Chars, "%f", asteroiddistanceweight);
		anwser+=string("\nasteroiddistanceweight\t")+Chars;
		sprintf(Chars, "%f", maxboidsququetoasteroid);
		anwser+=string("\nmaxboidsququetoasteroid\t")+Chars;
		sprintf(Chars, "%f", infiniteasteroidweight);
		anwser+=string("\ninfiniteasteroidweight\t")+Chars;
		sprintf(Chars, "%f", maxboidsququetoenemy);
		anwser+=string("\nmaxboidsququetoenemy\t")+Chars;
		sprintf(Chars, "%f", maxboidsququetoharvester);
		anwser+=string("\nmaxboidsququetoharvester\t")+Chars;

		anwser+=string("\n~decisionpreferences\n");
		return anwser;
	}
	void printme()
	{
		cout<<"minloadp\t"<<minloadp<<endl<<flush;
		cout<<"maxloadp\t"<<maxloadp<<endl<<flush;
		cout<<"asteroidcolourweight\t"<<asteroidcolourweight<<endl<<flush;
		cout<<"asteroiddistanceweight\t"<<asteroiddistanceweight<<endl<<flush;
		cout<<"maxboidsququetoasteroid\t"<<maxboidsququetoasteroid<<endl<<flush;
		cout<<"infiniteasteroidweight\t"<<infiniteasteroidweight<<endl<<flush;
		cout<<"maxboidsququetoenemy\t"<<maxboidsququetoenemy<<endl<<flush;
		cout<<"maxboidsququetoharvester\t"<<maxboidsququetoharvester<<endl<<flush;
	}
	bool operator!=(const decisionpreferences& Other)const
	{
		return !operator==(Other);
	}
	bool operator==(const decisionpreferences& Other)const
	{
		return((minloadp==Other.minloadp)&&
		(maxloadp==Other.maxloadp)&&
		(asteroidcolourweight==Other.asteroidcolourweight)&&
		(asteroiddistanceweight==Other.asteroiddistanceweight)&&
		(maxboidsququetoasteroid==Other.maxboidsququetoasteroid)&&
		(infiniteasteroidweight==Other.infiniteasteroidweight)&&
		(maxboidsququetoenemy==Other.maxboidsququetoenemy)&&
		(maxboidsququetoharvester==Other.maxboidsququetoharvester));
	}
	bool unittest()
	{
		decisionpreferences tmp(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8);
		if(tmp==decisionpreferences(separatestrings(tmp.print())))
		{
			return true;
		}
		tmp.printme();
		decisionpreferences(separatestrings(tmp.print())).printme();
		return false;
	}
};

#endif /* DECISIONPREFERENCES_H_ */
