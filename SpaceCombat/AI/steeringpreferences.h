#ifndef STEERINGPREFERENCES_H_
#define STEERINGPREFERENCES_H_

#include "../stringhandling.h"
#include "../math.h"
//#include "../evolution.cpp"
//#define STEERINGEVOLUTIONSPEED 0.5


class steeringpreferences
{
public:
	random* myrandom;
	float wanderp;
	float seekp, tpseekp;//top priorityseek
	float fleep;//steering priorities

	float arrivep, arriveslowingdistance, arrivefcoeff;
	float followp, followmaxdistance, followgoalprecision;

	//10 variables

	float separationp, alignmentp, cohesionp;

	float avoidp, avoidtriggerdistance;
	float avoidasteroidp, avoidasteroidtriggerdistance;

	float gravitateplacep, gravitateplacemaxdistance;

	float mothershipdockradius, asteroiddockradius;

	float threshold;
	steeringpreferences(const float& WanderPreference=0.0,
			const float& SeekPreference=0.0,
			const float& TopPrioritySeekPreference=0.0,
			const float& FleePreference=0.0,
			const float& ArrivePreference=0.0,
			const float& FollowPreference=0.0,
			const float& ArriveSlowingDistance=0.0,
			const float& ArriveFunctionCoefficient=0.0,
			const float& MaxFollowDistance=0.0,
			const float& FollowGoalPrecision=0.0,

			const float& SeparationPreference=0.0,
			const float& AlignmentPreference=0.0,
			const float& CohersionPreference=0.0,
			const float& AvoidPreference=0.0,
			const float& AvoidTriggerDistance=0.0,
			const float& AsteroidAvoidPreference=0.0,
			const float& AsteroidAvoidTriggerDistance=0.0,
			const float& GravitatePlacePreference=0.0,
			const float& GravitatePlaceMaxDistance=0.0,
			const float& MothershipDockRadius=0.0,

			const float& AsteroidDockRadius=0.0,
			const float& Threshold=0.01):
			myrandom(random::getinstance()),
			wanderp(WanderPreference),
			seekp(SeekPreference),
			tpseekp(TopPrioritySeekPreference),
			fleep(FleePreference),
			arrivep(ArrivePreference),
			arriveslowingdistance(ArriveSlowingDistance),
			arrivefcoeff(ArriveFunctionCoefficient),

			followp(FollowPreference),
			followmaxdistance(MaxFollowDistance),
			followgoalprecision(FollowGoalPrecision),

			separationp(SeparationPreference),
			alignmentp(AlignmentPreference),
			cohesionp(CohersionPreference),

			avoidp(AvoidPreference),
			avoidtriggerdistance(AvoidTriggerDistance),
			avoidasteroidp(AsteroidAvoidPreference),
			avoidasteroidtriggerdistance(AsteroidAvoidTriggerDistance),

			gravitateplacep(GravitatePlacePreference),
			gravitateplacemaxdistance(GravitatePlaceMaxDistance),
			mothershipdockradius(MothershipDockRadius),
			asteroiddockradius(AsteroidDockRadius),
			threshold(Threshold)
	{
	}
	steeringpreferences(const steeringpreferences& Other,
			const bool& Evolve=false):
			myrandom(random::getinstance()),
			wanderp(evolve(Other.wanderp, Evolve)),
			seekp(evolve(Other.seekp, Evolve)),
			tpseekp(evolve(Other.tpseekp, Evolve)),
			fleep(evolve(Other.fleep, Evolve)),

			arrivep(evolve(Other.arrivep, Evolve)),
			arriveslowingdistance(evolve(Other.arriveslowingdistance, Evolve)),
			arrivefcoeff(evolve(Other.arrivefcoeff, Evolve)),

			followp(evolve(Other.followp, Evolve)),
			followmaxdistance(evolve(Other.followmaxdistance, Evolve)),
			followgoalprecision(evolve(Other.followgoalprecision, Evolve)),

