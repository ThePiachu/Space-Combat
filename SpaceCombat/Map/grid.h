#ifndef GRID_H_
#define GRID_H_

#include "../math.h"
//#include "../boid.h"

#include "asteroid.h"
#include "ship.h"
#include "mothership.h"

#include <map>
#include <vector>
#include <iostream>
using namespace std;

//#define MAXAGE 500.0
#define MAXAGE 100.0

#include "gridelement.h"

//TODO: make sure subgris aren`t expanding for no reason, as in, if enemy ships are moving out current grid range etc


class grid
{
public:
	//for use of metagrid
	vector <asteroid*> allasteroids;//TODO: implement allasteroids with metagrid
	vector <mothership*> allmotherships;//TODO: implement?
	vector <pair<colour, grid*> > subgrids;


	//for normal use
	grid* metagrid;//pointer to metagrid
	map<point, gridelement, pointcompare> gridmap;
	float sidelength;
	colour mothershipcolour;//to be used as distinction for the grids
	grid(const float& GridElementSideLength=2.0):
		allasteroids(),
		allmotherships(),
		subgrids(),
		metagrid(NULL),
		gridmap(),
		sidelength(GridElementSideLength),
		mothershipcolour()
	{
	}
	grid(const colour& MothershipColour, grid* MetaGrid):
		allasteroids(),
		allmotherships(),
		subgrids(),
		//movedboids(),
		metagrid(MetaGrid),
		gridmap(),
		sidelength(MetaGrid->sidelength),
		mothershipcolour(MothershipColour)
	{
		MetaGrid->newgrid(mothershipcolour, this);
	}
	~grid()
	{
		if(metagrid!=NULL)removegrid(this);
	}

	void newgrid(const colour& MothershipColour, grid* NewGrid)
	{
		subgrids.push_back(pair<colour, grid*> (MothershipColour, NewGrid));
		if(metagrid!=NULL)metagrid->newgrid(MothershipColour, NewGrid);
	}
	void removegrid(grid* GridToRemove)
	{
		for(unsigned int i=0;i<subgrids.size();i++)
		{
			if(subgrids.at(i).second==GridToRemove)
			{
				subgrids.erase(subgrids.begin()+i);
				break;
			}
		}
		if(metagrid!=NULL)metagrid->removegrid(GridToRemove);
	}


	void preparegrid(const int& SizeInEachDirection=1, const point& Center=point(0.0, 0.0, 0.0));
	inline
	void drawme(const unsigned int Mode=0)const
	{
		map<point, gridelement>::const_iterator it;
		for (it=gridmap.begin();
				it!=gridmap.end();
				it++)
		{
			it->second.drawme(Mode);
		}
	}

	gridelement* addship(pair<colour, ship*> Ship)
	{
		if (Ship.second==NULL) return NULL;
		else
		{
			//cout<<"gridelement* addship(pair<colour, ship*> Ship)"<<endl<<flush;
			point tmppoint(Ship.second->position.approx(sidelength*2.0));
			map<point, gridelement, pointcompare>::iterator it;
			it=gridmap.find(tmppoint);
			if (it==gridmap.end())
			{//inserting new element dynamicly
				it=newgridelement(tmppoint);
			}
			//cout<<"before it->second.addship(Ship);"<<endl<<flush;
			it->second.addship(Ship);
			return &it->second;
		}
	}

	gridelement* addasteroid(asteroid* Asteroid)
	{
		//to be used by metagrid
		if (Asteroid==NULL) return NULL;
		else
		{
			allasteroids.push_back(Asteroid);
			for(unsigned int i=0;i<subgrids.size();i++)
			{
				subgrids.at(i).second->addasteroid(Asteroid);
			}
			return insertasteroidintogrid(Asteroid);
		}
	}
	gridelement* insertasteroidintogrid(asteroid* Asteroid)
	{
		if (Asteroid==NULL) return NULL;
		point tmppoint(Asteroid->position.approx(sidelength*2.0));
		map<point, gridelement, pointcompare>::iterator it;
		it=gridmap.find(tmppoint);
		if (it==gridmap.end())
		{//inserting new element dynamicly
			it=newgridelement(tmppoint);
		}
		it->second.addasteroid(Asteroid);
		return &it->second;
	}

