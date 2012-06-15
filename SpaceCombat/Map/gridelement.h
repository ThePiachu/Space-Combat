#ifndef GRIDELEMENT_H_
#define GRIDELEMENT_H_

#define AGEINGFACTOR 1.0

#include "../math.h"
#include "ship.h"
#include "asteroid.h"
#include <vector>
#include <iostream>
using namespace std;

class gridelement
{
public:
	vector<pair<colour, ship*> > allships;//colour of the mothership of the ship and the ship itself
	vector<asteroid*> asteroidlist;
	//neighbours
	vector<gridelement*>neighbours;
	point center;
	float width;
	float asteroidtotalvolume;
	float timesincelastcheck;
	gridelement(const point& Center=point(), const float& Width=0.0):
		allships(),
		asteroidlist(),
		neighbours(),
		center(Center),
		width(Width),
		asteroidtotalvolume(0.0),
		timesincelastcheck(0.0)
	{
		//cout<<"New Gridelement"<<endl<<flush;
	}
	~gridelement()
	{//TODO: use some age for deleting old grid elements
		for(unsigned int i=0;i<neighbours.size();i++)
		{
			neighbours.at(i)->removeneighbour(this);
		}
		neighbours.erase(neighbours.begin(), neighbours.end());
	}

	void removeneighbour(const gridelement* Neighbour)
	{
		for(unsigned int i=0;i<neighbours.size();i++)
		{
			if(neighbours.at(i)==Neighbour)
			{
				neighbours.erase(neighbours.begin()+i);
				break;
			}
		}
	}

	inline
	void addship(const pair<colour, ship*> Ship)
	{
		//cout<<"void addship(const pair<colour, ship*> Ship)"<<endl<<flush;
		allships.push_back(Ship);
		//cout<<"allships.size(): "<<allships.size()<<endl<<flush;
	}

	/*inline
	void addfriendlyship(ship* Ship)
	{
		friendlyships.push_back(Ship);
	}*/
	/*inline
	void addenemyship(ship* Ship)
	{
		enemyships.push_back(Ship);
	}
	inline
	void addneutralship(ship* Ship)
	{
		neutralships.push_back(Ship);
	}*/
	inline
	void addasteroid(asteroid* Asteroid)
	{
		asteroidlist.push_back(Asteroid);
		asteroidtotalvolume+=Asteroid->volume;
	}
	float setagefromneighbours()
	{
		if(neighbours.empty())return timesincelastcheck;
		float tmp=neighbours.at(0)->timesincelastcheck;
		for(unsigned int i=1;i<neighbours.size();i++)
		{
			if(neighbours.at(i)->timesincelastcheck<tmp)tmp=neighbours.at(i)->timesincelastcheck;
		}
		timesincelastcheck=tmp;
		return timesincelastcheck;
	}
	float agegridelement()
	{
		if((allships.size()+asteroidlist.size())>0)return timesincelastcheck=0.0;
		else return timesincelastcheck+=AGEINGFACTOR;
	}



	bool removeship(pair<colour, ship*> Ship)
	{
		for (unsigned int i=0;i<allships.size();i++)
		{
			if (allships.at(i).second==Ship.second)
			{
				allships.erase(allships.begin()+i);
				return true;
			}
		}
		return false;
	}
	bool removeship(ship* Ship)
	{
		for (unsigned int i=0;i<allships.size();i++)
		{
			if (allships.at(i).second==Ship)
			{
				allships.erase(allships.begin()+i);
				return true;
			}
		}
		return false;
	}
	/*bool removefriendlyship(ship* Ship)
	{
		for (unsigned int i=0;i<friendlyships.size();i++)
		{
			if (friendlyships.at(i)==Ship)
			{
				friendlyships.erase(friendlyships.begin()+i);
				return true;
			}
		}
		return false;
	}*/
	/*bool removeenemyship(ship* Ship)
	{
		for (unsigned int i=0;i<enemyships.size();i++)
		{
			if (enemyships.at(i)==Ship)
			{
				enemyships.erase(enemyships.begin()+i);
				return true;
			}
		}
		return false;
	}
	bool removeneutralship(ship* Ship)
	{
		for (unsigned int i=0;i<neutralships.size();i++)
		{
			if (neutralships.at(i)==Ship)
			{
				neutralships.erase(neutralships.begin()+i);
				return true;
			}
		}
		return false;
	}*/