			separationp(evolve(Other.separationp, Evolve)),
			alignmentp(evolve(Other.alignmentp, Evolve)),
			cohesionp(evolve(Other.cohesionp, Evolve)),

			avoidp(evolve(Other.avoidp, Evolve)),
			avoidtriggerdistance(evolve(Other.avoidtriggerdistance, Evolve)),
			avoidasteroidp(evolve(Other.avoidasteroidp, Evolve)),
			avoidasteroidtriggerdistance(evolve(Other.avoidasteroidtriggerdistance, Evolve)),

			gravitateplacep(evolve(Other.gravitateplacep, Evolve)),
			gravitateplacemaxdistance(evolve(Other.gravitateplacemaxdistance, Evolve)),


			mothershipdockradius(evolve(Other.mothershipdockradius, Evolve)),
			asteroiddockradius(evolve(Other.asteroiddockradius, Evolve)),
			threshold(evolve(Other.threshold, Evolve))
	{
	}
	steeringpreferences(const steeringpreferences& Other,
			const bool& Evolve, const bool& SpecialEvolve)://a function for selective evolution
			myrandom(random::getinstance()),
			wanderp(evolve(Other.wanderp, Evolve, SpecialEvolve)),
			seekp(evolve(Other.seekp, Evolve, SpecialEvolve)),
			tpseekp(evolve(Other.tpseekp, Evolve, SpecialEvolve)),
			fleep(evolve(Other.fleep, Evolve, SpecialEvolve)),

			arrivep(evolve(Other.arrivep, Evolve, SpecialEvolve)),
			arriveslowingdistance(evolve(Other.arriveslowingdistance, Evolve, SpecialEvolve)),
			arrivefcoeff(evolve(Other.arrivefcoeff, Evolve, SpecialEvolve)),

			followp(evolve(Other.followp, Evolve, SpecialEvolve)),
			followmaxdistance(evolve(Other.followmaxdistance, Evolve, SpecialEvolve)),
			followgoalprecision(evolve(Other.followgoalprecision, Evolve, SpecialEvolve)),

			separationp(evolve(Other.separationp, Evolve, SpecialEvolve)),
			alignmentp(evolve(Other.alignmentp, Evolve, SpecialEvolve)),
			cohesionp(evolve(Other.cohesionp, Evolve, SpecialEvolve)),

			avoidp(evolve(Other.avoidp, Evolve, SpecialEvolve)),
			avoidtriggerdistance(evolve(Other.avoidtriggerdistance, Evolve, SpecialEvolve)),
			avoidasteroidp(evolve(Other.avoidasteroidp, Evolve, SpecialEvolve)),
			avoidasteroidtriggerdistance(evolve(Other.avoidasteroidtriggerdistance, Evolve, SpecialEvolve)),

			gravitateplacep(evolve(Other.gravitateplacep, Evolve, SpecialEvolve)),
			gravitateplacemaxdistance(evolve(Other.gravitateplacemaxdistance, Evolve, SpecialEvolve)),


			mothershipdockradius(evolve(Other.mothershipdockradius, Evolve, SpecialEvolve)),
			asteroiddockradius(evolve(Other.asteroiddockradius, Evolve, SpecialEvolve)),
			threshold(evolve(Other.threshold, Evolve, SpecialEvolve))
	{
	}
	steeringpreferences(const steeringpreferences* Other,
			const bool& Evolve=false):
			myrandom(random::getinstance()),
			wanderp(evolve(Other->wanderp, Evolve)),
			seekp(evolve(Other->seekp, Evolve)),
			tpseekp(evolve(Other->tpseekp, Evolve)),
			fleep(evolve(Other->fleep, Evolve)),

			arrivep(evolve(Other->arrivep, Evolve)),
			arriveslowingdistance(evolve(Other->arriveslowingdistance, Evolve)),
			arrivefcoeff(evolve(Other->arrivefcoeff, Evolve)),

