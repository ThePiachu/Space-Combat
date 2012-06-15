#ifndef SHIP_H_
#define SHIP_H_

#define SHIPSPEED 0.2
#define SHIPCAPACITY 0.5
#define ACCELERATIONMAGNITUDE 1.0
#define RANGEOFSIGHT 2.0
#define DOCKINGINCREMENT 0.1
#define DOCKINGLINELENGTH 1.0
#define RESOURCESTRANSFERRATE 0.05
#define STARTINGHEALTH 100.0
#define HITHEALTHCOST 10.0
#define HEALINGRATE 1.0
#define PENALTYACCELERATIONMAGNITUDE 1.0

#define SHIPSPEAK false

#include "../math.h"
#include "asteroid.h"
#include <vector>
#include <string>
#include <map>
using namespace std;


class ship
{
protected:
	ship(const point& Position,
			const colour& Colour,
			const float& Speed,
			const float& Acceleration,
			const myvector& Front,
			const float& BoundingRadius=0.1*sqrt(2),
			const float& Capacity=SHIPCAPACITY,
			const float& Health=STARTINGHEALTH):
		position(Position),
		speed(Speed),
		accelerationmagnitude(Acceleration),
		rangeofsight(RANGEOFSIGHT),
		velocity(Front),
		currentacceleration(),
		defaultfront(Front),
		accelerationstep(1),
		rotation(),
		mycolour(Colour),
		mothershipcolour(mycolour),
		acceleration(),
		boundingradius(BoundingRadius),
		maxcapacity(Capacity),
		currentload(0.0),
		dockingline(0.0, 0.0, 0.0),
		dockinglinestate(0.0),
		asteroidtarget(NULL),
		shiptarget(NULL),
		shiptoprotect(NULL),
		pathset(false),
		endofpathreached(false),
		health(Health),
		penaltyacceleration(0.0, 0.0, 0.0),
		penaltyaccelerationmagnitude(PENALTYACCELERATIONMAGNITUDE),//TODO: change for mothership?
		shipstargetingme(),
		shipsprotectingme(),
		shiptype(0),
		tmpreward(0)
	{
	}
public:
	point position;
	float speed, accelerationmagnitude, rangeofsight;
	myvector velocity, currentacceleration, defaultfront;
	unsigned int accelerationstep;
	quaternion rotation;
	colour mycolour, mothershipcolour;
	vector<myvector>acceleration;
	float boundingradius;
	float maxcapacity, currentload;
	myvector dockingline;//a vector from ship to asteroid used for gaining resources
	float dockinglinestate;//from 0 to 1, controling the ratio of the length of the docking line
	asteroid* asteroidtarget;
	ship* shiptarget;
	ship* shiptoprotect;
	bool pathset;//a variable indicating that the ship has plotted a path
	bool endofpathreached;//a variable indicating that end of a single path was reached
	float health;
	myvector penaltyacceleration;
	float penaltyaccelerationmagnitude;
	vector<ship*>shipstargetingme, shipsprotectingme;
	unsigned int shiptype;//0 - fighter, 1 - harvester
	float tmpreward;//a score reward awarded to the ship that later will be picked up by the pilot
	ship(const point& Position=point(0.0, 0.0, 0.0), const colour& Colour=colour(), const unsigned int& ShipType=0):
		position(Position),
		speed(SHIPSPEED),
		accelerationmagnitude(ACCELERATIONMAGNITUDE),
		rangeofsight(RANGEOFSIGHT),
		velocity(1.0, 0.0, 0.0),
		currentacceleration(),
		defaultfront(1.0, 0.0, 0.0),
		accelerationstep(1),
		rotation(),
		mycolour(Colour),
		mothershipcolour(mycolour),
		acceleration(),
		boundingradius(0.1*sqrt(2)),
		maxcapacity(SHIPCAPACITY),
		currentload(0.0),
		dockingline(0.0, 0.0, 0.0),
		dockinglinestate(0.0),
		asteroidtarget(NULL),
		shiptarget(NULL),
		shiptoprotect(NULL),
		pathset(false),
		endofpathreached(false),
		health(STARTINGHEALTH),
		penaltyacceleration(0.0, 0.0, 0.0),
		penaltyaccelerationmagnitude(PENALTYACCELERATIONMAGNITUDE),
		shipstargetingme(),
		shipsprotectingme(),
		shiptype(ShipType),
		tmpreward(0)
	{
	}
	virtual ~ship()
	{
		iamdead();
		//cout<<"Deleted"<<endl<<flush;
	}
	inline
	void setshiptype(const unsigned int& ShipType=0)
	{
		shiptype=ShipType;
	}
	inline
	void iamdead()
	{
		if(SHIPSPEAK)cout<<"ship::iamdead"<<endl<<flush;
		unsetasteroidtarget();
		untargetme();
		untarget();
		if(SHIPSPEAK)cout<<"~ship::iamdead"<<endl<<flush;
	}
	inline
	void setshiptarget(ship* Target)
	{
		if(shiptarget!=NULL)shiptarget->iamnottargetingyouanymore(this);
		shiptarget=Target;
		if(shiptarget!=NULL)Target->iamtargetingyou(this);
	}
	inline
	void setfriendlyshiptarget(ship* FriendlyTarget)
	{
		if(shiptoprotect!=NULL)shiptoprotect->iamnotprotectingyouanymore(this);
		shiptoprotect=FriendlyTarget;
		if(shiptoprotect!=NULL)FriendlyTarget->iamprotectingyou(this);
	}