	bool removeasteroid(asteroid* Asteroid)
	{
		for (unsigned int i=0;i<asteroidlist.size();i++)
		{
			if (asteroidlist.at(i)==Asteroid)
			{
				asteroidtotalvolume-=asteroidlist.at(i)->volume;
				asteroidlist.erase(asteroidlist.begin()+i);
				return true;
			}
		}
		return false;
	}


	/*vector<ship*> checkenemyships()
	{//function returning all enemy ships not within this grid element
		vector<ship*> anwser;
		for (unsigned int i=enemyships.size()-1;i>(unsigned int)-1;i--)
		{
			if (center.biggestaxisdistance(enemyships.at(i)->position)>width)
			{
				anwser.push_back(enemyships.at(i));
				enemyships.erase(enemyships.begin()+i);
			}
		}
		return anwser;
	}
	vector<ship*> checkneutralships()
	{//function returning all neutral ships not within this grid element
		vector<ship*> anwser;
		for (unsigned int i=neutralships.size()-1;i>(unsigned int)-1;i--)
		{
			if (center.biggestaxisdistance(neutralships.at(i)->position)>width)
			{
				anwser.push_back(neutralships.at(i));
				neutralships.erase(neutralships.begin()+i);
			}
		}
		return anwser;
	}*/
	vector<pair<colour, ship*> > checkallships()
	{
		//cout<<"vector<pair<colour, ship*> > checkallships()"<<endl<<flush;
		//cout<<"allships.size() in gridelement: "<<allships.size()<<endl<<flush;
		vector<pair<colour, ship*> > anwser;

		for (unsigned int i=0;i<allships.size();i++)
		{
			if (center.biggestaxisdistance(allships.at(i).second->position)>width)
			{
				anwser.push_back(allships.at(i));
				allships.erase(allships.begin()+i);
				i--;
			}
		}
		return anwser;
	}
	/*vector<ship*> checkfriendlyships()
	{//function returning all friendly ships not within this grid element
		vector<ship*> anwser;

		for (unsigned int i=0;i<friendlyships.size();i++)
		{
			if (center.biggestaxisdistance(friendlyships.at(i)->position)>width)
			{
				anwser.push_back(friendlyships.at(i));
				friendlyships.erase(friendlyships.begin()+i);
				i--;
			}
		}
		return anwser;
	}*/
	vector <asteroid*> checkasteroids()
	{
		vector<asteroid*> anwser;
		for (unsigned int i=0;i<asteroidlist.size();i++)
		{
			if (center.biggestaxisdistance(asteroidlist.at(i)->position)>width)
			{
				anwser.push_back(asteroidlist.at(i));
				asteroidtotalvolume-=asteroidlist.at(i)->volume;
				asteroidlist.erase(asteroidlist.begin()+i);
				i--;
			}
		}
		//cout<<"returned "<<anwser.size()<<endl;
		return anwser;
	}

	void drawme(const unsigned int) const;

