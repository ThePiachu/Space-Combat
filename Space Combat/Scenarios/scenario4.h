#ifndef SCENARIO4_H_
#define SCENARIO4_H_

#include "scenario.h"
#include "../math.h"
#include "../map.h"
#include "../ai.h"
//#define SCENARIO4STARS 5000
//#define SCENARIO4BOIDAMOUNT 1500
#define SCENARIO4SHIPAMOUNT 200
class scenario4:public scenario
{
	char Chars[100];
	int i, fps, tmptime;
	string result;
	path mypath;
	grid metagrid;
	pilots allpilots;
	steeringpreferences defaultsteering;
	unsigned int displaygrid;
	fsme defaultfsme;
	fsm defaultfsm;
public:
	scenario4():
		i(0), fps(0), tmptime(time(NULL)),
		result(),
		mypath(),
		metagrid(2.0),
		allpilots(),
		defaultsteering(),
		displaygrid(1),
		defaultfsme(),
		defaultfsm()
	{
	}
	~scenario4()
	{
		allpilots.clear();
	}
	void nexttime()
	{

		i++;
		if (tmptime!=time(NULL))
		{
			tmptime=time(NULL);
			fps=i;
			i=0;
			result=string("FPS: ")+itoa(fps, Chars, 10);
			myhud->setbottomleft(result);
		}

		allpilots.nexttime();
		metagrid.checkallships();
		//myboids->moveme();
		//myboids->moveme(2, i%2);
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		metagrid.clear();
		allpilots.clear();
		defaultsteering.reset();
		defaultfsm.clear();
		defaultfsme.clear();

		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.2);
		defaultsteering.setseparation(0.3);
		defaultsteering.setcohesion(0.1);
		defaultsteering.setavoid(1.0);
		defaultsteering.setfollow(3.0, 0.3, 0.5);

		/*defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(1.0);
		//defaultsteering.setfollow(1.0, 0.6, 1.0);
		defaultsteering.setfollow(5.0, 0.5, 1.0);*/
		steeringcontrol orders;
		orders.setgo(true);
		orders.setloopedpathfollow(true);
		decisionpreferences decprefs;

		state tmpstate(string("Follow"),
				//defaultsteering, decprefs,
				orders);

		fsme defaultfsme;
		defaultfsme.setname("Default");
		defaultfsme.addstate(tmpstate);