	map<point, gridelement, pointcompare>::iterator newgridelement(const point& Index)
	{
		pair<map<point, gridelement, pointcompare>::iterator,bool> tmppair
			=gridmap.insert(
				pair<point, gridelement>
					(Index,
					gridelement(Index,
							sidelength)));
		if (tmppair.second)
		{
			map<point, gridelement, pointcompare>::iterator it;
			vector<point> missingneighbours(tmppair.first->second.givemissingneigbours());
			for (unsigned j=0;j<missingneighbours.size();j++)
			{
				it=gridmap.find(missingneighbours.at(j));
				if (it!=gridmap.end())
				{
					tmppair.first->second.addneighbour(it->second);
					it->second.addneighbour(tmppair.first->second);
				}
			}
			tmppair.first->second.setagefromneighbours();//makes sure the grid element won't stay too long if it is not refreshed
		}
		return tmppair.first;
	}
	inline
	point approximatepoint(const point& Point)const
	{
		return Point.approx(sidelength*2.0);
	}

	gridelement* findgridelement(const point& Point)
	{
		map<point, gridelement, pointcompare>::iterator it;
		it=gridmap.find(approximatepoint(Point));
		if (it==gridmap.end()) return NULL;
		else return &(it->second);
	}
	gridelement* forcefindgridelement(const point& Point)
	{
		map<point, gridelement, pointcompare>::iterator it;
		it=gridmap.find(approximatepoint(Point));
		if (it==gridmap.end())
		{
			preparegrid(1, Point);
			return &(gridmap.find(approximatepoint(Point))->second);
		}
		forceneighbours(&(it->second));
		return &(it->second);
	}
	vector<gridelement*> forcegiveneighbours(const point& Point)
	{
		map<point, gridelement, pointcompare>::iterator it;
		it=gridmap.find(approximatepoint(Point));
		vector<point> missingneighbours=it->second.givemissingneigbours();
		if (missingneighbours.empty()) return it->second.giveneighbours();
		else
		{
			addnodes(missingneighbours);
			return it->second.giveneighbours();
		}
	}


	void addnodes(vector <point> NodeIndexes)
	{
		vector<map<point, gridelement, pointcompare>::iterator> its;//list of new inserted elements
		pair<map<point, gridelement, pointcompare>::iterator,bool> tmppair;
		map<point, gridelement, pointcompare>::iterator it;//iterator
		point tmppoint;
		for (unsigned int i=0;i<NodeIndexes.size();i++)
		{
			tmppoint(NodeIndexes.at(i).approx(sidelength*2.0));
			tmppair=//tries inserting a new grid element into the grid
				gridmap.insert(
					pair<point, gridelement>
						(tmppoint,
						gridelement(tmppoint,
								sidelength)));
			if (tmppair.second)
			{//if true, means it is a new element
				its.push_back(tmppair.first);
			}//otherwise there already is an element like that
		}
		vector<point> missingneighbours;
		for (unsigned int i=0;i<its.size();i++)
		{
			missingneighbours=(*(its.at(i))).second.givemissingneigbours();
			//total+=missingneighbours.size();
			for (unsigned j=0;j<missingneighbours.size();j++)
			{
				it=gridmap.find(missingneighbours.at(j));
				if (it!=gridmap.end())
				{
					(*(its.at(i))).second.addneighbour(it->second);
					it->second.addneighbour((*(its.at(i))).second);
					it->second.setagefromneighbours();
				}
			}
		}
	}
	inline
	void forceneighbours(gridelement* Node)
	{//a function that makes sure the given node has all neighbours
		addnodes(Node->givemissingneigbours());
	}

