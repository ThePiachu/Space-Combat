#ifndef STEERINGCONTROL_H_
#define STEERINGCONTROL_H_

#include "../stringhandling.h"

class steeringcontrol
{//a class to control whether the pilot should be performing certain steering behaviours
public:
	bool go;
	bool seekingtarget, seekingtoppriority, seekingtargetship;
	bool singlepathfollow, loopedpathfollow;
	bool gravitateplace, gravitatemothership;
	bool lookformothership, dockwithmothership;
	bool undock;
	bool lookforasteroid, dockwithasteroid;
	bool astar;//whether the boid should use A*
	bool lookforboid, attackboid, defendyourself;
	bool lookforharvester, protectharvester;

	steeringcontrol():
		go(false),

		seekingtarget(false),
		seekingtoppriority(false),
		seekingtargetship(false),

		singlepathfollow(false),
		loopedpathfollow(false),

		gravitateplace(false),
		gravitatemothership(false),

		lookformothership(false),
		dockwithmothership(false),
		undock(false),

		lookforasteroid(false),
		dockwithasteroid(false),
		astar(false),

		lookforboid(false),
		attackboid(false),
		defendyourself(false),


		lookforharvester(false),
		protectharvester(false)
	{
	}
	steeringcontrol(const vector<string>& FileSteeringControl):
		go(false),

		seekingtarget(false),
		seekingtoppriority(false),
		seekingtargetship(false),

		singlepathfollow(false),
		loopedpathfollow(false),

		gravitateplace(false),
		gravitatemothership(false),

		lookformothership(false),
		dockwithmothership(false),
		undock(false),

		lookforasteroid(false),
		dockwithasteroid(false),

		astar(false),

		lookforboid(false),
		attackboid(false),
		defendyourself(false),

