#ifndef MOTHERSHIPAI_H_
#define MOTHERSHIPAI_H_

#define NEWPILOTPOSITIONFUNCTION myrandom->randombubbleposition(3)
#define SHIPCOST 1.0

#define MOTHERSHIPAISPEAK false

#include "../math.h"
#include "../map.h"
#include "pilot.h"
#include "pilots.h"

class mothershipai
{//the AI of the mothership
public:
	random* myrandom;
	mothership me;
	//grid mygrid;
	grid* metagrid;
	pilots allpilots;
	pilot defaultfighterpilot;
	pilot defaultharvesterpilot;
	float generatefighterprobability;
	mothershipai():
		myrandom(random::getinstance()),
		me(),
		//mygrid(2.0),
		metagrid(NULL),
		allpilots(),
		defaultfighterpilot(pilot::examplepilot()),
		defaultharvesterpilot(pilot::exampleminer()),
		generatefighterprobability(1.0)
	{
		defaultfighterpilot.mycolour=me.mycolour;
		defaultharvesterpilot.mycolour=me.mycolour;
		//allpilots.setgrid(&mygrid);
	}
	mothershipai(const point& Position,
			grid* MetaGrid):
		myrandom(random::getinstance()),
		me(Position),
		//mygrid(2.0),
		metagrid(MetaGrid),
		allpilots(),
		defaultfighterpilot(pilot::examplepilot()),
		defaultharvesterpilot(pilot::exampleminer()),
		generatefighterprobability(1.0)
	{
		defaultfighterpilot.mycolour=me.mycolour;
		defaultharvesterpilot.mycolour=me.mycolour;
		allpilots.setgrid(MetaGrid);
		//allpilots.setgrid(&mygrid);
	}
	mothershipai(const point& Position,
			const unsigned int& ScenarioNumber,
			const unsigned int& R, const unsigned int& G ,const unsigned int& B,
			grid* MetaGrid,
			const float& MinimumScoreToSavePilot=1.5):
		myrandom(random::getinstance()),
		me(Position, colour(R, G, B, 1.0)),
		//mygrid(me.mycolour, MetaGrid),//TODO: implement from metagrid
		metagrid(MetaGrid),
		allpilots(MinimumScoreToSavePilot),
		defaultfighterpilot(pilot::examplepilot()),
		defaultharvesterpilot(pilot::exampleminer()),
		generatefighterprobability(1.0)
	{
		defaultfighterpilot.mycolour=me.mycolour;
		defaultharvesterpilot.mycolour=me.mycolour;
		allpilots.setgrid(MetaGrid);
		allpilots.setsubfolderandcolour(ScenarioNumber, R, G, B);
	}
	~mothershipai()
	{
	}
	void drawme(const bool& DrawPilots=false, const unsigned int& ShipDrawingMode=1, const unsigned int PilotDrawingMode=1)
	{
		me.drawme();
		if(DrawPilots)allpilots.drawme(ShipDrawingMode, PilotDrawingMode);
	}
	void drawships(const bool& DrawPilots=true, const unsigned int& ShipDrawingMode=1, const unsigned int PilotDrawingMode=1)
	{
		if(DrawPilots)allpilots.drawme(ShipDrawingMode, PilotDrawingMode);
	}
	void moveme()
	{
		me.moveme();
	}
	void stopme()
	{
		me.setacceleration(-me.velocity);
	}
	void newevolvedpilot(const bool& PilotIsHarvester=false, const bool& Evolve=true)
	{
		allpilots.newevolvedpilot2(me.position.movebyvector(NEWPILOTPOSITIONFUNCTION), Evolve, PilotIsHarvester);
	}
	void newevolvedpilot(const bool& PilotIsHarvester, const bool& Evolve, const bool& SpecialEvolve)
	{//function for selective evolution
		allpilots.newevolvedpilot2(me.position.movebyvector(NEWPILOTPOSITIONFUNCTION), Evolve, PilotIsHarvester, SpecialEvolve);
	}
	void newbasicpilot(const bool& PilotIsHarvester=false, const bool& Evolve=false)
	{
		allpilots.newbasicpilot2(me.position.movebyvector(NEWPILOTPOSITIONFUNCTION), Evolve, PilotIsHarvester);
	}
	void newbasicpilot(const bool& PilotIsHarvester, const bool& Evolve, const bool& SpecialEvolve)
	{//a function for selective evolution
		allpilots.newbasicpilot2(me.position.movebyvector(NEWPILOTPOSITIONFUNCTION), Evolve, SpecialEvolve, PilotIsHarvester);
	}

