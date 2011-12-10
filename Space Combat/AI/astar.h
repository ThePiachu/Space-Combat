#ifndef ASTAR_H_
#define ASTAR_H_

#include "../math.h"
#include "../map.h"
#include "../stringhandling.h"

#include <iostream>
#include <vector>
#include <queue>
class mycomparison
{//a comparison class for comparing which node in the grid is closest to the goal
public:
	mycomparison()
	{
	}
	bool operator()
			(
				const pair<pair<float, float>, gridelement*>& One,
				const pair<pair<float, float>, gridelement*>& Two
			) const
	{
		return ((One.first.first+One.first.second)>(Two.first.first+Two.first.second));
	}
};


class astar
{//a class for pathfinding
	random* myrandom;//random class
	grid* mygrid;//pointer to the grid class

	float remainingdistanceweight;//how important the remaining distance is
	//float enemyshipweight;//how important are enemy ships
	//float neutralshipweight;//how important are neutral ships
	//float friendlyshipweight;//how important are friendly ships
	float shipweight;//how important are ships
	float asteroidweight;//how important are asteroids
	float covereddistanceweight;//how importatn is the distance alraedy traveled

public:
	astar
	(
		const float& RemainingDistanceWeight=1.0,
		const float& ShipWeight=0.1,
		const float& AsteroidWeight=0.5,
		const float& CoveredDistanceWeight=0.5
	):
		myrandom(random::getinstance()),
		mygrid(NULL),
		remainingdistanceweight(RemainingDistanceWeight),
		shipweight(ShipWeight),
		asteroidweight(AsteroidWeight),
		covereddistanceweight(CoveredDistanceWeight)
	{
	}
	astar
	(
		grid* Grid,
		const float& RemainingDistanceWeight=1.0,
		const float& ShipWeight=0.1,
		const float& AsteroidWeight=0.5,
		const float& CoveredDistanceWeight=0.5
	):
		myrandom(random::getinstance()),
		mygrid(Grid),
		remainingdistanceweight(RemainingDistanceWeight),
		shipweight(ShipWeight),
		asteroidweight(AsteroidWeight),
		covereddistanceweight(CoveredDistanceWeight)
	{
	}
	astar//inheritence
	(
		grid* Grid,
		const astar& Parent,
		const bool& Evolve=false
	):
		myrandom(random::getinstance()),
		mygrid(Grid),
		remainingdistanceweight(evolve(Parent.remainingdistanceweight, Evolve)),
		shipweight(evolve(Parent.shipweight, Evolve)),
		asteroidweight(evolve(Parent.asteroidweight, Evolve)),
		covereddistanceweight(evolve(Parent.covereddistanceweight, Evolve))
	{
	}
	astar//inheritence
	(
		grid* Grid,
		const astar& Parent,
		const bool& Evolve,
		const bool& SpecialEvolve
	)://function for selective evolution
		myrandom(random::getinstance()),
		mygrid(Grid),
		remainingdistanceweight(evolve(Parent.remainingdistanceweight, Evolve)),
		shipweight(evolve(Parent.shipweight, Evolve)),
		asteroidweight(evolve(Parent.asteroidweight, Evolve)),
		covereddistanceweight(evolve(Parent.covereddistanceweight, Evolve))
	{
	}
	astar//recreating from file
	(
		const vector<string>& FileAstar
	):
		myrandom(random::getinstance()),
		mygrid(NULL),
		remainingdistanceweight(0.0),
		shipweight(0.0),
		asteroidweight(0.0),
		covereddistanceweight(0.0)
	{
		for(unsigned int i=0;i<FileAstar.size();i++)
		{
			if(FileAstar.at(i).find("remainingdistanceweight")==0)
				remainingdistanceweight=getfloat(FileAstar.at(i));
			if(FileAstar.at(i).find("shipweight")==0)
				shipweight=getfloat(FileAstar.at(i));
			if(FileAstar.at(i).find("asteroidweight")==0)
				asteroidweight=getfloat(FileAstar.at(i));
			if(FileAstar.at(i).find("covereddistanceweight")==0)
				covereddistanceweight=getfloat(FileAstar.at(i));
		}
	}
	~astar()
	{
	}
	string print()const
	{
		char Chars[100];
		string anwser("\nastar");

		sprintf(Chars, "%f", remainingdistanceweight);
		anwser+=string("\nremainingdistanceweight\t")+Chars;
		sprintf(Chars, "%f", shipweight);
		anwser+=string("\nshipweight\t")+Chars;
		sprintf(Chars, "%f", asteroidweight);
		anwser+=string("\nasteroidweight\t")+Chars;
		sprintf(Chars, "%f", covereddistanceweight);
		anwser+=string("\ncovereddistanceweight\t")+Chars;

		anwser+=string("\n~astar\n");
		return anwser;
	}
	inline
	bool operator!=(const astar& Other)const
	{
		return !operator==(Other);
	}
	inline
	bool operator==(const astar& Other)const
	{
		return ((remainingdistanceweight==Other.remainingdistanceweight)&&
		(shipweight==Other.shipweight)&&
		(asteroidweight==Other.asteroidweight)&&
		(covereddistanceweight==Other.covereddistanceweight));
	}

	void setgrid(grid* Grid)
	{//setting the grid
		mygrid=Grid;
	}

	path randomdestination(const point& Start,const float& Spread, const point& RandomCenter=point())
	{//creates a path between the Start position
		//and a random position in space of a cube,
		//centered at Ranom Center with side of Spread
		point end(RandomCenter.movebyvector(myrandom->randomcubeposition(Spread)));
		return findpath(Start, end);
	}

