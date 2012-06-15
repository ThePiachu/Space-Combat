#ifndef SCENARIO8_H_
#define SCENARIO8_H_

#include "scenario.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO8ITERATIONTIME 10
#define SCENARIO8SHIPAMOUNT 50
#define EVOLUTIONSCENARIO true
#define SCENARIO8STARTINGSHIPS 10

class scenario8:public scenario
{
	char Chars[100];
	int x, y, fps, tmptime;
	string result;
	asteroids myasteroids;
	grid metagrid;
	//pilots allpilots;
	//vector<pilot*> pilots;
	//steeringpreferences defaultsteering;
	unsigned int displaygrid;
	mothershipai mai1;
	mothershipai mai2;
	//fsme defaultfsme;
	//fsm defaultfsm;
public:
	scenario8():// scenario(),
	x(0), y(0), fps(0), tmptime(time(NULL)),
	result(),
	myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 20.0, point(0.0, 0.0, 20.0), 0.1),
	metagrid(2.0),
	//allpilots(),
	//defaultsteering(),
	displaygrid(1),
	mai1(point(10.0, 0.0, 0.0), 8, 2, 1, 0, &metagrid),
	mai2(point(-10.0, 0.0, 0.0), 8, 1, 2, 0, &metagrid)
	{
		mai1.me.velocity=0.0;
		mai1.setdefaultpilot(pilot::exampleangrypilot());
		mai2.me.velocity=0.0;
		mai2.setdefaultpilot(pilot::exampleangrypilot());
		//mai.setmycolour(2, 1, 0);
		mai1.setusefilepilot(USEFILEPILOT);
		mai2.setusefilepilot(USEFILEPILOT);
	}
	void nexttime()
	{
		x++;
		if(x%3==0)
		{
			myasteroids.generateasteroid();

		}
		if (tmptime!=time(NULL))
		{
			if(EVOLUTIONSCENARIO)
			{
				/*mai1.newevolvedpilot();
				mai2.newevolvedpilot();*/
				mai1.newbasicpilot();
				//if (y%10==0)
					mai2.newbasicpilot();


				mai1.newbasicpilot();
				mai2.newbasicpilot();
				mai1.newbasicpilot();
				mai2.newbasicpilot();
				mai1.newbasicpilot();
				mai2.newbasicpilot();
			}
			printstring();
			//myasteroids.generateasteroid();
			y++;
			/*if(EVOLUTIONSCENARIO)
				if(y%10==0)
					mai.killoldestboid();*/
			tmptime=time(NULL);
			fps=x;
			x=0;
			/*cout<<"Counting"<<endl<<flush;
			cout<<"All ships: "<<mai.allpilots.allpilots.size()<<endl<<flush;
			cout<<"All ships in gridelements: "<<metagrid.countallships()<<endl<<flush;
			cout<<"Asteroids: "<<myasteroids.allasteroids.size()<<endl<<flush;
			cout<<"Asteroids in gridelements: "<<metagrid.countasteroids()<<endl<<flush;
			cout<<"Friendly ships in gridelements: "<<metagrid.countfriendlyships()<<endl<<flush;*/
		}
		//allpilots.nexttime();
		mai1.nexttime();
		mai2.nexttime();
		//mai.stopme();
		//mai.moveme();

		myasteroids.moveme();
		metagrid.checkallasteroids();
		myasteroids.checkfordeletion();
		metagrid.checkallships();
		//metagrid.checkallfriendlyships();
		if(EVOLUTIONSCENARIO)
			//mai.checkfordeletion();
			metagrid.checkcolisionswithshiphit();
			//mai.checkfordeadpilots();
			//allpilots.deleteships(metagrid.checkcolisionswithdeletion());
		metagrid.agegrid(true);
	}
	~scenario8()
	{
		metagrid.clear();
		myasteroids.clear();
		mai1.clear();
		mai2.clear();
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		myhud=HUD;
		myhud->settopleft(string("Scenario 8"));
		vector<colour> tmp;
		tmp.push_back(colour(1.0, 1.0, 1.0));
		if (myhud!=NULL)myhud->settopleftcolour(tmp);
		cam=Camera;

		metagrid.clear();
		myasteroids.clear();
		myasteroids.setgrid(&metagrid);
		/*mai1.clear();
		mai1.restart(SCENARIO8STARTINGSHIPS, SCENARIO8SHIPAMOUNT);
		mai2.clear();
		mai2.restart(SCENARIO8STARTINGSHIPS, SCENARIO8SHIPAMOUNT);*/
		mai1.clear();
		mai1.restart(SCENARIO8STARTINGSHIPS, SCENARIO8SHIPAMOUNT, false, false);
		mai2.clear();
		//mai2.setdefaultpilot(pilot::exampleangrypilot());
		mai2.restart(SCENARIO8STARTINGSHIPS, SCENARIO8SHIPAMOUNT, false, false);




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
			myasteroids.drawme();
			metagrid.drawme(displaygrid);
			//allpilots.drawme(1);
			mai1.drawme(true, 1);
			mai2.drawme(true, 1);
		glPopMatrix();
	}
	void handlekey(int Key)
	{
		switch(Key)
		{
			break;
		case (int)'?':
			//allpilots.printallstates();
			myasteroids.printlocks();
			break;
		case (int)'/':
			displaygrid++;
			break;
		case (int) '!':
			if(USEFILEPILOT)
			{
				mai1.allpilots.fp.compiledata(false);
				mai2.allpilots.fp.compiledata(false);
			}
			break;
		}
	}


	void printstring()
	{
		result=string("FPS: ")+itoa(fps, Chars, 10);
		result+=string("  Number of asteroids: ")+itoa(myasteroids.allasteroids.size(), Chars, 10);
		//result+=string("  In grid: ")+itoa(metagrid.allasteroidssize(), Chars, 10);
		//result+=string("  In grids: ")+itoa(metagrid.countasteroids(), Chars, 10);
		myhud->setbottomleft(result);

		result=string("At ")+itoa(y, Chars, 10);
		result+=string("\nNumber of boids 1: ")+itoa(mai1.pilotssize(), Chars, 10);
		result+=string("\nNumber of boids 2: ")+itoa(mai2.pilotssize(), Chars, 10);

		myhud->settopleft(result);
		//cout<<result<<endl<<flush;
	}

};

#endif /* SCENARIO8_H_ */