			followp(evolve(Other->followp, Evolve)),
			followmaxdistance(evolve(Other->followmaxdistance, Evolve)),
			followgoalprecision(evolve(Other->followgoalprecision, Evolve)),

			separationp(evolve(Other->separationp, Evolve)),
			alignmentp(evolve(Other->alignmentp, Evolve)),
			cohesionp(evolve(Other->cohesionp, Evolve)),

			avoidp(evolve(Other->avoidp, Evolve)),
			avoidtriggerdistance(evolve(Other->avoidtriggerdistance, Evolve)),
			avoidasteroidp(evolve(Other->avoidasteroidp, Evolve)),
			avoidasteroidtriggerdistance(evolve(Other->avoidasteroidtriggerdistance, Evolve)),

			gravitateplacep(evolve(Other->gravitateplacep, Evolve)),
			gravitateplacemaxdistance(evolve(Other->gravitateplacemaxdistance, Evolve)),


			mothershipdockradius(evolve(Other->mothershipdockradius, Evolve)),
			asteroiddockradius(evolve(Other->asteroiddockradius, Evolve)),
			threshold(evolve(Other->threshold, Evolve))
	{
	}
	steeringpreferences(const steeringpreferences* Other,
				const bool& Evolve, const bool& SpecialEvolve)://function for selective evolution
			myrandom(random::getinstance()),
			wanderp(evolve(Other->wanderp, Evolve, SpecialEvolve)),
			seekp(evolve(Other->seekp, Evolve, SpecialEvolve)),
			tpseekp(evolve(Other->tpseekp, Evolve, SpecialEvolve)),
			fleep(evolve(Other->fleep, Evolve, SpecialEvolve)),

			arrivep(evolve(Other->arrivep, Evolve, SpecialEvolve)),
			arriveslowingdistance(evolve(Other->arriveslowingdistance, Evolve, SpecialEvolve)),
			arrivefcoeff(evolve(Other->arrivefcoeff, Evolve, SpecialEvolve)),

			followp(evolve(Other->followp, Evolve, SpecialEvolve)),
			followmaxdistance(evolve(Other->followmaxdistance, Evolve, SpecialEvolve)),
			followgoalprecision(evolve(Other->followgoalprecision, Evolve, SpecialEvolve)),

			separationp(evolve(Other->separationp, Evolve, SpecialEvolve)),
			alignmentp(evolve(Other->alignmentp, Evolve, SpecialEvolve)),
			cohesionp(evolve(Other->cohesionp, Evolve, SpecialEvolve)),

			avoidp(evolve(Other->avoidp, Evolve, SpecialEvolve)),
			avoidtriggerdistance(evolve(Other->avoidtriggerdistance, Evolve, SpecialEvolve)),
			avoidasteroidp(evolve(Other->avoidasteroidp, Evolve, SpecialEvolve)),
			avoidasteroidtriggerdistance(evolve(Other->avoidasteroidtriggerdistance, Evolve, SpecialEvolve)),

			gravitateplacep(evolve(Other->gravitateplacep, Evolve, SpecialEvolve)),
			gravitateplacemaxdistance(evolve(Other->gravitateplacemaxdistance, Evolve, SpecialEvolve)),


			mothershipdockradius(evolve(Other->mothershipdockradius, Evolve, SpecialEvolve)),
			asteroiddockradius(evolve(Other->asteroiddockradius, Evolve, SpecialEvolve)),
			threshold(evolve(Other->threshold, Evolve, SpecialEvolve))
	{
	}
	steeringpreferences(const vector<string>& FileSteeringPreferences):
		myrandom(random::getinstance()),
		wanderp(0.0),
		seekp(0.0),
		tpseekp(0.0),
		fleep(0.0),
		arrivep(0.0),
		arriveslowingdistance(0.0),
		arrivefcoeff(0.0),

		followp(0.0),
		followmaxdistance(0.0),
		followgoalprecision(0.0),

		separationp(0.0),
		alignmentp(0.0),
		cohesionp(0.0),

