#ifndef SCENARIO10_H_
#define SCENARIO10_H_

#include "scenario.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO10ITERATIONTIME 10
#define SCENARIO10SHIPAMOUNT 50
//#define SCENARIO10SHIPAMOUNT 10
#define EVOLUTIONSCENARIO true
#define EVOLUTIONSPECIALSCENARIO true
#define SCENARIO10STARTINGSHIPS 0
#define COSTRATIO 1.0
#define FIGHTERPROBABILITY 0.7

#define SCENARIO10SPEAK false

class scenario10:public scenario
{
	char Chars[100];
	int x, y, fps, tmptime;
	string result;
	asteroids myasteroids;
	grid metagrid;
	unsigned int displaygrid;
	mothershipai mai1;
	mothershipai mai2;
public:
	scenario10():// scenario(),
	x(0), y(0), fps(0), tmptime(time(NULL)),
	result(),
	//myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 5.0, point(0.0, 0.0, 20.0), 0.1),
	myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 3.0, point(0.0, 0.0, 20.0), 0.1),
	metagrid(2.0),
	displaygrid(1),
	mai1(point(10.0, 0.0, 0.0), 10, 2, 1, 0, &metagrid),
	mai2(point(-10.0, 0.0, 0.0), 10, 1, 2, 0, &metagrid)
	{
		mai1.me.velocity=0.0;
		mai1.setdefaultpilot(pilot::examplefighter(), false);
		mai1.setdefaultpilot(pilot::exampleminer(), true);
		mai1.setgeneratefighterprobability(FIGHTERPROBABILITY);
		mai1.setresources(50.0);
		mai2.me.velocity=0.0;
		mai2.setdefaultpilot(pilot::examplefighter(), false);
		mai2.setdefaultpilot(pilot::exampleminer(), true);
		mai2.setgeneratefighterprobability(FIGHTERPROBABILITY);
		mai2.setresources(50.0);
		mai1.setusefilepilot(USEFILEPILOT);
		mai2.setusefilepilot(USEFILEPILOT);

	}
	void nexttime()
	{
		if(SCENARIO10SPEAK)cout<<"nexttime"<<endl<<flush;
		if(SCENARIO10SPEAK)cout<<"x: "<<x<<endl<<flush;
		x++;
		//if(x%10==0)
		if(x%20==0)
		{
			myasteroids.generateasteroid();
		}
		printstring();
		if (tmptime!=time(NULL))
		{
			y++;
			if(EVOLUTIONSCENARIO)
			{
				if(SCENARIO10SPEAK)cout<<"decidewhattogenerate"<<endl<<flush;
				/*mai1.newevolvedpilot();
				mai2.newevolvedpilot();*/
				mai1.decidewhattogenerate(COSTRATIO, true, true, EVOLUTIONSPECIALSCENARIO);
				mai2.decidewhattogenerate(COSTRATIO, false, false);
				if(SCENARIO10SPEAK)cout<<"~decidewhattogenerate"<<endl<<flush;
				//cout<<"decidewhattogenerate"<<endl<<flush;
			}
			//myasteroids.generateasteroid();
			if(EVOLUTIONSCENARIO)
				if(y%10==0)
				{
					if(SCENARIO10SPEAK)cout<<"killoldestpilot"<<endl<<flush;
					mai1.killoldestpilot();
					mai2.killoldestpilot();
					//mai1.killoldestpilot(true);
					//mai2.killoldestpilot(true);
					//mai1.killoldestpilot(false);
					//mai2.killoldestpilot(false);
					if(SCENARIO10SPEAK)cout<<"~killoldestpilot"<<endl<<flush;
				}
			tmptime=time(NULL);
			fps=x;
			x=0;
		}
		//allpilots.nexttime();
		if(SCENARIO10SPEAK)cout<<"mai nexttime"<<endl<<flush;
		mai1.nexttime();
		mai2.nexttime();
		if(SCENARIO10SPEAK)cout<<"~mai nexttime"<<endl<<flush;
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
		if(SCENARIO10SPEAK)cout<<"~nexttime"<<endl<<flush;
	}
	~scenario10()
	{
		mai1.clear();
		mai2.clear();
		myasteroids.clear();
		metagrid.clear();
		myasteroids.clear();
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		myhud=HUD;
		myhud->settopleft(string("Scenario 10"));
		vector<colour> tmp;
		tmp.push_back(colour(1.0, 1.0, 1.0));
		if (myhud!=NULL)myhud->settopleftcolour(tmp);
		cam=Camera;


		mai1.clear();
		mai1.restart(SCENARIO10STARTINGSHIPS, SCENARIO10SHIPAMOUNT, true, true, EVOLUTIONSPECIALSCENARIO);
		mai2.clear();
		mai2.restart(SCENARIO10STARTINGSHIPS, SCENARIO10SHIPAMOUNT, true, false);
		myasteroids.clear();
		metagrid.clear();
		myasteroids.setgrid(&metagrid);


		mai1.setresources(50.0);
		mai2.setresources(50.0);


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
			mai1.drawme(true, 3);
			mai2.drawme(true, 3);
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
		case (int)'*':
			mai2.allpilots.increasefear(100.0);
			mai1.allpilots.increasefear(100.0);
		case (int)'+':
			mai2.allpilots.increaseanger(100.0);
			mai1.allpilots.increaseanger(100.0);
			break;
		case (int)'-':
			mai2.allpilots.resetemotions();
			mai1.allpilots.resetemotions();
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
		result+=string("\nNumber of boids 1, evolving:     ")+itoa(mai1.pilotssize(), Chars, 10);
		result+=string("\nNumber of boids 2, non evolving: ")+itoa(mai2.pilotssize(), Chars, 10);



		sprintf(Chars, "%f", mai1.score());
		result+=string("\nScore 1: \t")+Chars;
		sprintf(Chars, "%f", mai2.score());
		result+=string("\nScore 2: \t")+Chars;


		myhud->settopleft(result);
		//cout<<result<<endl<<flush;
	}

};

#endif /* SCENARIO10_H_ */
