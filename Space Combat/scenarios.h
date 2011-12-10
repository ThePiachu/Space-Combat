#ifndef SCENARIOS_H_
#define SCENARIOS_H_

#define NUMBEROFSCENARIOS 10
#define DEFAULTSCENARIO 0

#include "Scenarios/scenario.h"
#include "Scenarios/scenario0.h"
#include "Scenarios/scenario1.h"
#include "Scenarios/scenario2.h"
#include "Scenarios/scenario3.h"
#include "Scenarios/scenario4.h"
#include "Scenarios/scenario5.h"
#include "Scenarios/scenario6.h"
#include "Scenarios/scenario7.h"
#include "Scenarios/scenario8.h"
#include "Scenarios/scenario9.h"
#include "Scenarios/scenario10.h"



#include "cams.h"
#include "math.h"
#include "stars.h"
#include "hud.h"
#include "map.h"
#include "AI/astar.h"

#include <iostream>

using namespace std;






class scenarios
{
	stars mystars;
	quaternioncamera2 *cam;
	hud *myhud;
	int currentscenario;
	scenario0 s0;
	scenario1 s1;
	scenario2 s2;
	scenario3 s3;
	scenario4 s4;
	scenario5 s5;
	scenario6 s6;
	scenario7 s7;
	scenario8 s8;
	scenario9 s9;
	scenario10 s10;
public:
	scenarios(): currentscenario(DEFAULTSCENARIO)
	{
	}
	~scenarios()
	{
	}
	void setscenario(unsigned int Number=DEFAULTSCENARIO)
	{
		if (Number<=NUMBEROFSCENARIOS)
		{
			currentscenario=Number;
		}
		else currentscenario=DEFAULTSCENARIO;
		switch(currentscenario)
		{
		case 0:
			s0.startscenario(cam, myhud, &mystars);
			break;
		case 1:
			s1.startscenario(cam, myhud, &mystars);
			break;
		case 2:
			s2.startscenario(cam, myhud, &mystars);
			break;
		case 3:
			s3.startscenario(cam, myhud, &mystars);
			break;
		case 4:
			s4.startscenario(cam, myhud, &mystars);
			break;
		case 5:
			s5.startscenario(cam, myhud, &mystars);
			break;
		case 6:
			s6.startscenario(cam, myhud, &mystars);
			break;
		case 7:
			s7.startscenario(cam, myhud, &mystars);
			break;
		case 8:
			s8.startscenario(cam, myhud, &mystars);
			break;
		case 9:
			s9.startscenario(cam, myhud, &mystars);
			break;
		case 10:
			s10.startscenario(cam, myhud, &mystars);
			break;
		}
	}
	void setscenarios(quaternioncamera2 *Camera, hud* HUD)
	{
		cam=Camera;
		myhud=HUD;
		setscenario(DEFAULTSCENARIO);
	}
	void handlekey (const int& Key)
	{

		switch (currentscenario)
		{
		case 0:
			s0.handlekey(Key);
			break;
		case 1:
			s1.handlekey(Key);
			break;
		case 2:
			s2.handlekey(Key);
			break;
		case 3:
			s3.handlekey(Key);
			break;
		case 4:
			s4.handlekey(Key);
			break;
		case 5:
			s5.handlekey(Key);
			break;
		case 6:
			s6.handlekey(Key);
			break;
		case 7:
			s7.handlekey(Key);
			break;
		case 8:
			s8.handlekey(Key);
			break;
		case 9:
			s9.handlekey(Key);
			break;
		case 10:
			s10.handlekey(Key);
			break;
		default:
			break;
		}

	}
	void handlespecialkey (const int& Key)
	{
		switch(Key)
		{
		case GLUT_KEY_F1:
			setscenario(1);
			break;
		case GLUT_KEY_F2:
			setscenario(2);
			break;
		case GLUT_KEY_F3:
			setscenario(3);
			break;
		case GLUT_KEY_F4:
			setscenario(4);
			break;
		case GLUT_KEY_F5:
			setscenario(5);
			break;
		case GLUT_KEY_F6:
			setscenario(6);
			break;
		case GLUT_KEY_F7:
			setscenario(7);
			break;
		case GLUT_KEY_F8:
			setscenario(8);
			break;
		case GLUT_KEY_F9:
			setscenario(9);
			break;
		case GLUT_KEY_F10:
			setscenario(10);
			break;
		case GLUT_KEY_F11:
			setscenario();
			break;
		case GLUT_KEY_F12:
			setscenario();
			break;
		default:
			break;
		}
	}
	void nexttime()
	{
		switch (currentscenario)
		{
		case 0:
			s0.nexttime();
			break;
		case 1:
			s1.nexttime();
			break;
		case 2:
			s2.nexttime();
			break;
		case 3:
			s3.nexttime();
			break;
		case 4:
			s4.nexttime();
			break;
		case 5:
			s5.nexttime();
			break;
		case 6:
			s6.nexttime();
			break;
		case 7:
			s7.nexttime();
			break;
		case 8:
			s8.nexttime();
			break;
		case 9:
			s9.nexttime();
			break;
		case 10:
			s10.nexttime();
			break;
		default:
			break;
		}
	}
	void drawme()
	{
		switch (currentscenario)
		{
		case 0:
			s0.drawme();
			break;
		case 1:
			s1.drawme();
			break;
		case 2:
			s2.drawme();
			break;
		case 3:
			s3.drawme();
			break;
		case 4:
			s4.drawme();
			break;
		case 5:
			s5.drawme();
			break;
		case 6:
			s6.drawme();
			break;
		case 7:
			s7.drawme();
			break;
		case 8:
			s8.drawme();
			break;
		case 9:
			s9.drawme();
			break;
		case 10:
			s10.drawme();
			break;
		default:
			break;
		}
	}
};








#endif /* SCENARIOS_H_ */