		avoidp(0.0),
		avoidtriggerdistance(0.0),
		avoidasteroidp(0.0),
		avoidasteroidtriggerdistance(0.0),

		gravitateplacep(0.0),
		gravitateplacemaxdistance(0.0),
		mothershipdockradius(0.0),
		asteroiddockradius(0.0),
		threshold(0.0)
	{
		for(unsigned int i=0;i<FileSteeringPreferences.size();i++)
		{
			if(FileSteeringPreferences.at(i).find("wanderp")==0)
				wanderp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("seekp")==0)
				if(FileSteeringPreferences.at(i).find("tpseekp")==string::npos)//making sure its not tpseekp
					seekp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("tpseekp")==0)
				tpseekp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("fleep")==0)
				fleep=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("arrivep")==0)
				arrivep=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("arriveslowingdistance")==0)
				arriveslowingdistance=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("arrivefcoeff")==0)
				arrivefcoeff=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("followp")==0)
				followp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("followmaxdistance")==0)
				followmaxdistance=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("followgoalprecision")==0)
				followgoalprecision=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("separationp")==0)
				separationp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("alignmentp")==0)
				alignmentp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("cohesionp")==0)
				cohesionp=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("avoidp")==0)
				avoidp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("avoidtriggerdistance")==0)
				avoidtriggerdistance=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("avoidasteroidp")==0)
				avoidasteroidp=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("avoidasteroidtriggerdistance")==0)
				avoidasteroidtriggerdistance=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("gravitateplacep")==0)
				gravitateplacep=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("gravitateplacemaxdistance")==0)
				gravitateplacemaxdistance=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("mothershipdockradius")==0)
				mothershipdockradius=getfloat(FileSteeringPreferences.at(i));
			if(FileSteeringPreferences.at(i).find("asteroiddockradius")==0)
				asteroiddockradius=getfloat(FileSteeringPreferences.at(i));

			if(FileSteeringPreferences.at(i).find("threshold")==0)
				threshold=getfloat(FileSteeringPreferences.at(i));
		}
	}
	~steeringpreferences()
	{
	}

	steeringpreferences& operator()(const steeringpreferences& Other, const bool& Evolve=true)
	{//inheritance
		wanderp=evolve(Other.wanderp, Evolve);
		seekp=evolve(Other.seekp, Evolve);
		tpseekp=evolve(Other.tpseekp, Evolve);
		fleep=evolve(Other.fleep, Evolve);

		arrivep=evolve(Other.arrivep, Evolve);
		arriveslowingdistance=evolve(Other.arriveslowingdistance, Evolve);
		arrivefcoeff=evolve(Other.arrivefcoeff, Evolve);

		followp=evolve(Other.followp, Evolve);
		followmaxdistance=evolve(Other.followmaxdistance, Evolve);
		followgoalprecision=evolve(Other.followgoalprecision, Evolve);

		separationp=evolve(Other.separationp, Evolve);
		alignmentp=evolve(Other.alignmentp, Evolve);
		cohesionp=evolve(Other.cohesionp, Evolve);

		avoidp=evolve(Other.avoidp, Evolve);
		avoidtriggerdistance=evolve(Other.avoidtriggerdistance, Evolve);
		avoidasteroidp=evolve(Other.avoidasteroidp, Evolve);
		avoidasteroidtriggerdistance=evolve(Other.avoidasteroidtriggerdistance, Evolve);

		gravitateplacep=evolve(Other.gravitateplacep, Evolve);
		gravitateplacemaxdistance=evolve(Other.gravitateplacemaxdistance, Evolve);


		mothershipdockradius=evolve(Other.mothershipdockradius, Evolve);
		asteroiddockradius=evolve(Other.asteroiddockradius, Evolve);

		threshold=evolve(Other.threshold, Evolve);

		return *this;
	}
	steeringpreferences& operator=(const steeringpreferences& Other)
	{
		wanderp=Other.wanderp;
		seekp=Other.seekp;
		tpseekp=Other.tpseekp;
		fleep=Other.fleep;

		arrivep=Other.arrivep;
		arriveslowingdistance=Other.arriveslowingdistance;
		arrivefcoeff=Other.arrivefcoeff;

		followp=Other.followp;
		followmaxdistance=Other.followmaxdistance;
		followgoalprecision=Other.followgoalprecision;

		separationp=Other.separationp;
		alignmentp=Other.alignmentp;
		cohesionp=Other.cohesionp;

		avoidp=Other.avoidp;
		avoidtriggerdistance=Other.avoidtriggerdistance;
		avoidasteroidp=Other.avoidasteroidp;
		avoidasteroidtriggerdistance=Other.avoidasteroidtriggerdistance;

		gravitateplacep=Other.gravitateplacep;
		gravitateplacemaxdistance=Other.gravitateplacemaxdistance;


		mothershipdockradius=Other.mothershipdockradius;
		asteroiddockradius=Other.asteroiddockradius;

		threshold=Other.threshold;

		return *this;
	}
	bool operator!=(const steeringpreferences& Other)const
	{
		return !operator==(Other);
	}
	bool operator==(const steeringpreferences& Other)const
	{
		return((wanderp==Other.wanderp)&&
		(seekp==Other.seekp)&&
		(tpseekp==Other.tpseekp)&&
		(fleep==Other.fleep)&&

		(arrivep==Other.arrivep)&&
		(arriveslowingdistance==Other.arriveslowingdistance)&&
		(arrivefcoeff==Other.arrivefcoeff)&&

		(followp==Other.followp)&&
		(followmaxdistance==Other.followmaxdistance)&&
		(followgoalprecision==Other.followgoalprecision)&&

		(separationp==Other.separationp)&&
		(alignmentp==Other.alignmentp)&&
		(cohesionp==Other.cohesionp)&&

		(avoidp==Other.avoidp)&&
		(avoidtriggerdistance==Other.avoidtriggerdistance)&&
		(avoidasteroidp==Other.avoidasteroidp)&&
		(avoidasteroidtriggerdistance==Other.avoidasteroidtriggerdistance)&&

		(gravitateplacep==Other.gravitateplacep)&&
		(gravitateplacemaxdistance==Other.gravitateplacemaxdistance)&&


		(mothershipdockradius==Other.mothershipdockradius)&&
		(asteroiddockradius==Other.asteroiddockradius)&&

		(threshold==Other.threshold));
	}

	inline
	void setwander(const float& Wander=0.0)
	{
		wanderp=Wander;
	}
	inline
	void setseek(const float& Seek=0.0)
	{
		seekp=Seek;
	}
	inline
	void settoppriorityseek(const float& TPSeek=0.0)
	{
		tpseekp=TPSeek;
	}
	inline
	void setflee(const float& Flee=0.0)
	{
		fleep=Flee;
	}
	inline
	void setarrive(const float& Arrive=0.0, const float& ArriveSlowingDistance=3.0, const float& ArriveFunctionCoefficient=1.0)
	{
		arrivep=Arrive;
		arriveslowingdistance=ArriveSlowingDistance;
		arrivefcoeff=ArriveFunctionCoefficient;
	}
	inline
	void setfollow(const float& Follow=0.0, const float& MaxFollowDistance=1.0, const float& Precision=0.6)
	{
		followp=Follow;
		followmaxdistance=MaxFollowDistance;
		followgoalprecision=Precision;
	}
	inline
	void setseparation(const float& Separation=0.0)
	{
		separationp=Separation;
	}
	inline
	void setalignment(const float& Alignment=0.0)
	{
		alignmentp=Alignment;
	}
	inline
	void setcohesion(const float& Cohersion=0.0)
	{
		cohesionp=Cohersion;
	}
	inline
	void setavoid(const float& Avoid=0.0, const float& AvoidTriggerDistance=0.5)
	{
		avoidp=Avoid;
		avoidtriggerdistance=AvoidTriggerDistance;
	}
	inline
	void setasteroidavoid(const float& AsteroidAvoidPreference=0.0, const float& AsteroidAvoidTriggerDistance=0.5)
	{
		avoidasteroidp=AsteroidAvoidPreference;
		avoidasteroidtriggerdistance=AsteroidAvoidTriggerDistance;
	}
	inline
	void setgravitate(const float& Gravitate=0.0, const float& MaxDistance=5.0)
	{
		gravitateplacep=Gravitate;
		gravitateplacemaxdistance=MaxDistance;
	}
	inline
	void setdockradius(const float& MothershipDockRadius=0.5, const float& AsteroidDockRadius=0.5)
	{
		mothershipdockradius=MothershipDockRadius;
		asteroiddockradius=AsteroidDockRadius;
	}


	inline
	bool wander()const
	{
		return wanderp>threshold;
	}
	inline
	bool seek()const
	{
		return seekp>threshold;
	}
	inline
	bool toppriorityseek()const
	{
		return tpseekp>threshold;
	}
	inline
	bool flee()const
	{
		return fleep>threshold;
	}
	inline
	bool arrive()const
	{
		return arrivep>threshold;
	}
	inline
	bool follow()const
	{
		return followp>threshold;
	}
	inline
	bool separation()const
	{
		return separationp>threshold;
	}
	inline
	bool alignment()const
	{
		return alignmentp>threshold;
	}
	inline
	bool  cohesion()const
	{
		return cohesionp>threshold;
	}
	inline
	bool avoid() const
	{
		return avoidp>threshold;
	}
	inline
	bool gravitateplace() const
	{
		return gravitateplacep>threshold;
	}

	steeringpreferences& operator+(const steeringpreferences& Other)
	{
		return steeringpreferences(*this, false)+=Other;
	}

	steeringpreferences& operator+=(const steeringpreferences& Other)
	{
		wanderp+=Other.wanderp;
		seekp+=Other.seekp;
		tpseekp+=Other.tpseekp;
		fleep+=Other.fleep;
		arrivep+=Other.arrivep;
		arriveslowingdistance+=Other.arriveslowingdistance;
		arrivefcoeff+=Other.arrivefcoeff;
		followp+=Other.followp;
		followmaxdistance+=Other.followmaxdistance;
		followgoalprecision+=Other.followgoalprecision;

		separationp+=Other.separationp;
		alignmentp+=Other.alignmentp;
		cohesionp+=Other.cohesionp;
		avoidp+=Other.avoidp;
		avoidtriggerdistance+=Other.avoidtriggerdistance;
		avoidasteroidp+=Other.avoidasteroidp;
		avoidasteroidtriggerdistance+=Other.avoidasteroidtriggerdistance;

		gravitateplacep+=Other.gravitateplacep;
		gravitateplacemaxdistance+=Other.gravitateplacemaxdistance;

		mothershipdockradius+=Other.mothershipdockradius;
		asteroiddockradius+=Other.asteroiddockradius;

		threshold+=Other.threshold;
		return *this;
	}
	steeringpreferences& operator/(const float& HowMuch)
	{
		return steeringpreferences(*this, false)/=HowMuch;
	}
	steeringpreferences& operator/=(const float& HowMuch)
	{
		wanderp/=HowMuch;
		seekp/=HowMuch;
		tpseekp/=HowMuch;
		fleep/=HowMuch;
		arrivep/=HowMuch;
		arriveslowingdistance/=HowMuch;
		arrivefcoeff/=HowMuch;
		followp/=HowMuch;
		followgoalprecision/=HowMuch;
		separationp/=HowMuch;

		alignmentp/=HowMuch;
		cohesionp/=HowMuch;
		avoidp/=HowMuch;
		avoidtriggerdistance/=HowMuch;
		followmaxdistance/=HowMuch;
		avoidasteroidp/=HowMuch;
		avoidasteroidtriggerdistance/=HowMuch;
		mothershipdockradius/=HowMuch;
		gravitateplacep/=HowMuch;
		gravitateplacemaxdistance/=HowMuch;

		asteroiddockradius/=HowMuch;
		threshold/=HowMuch;

		return *this;
	}

	string print()const
	{
		string result("\nsteeringpreferences");
		char Chars[100];
		if(wanderp!=0.0)
		{
			result+=string("\nwanderp\t");
			sprintf(Chars, "%f", wanderp);
			result+=Chars;
		}
		if(seekp!=0.0)
		{
			result+=string("\nseekp\t");
			sprintf(Chars, "%f", seekp);
			result+=Chars;
		}
		if(tpseekp!=0.0)
		{
			result+=string("\ntpseekp\t");
			sprintf(Chars, "%f", tpseekp);
			result+=Chars;
		}
		if(fleep!=0.0)
		{
			result+=string("\nfleep\t");
			sprintf(Chars, "%f", fleep);
			result+=Chars;
		}
		if(arrivep!=0.0)
		{
			result+=string("\narrivep\t");
			sprintf(Chars, "%f", arrivep);
			result+=Chars;
		}
		if(arriveslowingdistance!=0.0)
		{
			result+=string("\narriveslowingdistance\t");
			sprintf(Chars, "%f", arriveslowingdistance);
			result+=Chars;
		}
		if(arrivefcoeff!=0.0)
		{
			result+=string("\narrivefcoeff\t");
			sprintf(Chars, "%f", arrivefcoeff);
			result+=Chars;
		}
		if(followp!=0.0)
		{
			result+=string("\nfollowp\t");
			sprintf(Chars, "%f", followp);
			result+=Chars;
		}
		if(followgoalprecision!=0.0)
		{
			result+=string("\nfollowgoalprecision\t");
			sprintf(Chars, "%f", followgoalprecision);
			result+=Chars;
		}
		if(followmaxdistance!=0.0)
		{
			result+=string("\nfollowmaxdistance\t");
			sprintf(Chars, "%f", followmaxdistance);
			result+=Chars;
		}

		if(separationp!=0.0)
		{
			result+=string("\nseparationp\t");
			sprintf(Chars, "%f", separationp);
			result+=Chars;
		}

		if(alignmentp!=0.0)
		{
			result+=string("\nalignmentp\t");
			sprintf(Chars, "%f", alignmentp);
			result+=Chars;
		}
		if(cohesionp!=0.0)
		{
			result+=string("\ncohesionp\t");
			sprintf(Chars, "%f", cohesionp);
			result+=Chars;
		}


		if(avoidp!=0.0)
		{
			result+=string("\navoidp\t");
			sprintf(Chars, "%f", avoidp);
			result+=Chars;
		}
		if(avoidtriggerdistance!=0.0)
		{
			result+=string("\navoidtriggerdistance\t");
			sprintf(Chars, "%f", avoidtriggerdistance);
			result+=Chars;
		}
		if(avoidasteroidp!=0.0)
		{
			result+=string("\navoidasteroidp\t");
			sprintf(Chars, "%f", avoidasteroidp);
			result+=Chars;
		}
		if(avoidasteroidtriggerdistance!=0.0)
		{
			result+=string("\navoidasteroidtriggerdistance\t");
			sprintf(Chars, "%f", avoidasteroidtriggerdistance);
			result+=Chars;
		}
		if(mothershipdockradius!=0.0)
		{
			result+=string("\nmothershipdockradius\t");
			sprintf(Chars, "%f", mothershipdockradius);
			result+=Chars;
		}
		if(gravitateplacep!=0.0)
		{
			result+=string("\ngravitateplacep\t");
			sprintf(Chars, "%f", gravitateplacep);
			result+=Chars;
		}
		if(gravitateplacemaxdistance!=0.0)
		{
			result+=string("\ngravitateplacemaxdistance\t");
			sprintf(Chars, "%f", gravitateplacemaxdistance);
			result+=Chars;
		}


		if(asteroiddockradius!=0.0)
		{
			result+=string("\nasteroiddockradius\t");
			sprintf(Chars, "%f", asteroiddockradius);
			result+=Chars;
		}

		if(threshold!=0.0)
		{
			result+=string("\nthreshold\t");
			sprintf(Chars, "%f", threshold);
			result+=Chars;
		}

		result+=string("\n~steeringpreferences\n");
		return result;
	}
	void printme()
	{
		if(wanderp!=0.0)cout<<"wanderp\t"<<wanderp<<endl;
		if(seekp!=0.0)cout<<"seekp\t"<<seekp<<endl;
		if(tpseekp!=0.0)cout<<"tpseekp\t"<<tpseekp<<endl;
		if(fleep!=0.0)cout<<"fleep\t"<<fleep<<endl;

		if(arrivep!=0.0)cout<<"arrivep\t"<<arrivep<<endl;
		if(arriveslowingdistance!=0.0)cout<<"arriveslowingdistance\t"<<arriveslowingdistance<<endl;
		if(arrivefcoeff!=0.0)cout<<"arrivefcoeff\t"<<arrivefcoeff<<endl;
		if(followp!=0.0)cout<<"followp\t"<<followp<<endl;
		if(followgoalprecision!=0.0)cout<<"followgoalprecision\t"<<followgoalprecision<<endl;
		if(followmaxdistance!=0.0)cout<<"followmaxdistance\t"<<followmaxdistance<<endl;

		if(separationp!=0.0)cout<<"separationp\t"<<separationp<<endl;
		if(alignmentp!=0.0)cout<<"alignmentp\t"<<alignmentp<<endl;
		if(cohesionp!=0.0)cout<<"cohesionp\t"<<cohesionp<<endl;

		if(avoidp!=0.0)cout<<"avoidp\t"<<avoidp<<endl;
		if(avoidtriggerdistance!=0.0)cout<<"avoidtriggerdistance\t"<<avoidtriggerdistance<<endl;
		if(avoidasteroidp!=0.0)cout<<"avoidasteroidp\t"<<avoidasteroidp<<endl;
		if(avoidasteroidtriggerdistance!=0.0)cout<<"avoidasteroidtriggerdistance\t"<<avoidasteroidtriggerdistance<<endl;
		if(gravitateplacep!=0.0)cout<<"gravitateplacep\t"<<gravitateplacep<<endl;
		if(gravitateplacemaxdistance!=0.0)cout<<"gravitateplacemaxdistance\t"<<gravitateplacemaxdistance<<endl;


		if(mothershipdockradius!=0.0)cout<<"mothershipdockradius\t"<<mothershipdockradius<<endl;
		if(asteroiddockradius!=0.0)cout<<"asteroiddockradius\t"<<asteroiddockradius<<endl;

		if(threshold!=0.0)cout<<"threshold\t"<<threshold<<endl;
	}

	void reset()
	{
		wanderp=0.0;
		seekp=0.0;
		tpseekp=0.0;
		fleep=0.0;
		arrivep=0.0;
		arriveslowingdistance=0.0;
		arrivefcoeff=0.0;
		followp=0.0;
		followgoalprecision=0.0;
		separationp=0.0;
		alignmentp=0.0;
		cohesionp=0.0;
		avoidp=0.0;
		avoidtriggerdistance=0.0;
		followmaxdistance=0.0;
		avoidasteroidp=0.0;
		avoidasteroidtriggerdistance=0.0;
		mothershipdockradius=0.0;
		gravitateplacep=0.0;
		gravitateplacemaxdistance=0.0;
		asteroiddockradius=0.0;
		threshold=0.0;
	}

	bool unittest()
	{
		steeringpreferences tmp(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
				1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
				2.1, 2.2);
		if(tmp==steeringpreferences(separatestrings(tmp.print())))
		{
			return true;
		}
		tmp.printme();
		steeringpreferences(separatestrings(tmp.print())).printme();
		return false;
	}
};

#endif /* STEERINGPREFERENCES_H_ */
