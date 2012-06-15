#ifndef ASTEROID_H_
#define ASTEROID_H_

#define DRAWINGACCURACY 4 //how accurate is the drawing function for the asteroid (how many slices and sections the sphere has)

#include "../math.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <map>
using namespace std;

#define SPHERECONSTANT 4/3*M_PI
#define ANTISPHERECONSTANT 1/SPHERECONSTANT

class asteroid
{
public:
	point position;//asteroid's position
	colour mycolour;//asterid's colour
	float volume;//asteroid's volume (used for mining)
	float radius;//asteroid's radius (used for colision detection and drawing)
	myvector velocity;//asteroid's velocity
	map<colour, unsigned int> locked;//a lock so the asteroid would not be deleted while it is being references to by a boid
	//unsigned int locked;//a lock so the asteroid would not be deleted while it is being references to by a boid
	bool mineable;//a variable showing whether the asteroid is minable, or is just an obstacle
	bool infinite;//a variable showing that the asteroid will not deterioate because of mining
	asteroid(const point& Position=point(),
			const colour& Colour=colour(),
			const float& Volume=1.0,
			const myvector& Velocity=myvector(),
			const bool& Mineable=true,
			const bool& Infinite=false):
		position(Position),
		mycolour(Colour),
		volume(Volume),
		radius(pow(volume*ANTISPHERECONSTANT, 1.0/3.0)),
		velocity(Velocity),
		locked(),
		mineable(Mineable),
		infinite(Infinite)
	{
	}
	asteroid(const asteroid& Other):
		position(Other.position),
		mycolour(Other.mycolour),
		volume(Other.volume),
		radius(pow(volume*ANTISPHERECONSTANT, 1.0/3.0)),
		velocity(Other.velocity),
		locked(),
		mineable(Other.mineable),
		infinite(Other.infinite)
	{
	}
	~asteroid()
	{
	}
	void drawme(const unsigned int& Mode=0,//mode of drawing (0 - solid sphere, 1 - wire sphere)
			const float& RadiusRadio=1.0)//ratio of how big the asteroid will be drawn with respect to its actual size
			const
	{//a function to draw the asteroid
		glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			mycolour.setcolour();
			switch(Mode)
			{
			case 0:
				glutSolidSphere(radius*RadiusRadio, DRAWINGACCURACY, DRAWINGACCURACY);
				break;
			case 1:
				glutWireSphere(radius*RadiusRadio, DRAWINGACCURACY, DRAWINGACCURACY);
				break;
			}
		glPopMatrix();
	}
	inline
	void moveme()
	{//moving the asteroid
		position.movemebyvector(velocity);
	}
	inline
	void changecolour (const GLfloat& R=1.0, const GLfloat& G=1.0, const GLfloat& B=1.0)
	{//changing the colour of the asteroid
		mycolour.changecolour(R, G, B);
	}
	inline
	void randomizecolour (void)
	{//randomizing the colour
		mycolour.randomcolour();
	}
	inline
	void setposition (const float& X=0.0, const float& Y=0.0, const float& Z=0.0)
	{//setting the position of the asteroid
		position.setposition(X, Y, Z);
	}
	inline
	void printme() const
	{//writing the information about the asteroid
		position.printme();
	}
	float mine(const float& HowMuch=0.0)
	{//function to handle proper mining of the asteroid
		if(infinite)return HowMuch;//infinite mining
		float tmpvolume=volume-HowMuch;
		if(tmpvolume<0.0)
		{
			tmpvolume=volume;
			volume=0;
			radius=0;
		}
		else
		{
			volume=tmpvolume;
			recalculateradius();
			tmpvolume=HowMuch;
		}
		return tmpvolume;
	}
	void unmine(const float& HowMuch=0.0)
	{//canceling the mining, in case sometihng needs to be returned
		volume+=HowMuch;
		recalculateradius();
	}
	inline
	void recalculateradius()
	{//a function to recalculate the radius based on the change in volume
		radius=pow(volume*ANTISPHERECONSTANT, 1.0/3.0);
	}
	inline
	bool islocked() const
	{//a function indicating whether there are any boids using this asteroid
		map<colour, unsigned int>::const_iterator it;
		for(it=locked.begin();it!=locked.end();++it)
		{
			if(it->second>0) return true;
		}
		return false;
	}
	inline
	bool isunlocked()const
	{//opposite of the above function
		unsigned int tmp=0;
		map<colour, unsigned int>::const_iterator it;
		for(it=locked.begin();it!=locked.end();++it)
		{
			tmp+=it->second;
		}
		return tmp==0;
	}
	inline
	void lock(const colour& ColourKey)
	{//a function to prevent the asteroid from being deleted
		map<colour, unsigned int>::iterator it;
		it=locked.find(ColourKey);
		if(it==locked.end())
		{
			it=locked.insert(pair<colour, unsigned int> (ColourKey, 0)).first;
		}
		it->second++;
	}
	inline
	void unlock(const colour& ColourKey)
	{//opposite of the above function
		map<colour, unsigned int>::iterator it;
		it=locked.find(ColourKey);
		if(it!=locked.end())
		{
			it->second--;
		}
	}
	inline
	bool empty() const
	{//returns true if asteroid is depleted
		return volume==0.0;
	}
	inline
	bool notempty()const
	{//opposite of the above function
		return volume!=0.0;
	}
	inline
	void resetlock(const colour& ColourKey)
	{//a function to reset the lock on the asteroid
		map<colour, unsigned int>::iterator it;
		it=locked.find(ColourKey);
		if(it!=locked.end())
		{
			it->second=0;
		}
	}
	inline
	unsigned int lockedui(const colour& ColourKey)
	{//returns how many boids are locking the asteroid
		map<colour, unsigned int>::iterator it;
		it=locked.find(ColourKey);
		if(it==locked.end())
		{
			it=locked.insert(pair<colour, unsigned int> (ColourKey, 0)).first;
		}
		return it->second;
	}
	inline
	float lockedf(const colour& ColourKey)
	{//as above, but as a float
		map<colour, unsigned int>::iterator it;
		it=locked.find(ColourKey);
		if(it==locked.end())
		{
			it=locked.insert(pair<colour, unsigned int> (ColourKey, 0)).first;
		}
		return 1.0*it->second;
	}
	inline
	bool ismineable()const
	{//returns true, if the asteroid can be mined
		return mineable;
	}
	inline
	void setmineable(const bool& Mineable=true)
	{
		mineable=Mineable;
	}
	inline
	void resetlocks()
	{//a function to reset the lock on the asteroid
		map<colour, unsigned int>::iterator it;
		for(it=locked.begin();it!=locked.end();++it)
		{
			it->second=0;
		}
	}
	inline
	unsigned int lockeduis()
	{//returns how many boids are locking the asteroid
		unsigned int anwser=0;
		map<colour, unsigned int>::iterator it;
		for(it=locked.begin();it!=locked.end();++it)
		{
			anwser+=it->second;
		}
		return anwser;
	}
};

#endif /* ASTEROID_H_ */
