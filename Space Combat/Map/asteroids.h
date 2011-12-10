#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

#include "../math.h"
#include "asteroid.h"
#include "grid.h"
#include <iostream>
#include <vector>

using namespace std;


class asteroids
{//a function to handle all the asteroids in the system
public:
	vector<asteroid*> allasteroids;//vector of pointers to nonstatic asteroids
	vector<asteroid*> staticasteroids;//vector of pointers to static asteroids

	//the variables of a disc on which new asteroids are created
	point center;//disc's center
	float radius;//disc's radius
	myvector direction;//new asteroid's direction

	plane terminatingplane;//the plane, that destroys all unlocked asteroids upon going under it

	float asteroidspeed;//the speed of new asteroids
	colour asteroidcolour;//colour of new asteroids
	grid* metagrid;//pointer to the main system grid
	random* myrandom;//random class
	asteroids(const myvector& Direction=myvector(0.0, 0.0, 1.0),
			const point& DiscCenter=point(0.0, 0.0, 0.0),
			const float& DiscRadius=10.0,
			const point& TerminatingPlanePoint=point(0.0, 0.0, 10.0),
			const float& AsteroidSpeed=0.1):
		allasteroids(),
		staticasteroids(),
		center(DiscCenter),
		radius(DiscRadius),
		direction(Direction),
		terminatingplane(TerminatingPlanePoint, -Direction),
		asteroidspeed(AsteroidSpeed),
		asteroidcolour(1.0, 0.0, 0.0),
		metagrid(NULL),
		myrandom(random::getinstance())
	{
	}
	~asteroids()
	{
		clear();
	}
	inline
	void setcolour(const colour& Colour)
	{//sets the asteroid colour, if they all are to have the same colour
		asteroidcolour.setme(Colour);
	}
	inline
	unsigned int numberofasteroids()
	{//returns how many non-static asteroids there are
		return allasteroids.size();
	}
	inline
	void drawme() const
	{//draws all the asteroids
		for (unsigned int i=0;i<allasteroids.size();i++)
		{
			allasteroids.at(i)->drawme();
		}
		for (unsigned int i=0;i<staticasteroids.size();i++)
		{
			staticasteroids.at(i)->drawme();
		}
	}

	inline
	void moveme()
	{//moves all the asteroids
		for (unsigned int i=0;i<allasteroids.size();i++)
		{
			allasteroids.at(i)->moveme();
		}
	}
	void checkfordeletion()
	{//checks which asteroids should be deleted and deletes the ones that are not targeted by any ship
		for (unsigned int i=0;i<allasteroids.size();i++)
		{
			if(allasteroids.at(i)->isunlocked())
			{
				if((allasteroids.at(i)->volume==0.0)||//if the asteroid is empty
						(terminatingplane.ispointbelow//or has passed the plane that deletes the asteroids
								(allasteroids.at(i)->position, allasteroids.at(i)->radius)))
				{
					if(metagrid!=NULL)metagrid->removeasteroid(allasteroids.at(i));
					else cout<<"METAGRID NULL!"<<endl<<flush;
					delete(allasteroids.at(i));
					allasteroids.at(i)=NULL;
					allasteroids.erase(allasteroids.begin()+i);
					i--;
				}
			}
		}
	}

	inline
	void generateasteroid(const bool& Mineable=true)
	{//generates an asteroid on the plane specified
		asteroid* newasteroid=new asteroid(
				center.movebyvector(myrandom->randomdiscposition(radius)),
				colour(1.0),
				1.0,
				direction*asteroidspeed);
		newasteroid->setmineable(Mineable);
		allasteroids.push_back(newasteroid);
		if(metagrid!=NULL) metagrid->addasteroid(newasteroid);
	}
	inline
	void generateastaticcubeasteroids(const bool& Mineable=true)
	{//generates an asteroid in a cube
		asteroid* newasteroid=new asteroid(
				center.movebyvector(myrandom->randomcubeposition(radius)),
				asteroidcolour,
				1.0,
				myvector(0.0, 0.0, 0.0));
		newasteroid->setmineable(Mineable);
		staticasteroids.push_back(newasteroid);
		if(metagrid!=NULL) metagrid->addasteroid(newasteroid);
	}
	inline
	void generateastaticcubeasteroids(const point& CubeCenter, const float& Radius, const bool& Mineable=true)
	{//generates an asteroid in a cube
		asteroid* newasteroid=new asteroid(
				CubeCenter.movebyvector(myrandom->randomcubeposition(Radius)),
				asteroidcolour,
				1.0,
				myvector(0.0, 0.0, 0.0));
		newasteroid->setmineable(Mineable);
		staticasteroids.push_back(newasteroid);
		if(metagrid!=NULL) metagrid->addasteroid(newasteroid);
	}

	inline
	void addasteroid(const asteroid& Asteroid)
	{
		asteroid* newasteroid=new asteroid(Asteroid);
		staticasteroids.push_back(newasteroid);
		if(metagrid!=NULL) metagrid->addasteroid(newasteroid);

	}

	inline
	void setgrid(grid* Metagrid)
	{//sets the metagrid and puts all asteroids already generated into it
		if(metagrid!=Metagrid)
		{
			metagrid=Metagrid;
			if (metagrid!=NULL)
			{
				for(unsigned int i=0;i<allasteroids.size();i++)
				{
					metagrid->addasteroid(allasteroids.at(i));
				}
				for(unsigned int i=0;i<staticasteroids.size();i++)
				{
					metagrid->addasteroid(staticasteroids.at(i));
				}
			}
		}
	}

	inline
	void setspeed(const float& Speed)
	{//sets the speed of the new asteroids
		asteroidspeed=Speed;
	}
	inline
	void setdirection(const myvector& Direction)
	{//sets the direction in which the asteroids travel
		direction=Direction;
	}
	inline
	void setgeneratingdisc(const point& DiscCenter, const float& DiscRadius)
	{//sets the disc that is generating the asteroids
		center=DiscCenter;
		radius=DiscRadius;
	}
	inline
	void setterminatingplane(const point& PlanePoint)
	{//sets the plane that deletes the asteroids
		terminatingplane(PlanePoint, -direction);
	}
	inline
	void setterminatingplane(const plane& Terminating)
	{//sets the plane that deletes the asteroids
		terminatingplane=Terminating;
	}
	inline
	void clear()
	{//a function that deletes all asteroids and clears the vector that was holding them
		for(unsigned int i=0;i<allasteroids.size();i++)
		{
			delete(allasteroids.at(i));
		}
		allasteroids.clear();
		for(unsigned int i=0;i<staticasteroids.size();i++)
		{
			delete(staticasteroids.at(i));
		}
		staticasteroids.clear();
	}
	inline
	void resetalllocks()
	{//resets all locks of all asteroids
		for(unsigned int i=0;i<allasteroids.size();i++)
		{
			allasteroids.at(i)->resetlocks();
		}
	}
	inline
	void printlocks()
	{//writes the lock numbers of all asteroids
		for(unsigned int i=0;i<allasteroids.size();i++)
		{
			cout<<allasteroids.at(i)->lockeduis()<<endl<<flush;
		}
	}
};

#endif /* ASTEROIDS_H_ */
