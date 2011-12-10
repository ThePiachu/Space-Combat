#ifndef SCENARIO3_H_
#define SCENARIO3_H_

#include "scenario.h"
class scenario3:public scenario
{
	char Chars[100];
	int i, fps, tmptime;
	string result;
	gridelement gridel;
	grid fullgrid;
	asteroids myasteroids;
	vector<star> starsv;
	random* myrandom;
	astar as;
	path mypath;
	unsigned int displaygrid;
public:
	scenario3():
		i(0), fps(0), tmptime(time(NULL)),
		result(),
		gridel(point(0.0, 0.0, 0.0), 1.0),
		fullgrid(1.0),
		myasteroids(),
		starsv(),
		myrandom(random::getinstance()),
		as(&fullgrid),
		mypath(),
		displaygrid(0)
	{
	}
	~scenario3()
	{
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		myhud=HUD;
		cam=Camera;
		mystars=Stars;
		myhud->settopleft(string("Scenario 3"));

		//mypath.unittest();
		//gridel.unittest();
		//unsigned int x=5;
		//cout<<-x<<endl<<flush;
		//for (int i=-x;i<x;i++)cout<<i<<endl<<flush;
		//int x=5;
		//cout<<-x<<endl<<flush;
		//for (int i=-x;i<x;i++)cout<<i<<endl<<flush;

		//cout<<endl<<"Fullgrid:"<<endl<<flush;
		//fullgrid.preparegrid(0);
		fullgrid.preparegrid(1);
		//fullgrid.preparegrid(2);
		//fullgrid.preparegrid(3);
		fullgrid.preparegrid(1, point(10.0, 10.3, 11.0));

		myasteroids.setcolour(colour(0.0, 0.0, 1.0));

		myasteroids.setgrid(&fullgrid);


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
	}
	void drawme()const
	{
		glPushMatrix();
		//cam.rotatecamera();

			glColor3f(1.0, 1.0, 1.0);
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
		glPopMatrix();

		//gridel.drawme();
		fullgrid.drawme(displaygrid);

		glPointSize(5.0f);

		for (unsigned int i=0;i<starsv.size();i++)
		{
			starsv.at(i).drawme();
		}
		glPointSize(1.0f);
		myasteroids.drawme();



		glLineWidth(10.0);

		glColor3f(1.0, 0.0, 0.0);
		mypath.drawmesingle();
		glColor3f(1.0, 1.0, 1.0);

		glLineWidth(1.0);
		//mypath.drawme();
		//myboids->drawme();
	}

	void handlekey(int Key)
	{
		switch(Key)
		{
		case (int)'+':
			myasteroids.generateastaticcubeasteroids();
			//starsv.push_back(star(myrandom->randomcubeposition(10.0),0.0f,0.0f,0.5f));
			//fullgrid.forceneighbours(fullgrid.addstar(starsv.back()));
			//fullgrid.addstar(&starsv.back());
			break;
		case (int)'-':
			//mypath=as.randompath(5.0);
			mypath=as.findpath(point(9.5, 0.0, 0.0), point(-0.5, 0.0, 0.0));
			//fullgrid.forcefindgridelement(myrandom->randomcubeposition(10.0));
			break;
		case (int)'*':
			mypath=as.randompath(50.0);//+as.randompath(50.0);
			//mypath=as.findpath(point(9.5, 0.0, 0.0), point(-0.5, 0.0, 0.0));
			//fullgrid.forcefindgridelement(myrandom->randomcubeposition(10.0));
			break;
		case (int)'/':
			displaygrid++;
			break;
		}
	}
};
#endif /* SCENARIO3_H_ */