		defaultfsme.setcurrentstate("Follow");

		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);

		defaultfsm.addfsme(defaultfsme);


		myhud=HUD;
		cam=Camera;
		myhud->settopleft(string("Scenario 4"));
		//myboids=Boids;
		mystars=Stars;

		mypath.clear();

		//mystars->setstars(SIZE, SCENARIO4STARS);
		//cam->setzoom(7.0*SIZE);
		//myboids->setamount(SCENARIO4BOIDAMOUNT);
		//myboids->setuniverse(*mystars);
		//myboids->setdisplay(&myhud->topleft);
		//myboids->setallsteering(1.0, 0.0, 0.0, 0.0, 1.0);

		tmptime=time(NULL);

		// HEY
		//CHRIS
		//path:

		//loop back to H:
		mypath.addpoint(point(-5.0, 6.0, -3.0));
		//H
		mypath.addpoint(point(-5.0, 6.0, 0.0));
		mypath.addpoint(point(-5.0, 1.0, 0.0));
		mypath.addpoint(point(-5.0, 3.5, 0.0));
		mypath.addpoint(point(-3.0, 3.5, 0.0));
		mypath.addpoint(point(-3.0, 6.0, 0.0));
		mypath.addpoint(point(-3.0, 1.0, 0.0));

		//fade into background
		mypath.addpoint(point(-3.0, 1.0, -3.0));
		mypath.addpoint(point(1.0, 6.0, -3.0));

		//E
		mypath.addpoint(point(1.0, 6.0, 0.0));
		mypath.addpoint(point(-1.0, 6.0, 0.0));
		mypath.addpoint(point(-1.0, 3.5, 0.0));
		mypath.addpoint(point(0.0, 3.5, 0.0));
		mypath.addpoint(point(-1.0, 3.5, 0.0));
		mypath.addpoint(point(-1.0, 1.0, 0.0));
		mypath.addpoint(point(1.0, 1.0, 0.0));

		//fade into background
		mypath.addpoint(point(1.0, 1.0, -3.0));
		mypath.addpoint(point(3.0, 6.0, -3.0));

		//Y
		mypath.addpoint(point(3.0, 6.0, 0.0));
		mypath.addpoint(point(4.0, 3.5, 0.0));
		mypath.addpoint(point(5.0, 6.0, 0.0));
		mypath.addpoint(point(4.0, 3.5, 0.0));
		mypath.addpoint(point(4.0, 1.0, 0.0));


		mypath.addpoint(point(4.0, 1.0, -3.0));
		mypath.addpoint(point(-7.0, 0.0, -3.0));

		//C
		mypath.addpoint(point(-7.0, 0.0, 0.0));
		mypath.addpoint(point(-9.0, 0.0, 0.0));
		mypath.addpoint(point(-9.0, -4.0, 0.0));
		mypath.addpoint(point(-7.0, -4.0, 0.0));


		mypath.addpoint(point(-7.0, -4.0, -3.0));
		mypath.addpoint(point(-5.0, 0.0, -3.0));

		//H
		mypath.addpoint(point(-5.0, 0.0, 0.0));
		mypath.addpoint(point(-5.0, -4, 0.0));
		mypath.addpoint(point(-5.0, -2.0, 0.0));
		mypath.addpoint(point(-3.0, -2.0, 0.0));
		mypath.addpoint(point(-3.0, 0.0, 0.0));
		mypath.addpoint(point(-3.0, -4.0, 0.0));


		mypath.addpoint(point(-3.0, -4.0, -3.0));
		mypath.addpoint(point(-1.0, -4.0, -3.0));

		//R
		mypath.addpoint(point(-1.0, -4.0, 0.0));
		mypath.addpoint(point(-1.0, 0.0, 0.0));
		mypath.addpoint(point(0.0, 0.0, 0.0));
		mypath.addpoint(point(1.0, -1.0, 0.0));
		mypath.addpoint(point(0.0, -2.0, 0.0));
		mypath.addpoint(point(1.0, -4.0, 0.0));


		mypath.addpoint(point(1.0, -4.0, -3.0));
		mypath.addpoint(point(4.0, -4.0, -3.0));

		//I
		mypath.addpoint(point(3.5, -4.0, 0.0));
		mypath.addpoint(point(3.5, 0.0, 0.0));
		//I again
		mypath.addpoint(point(3.5, -4.0, 0.0));
		mypath.addpoint(point(3.3, 0.0, 0.0));

		mypath.addpoint(point(3.5, 0.0, -3.0));
		mypath.addpoint(point(8.0, 0.0, -3.0));

		//S
		mypath.addpoint(point(8.0, 0.0, 0.0));
		mypath.addpoint(point(6.0, 0.0, 0.0));
		mypath.addpoint(point(6.0, -2.0, 0.0));
		mypath.addpoint(point(8.0, -2.0, 0.0));
		mypath.addpoint(point(8.0, -4.0, 0.0));
		mypath.addpoint(point(6.0, -4.0, 0.0));


		mypath.addpoint(point(6.0, -4.0, -3.0));
		//and loops back to H

		allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(SCENARIO4SHIPAMOUNT);

		allpilots.setdefaultloopedpath(mypath);


		for (unsigned int i=0;i<SCENARIO4SHIPAMOUNT;i++)
		{
			allpilots.newbasicpilot2(myrandom->randomcubeposition(8));
		}
		allpilots.assignloopedpath();
		//myboids->setboidsloopedpath(mypath);
	}
	void drawme()
	{
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		//cam.rotatecamera();

			//drawing the 3 unit vectors
			glBegin(GL_LINES);
				glColor3f(1.0,0.0,0.0);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(1.0,0.0,0.0);

				glColor3f(0.0,1.0,0.0);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(0.0,1.0,0.0);

				glColor3f(0.0,0.0,1.0);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(0.0,0.0,1.0);
			glEnd();
			glColor3f(1.0,1.0,1.0);
			//mystars->drawme();
		glPopMatrix();

		//myboids->drawme();

		allpilots.drawme();
		metagrid.drawme(displaygrid);
	}
	void handlekey(int Key)
	{
		switch(Key)
		{
		case (int)'/':
			displaygrid++;
			break;
		default:
			break;
		}
	}
};

#endif /* SCENARIO4_H_ */