		lookforharvester(false),
		protectharvester(false)
	{
		for(unsigned int i=0;i<FileSteeringControl.size();i++)
		{
			if(FileSteeringControl.at(i).find("go")==0)
				go=true;

			if(FileSteeringControl.at(i).find("seekingtarget")==0)
				seekingtarget=true;
			if(FileSteeringControl.at(i).find("seekingtoppriority")==0)
				seekingtoppriority=true;
			if(FileSteeringControl.at(i).find("seekingtargetship")==0)
				seekingtargetship=true;

			if(FileSteeringControl.at(i).find("singlepathfollow")==0)
				singlepathfollow=true;
			if(FileSteeringControl.at(i).find("loopedpathfollow")==0)
				loopedpathfollow=true;

			if(FileSteeringControl.at(i).find("gravitateplace")==0)
				gravitateplace=true;
			if(FileSteeringControl.at(i).find("gravitatemothership")==0)
				gravitateplace=true;

			if(FileSteeringControl.at(i).find("lookformothership")==0)
				lookformothership=true;
			if(FileSteeringControl.at(i).find("dockwithmothership")==0)
				dockwithmothership=true;
			if(FileSteeringControl.at(i).find("undock")==0)
				undock=true;

			if(FileSteeringControl.at(i).find("lookforasteroid")==0)
				lookforasteroid=true;
			if(FileSteeringControl.at(i).find("dockwithasteroid")==0)
				dockwithasteroid=true;
			if(FileSteeringControl.at(i).find("astar")==0)
				astar=true;

			if(FileSteeringControl.at(i).find("lookforboid")==0)
				lookforboid=true;
			if(FileSteeringControl.at(i).find("attackboid")==0)
				attackboid=true;
			if(FileSteeringControl.at(i).find("defendyourself")==0)
				defendyourself=true;

			if(FileSteeringControl.at(i).find("lookforharvester")==0)
				lookforharvester=true;
			if(FileSteeringControl.at(i).find("protectharvester")==0)
				protectharvester=true;
		}
	}
	~steeringcontrol()
	{
	}
	string print()const
	{
		string anwser("\nsteeringcontrol");
		if(go)anwser+=string("\ngo");

		if(seekingtarget)anwser+=string("\nseekingtarget");
		if(seekingtoppriority)anwser+=string("\nseekingtoppriority");
		if(seekingtargetship)anwser+=string("\nseekingtargetship");

		if(singlepathfollow)anwser+=string("\nsinglepathfollow");
		if(loopedpathfollow)anwser+=string("\nloopedpathfollow");

		if(gravitateplace)anwser+=string("\ngravitateplace");
		if(gravitateplace)anwser+=string("\ngravitatemothership");

		if(lookformothership)anwser+=string("\nlookformothership");
		if(dockwithmothership)anwser+=string("\ndockwithmothership");
		if(undock)anwser+=string("\nundock");

		if(lookforasteroid)anwser+=string("\nlookforasteroid");
		if(dockwithasteroid)anwser+=string("\ndockwithasteroid");

		if(astar)anwser+=string("\nastar");

		if(lookforboid)anwser+=string("\nlookforboid");
		if(attackboid)anwser+=string("\nattackboid");
		if(defendyourself)anwser+=string("\ndefendyourself");

		if(lookforharvester)anwser+=string("\nlookforharvester");
		if(protectharvester)anwser+=string("\nprotectharvester");

		anwser+=string("\n~steeringcontrol\n");
		return anwser;
	}
	inline
	operator bool()const
	{
		return go;
	}
	inline
	void stopall()
	{
		go=false;

		seekingtarget=false;
		seekingtoppriority=false;
		seekingtargetship=false;

		singlepathfollow=false;
		loopedpathfollow=false;

		gravitateplace=false;
		gravitatemothership=false;

		lookformothership=false;
		dockwithmothership=false;
		undock=false;

		lookforasteroid=false;
		dockwithasteroid=false;

		astar=false;

		lookforboid=false;
		attackboid=false;
		defendyourself=false;

		lookforharvester=false;
		protectharvester=false;
	}
	inline
	void setgo(const bool& Go=false)
	{
		go=Go;
	}
	inline
	void setseekingtoppriority(const bool& SeekingTopPriority=false)
	{
		seekingtoppriority=SeekingTopPriority;
	}
	inline
	void setseekingtarget(const bool& SeekingTarget=false)
	{
		seekingtarget=SeekingTarget;
	}
	inline
	void setseekingtargetship(const bool& SeekingTargetShip=false)
	{
		seekingtargetship=SeekingTargetShip;
	}
	inline
	void setsinglepathfollow(const bool& SinglePathFollow=false)
	{
		singlepathfollow=SinglePathFollow;
	}
	inline
	void setloopedpathfollow(const bool& LoopedPathFollow=false)
	{
		loopedpathfollow=LoopedPathFollow;
	}
	inline
	void setgravitateplace(const bool& GravitatePlace=false)
	{
		gravitateplace=GravitatePlace;
	}
	inline
	void setgravitatemothership(const bool& GravitateMothership=false)
	{
		gravitatemothership=GravitateMothership;
	}
	inline
	void setdockwithmothership(const bool& MothershipDock=false)
	{
		dockwithmothership=MothershipDock;
	}
	inline
	void setlookformothership(const bool& LookForMothership=false)
	{
		lookformothership=LookForMothership;
	}
	inline
	void setundock(const bool& Undock=false)
	{
		undock=Undock;
	}
	inline
	void setlookforasteroid(const bool& LookForAsteroid=false)
	{
		lookforasteroid=LookForAsteroid;
	}
	inline
	void setdockwithasteroid(const bool& DockWithAsteroid=false)
	{
		dockwithasteroid=DockWithAsteroid;
	}
	inline
	void setastat(const bool& Astar=false)
	{
		astar=Astar;
	}
	inline
	void setattackboid(const bool& AttackBoid=false)
	{
		attackboid=AttackBoid;
	}
	inline
	void setlookforboid(const bool& LookForBoid=false)
	{
		lookforboid=LookForBoid;
	}
	inline
	void setdefendyourself(const bool& DefendYourself=false)
	{
		defendyourself=DefendYourself;
	}
	inline
	void setlookforharvester(const bool& LookForHarvester=false)
	{
		lookforharvester=LookForHarvester;
	}
	inline
	void setprotectharvester(const bool& ProtectHarvester=false)
	{
		protectharvester=ProtectHarvester;
	}
	void operator()(const steeringcontrol& Other)
	{
		go=Other.go;

		seekingtarget=Other.seekingtarget;
		seekingtoppriority=Other.seekingtoppriority;
		seekingtargetship=Other.seekingtargetship;

		singlepathfollow=Other.singlepathfollow;
		loopedpathfollow=Other.loopedpathfollow;

		gravitateplace=Other.gravitateplace;
		gravitatemothership=Other.gravitatemothership;

		lookformothership=Other.lookformothership;
		dockwithmothership=Other.dockwithmothership;
		undock=Other.undock;

		lookforasteroid=Other.lookforasteroid;
		dockwithasteroid=Other.dockwithasteroid;

		astar=Other.astar;

		lookforboid=Other.lookforboid;
		attackboid=Other.attackboid;
		defendyourself=Other.defendyourself;

		lookforharvester=Other.lookforharvester;
		protectharvester=Other.protectharvester;

	}
	bool operator==(const steeringcontrol& Other)const
	{
		return ((go==Other.go)&&

		(seekingtarget==Other.seekingtarget)&&
		(seekingtoppriority==Other.seekingtoppriority)&&
		(seekingtargetship==Other.seekingtargetship)&&

		(singlepathfollow==Other.singlepathfollow)&&
		(loopedpathfollow==Other.loopedpathfollow)&&

		(gravitateplace==Other.gravitateplace)&&
		(gravitatemothership==Other.gravitatemothership)&&

		(lookformothership==Other.lookformothership)&&
		(dockwithmothership==Other.dockwithmothership)&&
		(undock==Other.undock)&&

		(lookforasteroid==Other.lookforasteroid)&&
		(dockwithasteroid==Other.dockwithasteroid)&&

		(astar==Other.astar)&&

		(lookforboid==Other.lookforboid)&&
		(attackboid==Other.attackboid)&&
		(defendyourself==Other.defendyourself)&&

		(lookforharvester==Other.lookforharvester)&&
		(protectharvester==Other.protectharvester));
	}
	void reset()
	{
		go=false;

		seekingtarget=false;
		seekingtoppriority=false;
		seekingtargetship=false;

		singlepathfollow=false;
		loopedpathfollow=false;

		gravitateplace=false;
		gravitatemothership=false;

		lookformothership=false;
		dockwithmothership=false;
		undock=false;

		lookforasteroid=false;
		dockwithasteroid=false;

		astar=false;

		lookforboid=false;
		attackboid=false;
		defendyourself=false;

		lookforharvester=false;
		protectharvester=false;
	}
};

#endif /* STEERINGCONTROL_H_ */