	vector <pair<colour, ship*> > findships(const point& Position, const float& Range)
	{
		point approximatedpoint=approximatepoint(Position);
		point foundpoint;
		map<point, gridelement, pointcompare>::iterator it, tmpit;
		it=gridmap.find(approximatedpoint);
		vector <pair<colour, ship*> > anwser;

		unsigned int searchsize=(unsigned int)ceil(Range/sidelength);//calculates how far from the initial nodes to look for neighbouring boids

		vector<map<point, gridelement, pointcompare>::iterator> iteratorstocheck;
		map<point, map<point, gridelement, pointcompare>::iterator, pointcompare> checked;
		iteratorstocheck.push_back(it);
		checked.insert(pair<point, map<point, gridelement, pointcompare>::iterator>(it->first, it));

		for(unsigned int i=0;i<searchsize;i++)
		{
			if(!iteratorstocheck.empty())
			{
				it=iteratorstocheck.back();
				iteratorstocheck.pop_back();
				for(unsigned int j=0;j<it->second.neighbours.size();j++)
				{
					if(checked.find(it->first)==checked.end())
					{
						tmpit=gridmap.find(it->second.neighbours.at(j)->center);
						iteratorstocheck.push_back(tmpit);
						checked.insert
						(
								pair<point, map<point, gridelement, pointcompare>::iterator>
							(
								tmpit->first, tmpit
							)
						);
					}
				}
			}
		}
		map<point, map<point, gridelement, pointcompare>::iterator>::iterator checkedit;
		for(checkedit=checked.begin();checkedit!=checked.end();checkedit++)
		{
			anwser.insert(anwser.end(),checkedit->second->second.allships.begin(),checkedit->second->second.allships.end());
		}

		for (unsigned int i=0;i<anwser.size();i++)
		{
			if (Position.distanceto(anwser.at(i).second->position)>Range)
			{
				anwser.erase(anwser.begin()+i);
				i--;
			}
		}
		return anwser;
	}
	vector <asteroid*> findasteroids(const point& Position, const float& Range)
	{
		point approximatedpoint=approximatepoint(Position);
		point foundpoint;
		map<point, gridelement, pointcompare>::iterator it, tmpit;
		it=gridmap.find(approximatedpoint);
		vector<asteroid*> anwser;

		unsigned int searchsize=(unsigned int)ceil(Range/sidelength);//calculates how far from the initial nodes to look for neighbouring boids

		vector<map<point, gridelement, pointcompare>::iterator> iteratorstocheck;
		map<point, map<point, gridelement, pointcompare>::iterator, pointcompare> checked;
		iteratorstocheck.push_back(it);
		checked.insert(pair<point, map<point, gridelement, pointcompare>::iterator>(it->first, it));

		for(unsigned int i=0;i<searchsize;i++)
		{
			if(!iteratorstocheck.empty())
			{
				it=iteratorstocheck.back();
				iteratorstocheck.pop_back();
				for(unsigned int j=0;j<it->second.neighbours.size();j++)
				{
					if(checked.find(it->first)==checked.end())
					{
						tmpit=gridmap.find(it->second.neighbours.at(j)->center);
						iteratorstocheck.push_back(tmpit);
						checked.insert
						(
								pair<point, map<point, gridelement, pointcompare>::iterator>
							(
								tmpit->first, tmpit
							)
						);
					}
				}
			}
		}
		map<point, map<point, gridelement, pointcompare>::iterator>::iterator checkedit;
		for(checkedit=checked.begin();checkedit!=checked.end();checkedit++)
		{
			anwser.insert(anwser.end(),checkedit->second->second.asteroidlist.begin(),checkedit->second->second.asteroidlist.end());
		}

		for (unsigned int i=0;i<anwser.size();i++)
		{
			if (Position.distanceto(anwser.at(i)->position)>Range)
			{
				anwser.erase(anwser.begin()+i);
				i--;
			}
		}

		return anwser;
	}

