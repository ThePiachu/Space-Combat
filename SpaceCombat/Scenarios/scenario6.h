#ifndef SCENARIO6_H_
#define SCENARIO6_H_

#include "scenario.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO6ITERATIONTIME 10
#define SCENARIO6SHIPAMOUNT 100
#define EVOLUTIONSCENARIO true
#define SCENARIO6STARTINGSHIPS 100
//#define SCENARIO6STARTINGSHIPS 0

class scenario6:public scenario
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
	mothershipai mai;
	//fsme defaultfsme;
	//fsm defaultfsm;
public:
	scenario6():// scenario(),
	x(0), y(0), fps(0), tmptime(time(NULL)),
	result(),
	myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 20.0, point(0.0, 0.0, 20.0), 0.1),
	metagrid(2.0),
	//allpilots(),
	//defaultsteering(),
	displaygrid(1),
	mai(point(0.0, 0.0, 0.0), 6, 2, 1, 0, &metagrid)//,
	//defaultfsme(),
	//defaultfsm()
	{
		mai.me.velocity=0.0;
		mai.setusefilepilot(USEFILEPILOT);
		//mai.setmycolour(2, 1, 0);
	}
	void nexttime()
	{
		x++;
		if(x%3==0)
		{
			myasteroids.generateasteroid();

			if(EVOLUTIONSCENARIO)
			{
				mai.newevolvedpilot();
				//mai.newbasicpilot();
				//allpilots.newevolvedpilot
				//	(mai.me.position.movebyvector(myrandom->randombubbleposition(3)));
			}
		}
		if (tmptime!=time(NULL))
		{
			printstring();
			//myasteroids.generateasteroid();
			y++;
			if(EVOLUTIONSCENARIO)
				//if(y%10==0)
					mai.killoldestpilot();
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
		mai.nexttime();
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
	}
	~scenario6()
	{
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		myhud=HUD;
		myhud->settopleft(string("Scenario 6"));
		vector<colour> tmp;
		tmp.push_back(colour(1.0, 1.0, 1.0));
		if (myhud!=NULL)myhud->settopleftcolour(tmp);
		cam=Camera;

		metagrid.clear();
		myasteroids.clear();
		myasteroids.setgrid(&metagrid);
		mai.clear();
		mai.restart(SCENARIO6STARTINGSHIPS, SCENARIO6SHIPAMOUNT);

		//metagrid.preparegrid(3, point(0.0, 0.0, 0.0));

		//myasteroids.setgrid(NULL);
		//allpilots.clear();
		//defaultfsm.clear();
		//defaultfsme.clear();

		//createdefaultfsm();
		//createtestfsme();




		/*allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(2*SCENARIO6SHIPAMOUNT);
		allpilots.setmothership(&mai.me);*/
		/*for (unsigned int i=0;i<SCENARIO6STARTINGSHIPS;i++)
		{
			allpilots.newbasicpilot(myrandom->randomcubeposition(5), false);
		}*/
		/*allpilots.preloadtextpilots(100);//loads up to 100 pilots from saved text files
		for (unsigned int i=0;i<SCENARIO6STARTINGSHIPS;i++)
		{
			allpilots.newevolvedpilot(myrandom->randomcubeposition(5), true);
		}*/

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
			myasteroids.drawme();
			metagrid.drawme(displaygrid);
			//allpilots.drawme(1);
			mai.drawme(true, 1);
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
			if(USEFILEPILOT)mai.allpilots.fp.compiledata(false);
			break;
		}
	}

	void printstring()
	{
		result=string("FPS: ")+itoa(fps, Chars, 10);
		result+=string("  Number of asteroids: ")+itoa(myasteroids.allasteroids.size(), Chars, 10);
		//result+=string("  In grid: ")+itoa(metagrid.allasteroidssize(), Chars, 10);
		//result+=string("  In grids: ")+itoa(metagrid.countasteroids(), Chars, 10);
		result+=string("  Number of boids: ")+itoa(mai.pilotssize(), Chars, 10);
		myhud->setbottomleft(result);

		result=string("At ")+itoa(y, Chars, 10);
		sprintf(Chars, "%f", mai.givetopscore());
		result+=string("\nTop Score: ")+Chars;
		sprintf(Chars, "%f", mai.averagescore());
		result+=string("\nAverage Score: ")+Chars;

		myhud->settopleft(result);
		//cout<<result<<endl<<flush;
	}

};

#endif /* SCENARIO6_H_ */
