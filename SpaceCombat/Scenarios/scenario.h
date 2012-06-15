#ifndef SCENARIO_H_
#define SCENARIO_H_

#define SIZE 5

#include "../cams.h"
#include "../math.h"
#include "../stars.h"
#include "../hud.h"
#include "../map.h"
#include "../AI/astar.h"

#include <iostream>

#define USEFILEPILOT false //global variable to disable the use of filepilot class
//#define USEFILEPILOT true //global variable to disable the use of filepilot class

using namespace std;

class scenario
{
public:
	hud *myhud;
	quaternioncamera2 *cam;
	//boids *myboids;
	stars *mystars;
	random* myrandom;
	scenario():
	myhud(NULL),
	cam(NULL),
	mystars(NULL),
	myrandom(random::getinstance())
	{
	}
	virtual ~scenario()
	{
	}
	void virtual startscenario(quaternioncamera2 *Camera, hud* HUD,
			stars *Stars)
	{
		myhud=HUD;
		cam=Camera;
		mystars=Stars;
	}
	void virtual handlekey (const int& Key)
	{
	}
	void virtual nexttime()
	{
	}
	void virtual drawme() const
	{
	}
};

#endif /* SCENARIO_H_ */