	vector<point>givemissingneigbours();
	inline
	void addneighbour(gridelement* Neighbour)
	{
		bool add=true;
		for (unsigned int i=0;i<neighbours.size();i++)
		{
			if (neighbours.at(i)==Neighbour)
			{
				add=false;
				break;
			}
		}
		if (add)neighbours.push_back(Neighbour);
	}
	inline
	void addneighbour(gridelement& Neighbour)
	{
		bool add=true;
		for (unsigned int i=0;i<neighbours.size();i++)
		{
			if (neighbours.at(i)==&Neighbour)
				{
					add=false;
					break;
				}
		}
		if (add)neighbours.push_back(&Neighbour);
	}
	inline
	void printme()
	{
		cout<<"Me:"<<endl<<flush;
		center.printme();
		cout<<"Me neighbours:"<<endl<<flush;
		for (unsigned int i=0;i<neighbours.size();i++)
		{
			neighbours.at(i)->center.printme();
		}
	}
	inline
	vector<gridelement*> giveneighbours()const
	{
		//cout<<"missing "<<neighbours.size()-26<<" neighbours"<<endl<<flush;
		return neighbours;
	}
	/*inline
	unsigned int enemyshipnumber()
	{
		return enemyships.size();
	}*/
	/*inline
	unsigned int friendlyshipnumber()
	{
		return friendlyships.size();
	}*/
	inline
	unsigned int shipnumber()
	{
		return allships.size();
	}
	/*inline
	unsigned int neutralshipsnumber()
	{
		return neutralships.size();
	}*/
	inline
	unsigned int asteroidnumber()
	{
		return asteroidlist.size();
	}
	inline
	float asteroidvolume()
	{
		return asteroidtotalvolume;
	}
	/*inline
	void purgecontent()
	{
		//boids.clear();
		enemyships.clear();
		neutralships.clear();
		friendlyships.clear();
		asteroidlist.clear();
		asteroidtotalvolume=0.0;
	}*/
	inline
	void clear()
	{
		//enemyships.clear();
		//neutralships.clear();
		allships.clear();
		//friendlyships.clear();
		asteroidlist.clear();
		asteroidtotalvolume=0.0;
	}










	/*vector<ship*> checkcolisions(const bool& Speak=false)
	{
		float distance, mindistance;
		vector<ship*> allships=friendlyships, destroyedships;
		vector<asteroid*> allasteroids=asteroidlist;
		for(unsigned int i=0;i<neighbours.size();i++)
		{
			allasteroids.insert(allasteroids.end(), neighbours.at(i)->asteroidlist.begin(), neighbours.at(i)->asteroidlist.end());
		}
		for (unsigned int i=0;i<friendlyships.size();i++)
		{
			for(unsigned int j=i+1;j<allships.size();j++)
			{
				distance=friendlyships.at(i)->position.distanceto(allships.at(j)->position);
				mindistance=friendlyships.at(i)->boundingradius+allships.at(j)->boundingradius;
				if(distance<mindistance)
				{
					destroyedships.push_back(friendlyships.at(i));
					destroyedships.push_back(allships.at(j));
					if(Speak)
					{
						cout<<"i "<<i<<" j "<<j<<" out of "<<friendlyships.size()<<endl<<flush;
						friendlyships.at(i)->mycolour.changecolour(0.0, 0.0, 0.0);
						allships.at(j)->mycolour.changecolour(0.0, 0.0, 0.0);
						cout<<"Colision detected "<<friendlyships.at(i)<<" vs "<<allships.at(j)<<endl<<flush;
						cout<<"Distance: "<<distance<<endl<<flush;
						cout<<"Out of "<<mindistance<<endl<<flush;
					}
				}
			}
			for(unsigned int j=0;j<allasteroids.size();j++)
			{
				distance=friendlyships.at(i)->position.distanceto(allasteroids.at(j)->position);
				mindistance=friendlyships.at(i)->boundingradius+allasteroids.at(j)->radius;
				if(distance<mindistance)
				{
					//cout<<"i "<<i<<" j "<<j<<" out of "<<friendlyships.size()<<endl<<flush;
					destroyedships.push_back(friendlyships.at(i));
					//friendlyships.at(i)->mycolour.changecolour(1.0, 1.0, 1.0);
					//allasteroids.at(j)->mycolour.changecolour(0.0, 0.0, 0.0);



					if(Speak)
					{
						cout<<"Asteroid colision detected "<<friendlyships.at(i)<<" vs "<<allasteroids.at(j)<<endl<<flush;
						cout<<"Distance: "<<distance<<endl<<flush;
						cout<<"Out of "<<mindistance<<endl<<flush;
					}
				}
			}
		}
		return destroyedships;
	}*/
	void checkcolisionswithshiphit(const bool& CustomHit=false, const float& CustomHitAmount=10.0)
	{
		float distance, mindistance;
		vector<pair<colour, ship*> > tmpships=allships;
		vector<asteroid*> allasteroids=asteroidlist;
		for(unsigned int i=0;i<neighbours.size();i++)
		{
			allasteroids.insert(allasteroids.end(), neighbours.at(i)->asteroidlist.begin(), neighbours.at(i)->asteroidlist.end());
			tmpships.insert(tmpships.end(), neighbours.at(i)->allships.begin(), neighbours.at(i)->allships.end());
		}
		for (unsigned int i=0;i<allships.size();i++)
		{
			for(unsigned int j=i+1;j<tmpships.size();j++)
			{
				distance=allships.at(i).second->position.distanceto(tmpships.at(j).second->position);
				mindistance=allships.at(i).second->boundingradius+tmpships.at(j).second->boundingradius;
				if(distance<mindistance)
				{
					if(CustomHit)allships.at(i).second->makehit(tmpships.at(j).second->position, CustomHitAmount);
					else allships.at(i).second->makehit(tmpships.at(j).second->position);
					//tmpships.at(j).second->makehit(allships.at(i).second->position);
				}
			}
			for(unsigned int j=0;j<allasteroids.size();j++)
			{
				distance=allships.at(i).second->position.distanceto(allasteroids.at(j)->position);
				mindistance=allships.at(i).second->boundingradius+allasteroids.at(j)->radius;
				if(distance<mindistance)
				{
					if(CustomHit)allships.at(i).second->makehit(allasteroids.at(j)->position, CustomHitAmount);
					else allships.at(i).second->makehit(allasteroids.at(j)->position);
				}
			}
		}
	}

