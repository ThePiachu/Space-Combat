#ifndef STARS_H_
#define STARS_H_

#include "math.h"
#include <algorithm>
//#include <GL\gl.h>

#define CUBEMODE	1
#define BOXMODE		2
#define BUBBLEMODE	3
#define DISCMODE	4
#define SQUAREMODE	5
#define SPHEREMODE	6


using namespace std;




class star
{
public:
	point position;
	colour mycolour;
	star(const point& Position, const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0): position(Position), mycolour(R, G, B)
	{
	}
	star(const float& X=0.0, const float& Y=0.0, const float& Z=0.0,
			const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0): position(X, Y, Z), mycolour(R, G, B)
	{
	}
	star(const myvector& VectorFromOrigin,
			const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0): position(point(0.0, 0.0, 0.0).movemebyvector(VectorFromOrigin)), mycolour(R, G, B)
	{
	}
	star(const basicvector& VectorFromOrigin,
			const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0): position(point(0.0, 0.0, 0.0).movemebyvector(VectorFromOrigin)), mycolour(R, G, B)
	{
	}
	void drawme (void) const
	{
		mycolour.setcolour();
		glBegin(GL_POINTS);
			glVertex3f(position.x, position.y, position.z);
		glEnd();
	}
	void changecolour (const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0)
	{
		mycolour.changecolour(R, G, B);
	}
	void randomizecolour (void)
	{
		mycolour.randomcolour();
	}
	void setposition (const float& X=0.0, const float& Y=0.0, const float& Z=0.0)
	{
		position.setposition(X, Y, Z);
	}
	void printme() const
	{
		position.printme();
	}
};

bool comparex(const star* one, const star* two);
bool comparey(const star* one, const star* two);
bool comparez(const star* one, const star* two);

class stars
{
	int mode;
	float distance;
	unsigned int amount;
	vector <star> universe;
	vector <star*> listx, listy, listz;
	random* myrandom;
public:
	stars(float Distance=5.0, unsigned int Amount=100):
		distance(Distance), amount(Amount),
		myrandom(random::getinstance())
	{
		mode=0;
	}
	~stars()
	{
	}
	void setstars(float Distance=5.0f, unsigned int Amount=100)
	{
		mode=0;
		distance=Distance;
		amount=Amount;
		universe.clear();
	}
	void setlists()
	{
		listx.clear();
		listy.clear();
		listz.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			listx.push_back(&universe.at(i));
			listy.push_back(&universe.at(i));
			listz.push_back(&universe.at(i));
		}
		sort(listx.begin(), listx.end(), comparex);
		sort(listy.begin(), listy.end(), comparey);
		sort(listz.begin(), listz.end(), comparez);
	}
	unsigned int starcount() const
	{
		return amount;
	}
	bool isfilled() const
	{//returns true if there are any stars in the vector
		return !universe.empty();
	}
	void fillcube()
	{
		mode=CUBEMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(star(myrandom->randomcubeposition(distance)));
		}
		setlists();
	}
	void fillbox()
	{
		mode=BOXMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(star(myrandom->randomboxposition(distance)));
		}
		setlists();
	}
	void fillbubble(float dx=1.0, float dy=1.0, float dz=1.0)
	{
		mode=BUBBLEMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(myrandom->randombubbleposition(distance, dx, dy, dz));
		}
		setlists();
	}
	void filldisc()
	{
		mode=DISCMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(star(myrandom->randomdiscposition(distance)));
		}
		setlists();
	}
	void fillsquare()
	{
		mode=SQUAREMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(star(myrandom->randomsquareposition(distance)));
		}
		setlists();
	}
	void fillsphere()
	{
		mode=SPHEREMODE;
		universe.clear();
		for (unsigned int i=0;i<amount;i++)
		{
			universe.push_back(star(myrandom->randomsphereposition(distance)));
		}
		setlists();
	}
	void drawme() const
	{
		if (!universe.empty())
		{
			for (unsigned int i=0;i<amount;i++)
			{
				universe[i].drawme();
			}
		}
	}
	void randomizestars(void)
	{
		if(universe.empty()==0)
		{
			for (unsigned int i=0;i<amount;i++)
			{
				universe[i].randomizecolour();
			}
		}
	}
	star* randomstar(void)
	{
		if (amount==0) return NULL;
		return &universe.at(myrandom->randomunsignedint(amount));
	}
	void printme() const
	{
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			universe[i].printme();
		}
	}
	void printbyx() const
	{
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			listx.at(i)->printme();
		}
	}
	void printbyy() const
	{
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			listy.at(i)->printme();
		}
	}
	void printbyz() const
	{
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			listz.at(i)->printme();
		}
	}
	unsigned int findclosestindex(const point& Point)
	{
		unsigned int result=0;
		float tmpdistance=universe.at(result).position.distanceto(Point);
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			if(universe.at(i).position.distanceto(Point)<(tmpdistance))
			{
				result=i;
				tmpdistance=universe.at(result).position.distanceto(Point);
			}
		}
		return result;
	}
	star* findcloseststar(const point& Point)
	{
		return &universe.at(findclosestindex(Point));
	}
	vector<star*> findallwithinsphere(const point& Center, const float& Radius)
	{//a function to find all stars within a sphere
		vector <star*> tmpstars(findallwithincube(Center, Radius));
		if (tmpstars.empty()==0)
		{
			for (unsigned int i=tmpstars.size()-1;i>0;i--)
			{
				if (tmpstars.at(i)->position.distanceto(Center)>Radius)
				{
					tmpstars.erase(tmpstars.begin()+i);
				}
			}
		}
		/*if (tmpstars.empty()==0)
		{
			for (unsigned int i=tmpstars.size()-1;i>0;i--)
			{
				tmpstars.at(i)->printme();
			}
		}*/
		return tmpstars;
	}
	vector<star*> findallwithincube(const point& Center, const float& SideByHalf)
	{//a function to find all stars within a cube aligned with the coordinate system
		vector<star*> result;
		if (universe.empty()==0)for (unsigned int i=0;i<amount;i++)
		{
			if (abs(listx.at(i)->position.x-Center.x)<SideByHalf)
				if (abs(listx.at(i)->position.y-Center.y)<SideByHalf)
					if (abs(listx.at(i)->position.z-Center.z)<SideByHalf)
						result.push_back(listx.at(i));
		}
		/*if (result.empty()==0)
		{
			for (unsigned int i=result.size()-1;i>0;i--)
			{
				result.at(i)->printme();
			}
		}*/
		return result;
	}
};



#endif
