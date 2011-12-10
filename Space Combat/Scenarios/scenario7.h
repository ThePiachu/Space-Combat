#ifndef SCENARIO7_H_
#define SCENARIO7_H_

#include "scenario.h"
#include "../math.h"
#include "../map.h"
#include "../ai.h"

#define SCENARIO7STARTINGSHIPS 100
#define SCENARIO7SHIPAMOUNT 100
#define INCREMENT 0.01

class scenario7:public scenario
{
	char Chars[100];
	int x, y, fps, tmptime;
	string result;
	asteroids myasteroids;
	grid metagrid;
	mothershipai mai;
	//pilots allpilots;
	steeringpreferences defaultsteering;
	unsigned int displaygrid, displaypilot, displaytext;
	float alignment, separation, cohesion, avoid, asteroidavoid;
	fsme defaultfsme;
	fsm defaultfsm;
	float remainingdistanceweight, shipweight, asteroidweight, covereddistanceweight;
	astar defaultastar;


public:
	scenario7():
		x(0), y(0), fps(0), tmptime(time(NULL)),
		result(),
		myasteroids(myvector(0.0, 0.0, 1.0), point(0.0, 0.0, -20.0), 20.0, point(0.0, 0.0, 20.0), 0.1),
		metagrid(2.0),
		mai(point(-20, 0.0, 0.0), &metagrid),
		//allpilots(),
		defaultsteering(),
		displaygrid(1),
		displaypilot(1),
		displaytext(1),
		alignment(0.2),
		separation(0.3),
		cohesion(0.4),
		avoid(2.0),
		asteroidavoid(2.0),
		defaultfsme(),
		defaultfsm(),
		remainingdistanceweight(1.0),
		shipweight(0.1),
		asteroidweight(0.5),
		covereddistanceweight(0.5),
		defaultastar(&metagrid, remainingdistanceweight, shipweight, asteroidweight, covereddistanceweight)
	{
		mai.me.velocity=0.0;
		mai.setusefilepilot(false);
		//mai.me.setposition(point(-20, 0.0, 0.0));
	}
	~scenario7()
	{
		metagrid.clear();
		myasteroids.clear();
		mai.clear();
		//allpilots.clear();
	}
	void nexttime()
	{
		if(x%3==0)
		{
			myasteroids.generateasteroid(false);
			mai.newbasicpilot();
			//allpilots.newbasicpilot2(mai.me.position.movebyvector(myrandom->randombubbleposition(3)), false);
		}
		x++;
		if (tmptime!=time(NULL))
		{
			y++;
			if(y%10==0)mai.killoldestpilot();
			tmptime=time(NULL);
			fps=x;
			x=0;

			result=string("FPS: ")+itoa(fps, Chars, 10);
			result+=string("  Number of dynamic asteroids: ")+itoa(myasteroids.allasteroids.size(), Chars, 10);
			result+=string("  Number of boids: ")+itoa(mai.pilotssize(), Chars, 10);
			myhud->setbottomleft(result);
		}
		//allpilots.nexttime();

		mai.nexttime();

		myasteroids.moveme();
		metagrid.checkallasteroids();
		myasteroids.checkfordeletion();
		metagrid.checkallships();
		metagrid.checkcolisionswithshiphit(true, 110.0);
		//allpilots.checkfordeadpilots();
		//allpilots.deleteships(metagrid.checkcolisionswithdeletion());
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		metagrid.clear();
		//allpilots.clear();
		//allpilots.setdefaultgravitatetarget(mai.me.position);
		myasteroids.clear();
		myasteroids.setgrid(&metagrid);

		mai.clear();

		createdefaultfsm();
		createasteroidobstacles();

		defaultastar=astar(&metagrid, remainingdistanceweight, shipweight, asteroidweight, covereddistanceweight);

		mai.setdefaultpilotfsm(defaultfsm);
		mai.setdefaultpilotastar(defaultastar);

		mai.restart(SCENARIO7STARTINGSHIPS, SCENARIO7SHIPAMOUNT, false, false);
		myasteroids.addasteroid
		(
			asteroid(point(20.0, 0.0, 0.0), colour(1.0, 1.0, 1.0), 10.0, myvector(0.0, 0.0, 0.0), true, true)
		);


		myhud=HUD;
		myhud->settopleft(string("Scenario 7"));
		vector<colour> tmp;
		tmp.push_back(colour(1.0, 1.0, 1.0));
		if (myhud!=NULL)myhud->settopleftcolour(tmp);
		cam=Camera;
		cam->setzoom(50.0);

		/*allpilots.setgrid(&metagrid);
		allpilots.setdefaultpilot(pilot(point(0.0, 0.0, 0.0), defaultfsm));
		allpilots.setpilotcap(SCENARIO7SHIPAMOUNT);
		allpilots.setmothership(&mai.me);*/

		/*for (unsigned int i=0;i<SCENARIO7SHIPAMOUNT;i++)
		{
			allpilots.newbasicpilot2(mai.me.position.movebyvector(myrandom->randomcubeposition(5)), false);
		}*/

		//allpilots.setallpilotastar(defaultastar);

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


		myasteroids.drawme();
		metagrid.drawme(displaygrid);
		//allpilots.drawme(1, displaypilot);
		mai.drawme(true, 1, displaypilot);

	}
	void handlekey(int Key)
	{
		switch(Key)
		{
		case (int)'/':
			displaygrid++;
		settopleft();
			break;
		case (int)'*':
			displaypilot++;
		settopleft();
			break;
		case (int)'-':
			displaytext++;
		settopleft();
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
		case (int)'z':
			remainingdistanceweight+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'x':
			remainingdistanceweight-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'c':
			shipweight+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'v':
			shipweight-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'b':
			asteroidweight+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'n':
			asteroidweight-=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)'m':
			covereddistanceweight+=INCREMENT;
		setboids();
		settopleft();
			break;
		case (int)',':
			covereddistanceweight-=INCREMENT;
		setboids();
		settopleft();
			break;
		/*case (int)'?':
			allpilots.printallstates();
			break;*/
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

		defaultastar=astar(&metagrid, remainingdistanceweight, shipweight, asteroidweight, covereddistanceweight);


		mai.setdefaultpilotfsm(defaultfsm);
		mai.setdefaultpilotastar(defaultastar);

		//allpilots.setallpilotfsm(defaultfsm);
		//allpilots.setallpilotastar(defaultastar);
	}