	vector<pair<colour, ship*> > checkcolisions(const bool& Speak=false)
	{
		float distance, mindistance;
		vector<pair<colour, ship*> > tmpships=allships, destroyedships;
		vector<asteroid*> allasteroids=asteroidlist;
		for(unsigned int i=0;i<neighbours.size();i++)
		{
			allasteroids.insert(allasteroids.end(), neighbours.at(i)->asteroidlist.begin(), neighbours.at(i)->asteroidlist.end());
		}
		for (unsigned int i=0;i<allships.size();i++)
		{
			for(unsigned int j=i+1;j<tmpships.size();j++)
			{
				distance=allships.at(i).second->position.distanceto(tmpships.at(j).second->position);
				mindistance=allships.at(i).second->boundingradius+tmpships.at(j).second->boundingradius;
				if(distance<mindistance)
				{
					destroyedships.push_back(allships.at(i));
					destroyedships.push_back(tmpships.at(j));
					if(Speak)
					{
						cout<<"i "<<i<<" j "<<j<<" out of "<<allships.size()<<endl<<flush;
						allships.at(i).second->mycolour.changecolour(0.0, 0.0, 0.0);
						tmpships.at(j).second->mycolour.changecolour(0.0, 0.0, 0.0);
						cout<<"Colision detected "<<allships.at(i).second<<" vs "<<tmpships.at(j).second<<endl<<flush;
						cout<<"Distance: "<<distance<<endl<<flush;
						cout<<"Out of "<<mindistance<<endl<<flush;
					}
				}
			}
			for(unsigned int j=0;j<allasteroids.size();j++)
			{
				distance=allships.at(i).second->position.distanceto(allasteroids.at(j)->position);
				mindistance=allships.at(i).second->boundingradius+allasteroids.at(j)->radius;
				if(distance<mindistance)
				{
					//cout<<"i "<<i<<" j "<<j<<" out of "<<friendlyships.size()<<endl<<flush;
					destroyedships.push_back(allships.at(i));
					//friendlyships.at(i)->mycolour.changecolour(1.0, 1.0, 1.0);
					//allasteroids.at(j)->mycolour.changecolour(0.0, 0.0, 0.0);



					if(Speak)
					{
						cout<<"Asteroid colision detected "<<allships.at(i).second<<" vs "<<allasteroids.at(j)<<endl<<flush;
						cout<<"Distance: "<<distance<<endl<<flush;
						cout<<"Out of "<<mindistance<<endl<<flush;
					}
				}
			}
		}
		return destroyedships;
	}

/*
	void checkpointers()
	{
		for (unsigned int i=0;i<friendlyships.size();i++)
		{
			for(unsigned int j=i+1;j<friendlyships.size();j++)
			{
				if(friendlyships.at(i)==friendlyships.at(j)) cout<<"YES!"<<endl<<flush;
			}
		}
	}*/