	void killoldestpilot(const bool& PilotIsHarvester)
	{
		allpilots.killoldestpilot(PilotIsHarvester);
	}
	void killoldestpilotrandom()
	{
		bool PilotIsHarvester=(myrandom->randomfloatbetween(0, 1)<generatefighterprobability);
		allpilots.killoldestpilot(PilotIsHarvester);
	}
	void killoldestpilot()
	{
		allpilots.killoldestpilot();
	}
	void nexttime()
	{
		if(MOTHERSHIPAISPEAK)cout<<"moveme"<<endl<<flush;
		moveme();
		if(MOTHERSHIPAISPEAK)cout<<"~moveme"<<endl<<flush;
		if(MOTHERSHIPAISPEAK)cout<<"allpilots.nexttime();"<<endl<<flush;
		allpilots.nexttime();
		if(MOTHERSHIPAISPEAK)cout<<"~allpilots.nexttime();"<<endl<<flush;
		//mygrid.checkallships();
		//TODO: sometihng with delete ships?
	}
	void decidewhattogenerate(const float& CostRatio=1.0, const bool& Evolve=true, const bool& EvolvedPilot=true)
	{
		if(me.resources>SHIPCOST*CostRatio)if(allpilots.arepilotsbelowcap())
		{
			if(myrandom->randomfloatbetween(0, 1.0)<generatefighterprobability)
			{
				if(MOTHERSHIPAISPEAK)cout<<"New fighter"<<endl<<flush;
				if(EvolvedPilot)newevolvedpilot(false, Evolve);
				else newbasicpilot(false, Evolve);
				me.unloadresources(SHIPCOST*CostRatio);
			}
			else
			{
				if(MOTHERSHIPAISPEAK)cout<<"New harvester"<<endl<<flush;
				if (EvolvedPilot)newevolvedpilot(true, Evolve);
				else newbasicpilot(true, Evolve);
				me.unloadresources(SHIPCOST*CostRatio);
			}
		}
	}
	void decidewhattogenerate(const float& CostRatio, const bool& Evolve, const bool& EvolvedPilot, const bool& EvolveSpecial)
	{//function for selective evolution
		if(me.resources>SHIPCOST*CostRatio)if(allpilots.arepilotsbelowcap())
		{
			if(myrandom->randomfloatbetween(0, 1.0)<generatefighterprobability)
			{
				if(MOTHERSHIPAISPEAK)cout<<"New fighter"<<endl<<flush;
				if(EvolvedPilot)newevolvedpilot(false, Evolve, EvolveSpecial);
				else newbasicpilot(false, Evolve, EvolveSpecial);
				me.unloadresources(SHIPCOST*CostRatio);
			}
			else
			{
				if(MOTHERSHIPAISPEAK)cout<<"New harvester"<<endl<<flush;
				if (EvolvedPilot)newevolvedpilot(true, Evolve, EvolveSpecial);
				else newbasicpilot(true, Evolve, EvolveSpecial);
				me.unloadresources(SHIPCOST*CostRatio);
			}
		}
	}
	void setmycolourandscenario(const unsigned int& ScenarioNumber, const unsigned int& R, const unsigned int& G ,const unsigned int& B)
	{
		me.mycolour.setme(colour(R, G, B, 1.0));
		allpilots.setsubfolderandcolour(ScenarioNumber, R, G, B);
	}
	void clear()
	{
		allpilots.clear();
		//mygrid.clear();

	}
	void restart(const unsigned int& BoidAmountToLoad, const unsigned int& PilotCap,
			const bool& Preload=true, const bool& Evolve=true)
	{
		//pilot defaultpilot=pilot::examplepilot();
		//defaultpilot.mycolour=me.mycolour;
		//allpilots.setgrid(&mygrid);
		allpilots.setgrid(metagrid);
		allpilots.setdefaultpilot(defaultfighterpilot, false);
		allpilots.setdefaultpilot(defaultharvesterpilot, true);
		allpilots.setpilotcap(PilotCap);
		allpilots.setmothership(&me);
		if(Preload)allpilots.preloadtextpilots(PilotCap, true);//loads pilots from saved text files
		if(Preload)allpilots.preloadtextpilots(PilotCap, false);//loads pilots from saved text files
		if(Evolve)for (unsigned int i=0;i<BoidAmountToLoad;i++)
		{
			//cout<<"before allpilots.newevolvedpilot2(NEWPILOTPOSITIONFUNCTION, true);"<<endl<<flush;
			newevolvedpilot();
			//decidewhattogenerate();
		}
		else for (unsigned int i=0;i<BoidAmountToLoad;i++)
		{
			//cout<<"before allpilots.newevolvedpilot2(NEWPILOTPOSITIONFUNCTION, true);"<<endl<<flush;
			newbasicpilot();
		}
	}
	void restart(const unsigned int& BoidAmountToLoad, const unsigned int& PilotCap,
				const bool& Preload, const bool& Evolve, const bool& SpecialEvolve)
	{//function for special evolution
		//pilot defaultpilot=pilot::examplepilot();
		//defaultpilot.mycolour=me.mycolour;
		//allpilots.setgrid(&mygrid);
		allpilots.setgrid(metagrid);
		allpilots.setdefaultpilot(defaultfighterpilot, false);
		allpilots.setdefaultpilot(defaultharvesterpilot, true);
		allpilots.setpilotcap(PilotCap);
		allpilots.setmothership(&me);
		if(Preload)allpilots.preloadtextpilots(PilotCap, true);//loads pilots from saved text files
		if(Preload)allpilots.preloadtextpilots(PilotCap, false);//loads pilots from saved text files
		if(Evolve)for (unsigned int i=0;i<BoidAmountToLoad;i++)
		{
			//cout<<"before allpilots.newevolvedpilot2(NEWPILOTPOSITIONFUNCTION, true);"<<endl<<flush;
			newevolvedpilot(false, true, SpecialEvolve);
			//decidewhattogenerate();
		}
		else for (unsigned int i=0;i<BoidAmountToLoad;i++)
		{
			//cout<<"before allpilots.newevolvedpilot2(NEWPILOTPOSITIONFUNCTION, true);"<<endl<<flush;
			newbasicpilot();
		}
	}
	inline
	void setdefaultpilotfsm(const fsm& DefaultFSM, const bool& PilotIsHarvester=false)
	{
		if(PilotIsHarvester)defaultharvesterpilot.setmyfsm(DefaultFSM);
		else defaultfighterpilot.setmyfsm(DefaultFSM);
		allpilots.setdefaultpilotfsm(DefaultFSM, PilotIsHarvester);
	}
	inline
	void setallpilotsfsm(const fsm& DefaultFSM, const bool& PilotIsHarvester=false)
	{
		if(PilotIsHarvester)defaultharvesterpilot.setmyfsm(DefaultFSM);
		else defaultfighterpilot.setmyfsm(DefaultFSM);
		allpilots.setallpilotfsm(DefaultFSM, PilotIsHarvester);
	}
	inline
	float givetopscore()
	{
		return allpilots.givetopscore();
	}
	inline
	float averagescore()
	{
		return allpilots.averagescore();
	}
	/*inline
	void checkfordeletion()
	{
		allpilots.deleteships(metagrid->checkcolisionswithdeletion());
	}*/
	inline
	unsigned int pilotssize()
	{
		return allpilots.size();
	}
	inline
	void checkfordeadpilots()
	{
		allpilots.checkfordeadpilots();
	}
	inline
	void setdefaultpilotastar(const astar& AStar, const bool& PilotIsHarvester=false)
	{
		if(PilotIsHarvester)defaultharvesterpilot.setastar(AStar);
		else defaultfighterpilot.setastar(AStar);
		allpilots.setallpilotastar(AStar, PilotIsHarvester);
	}
	void setdefaultpilot(const pilot& Pilot, const bool& PilotIsHarvester=false)
	{//setting default pilot
		if(PilotIsHarvester)defaultharvesterpilot(Pilot);
		else defaultfighterpilot(Pilot);
		allpilots.setdefaultpilot(Pilot, PilotIsHarvester);
	}
	inline
	void setgeneratefighterprobability(const float& NewProbability=1.0)
	{
		generatefighterprobability=NewProbability;
	}
	inline
	void setresources(const float& NewResources)
	{
		me.setresources(NewResources);
	}
	inline
	float score()const
	{
		return me.score();
	}

	inline
	void setusefilepilot(const bool& UseFilePilot=false)
	{
		allpilots.setusefilepilot(UseFilePilot);
	}

};

#endif /* MOTHERSHIPAI_H_ */