	fsm createdefaultfsm()
	{
		defaultsteering.reset();

		defaultsteering.setalignment(alignment);
		defaultsteering.setseparation(separation);
		defaultsteering.setcohesion(cohesion);
		defaultsteering.setavoid(avoid, 0.5);
		defaultsteering.setasteroidavoid(asteroidavoid, 0.5);


		defaultsteering.setseek(1.0);
		defaultsteering.setdockradius(0.6, 0.2);
		defaultsteering.setwander(1.0);
		defaultsteering.setgravitate(0.1, 25.0);
		defaultsteering.setfollow(2.0, 1.0, 1.0);


		decisionpreferences decprefs
		(
			0.3,
			0.8,
			-0.5,
			-0.5,
			1000.0,
			1000.0
		);
		state tmpstate;
		steeringcontrol orders;

		orders.reset();
		orders.setgo(true);
		orders.setgravitateplace(true);


		tmpstate=state(string("Decide what to do"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Look for Mothership"), shipfull);
		tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
		tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
		tmpstate.addtransitionintask(&ship::resetdockingline);
		tmpstate.addtransitionouttask(&ship::resetdockingline);


		defaultfsme.addstate(tmpstate);



		orders.reset();
		orders.setgo(true);
		orders.setlookformothership(true);

		defaultfsme.setname("Default");

		tmpstate=state(string("Look for Mothership"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Dock with Mothership"), shippathset);

		defaultfsme.addstate(tmpstate);



		orders.reset();
		orders.setgo(true);
		orders.setdockwithmothership(true);
		orders.setsinglepathfollow(true);

		defaultfsme.setname("Default");

		tmpstate=state(string("Dock with Mothership"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Undock from Mothership"), shipempty);

		defaultfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setundock(true);

		tmpstate=state(string("Undock from Mothership"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Decide what to do"), shipundocked);
		tmpstate.addtransitionouttask(&ship::resetdockingline);

		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setlookforasteroid(true);

		tmpstate=state(string("Look for Asteroid"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
		tmpstate.connectto(string("Decide what to do"), asteroidempty);
		tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setdockwithasteroid(true);
		orders.setsinglepathfollow(true);

		tmpstate=state(string("Dock with Asteroid"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Undock Asteroid"), shipfull);
		tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
		tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);
		tmpstate.addtransitionouttask(&ship::unsetpath);

		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setundock(true);

		tmpstate=state(string("Undock Asteroid"),
				//defaultsteering, decprefs,
				orders);
		tmpstate.connectto(string("Decide what to do"), shipundocked);
		tmpstate.addtransitionouttask(&ship::resetdockingline);

		defaultfsme.addstate(tmpstate);



		defaultfsme.setcurrentstate("Decide what to do");
		defaultfsme.setdefaultstate("Decide what to do");

		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);

		defaultfsm.addfsme(defaultfsme);

		//cout<<"defaultfsme defaultstate: "<<defaultfsme.defaultstate->name<<endl<<flush;

		return defaultfsm;
	}
	void createasteroidobstacles()
	{
		unsigned int tmpui=0;
		point tmppoint(0.0, 0.0, 0.0);
		for(int i=-10;i<10;i++)
		{
			for(int j=-10;j<10;j++)
			{
				tmppoint(0.0, i*2.0, j*2.0);
				tmpui=myrandom->randomunsignedint(10);
				if(tmpui>5)for(unsigned int k=0;k<tmpui;k++)
				{
					myasteroids.generateastaticcubeasteroids(tmppoint, 1.0, false);
				}
			}
		}
		for(int i=-2;i<2;i++)
		{
			for(int j=-2;j<2;j++)
			{
				tmppoint(0.0, i*2.0, j*2.0);
				tmpui=5;
				for(unsigned int k=0;k<tmpui;k++)
				{
					myasteroids.generateastaticcubeasteroids(tmppoint, 1.0, false);
				}
			}
		}
	}




	void settopleft()
	{
		if(myhud!=NULL)
		{
			result=string("");
			result+=string("Scenario 7:");
			result+=string("\nControls, Variable, Value: ");
			result+=string("\n- - Display/Hide text");

			if(displaytext%2)
			{
				result+=string("\n\nol - Alignment: ");
				sprintf(Chars, "%.2f", alignment);
				result+=Chars;
				result+=string("\nik - Separation: ");
				sprintf(Chars, "%.2f", separation);
				result+=Chars;
				result+=string("\nuj - Cohesion: ");
				sprintf(Chars, "%.2f", cohesion);
				result+=Chars;
				result+=string("\nyh - Avoid: ");
				sprintf(Chars, "%.2f", avoid);
				result+=Chars;
				result+=string("\ntg - AsteroidAvoid: ");
				sprintf(Chars, "%.2f", asteroidavoid);
				result+=Chars;
				result+=string("\n A Star variables:");
				result+=string("\nzx - A*RemainingDistanceWeight: ");
				sprintf(Chars, "%.2f", remainingdistanceweight);
				result+=Chars;
				result+=string("\ncv - A*ShipWeight: ");
				sprintf(Chars, "%.2f", shipweight);
				result+=Chars;
				result+=string("\nA*bn - AsteroidWeight: ");
				sprintf(Chars, "%.2f", asteroidweight);
				result+=Chars;
				result+=string("\nm, - A*CoveredDistanceWeight: ");
				sprintf(Chars, "%.2f", covereddistanceweight);
				result+=Chars;

				result+=string("\n\n/ - Grid Display: ")+itoa(displaygrid%6, Chars, 10);
				result+=string("\n* - A* Display: ")+itoa(displaypilot%2, Chars, 10);

				result+=string("\n\n Other Controls: ");
				result+=string("\n mouse click and movement - camera control");
				result+=string("\n wsadqe - Pitch, yaw and roll of camera");
				result+=string("\n rf - Camera zoom");
			}
			myhud->settopleft(result);
		}
	}
};

#endif /* SCENARIO7_H_ */