	ship* findclosestenemyship(const point& MyPosition, const colour& MyColour, const float& MaxShipsTargeting)
	{
		ship* anwser=NULL;
		for(unsigned int i=0;i<allships.size();i++)
		{
			if(allships.at(i).first!=MyColour)
			{//if the ship is an enemy
				if(anwser==NULL)
				{
					if(allships.at(i).second->shipstargetingme.size()<MaxShipsTargeting)
						anwser=allships.at(i).second;
				}
				else if(allships.at(i).second->shipstargetingme.size()<MaxShipsTargeting)
						if(MyPosition.distanceto(anwser->position)>MyPosition.distanceto(allships.at(i).second->position))
							anwser=allships.at(i).second;
			}
		}
		return anwser;
	}
	ship* findclosestharvester(const point& MyPosition, const colour& MyColour, const float& MaxShipsTargeting)
	{
		ship* anwser=NULL;
		for(unsigned int i=0;i<allships.size();i++)
		{
			if((allships.at(i).first==MyColour)&&(allships.at(i).second->shiptype==1))
			{//if the ship is a friendly harvester
				if(anwser==NULL)
				{
					if(allships.at(i).second->shipsprotectingme.size()<MaxShipsTargeting)
						anwser=allships.at(i).second;
				}
				else if(allships.at(i).second->shipsprotectingme.size()<MaxShipsTargeting)
						if(MyPosition.distanceto(anwser->position)>MyPosition.distanceto(allships.at(i).second->position))
							anwser=allships.at(i).second;
			}
		}
		return anwser;
	}


	bool unittest()
	{
		cout<<"gridelement test started"<<endl<<flush;
		gridelement tested(point(0.0, 0.0, 0.0), 1.0);
		/*vector<star> tmpstars;
		tmpstars.push_back(star(1.0, 2.0, 1.0));
		tmpstars.push_back(star(0.0, 0.0, 0.0));
		tmpstars.push_back(star(1.0, 0.0, 0.0));
		tmpstars.push_back(star(0.0, 1.0, 0.0));
		tmpstars.push_back(star(0.0, 0.0, 1.0));
		tmpstars.push_back(star(1.0, 1.0, 1.0));
		tmpstars.push_back(star(1.0, 2.0, 1.0));
		cout<<"addstar"<<endl<<flush;
		for (unsigned int i=0;i<tmpstars.size();i++)tested.addstar(&tmpstars.at(i));

		cout<<"teststars"<<endl<<flush;
		vector<star*> rejectedstars=tested.checkstars();
		for (unsigned int i=0;i<rejectedstars.size();i++)rejectedstars.at(i)->printme();*/

		//cout<<"printallstars"<<endl<<flush;
		//tested.printallstars();


		cout<<"All OK."<<endl<<flush;
		return true;
	}
	inline
	unsigned int countasteroids()
	{
		return asteroidlist.size();
	}
	inline
	unsigned int countaallships()
	{
		return allships.size();
	}
	/*inline
	unsigned int countfriendlyships()
	{
		return friendlyships.size();
	}*/

};

#endif /* GRIDELEMENT_H_ */
