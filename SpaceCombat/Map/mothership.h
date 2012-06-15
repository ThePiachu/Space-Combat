/*
 * mothership.h
 *
 *  Created on: 2010-01-22
 *      Author: ThePiachu
 */

#ifndef MOTHERSHIP_H_
#define MOTHERSHIP_H_

#include "ship.h"

class mothership: public ship
{
public:
	float resources;
	mothership(const point& Position=point(),
			const colour& Colour=colour(),
			const float& Speed=0.01,
			const float& Acceleration=0.01,
			const myvector& Front=myvector(0.0, 0.0, 1.0)):
			ship(Position, Colour, Speed, Acceleration, Front),
			resources(0.0)
	{
		//movement=myvector(2.0, 0.0, 0.0);
	}
	~mothership()
	{
	}

	void drawship(const unsigned int ShipDrawingMode=0)const
	{
		//glVertex3f(0.0, 0.0, 0.0);
		mycolour.setcolour();
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);//a distinctive top of boid
		glVertex3f(0.0, 0.0, 1.0);
		mycolour.setcolour();
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);//a distinctive bottom of boid
		glVertex3f(0.0, 0.0, -1.0);
		mycolour.setcolour();
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);//a distinctive bottom of boid
		glVertex3f(0.0, 0.0, -1.0);

		mycolour.setcolour();
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);//a distinctive bottom of boid
		glVertex3f(0.0, 0.0, 1.0);
		glEnd();
	}
	float loadresources(const float& HowMuch)
	{
		resources+=HowMuch;
		return HowMuch;
	}
	float unloadresources(const float& HowMuch)
	{
		resources-=HowMuch;
		if(resources>0.0)return HowMuch;
		else
		{
			float tmp=resources;
			resources=0.0;
			return HowMuch+tmp;
		}

	}
	inline
	void setresources(const float& NewResources)
	{
		resources=NewResources;
	}
	inline
	float score()const
	{
		return resources;
	}
};

#endif /* MOTHERSHIP_H_ */
