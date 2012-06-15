#ifndef SCENARIO2_H_
#define SCENARIO2_H_


#include "scenario.h"
#include "../math.h"
#include "../map.h"
#include "../ai.h"
#define SCENARIO2SHIPAMOUNT 100
#define LOOPED true
//#define LOOPED false


class scenario2:public scenario
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
	scenario2():
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
	~scenario2()
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
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		metagrid.clear();
		allpilots.clear();
		defaultfsm.clear();
		defaultfsme.clear();

		defaultsteering.reset();
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.2);
		defaultsteering.setseparation(0.3);
		defaultsteering.setcohesion(0.1);
		defaultsteering.setavoid(1.0);
		//defaultsteering.setasteroidavoid(1.0);
		defaultsteering.setfollow(3.0, 0.3, 0.5);

		steeringcontrol orders;
		orders.setgo(true);
		if (LOOPED)orders.setloopedpathfollow(true);
		else orders.setsinglepathfollow(true);
		decisionpreferences decprefs;

		state tmpstate(string("Follow"),
				//defaultsteering, decprefs,
				orders);

		defaultfsme.setname("Default");
		defaultfsme.addstate(tmpstate);

		defaultfsme.setcurrentstate("Follow");

		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);

		defaultfsm.addfsme(defaultfsme);

		myhud=HUD;
		cam=Camera;
		mystars=Stars;
		myhud->settopleft(string("Scenario 2"));

		mypath.clear();

		//mystars->setstars(SIZE, SCENARIO2STARS);
		//cam->setzoom(5.0*SIZE);
		//myboids->setamount(SCENARIO2BOIDAMOUNT);
		//myboids->setuniverse(*mystars);
		//myboids->setdisplay(&myhud->topleft);
		//myboids->setallsteering(1.0, 0.0, 0.0, 0.0, 1.0);

		tmptime=time(NULL);
		vector <point> points;
		points.push_back(point(0.0, 0.0, 0.0));
		points.push_back(point(0.0, 10.0, 0.0));
		points.push_back(point(0.0, 0.0, 10.0));
		points.push_back(point(10.0, 0.0, 0.0));
		points.push_back(point(10.0, 10.0, 0.0));
		mypath.addpoints(points);


		/*mypath.addpoint(point(0.0, 0.0, 0.0));
		mypath.addpoint(point(0.0, 10.0, 0.0));
		mypath.addpoint(point(0.0, 0.0, 10.0));
		mypath.addpoint(point(10.0, 0.0, 0.0));
		mypath.addpoint(point(10.0, 10.0, 0.0));*/

		//myboids->setboidsloopedpath(mypath);

		allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(SCENARIO2SHIPAMOUNT);
		if (LOOPED)allpilots.setdefaultloopedpath(mypath);
		else allpilots.setdefaultsinglepath(mypath);

		for (unsigned int i=0;i<SCENARIO2SHIPAMOUNT;i++)
		{
			allpilots.newbasicpilot2(myrandom->randomcubeposition(5));
		}
		if (LOOPED)allpilots.assignloopedpath();
		else allpilots.assignsinglepath();
		metagrid.checkallships();
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

		mypath.drawme();
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
		/*case (int)'9':
			for (unsigned int i=0;i<pilots.size();i++)
			{
				pilots.at(i).setboidsloopedpath(mypath);
			}
			break;*/
		default:
			break;
		}
	}
};

#endif /* SCENARIO2_H_ */
