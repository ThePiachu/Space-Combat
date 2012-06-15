#ifndef EVOLUTION_CPP_
#define EVOLUTION_CPP_

#include "random.h"

//#define EVOLUTIONSPEED 0.9
//#define EVOLUTIONSPEED 0.8
//#define EVOLUTIONSPEED 0.7
//#define EVOLUTIONSPEED 0.6
#define EVOLUTIONSPEED 0.5

//the evolution function, used by many classes for the purpose of evolving boids

inline
float evolve(const float& Number, const bool& Evolve=false, const float& EvolutionSpeed=EVOLUTIONSPEED)
{
	static random* myrandom=random::getinstance();
	static float tmp=0.0;
	tmp=myrandom->randomnormalcenteredatzero(1.0);
	if(tmp<0.0)tmp*=EvolutionSpeed;
	else if(tmp>0.0)tmp*=EvolutionSpeed/(1.0-EvolutionSpeed);
	//cout<<"Evolution number: "<<tmp<<endl<<flush;
	return Number+Evolve*Number*tmp;
}
inline
float evolve(const float& Number, const bool& Evolve, const bool& SpecialEvolve, const float& EvolutionSpeed=EVOLUTIONSPEED)
{
	static random* myrandom=random::getinstance();
	static float tmp=0.0;
	tmp=myrandom->randomnormalcenteredatzero(1.0);
	if(tmp<0.0)tmp*=EvolutionSpeed;
	else if(tmp>0.0)tmp*=EvolutionSpeed/(1.0-EvolutionSpeed);
	//cout<<"Evolution number: "<<tmp<<endl<<flush;
	return Number+Evolve*(!SpecialEvolve)*Number*tmp;
}
/*
inline
float evolve(const float& Number, const bool& Evolve=false, const float& EvolutionSpeed=EVOLUTIONSPEED)
{
	static random* myrandom=random::getinstance();
	return Number+Evolve*myrandom->randomnormalcenteredatzero(Number*EvolutionSpeed);
}*/


#endif //EVOLUTION_CPP_