	path randompath(const float& Spread, const point& RandomCenter=point())
	{//creates a path between
		//two random positions in space of a cube,
		//centered at Ranom Center with side of Spread
		point start(RandomCenter.movebyvector(myrandom->randomcubeposition(Spread)));
		point end(RandomCenter.movebyvector(myrandom->randomcubeposition(Spread)));
		return findpath(start, end);
	}




	path findpath(const point& Start, const point& End)
	{//function to find a path between two points
		vector<point> result;
		result.push_back(End);
		pair<float, gridelement*> tmpnode;
		vector<gridelement*> tmpnodes;

		//pair of pair of values equal to
		//first - obstacle value of the path taken
		//second - remaining distance to end node
		priority_queue<pair<pair<float, float>, gridelement*>,vector<pair<pair<float, float>, gridelement*> >,mycomparison> tochecknodelist;
		map<gridelement*, float> checkednodemap;//for reverse searching the nodes
		map<gridelement*, float>::iterator it;

		float nodeobstaclevalue=0.0;
		float tmpnodeobstaclevalue=0.0;

		gridelement* endnode(mygrid->forcefindgridelement(End));//node the end point is in
		gridelement* startnode(mygrid->forcefindgridelement(Start));//node the starting point is in

		tmpnode.first=0.0;
		tmpnode.second=startnode;
		unsigned int i=0;



		checkednodemap.insert
		(
			pair<gridelement*, float>
			(startnode, 0)
		);
		while(tmpnode.second!=endnode)
		{
			nodeobstaclevalue=tmpnode.first;

			/*nodeobstaclevalue=tmpnode.first
								+enemyshipweight*tmpnode.second->enemyshipnumber()
								+neutralshipweight*tmpnode.second->neutralshipsnumber()
								+friendlyshipweight*tmpnode.second->friendlyshipnumber()
								+asteroidweight*tmpnode.second->asteroidvolume();*/


			tmpnodes=tmpnode.second->giveneighbours();//gets all the neighbours of the node

			for(i=0;i<tmpnodes.size();i++)
			{//adds all neighbours to the list to be checked
				//the obstacle value of the next node is dependant on everything inside it (the more objects, the harder to move through),
				//plus the obstacle value of the previous node, plus the distance between the nodes
				tmpnodeobstaclevalue=
					nodeobstaclevalue
					+shipweight*tmpnodes.at(i)->shipnumber()
					+asteroidweight*tmpnodes.at(i)->asteroidvolume()
					+covereddistanceweight*tmpnode.second->center.distanceto(tmpnodes.at(i)->center);//distance
				if ((it=checkednodemap.find(tmpnodes.at(i)))==checkednodemap.end())
				{//if the node wasn`t checked previously, it is inserted
					tochecknodelist.push
					(
						pair<pair<float, float>, gridelement*>
						(
							pair<float, float>
							(
									tmpnodeobstaclevalue, tmpnodes.at(i)->center.distanceto(End)*remainingdistanceweight
							),
							tmpnodes.at(i)
						)
					);
					checkednodemap.insert
					(
						pair<gridelement*, float>
						(tmpnodes.at(i), tmpnodeobstaclevalue)
					);
				}
				else
				{//otherwise, if it is accessed by better route, the better value is stored
					if(it->second>tmpnodeobstaclevalue)it->second=tmpnodeobstaclevalue;
				}
			}
			checkednodemap.insert
				(
					pair<gridelement*, float>
					(tmpnode.second, tmpnode.first)
				);
			tmpnode.first=tochecknodelist.top().first.first;
			tmpnode.second=tochecknodelist.top().second;
			tochecknodelist.pop();//gets the next node from the list of nodes to check
			mygrid->forceneighbours(tmpnode.second);//makes sure the node has all neighbours
		}

		while(tmpnode.second!=startnode)
		{//rolling back A* search
			tmpnodes=tmpnode.second->giveneighbours();
			for(i=0;i<tmpnodes.size();i++)
			{//checks all neighbours
				it=checkednodemap.find(tmpnodes.at(i));
				if (it!=checkednodemap.end())
				{//if element was searched using A*
					if(it->second<tmpnode.first)
					{//choosing the better node to go to
						tmpnode.first=it->second;
						tmpnode.second=it->first;
					}
				}
			}
			result.push_back(tmpnode.second->center);
		}
		result.pop_back();//truncates the path from the begining to make it smoother
		result.push_back(Start);//insterts the start point into the path

		return -path(result);//returns a proper path
	}
	inline
	void setasteroidweight(const float& NewAsteroidWeight=0.5)
	{
		asteroidweight=NewAsteroidWeight;
	}
	astar& operator=(const astar& Other)
	{
		remainingdistanceweight=Other.remainingdistanceweight;
		shipweight=Other.shipweight;
		asteroidweight=Other.asteroidweight;
		covereddistanceweight=Other.covereddistanceweight;
		return *this;
	}
	bool unittest()
	{
		astar tmp(0.0, 1.0, 0.3, 0.4);
		if(tmp==astar(separatestrings(tmp.print())))
		{
			return true;
			//cout<<"YESS!"<<endl<<endl<<flush;
			//cout<<tmp.print()<<endl;
			//cout<<endl<<"VS"<<endl<<endl<<flush;
			//cout<<astar(separatestrings(tmp.print())).print()<<endl<<flush;
		}
		return false;
	}
};

#endif /* ASTAR_H_ */