	inline
	void setposition(const point& NewPosition)
	{
		position=NewPosition;
	}

	inline
	ship& operator()(const point& Position)
	{
		position=Position;
		return *this;
	}

	inline
	void printme() const
	{
		cout<<"Position: ";
		position.printme();
	}
	void drawme(const unsigned int& Mode=1)
	{
		//rotation.rotationbetweentwovectorsme(defaultfront, velocity);
		glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			dockingline.drawme();
			if(Mode%3==0)
			{
				if(asteroidtarget!=NULL)
				{
					myvector(position, asteroidtarget->position).drawme();
				}
				if(shiptarget!=NULL)
				{
					myvector(position, shiptarget->position).drawme();
				}
				if(shiptoprotect!=NULL)
				{
					myvector(position, shiptoprotect->position).drawme();
				}
			}
			glMultMatrixf(rotation.rotationmatrix());
			drawship(shiptype);
			//glutSolidSphere(boundingradius, 5, 5);
			glColor3f(1.0, 1.0, 1.0);//line colour
		glPopMatrix();
		if(Mode%5==0)if(asteroidtarget!=NULL)
		{
			asteroidtarget->drawme(1, 1.2);
		}
		//movement.drawme(position);
		//acceleration.drawme(position.movebyvector(movement));
		//position.printme();
	}
	virtual void drawship(const unsigned int ShipDrawingMode=0) const
	{
		glPushMatrix();
			glScalef(0.1, 0.1, 0.1);
			mycolour.setcolour();
			if(ShipDrawingMode==0)
			{
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(1.0, 0.0, 0.0);//front
					glVertex3f(-1.0, 1.0, 0.0);//left wing
					glVertex3f(-1.0, -1.0, 0.0);//right wing
					glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
					glVertex3f(-1.0, 0.0, 0.5);//top
					mycolour.setcolour();
					glVertex3f(1.0, 0.0, 0.0);//front
					glVertex3f(-1.0, 1.0, 0.0);//left wing
				glEnd();
			}
			if(ShipDrawingMode==1)
			{
				glBegin(GL_TRIANGLES);
					//bottom
					glVertex3f(1.0, 1.0, 0.0);//front left
					glVertex3f(-1.0, 1.0, 0.0);//left wing
					glVertex3f(-1.0, -1.0, 0.0);//right wing

					glVertex3f(1.0, 1.0, 0.0);//front left
					glVertex3f(1.0, -1.0, 0.0);//front right
					glVertex3f(-1.0, -1.0, 0.0);//right wing

					//top
					glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
					glVertex3f(-1.0, 0.0, 0.5);//top
					mycolour.setcolour();
					glVertex3f(1.0, -1.0, 0.0);//front right
					glVertex3f(-1.0, -1.0, 0.0);//right wing

					glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
					glVertex3f(-1.0, 0.0, 0.5);//top
					mycolour.setcolour();
					glVertex3f(1.0, 1.0, 0.0);//front left
					glVertex3f(1.0, -1.0, 0.0);//front right

					glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
					glVertex3f(-1.0, 0.0, 0.5);//top
					mycolour.setcolour();
					glVertex3f(1.0, 1.0, 0.0);//front left
					glVertex3f(-1.0, 1.0, 0.0);//left wing

					//back
					glVertex3f(-1.0, 1.0, 0.0);//left wing
					glVertex3f(-1.0, -1.0, 0.0);//right wing
					glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
					glVertex3f(-1.0, 0.0, 0.5);//top
					mycolour.setcolour();
				glEnd();
			}
		glPopMatrix();
	}
	inline
	void setaccelerationstep(unsigned int AccelerationStep=1)
	{
		currentacceleration*=accelerationstep;
		accelerationstep=(AccelerationStep?AccelerationStep:1);
		currentacceleration/=accelerationstep;
	}
	inline
	void setacceleration(const myvector& NewAcceleration=myvector())//,
			//const unsigned int AverageOver=1)
	{
		unsigned int i;
		for (i=accelerationstep-1;i<acceleration.size();i++)
		{
			acceleration.erase(acceleration.begin());
		}
		acceleration.push_back(NewAcceleration);
		currentacceleration(0.0, 0.0, 0.0);
		for (i=0;i<acceleration.size();i++)
		{
			currentacceleration+=acceleration.at(i);
		}
		currentacceleration/=accelerationstep;
		//currentacceleration.printme();
	}
	inline
	void moveme(const unsigned int& AverageAccelerationOverFrames=1)
	{
		//myvector tmpvelocity=velocity+currentacceleration*ACCELERATIONMAGNITUDE;
		//if(tmpvelocity.getsquaredmagnitude()>1.0)tmpvelocity.normaliseme();
		//rotation*=quaternion(velocity.normalise(), tmpvelocity.normalise());
		//cout<<"Acc";
		//currentacceleration.printme();
		currentacceleration+=penaltyacceleration;
		//if(penaltyacceleration.getsquaredmagnitude()>0.1)cout<<"penaltyacceleration"<<endl<<flush;
		penaltyacceleration.setmymagnitude(0.0);
		velocity+=currentacceleration*ACCELERATIONMAGNITUDE/AverageAccelerationOverFrames;
		//velocity=tmpvelocity;
		if(velocity.getsquaredmagnitude()>1.0)velocity.normaliseme();
		position.movemebyvector(velocity*speed);
		rotation.rotationbetweentwovectorsme(defaultfront, velocity);
	}
	inline
	void dockingmoveme(const myvector& TargetSpeed=myvector())
	{
		if(dockinglinestate!=1.0)
		{
			velocity+=currentacceleration*ACCELERATIONMAGNITUDE;
			position.movemebyvector(velocity*speed*(1.0-dockinglinestate)+TargetSpeed*dockinglinestate);
			if(velocity.getsquaredmagnitude()>1.0)velocity.normaliseme();
			rotation.rotationbetweentwovectorsme(defaultfront, velocity);
		}
		else
		{
			position.movemebyvector(TargetSpeed);
		}
	}
	inline
	float howfull() const
	{
		return currentload/maxcapacity;
	}
	inline
	float load(const float& HowMuch=RESOURCESTRANSFERRATE)
	{
		currentload+=HowMuch;
		if(currentload<maxcapacity) return 0.0;
		float tmp=currentload-maxcapacity;
		currentload=maxcapacity;
		return tmp;
	}
	float loadfromtargetasteroid(const float& HowMuch=RESOURCESTRANSFERRATE)
	{
		float remainingload=maxcapacity-currentload;
		if(HowMuch<remainingload)
		{
			currentload+=asteroidtarget->mine(HowMuch);
			return HowMuch;
		}
		else
		{
			currentload+=asteroidtarget->mine(remainingload);
			return remainingload;
		}
	}
	inline
	float unload(const float& HowMuch=RESOURCESTRANSFERRATE)
	{
		currentload-=HowMuch;
		if(currentload>=0.0) return HowMuch;
		float tmp=-currentload;
		currentload=0.0;
		return HowMuch-tmp;
	}
	inline
	void dock(const point& Target)
	{
		if(dockinglinestate<1.0)
		{
			dockinglinestate+=DOCKINGINCREMENT;
			if(dockinglinestate>1.0)dockinglinestate=1.0;
			dockingline(position, Target)*=dockinglinestate;
		}
	}
	inline
	void undock()
	{
		if(dockinglinestate>0.0)
		{
			dockinglinestate-=DOCKINGINCREMENT;
			if(dockinglinestate<0.0)dockinglinestate=0.0;
			dockingline.setmymagnitude(dockinglinestate);
		}
	}
	inline
	bool docked()const
	{
		return dockinglinestate==1.0;
	}
	inline
	bool undocked()const
	{
		return dockinglinestate==0.0;
	}
	inline
	bool isempty()const
	{
		return currentload==0.0;
	}
	inline
	void setasteroidtarget(asteroid* NewAsteroidTarget=NULL)
	{
		unsetasteroidtarget();
		asteroidtarget=NewAsteroidTarget;//setting new asteroid
		if(asteroidtarget!=NULL)asteroidtarget->lock(mothershipcolour);//locking it
	}
	inline
	void unsetasteroidtarget()
	{
		if(asteroidtarget!=NULL)asteroidtarget->unlock(mothershipcolour);//unlocking old asteroid
		asteroidtarget=NULL;//clearing the pointer
	}
	bool makehit(const point& HitFrom, const float& HitCost=HITHEALTHCOST)
	{
		health-=HitCost;
		penaltyacceleration+=myvector(HitFrom, position).setmymagnitude(PENALTYACCELERATIONMAGNITUDE);
		if(health<0.0)//if ship is destroyed, it notifies ships that are targeting it to drop their target
		{
			untargetme();
			return true;//ship killed
		}
		return false;//ship not killed
	}
	inline
	void untargetme()
	{//notifies ships that are targeting it to drop their target
		if(SHIPSPEAK)cout<<"ship::untargetme"<<endl<<flush;
		for (unsigned int i=0;i<shipstargetingme.size();i++)
		{
			if(SHIPSPEAK)cout<<"@"<<shipstargetingme.at(i)<<" setting shiptarget "<<shipstargetingme.at(i)->shiptarget<<" to NULL"<<endl<<flush;
			shipstargetingme.at(i)->shiptarget=NULL;
			if(SHIPSPEAK)cout<<"~shipstargetingme.at(i)->shiptarget=NULL;"<<endl<<flush;
		}
		shipstargetingme.clear();
		for (unsigned int i=0;i<shipsprotectingme.size();i++)
		{
			if(SHIPSPEAK)cout<<"@"<<shipsprotectingme.at(i)<<" setting shiptarget "<<shipsprotectingme.at(i)->shiptoprotect<<" to NULL"<<endl<<flush;
			shipsprotectingme.at(i)->shiptoprotect=NULL;
			if(SHIPSPEAK)cout<<"~shipsprotectingme.at(i)->shiptoprotect=NULL;"<<endl<<flush;
		}
		shipsprotectingme.clear();
		if(SHIPSPEAK)cout<<"~ship::untargetme"<<endl<<flush;
	}
	inline
	void untarget()
	{
		if(SHIPSPEAK)cout<<"ship::untarget"<<endl<<flush;
		if(shiptarget!=NULL)
		{
			shiptarget->iamnottargetingyouanymore(this);
		}
		shiptarget=NULL;
		if(shiptoprotect!=NULL)
		{
			shiptoprotect->iamnotprotectingyouanymore(this);
		}
		shiptoprotect=NULL;
		if(SHIPSPEAK)cout<<"~ship::untarget"<<endl<<flush;
	}
	inline
	void iamtargetingyou(ship* Me)
	{
		shipstargetingme.push_back(Me);
	}
	inline
	void iamprotectingyou(ship* Me)
	{
		shipsprotectingme.push_back(Me);
	}
	inline
	void iamnottargetingyouanymore(ship* Me)
	{
		if(SHIPSPEAK)cout<<"ship::iamnottargetingyouanymore"<<endl<<flush;
		for(unsigned int i=0;i<shipstargetingme.size();i++)
		{
			if (shipstargetingme.at(i)==Me)
			{
				shipstargetingme.erase(shipstargetingme.begin()+i);
				break;
			}
		}
		if(SHIPSPEAK)cout<<"~ship::iamnottargetingyouanymore"<<endl<<flush;
	}
	inline
	void iamnotprotectingyouanymore(ship* Me)
	{
		if(SHIPSPEAK)cout<<"ship::iamnotprotectingyouanymore"<<endl<<flush;
		for(unsigned int i=0;i<shipsprotectingme.size();i++)
		{
			if (shipsprotectingme.at(i)==Me)
			{
				shipsprotectingme.erase(shipsprotectingme.begin()+i);
				break;
			}
		}
		if(SHIPSPEAK)cout<<"~ship::iamnotprotectingyouanymore"<<endl<<flush;
	}
	inline
	void setmothershipcolour(const colour& MothershipColour)
	{
		mothershipcolour=MothershipColour;
	}


	inline
	void heal()
	{
		health+=HEALINGRATE;
		if(health>100.0) health=100.0;
	}
	inline
	void healall()
	{
		health=100.0;
	}
	inline
	void jettison()
	{
		currentload=0.0;
		//cout<<"Jettison!"<<endl<<flush;
	}
	inline
	void resetdockingline()
	{
		dockinglinestate=0.0;
		dockingline(0.0, 0.0, 0.0);
	}
	inline
	void setendofpathreached()
	{
		endofpathreached=true;
	}
	inline
	void unsetpath()
	{
		pathset=false;
	}
	inline
	void setpath()
	{
		pathset=true;
	}
	inline
	void unsetendofpathreached()
	{
		endofpathreached=false;
	}
	inline
	bool wasendofpathreached()const
	{
		return endofpathreached;
	}
	inline
	bool ispathset()const
	{
		return pathset;
	}
	inline
	void addreward(const float& Reward)
	{
		tmpreward+=Reward;
	}
	inline
	float getreward()
	{
		float anwser=tmpreward;
		tmpreward=0.0;
		return anwser;
	}


};

vector<pair<void (ship::*)(void), string> > givetransitiontasks();

#endif /* SHIP_H_ */