	void checkallships()
	{//To be called by for metagrid
		//TODO: use only metagrid?
		if(metagrid!=NULL);
		else
		{
			//cout<<"	void checkallships(). Gridelements: "<<gridmap.size()<<endl<<flush;
			map<point, gridelement, pointcompare>::iterator it;//iterator
			vector<pair<colour, ship*> > tmp;
			map<point, vector<pair<colour, ship*> >, pointcompare> movedships;
			map<point, vector<pair<colour, ship*> >, pointcompare>::iterator it2;
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				tmp=it->second.checkallships();//checks what ships have been moved in the grid element
				//cout<<"tmp size"<<tmp.size()<<endl<<flush;
				movedships.insert(pair<point, vector<pair<colour, ship*> > > (it->first, tmp));//saves both the ships and where they were moved from
			}

			for(unsigned int i=0;i<subgrids.size();i++)
			{
				subgrids.at(i).second->transferships(movedships);
			}
			for(it2=movedships.begin();it2!=movedships.end();it2++)
			{
				//cout<<"for(it2=movedships.begin();it2!=movedships.end();it2++)"<<endl<<flush;
				//cout<<"it2->second.size(): "<<it2->second.size()<<endl<<flush;
				for(unsigned int i=0;i<it2->second.size();i++)
				{
					//cout<<"before addship(it2->second.at(i));"<<endl<<flush;
					addship(it2->second.at(i));
				}
			}
		}
	}
	void transferships(const map<point, vector<pair<colour, ship*> >, pointcompare>& ShipsToMove)
	{//a function that moves the ships in the grid, to be called by metagrid onto subgrids
		map<point, vector<pair<colour, ship*> >, pointcompare>::const_iterator cit;
		map<point, gridelement, pointcompare>::iterator it;
		for(cit=ShipsToMove.begin();
				cit!=ShipsToMove.end();
					cit++)
		{
			it=gridmap.find(cit->first);
			if(it!=gridmap.end())
			{
				for(unsigned int i=0;i<cit->second.size();i++)
				{
					it->second.removeship(cit->second.at(i));
					addship(cit->second.at(i));
				}
			}
		}
	}
	void checkallasteroids()
	{
		//TODO: use metagrid?
		if(metagrid!=NULL);
		//if(metagrid!=NULL) metagrid->checkallasteroids();
		else
		{
			map<point, gridelement, pointcompare>::iterator it;//iterator
			vector <asteroid*> tmp;
			map<point, vector<asteroid*>, pointcompare> movedasteroids;
			map<point, vector<asteroid*>, pointcompare>::iterator it2;
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				tmp=it->second.checkasteroids();
				movedasteroids.insert(pair<point, vector<asteroid*> >(it->first, tmp));
			}
			for (it2=movedasteroids.begin();it2!=movedasteroids.end();it2++)
			{
				for(unsigned int i=0;i<it2->second.size();i++)
				{
					insertasteroidintogrid(it2->second.at(i));
				}
			}
			for(unsigned int i=0;i<subgrids.size();i++)
			{
				subgrids.at(i).second->transferasteroids(movedasteroids);
			}
		}
	}
	void transferasteroids(const map<point, vector<asteroid*>, pointcompare>& AsteroidsToMove)
	{//a function that moves the ships in the grid, to be called by metagrid onto subgrids
		map<point, vector<asteroid*>, pointcompare>::const_iterator cit;
		map<point, gridelement, pointcompare>::iterator it;
		for(cit=AsteroidsToMove.begin();cit!=AsteroidsToMove.end();cit++)
		{
			it=gridmap.find(cit->first);
			if(it!=gridmap.end())
			{
				for(unsigned int i=0;i<cit->second.size();i++)
				{
					it->second.removeasteroid(cit->second.at(i));
					insertasteroidintogrid(cit->second.at(i));
				}
			}
		}
	}
	void removeship(pair<colour, ship*> Ship)
	{
		//to be used by the metagrid
		//TODO: use metagrid?
		map<point, gridelement, pointcompare>::iterator it;//iterator
		bool tmp=false;
		it=gridmap.find(approximatepoint(Ship.second->position));
		if(it!=gridmap.end())tmp=it->second.removeship(Ship);
		if (!tmp)
		{//if asteroid was not correctly removed, checking the whole grid

			if(!tmp)cout<<"Possibly no, removeship"<<endl<<flush;
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				tmp+=it->second.removeship(Ship);
			}
		}
		if(!tmp)cout<<"No, removeship"<<endl<<flush;
		//TODO: remove from all grids?
	}
	void removeasteroid(asteroid* Asteroid)
	{
		//TODO: use metagrid?
		map<point, gridelement, pointcompare>::iterator it;//iterator
		bool tmp=false;
		it=gridmap.find(approximatepoint(Asteroid->position));
		if(it!=gridmap.end())tmp=it->second.removeasteroid(Asteroid);
		if (!tmp)
		{//if asteroid was not correctly removed, checking the whole grid

			if(!tmp)cout<<"Possibly no, asteroid"<<endl<<flush;
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				tmp+=it->second.removeasteroid(Asteroid);
			}
		}
		bool erased=false;
		if(!tmp)cout<<"No, asteroid"<<endl<<flush;
		else for (unsigned int i=0;i<allasteroids.size();i++)
		{
			if(allasteroids.at(i)==Asteroid)
			{
				allasteroids.erase(allasteroids.begin()+i);
				erased=true;
				break;
			}
		}
		if(!erased) cout<<"Erasing problem from allasteroids in grid."<<endl<<flush;
	}
	inline
	void clear()
	{
		//TODO: use metagrid?
		map<point, gridelement, pointcompare>::iterator it;//iterator
		for (it=gridmap.begin();it!=gridmap.end();it++)
		{
			it->second.clear();
		}
		allasteroids.clear();
		allmotherships.clear();
		for(unsigned int i=0;i<subgrids.size();i++)
		{
			subgrids.at(i).second->clear();
		}
	}
	vector<pair<colour, ship*> > checkcolisions()
	{
		if(metagrid!=NULL) return vector<pair<colour, ship*> >();
		else
		{
			map<point, gridelement, pointcompare>::iterator it;//iterator
			vector<pair<colour, ship*> > destroyedships, tmp;
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				tmp=it->second.checkcolisions();
				destroyedships.insert(destroyedships.end(),tmp.begin(), tmp.end());
			}
			return destroyedships;
		}
	}
	inline
	void checkcolisionswithcolourchange()
	{//to be used only by metagrid
		if(metagrid!=NULL);
		else
		{
			vector<pair<colour, ship*> > destroyedships=checkcolisions();
			for(unsigned int i=0;i<destroyedships.size();i++)
			{
				destroyedships.at(i).second->mycolour.changecolour(1.0, 1.0, 1.0);
			}
		}
	}
	void checkcolisionswithshiphit(const bool& CustomHit=false, const float& CustomHitAmount=10.0)
	{//a function to check which ships have been hit and making them hit
		//to be called only by metagrid
		if(metagrid!=NULL);
		else
		{
			map<point, gridelement, pointcompare>::iterator it;//iterator
			for (it=gridmap.begin();it!=gridmap.end();it++)
			{
				it->second.checkcolisionswithshiphit(CustomHit, CustomHitAmount);
			}
		}
	}


	asteroid* findbestasteroid
	(
		const ship& Ship, const float& AsteroidColourWeight,
		const float& AsteroidDistanceWeight,
		const float& MaxBoidsTargetingAsteroid,
		const float& InfiniteAsteroidWeight
	) const
	{
		if (allasteroids.empty()==true) return NULL;
		asteroid* anwser=NULL;
		float score=-1000000.0;
		float tmpscore=0;
		for(unsigned int i=0;i<allasteroids.size();i++)
		{
			if((allasteroids.at(i)->ismineable())&&(allasteroids.at(i)->notempty())&&
					(allasteroids.at(i)->lockedf(Ship.mothershipcolour)<MaxBoidsTargetingAsteroid))
			{
				tmpscore=(Ship.mycolour.distanceto(allasteroids.at(i)->mycolour)
							+Ship.position.distanceto(allasteroids.at(i)->position)*AsteroidDistanceWeight
								+InfiniteAsteroidWeight*allasteroids.at(i)->infinite)
								/allasteroids.at(i)->volume;;
				if(tmpscore>score)
				{
					score=tmpscore;
					anwser=allasteroids.at(i);
				}
			}
		}
		if(anwser!=NULL)
		{
			//anwser->printme();
			//cout<<"@ "<<anwser<<endl<<flush;
		}
		return anwser;
	}
	unsigned int countasteroids()
	{
		map<point, gridelement, pointcompare>::iterator it;//iterator
		unsigned int anwser=0;
		for (it=gridmap.begin();it!=gridmap.end();it++)
		{
			anwser+=it->second.countasteroids();
		}
		return anwser;
	}
	unsigned int countallships()
	{
		map<point, gridelement, pointcompare>::iterator it;//iterator
		unsigned int anwser=0;
		for (it=gridmap.begin();it!=gridmap.end();it++)
		{
			anwser+=it->second.countaallships();
		}
		return anwser;
	}
	unsigned int allasteroidssize()
	{
		return allasteroids.size();
	}

	ship* findclosestenemyship(const point& MyPosition, const colour& MyColour, const float& MaxShipsTargeting)
	{
		ship* anwser=NULL;
		ship* tmp=NULL;
		map<point, gridelement, pointcompare>::iterator it;

		for(it=gridmap.begin();it!=gridmap.end();it++)
		{
			tmp=it->second.findclosestenemyship(MyPosition, MyColour, MaxShipsTargeting);
			if(tmp!=NULL)
			{
				if(anwser==NULL)anwser=tmp;
				else if(MyPosition.distanceto(anwser->position)>MyPosition.distanceto(tmp->position))anwser=tmp;
			}
		}
		return anwser;
	}
	ship* findclosestharvester(const point& MyPosition, const colour& MyColour, const float& MaxShipsTargeting)
	{
		ship* anwser=NULL;
		ship* tmp=NULL;
		map<point, gridelement, pointcompare>::iterator it;

		for(it=gridmap.begin();it!=gridmap.end();it++)
		{
			tmp=it->second.findclosestharvester(MyPosition, MyColour, MaxShipsTargeting);
			if(tmp!=NULL)
			{
				if(anwser==NULL)anwser=tmp;
				else if(MyPosition.distanceto(anwser->position)>MyPosition.distanceto(tmp->position))anwser=tmp;
			}
		}
		return anwser;
	}


	void agegrid(const bool& ClearOldGridElements=false)
	{
		//TODO: use metagrid
		map<point, gridelement, pointcompare>::iterator it;
		vector<map<point, gridelement, pointcompare>::iterator> its;
		for(it=gridmap.begin();it!=gridmap.end();++it)
		{
			if(it->second.agegridelement()>MAXAGE)
			{
				if(ClearOldGridElements==true)
				{
					its.push_back(it);
				}
			}
		}
		if(ClearOldGridElements)
		{
			for(unsigned int i=0;i<its.size();i++)
			{
				gridmap.erase(its.at(i));
			}
		}
	}

	void unittest()
	{
		/*fullgrid.preparegrid(0);
		fullgrid.preparegrid(1);
		fullgrid.preparegrid(2);
		fullgrid.preparegrid(3);*/
	}
};

#endif /* GRID_H_ */
