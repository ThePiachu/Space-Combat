#ifndef SCENARIO1_H_
#define SCENARIO1_H_

#include "scenario.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO1STARS 5000
//#define SCENARIO1BOIDAMOUNT 300
#define SCENARIO1ITERATIONTIME 10
#define SCENARIO1SHIPAMOUNT 100
//#define SCENARIO1SHIPAMOUNT 0
#define SCENARIO1STARTINGSHIPS 0
//#define SCENARIO1SHIPAMOUNT 0

class scenario1:public scenario
{
	char Chars[100];
	int x, y, fps, tmptime;
	string result;
	asteroids myasteroids;
	grid metagrid;
	//pilots allpilots;
	//vector<pilot*> pilots;
	steeringpreferences defaultsteering;
	unsigned int displaygrid;
	fsme defaultfsme;
	fsm defaultfsm;
	mothershipai mai;
	bool writetext;
public:
	scenario1():
	x(0), y(0), fps(0), tmptime(time(NULL)),
	result(),
	myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 20.0, point(0.0, 0.0, 20.0), 0.1),
	metagrid(4.0),
	displaygrid(1),
	mai(point(0.0, 0.0, 0.0), 1, 1, 2, 0, &metagrid, 0.0),
	writetext(true)
	{
		mai.me.velocity=0.0;
		mai.setusefilepilot(USEFILEPILOT);
	}
	void nexttime()
	{
		//if(x%3==0)myasteroids.generateasteroid();
		myasteroids.generateasteroid();
		myasteroids.generateasteroid();
		myasteroids.generateasteroid();
		myasteroids.generateasteroid();
		myasteroids.generateasteroid();
		//myasteroids.generateasteroid();
		//myasteroids.generateasteroid();
		//myasteroids.generateasteroid();
		//myasteroids.generateasteroid();
		x++;
		if (tmptime!=time(NULL))
		{
			y++;
			tmptime=time(NULL);
			fps=x;
			x=0;
			result=string("FPS: ")+itoa(fps, Chars, 10);
			result+=string("  Number of asteroids: ")+itoa(myasteroids.numberofasteroids(), Chars, 10);
			result+=string("  Number of boids: ")+itoa(mai.allpilots.size(), Chars, 10);
			myhud->setbottomleft(result);

			mai.newevolvedpilot();
			mai.newevolvedpilot();
			//allpilots.newevolvedpilot2(myrandom->randomcubeposition(5), true);
			//allpilots.newevolvedpilot2(myrandom->randomcubeposition(5), true);

			steeringpreferences tmp(mai.allpilots.giveaveragesteeringpreferences());
			result=string("At ")+itoa(y, Chars, 10);
			//cout<<"At "<<y<<endl;
			//tmp.printme();
			result+=tmp.print();
			cout<<result<<endl<<flush;

			if(myhud!=NULL) if(writetext) myhud->settopleft(result);

		}
		mai.nexttime();
		//allpilots.nexttime();

		myasteroids.moveme();
		metagrid.checkallasteroids();
		myasteroids.checkfordeletion();
		metagrid.checkallships();
		//metagrid.checkallfriendlyships();
		metagrid.checkcolisionswithshiphit(true, 100.0);
		//allpilots.checkfordeadpilots();
		//allpilots.deleteships(metagrid.checkcolisionswithdeletion());
		metagrid.agegrid(true);

	}
	~scenario1()
	{
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		metagrid.clear();
		myasteroids.clear();
		myasteroids.setgrid(&metagrid);
		//allpilots.clear();
		defaultfsm.clear();
		defaultfsme.clear();

		defaultsteering.reset();
		defaultsteering.setwander(0.7);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(0.1, 0.5);
		defaultsteering.setasteroidavoid(0.1, 0.5);
		defaultsteering.setgravitate(0.1, 25.0);
		//defaultsteering.setgravitate(0.1, 200.0);

		steeringcontrol orders;
		orders.setgo(true);
		orders.setgravitateplace(true);

		decisionpreferences decprefs;

		state tmpstate(string("Default"),
				//defaultsteering, decprefs,
				orders);

		defaultfsme.setname("Default");
		defaultfsme.addstate(tmpstate);


		defaultfsme.addstate(tmpstate);

		defaultfsme.setcurrentstate("Default");


		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);


		defaultfsm.addfsme(defaultfsme);
		mai.setdefaultpilotfsm(defaultfsm);
		//defaultfsm.printme();

		myhud=HUD;
		myhud->settopleft(string("Scenario 1"));
		vector<colour> tmp;
		tmp.push_back(colour(1.0, 1.0, 1.0));
		if (myhud!=NULL)myhud->settopleftcolour(tmp);
		cam=Camera;
		mystars=Stars;

		metagrid.clear();
		myasteroids.clear();
		myasteroids.setgrid(&metagrid);
		mai.clear();
		mai.setdefaultpilotfsm(defaultfsm);
		mai.setallpilotsfsm(defaultfsm);
		mai.restart(SCENARIO1STARTINGSHIPS, SCENARIO1SHIPAMOUNT);

		/*allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(2*SCENARIO1SHIPAMOUNT);
		for (unsigned int i=0;i<SCENARIO1SHIPAMOUNT;i++)
		{
			allpilots.newbasicpilot2(myrandom->randomcubeposition(5), true);
		}*/

		mystars->setstars(SIZE, SCENARIO1STARS);
		//cam->setzoom(3.0*SIZE);

		tmptime=time(NULL);
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
			mystars->drawme();
			myasteroids.drawme();
			metagrid.drawme(displaygrid);
			mai.drawships(true, 1);
		glPopMatrix();
	}
	void handlekey(int Key)
	{
		switch(Key)
		{
		case (int)'1':
			mystars->fillcube();
			break;
		case (int)'2':
			mystars->fillbox();
			break;
		case (int)'3':
			mystars->filldisc();
			break;
		case (int)'4':
			mystars->fillsphere();
			break;
		case (int)'5':
			mystars->fillsquare();
			break;
		case (int)'6':
			mystars->fillbubble();
			break;
		case (int)'`':
		   	mystars->randomizestars();
			break;
		case (int)'.':
			myasteroids.generateasteroid();
			myasteroids.generateasteroid();
			myasteroids.generateasteroid();
			myasteroids.generateasteroid();
			myasteroids.generateasteroid();
			break;
		case (int)'-':
			writetext=!writetext;
			if (writetext==false)if(myhud!=NULL)myhud->settopleft(string(""));
			if(writetext==true) cout<<"writetext==true"<<endl<<flush;
			if(writetext==false) cout<<"writetext==false"<<endl<<flush;
			break;
		case (int)'/':
			displaygrid++;
			break;
		case (int) ',':
			metagrid.checkallasteroids();
			break;
		case (int) '!':
			if(USEFILEPILOT)mai.allpilots.fp.compiledata(false);
			break;
		}
	}

};

#endif /* SCENARIO1_H_ */
