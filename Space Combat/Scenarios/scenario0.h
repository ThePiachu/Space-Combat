#ifndef SCENARIO0_H_
#define SCENARIO0_H_


#include "scenario.h"
class scenario0:public scenario
{
	mothership she;
	myvector tmp;
	vector <point> points;
public:
	scenario0():
		she(point(), colour(), 0.0, 0.0),
	tmp(), points()
	{
	}
	~scenario0()
	{
	}
	void startscenario(quaternioncamera2 *Camera, hud* HUD, stars *Stars)
	{
		myhud=HUD;
		cam=Camera;
		mystars=Stars;
		myhud->settopleft(string("Scenario 0"));
	}
	void drawme()
	{
		she.drawme();
		she.velocity.drawme();
		for(unsigned int i=0;i<points.size();i++)points.at(i).drawme();
	}
	void handlekey (const int& Key)
	{
		switch(Key)
		{
		case '+':
			tmp(myrandom->randombubbleposition(2.0));
			she.velocity(tmp);
			break;
		case '-':
			points.clear();
			for (unsigned int i=0;i<200;i++)
			{
				points.push_back(myrandom->randomdomeposition(myvector(she.velocity), 90));
			}
			break;
		case '*':
			for(unsigned int i=0;i<1000000;i++)
			{
				cout<<myrandom->randomnormalcenteredatzero(1000)<<endl;
			}
			cout<<flush;
			break;
		case '/':
			point tmppoint(0.0, 0.0, 0.0);
			tmppoint.unittest();
			break;
		}
	}
};

#endif /* SCENARIO0_H_ */
