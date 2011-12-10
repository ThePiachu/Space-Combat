#ifndef SCENARIO5_H_
#define SCENARIO5_H_

#include "scenario.h"
#include "../math.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO5SHIPAMOUNT 200
#define INCREMENT 0.01

class scenario5:public scenario
{
	char Chars[100];
	int i, fps, tmptime;
	string result;
	grid metagrid;
	mothershipai mai;
	pilots allpilots;
	steeringpreferences defaultsteering;
	unsigned int displaygrid;
	float alignment, separation, cohesion, avoid, asteroidavoid;
	fsme defaultfsme;
	fsm defaultfsm;
public:
	scenario5():
		i(0), fps(0), tmptime(time(NULL)),
		result(),
		metagrid(2.0),
		mai(),
		allpilots(),
		defaultsteering(),
		displaygrid(1),
		alignment(0.2),
		separation(0.3),
		cohesion(0.4),
		avoid(2.0),
		asteroidavoid(2.0),
		defaultfsme(),
		defaultfsm()
	{
	}
	~scenario5()
	{
		allpilots.clear();
	}
	void nexttime()
	{
		/*allpilots.newbasicpilot();
		allpilots.newbasicpilot();
		allpilots.newbasicpilot();
		allpilots.killoldestboid();
		allpilots.killoldestboid();
		allpilots.killoldestboid();*/
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
		//metagrid.checkcolisionswithshiphit();
		//metagrid.checkallpointers();
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		metagrid.clear();
		allpilots.clear();
		defaultfsm.clear();
		defaultfsme.clear();


		//defaultsteering();
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(alignment);
		defaultsteering.setseparation(separation);
		defaultsteering.setcohesion(cohesion);
		defaultsteering.setavoid(avoid, 0.5);
		defaultsteering.setasteroidavoid(asteroidavoid, 0.5);
		//defaultsteering.setgravitate(0.1, 50.0);
		defaultsteering.setgravitate(0.1, 25.0);

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

		myhud=HUD;
		myhud->settopleft(string("Scenario 5"));
		cam=Camera;
		mystars=Stars;

		allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(2*SCENARIO5SHIPAMOUNT);

		for (unsigned int i=0;i<SCENARIO5SHIPAMOUNT;i++)
		{
			allpilots.newbasicpilot2(myrandom->randomcubeposition(5));
		}



		settopleft();
	}
	void drawme()
	{
		glPushMatrix();
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
		glPopMatrix();

		allpilots.drawme();
		metagrid.drawme(displaygrid);

	}
	void handlekey(int Key)
	{
		switch(Key)
		{
		case (int)'.':
			allpilots.newbasicpilot2(myrandom->randomcubeposition(5));
				break;
		case (int)'/':
			displaygrid++;
			break;




		case (int)'o':
			alignment+=INCREMENT;
			setboids();
			settopleft();
			break;
		case (int)'l':
			alignment-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'i':
			separation+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'k':
			separation-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'u':
			cohesion+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'j':
			cohesion-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'y':
			avoid+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'h':
			avoid-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'t':
			asteroidavoid+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'g':
			asteroidavoid-=INCREMENT;
		setboids();
		settopleft();
			break;
		default:
			break;
		}
	}
	void setboids()
	{
		defaultsteering.setalignment(alignment);
		defaultsteering.setseparation(separation);
		defaultsteering.setcohesion(cohesion);
		defaultsteering.setavoid(avoid, 0.5);


		defaultfsme.setallsteering(defaultsteering);
		defaultfsm.clear();
		defaultfsm.addfsme(defaultfsme);
		allpilots.setallpilotfsm(defaultfsm);

	}
	void settopleft()
	{
		if(myhud!=NULL)
		{
			result=string("Alignment: ");
			sprintf(Chars, "%f", alignment);
			result+=Chars;
			result+=string("\nSeparation: ");
			sprintf(Chars, "%f", separation);
			result+=Chars;
			result+=string("\nCohesion: ");
			sprintf(Chars, "%f", cohesion);
			result+=Chars;
			result+=string("\nAvoid: ");
			sprintf(Chars, "%f", avoid);
			result+=Chars;
			/*result+=string("\nAsteroidAvoid: ");
			sprintf(Chars, "%f", asteroidavoid);
			result+=Chars;*/

			myhud->settopleft(result);
		}
	}
};

#endif /* SCENARIO5_H_ */
