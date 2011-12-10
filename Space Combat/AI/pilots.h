#ifndef PILOTS_H_
#define PILOTS_H_

//#define TOPPILOTSMAXSIZE 100
#define PILOTSSPEAK false
//#define PILOTSSPEAK true
#include "pilot.h"
#include "filepilot.h"
#include <vector>
#include <algorithm>

using namespace std;

bool comparepilotpointerspairf(const pair<pilot*, bool>&, const pair<pilot*, bool>&);

class pilots
{//a class to handle all pilots
public:
	random* myrandom;//random class
	pilot basefighterpilot;//generic pilot, used for generating initial boids
	pilot baseharvesterpilot;//generic pilot, used for generating initial boids
	vector <pilot*> allfighterpilots;//vector of all living pilots
	vector <pair<pilot*, bool> > topfighterpilots;//vector of top pilots, including dead ones
	vector <pilot*> allharvesterpilots;//vector of all living pilots
	vector <pair<pilot*, bool> > topharvesterpilots;//vector of top pilots, including dead ones
	//bool true means pilot is alive, bool false - it is dead
	unsigned int pilotcap;//maximum number of pilots
	grid* metagrid;//pointer to the grid
	target newpilotgravitatetarget;//place where all the new pilots should gravitate at
	mothership* themothership;//pointer to pilots' mothership
	path defaultloopedpath, defaultsinglepath;//default paths the new pilots will follow
	filepilot fp;
	colour mothershipcolour;
	bool usefilepilot;
	pilots(const float& MinimumScoreToSavePilot=1.5):
		myrandom(random::getinstance()),
		basefighterpilot(),
		baseharvesterpilot(),
		allfighterpilots(),
		topfighterpilots(),
		allharvesterpilots(),
		topharvesterpilots(),
		pilotcap(0),
		metagrid(NULL),
		newpilotgravitatetarget(point(0.0, 0.0, 0.0), 0.0),
		themothership(NULL),
		defaultloopedpath(),
		defaultsinglepath(),
		fp(MinimumScoreToSavePilot),
		mothershipcolour(0.0, 0.0, 0.0),
		usefilepilot(false)
	{
	}
	~pilots()
	{
		clear();
	}

	void newevolvedpilot2(const point Position=point(0.0, 0.0, 0.0), const bool& Evolve=true, const bool& PilotIsHarvester=false)
	{//creating a new evolved pilot, basing on the group of living pilots, or the basic pilots
		if((allfighterpilots.size()+allharvesterpilots.size())<pilotcap)
		{//if there arn`t too many pilots
			if(PilotIsHarvester)
			{
				if(topharvesterpilots.size()>0)
				{//if there are any living pilots
					sort(topharvesterpilots.begin(), topharvesterpilots.end(), comparepilotpointerspairf);//they are sorted
					//if(topharvesterpilots.size()>TOPPILOTSMAXSIZE)
					if(topharvesterpilots.size()>2*pilotcap)
					{
						//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topharvesterpilots.size();i++)
						for(unsigned int i=2*pilotcap-1;topharvesterpilots.size()>2*pilotcap;i--)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(topharvesterpilots.at(i).second==false)
							{
								if(PILOTSSPEAK)cout<<"delete(topharvesterpilots.at(i).first);"<<endl<<flush;
								delete(topharvesterpilots.at(i).first);
								topharvesterpilots.erase(topharvesterpilots.begin()+i);
								//i--;
							}
						}
					}
					//unsigned int pilotnumber=myrandom->randomnormalunsignedintcenteredatzero(topharvesterpilots.size());
					//cout<<"Evolving from pilot number "<<pilotnumber<<" out of "<<topharvesterpilots.size()<<endl<<flush;
					allharvesterpilots.push_back
					(//new pilot is created
						new pilot
						(
							topharvesterpilots.at
							(
								//pilotnumber
								myrandom->randomnormalunsignedintcenteredatzero(topharvesterpilots.size())
							).first,
							Position,
							Evolve
						)
					);
					allharvesterpilots.back()->setshiptype(1);
					topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				}
				else
				{//otherwise, a new pilot is created form the basic pilot
					allharvesterpilots.push_back
					(
						new pilot
						(
							&baseharvesterpilot,
							Position,
							Evolve
						)
					);
					allharvesterpilots.back()->setshiptype(1);
					topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				}
				//setting the pilot up
				allharvesterpilots.back()->setgrid(metagrid);
				allharvesterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allharvesterpilots.back()->setmothership(themothership);
				allharvesterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				//putting pilot's ship in the grid
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allharvesterpilots.back()->myship));
				else cout<<"void newevolvedpilot2 metagrid==NULL";
			}
			else
			{
				if(topfighterpilots.size()>0)
				{//if there are any living pilots
					sort(topfighterpilots.begin(), topfighterpilots.end(), comparepilotpointerspairf);//they are sorted
					//if(topfighterpilots.size()>TOPPILOTSMAXSIZE)
					if(topfighterpilots.size()>2*pilotcap)
					{
						//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topfighterpilots.size();i++)
						for(unsigned int i=2*pilotcap-1;topfighterpilots.size()>2*pilotcap;i--)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(topfighterpilots.at(i).second==false)
							{
								if(PILOTSSPEAK)cout<<"delete(topfighterpilots.at(i).first);"<<endl<<flush;
								delete(topfighterpilots.at(i).first);
								topfighterpilots.erase(topfighterpilots.begin()+i);
								//i--;
							}
						}
					}
					//unsigned int pilotnumber=myrandom->randomnormalunsignedintcenteredatzero(topfighterpilots.size());
					//cout<<"Evolving from pilot number "<<pilotnumber<<" out of "<<topfighterpilots.size()<<endl<<flush;
					allfighterpilots.push_back
					(//new pilot is created
						new pilot
						(
							topfighterpilots.at
							(
								//pilotnumber
								myrandom->randomnormalunsignedintcenteredatzero(topfighterpilots.size())
							).first,
							Position,
							Evolve
						)
					);
					allfighterpilots.back()->setshiptype(0);
					topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				}
				else
				{//otherwise, a new pilot is created form the basic pilot
					allfighterpilots.push_back
					(
						new pilot
						(
							&basefighterpilot,
							Position,
							Evolve
						)
					);
					allfighterpilots.back()->setshiptype(0);
					topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				}
				//setting the pilot up
				allfighterpilots.back()->setgrid(metagrid);
				allfighterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allfighterpilots.back()->setmothership(themothership);
				allfighterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				//putting pilot's ship in the grid
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allfighterpilots.back()->myship));
				else cout<<"void newevolvedpilot2 metagrid==NULL";
			}
		}
	}
	void newevolvedpilot2(const point Position, const bool& Evolve, const bool& PilotIsHarvester, const bool& SpecialEvolve)
	{//creating a new evolved pilot, basing on the group of living pilots, or the basic pilots
		//function for selective evolution
		if((allfighterpilots.size()+allharvesterpilots.size())<pilotcap)
		{//if there arn`t too many pilots
			if(PilotIsHarvester)
			{
				if(topharvesterpilots.size()>0)
				{//if there are any living pilots
					sort(topharvesterpilots.begin(), topharvesterpilots.end(), comparepilotpointerspairf);//they are sorted
					//if(topharvesterpilots.size()>TOPPILOTSMAXSIZE)
					if(topharvesterpilots.size()>2*pilotcap)
					{
						//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topharvesterpilots.size();i++)
						for(unsigned int i=2*pilotcap-1;topharvesterpilots.size()>2*pilotcap;i--)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(topharvesterpilots.at(i).second==false)
							{
								if(PILOTSSPEAK)cout<<"delete(topharvesterpilots.at(i).first);"<<endl<<flush;
								delete(topharvesterpilots.at(i).first);
								topharvesterpilots.erase(topharvesterpilots.begin()+i);
								//i--;
							}
						}
					}
					//unsigned int pilotnumber=myrandom->randomnormalunsignedintcenteredatzero(topharvesterpilots.size());
					//cout<<"Evolving from pilot number "<<pilotnumber<<" out of "<<topharvesterpilots.size()<<endl<<flush;
					allharvesterpilots.push_back
					(//new pilot is created
						new pilot
						(
							topharvesterpilots.at
							(
								//pilotnumber
								myrandom->randomnormalunsignedintcenteredatzero(topharvesterpilots.size())
							).first,
							Position,
							Evolve,
							SpecialEvolve
						)
					);
					allharvesterpilots.back()->setshiptype(1);
					topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				}
				else
				{//otherwise, a new pilot is created form the basic pilot
					allharvesterpilots.push_back
					(
						new pilot
						(
							&baseharvesterpilot,
							Position,
							Evolve,
							SpecialEvolve
						)
					);
					allharvesterpilots.back()->setshiptype(1);
					topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				}
				//setting the pilot up
				allharvesterpilots.back()->setgrid(metagrid);
				allharvesterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allharvesterpilots.back()->setmothership(themothership);
				allharvesterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				//putting pilot's ship in the grid
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allharvesterpilots.back()->myship));
				else cout<<"void newevolvedpilot2 metagrid==NULL";
			}
			else
			{
				if(topfighterpilots.size()>0)
				{//if there are any living pilots
					sort(topfighterpilots.begin(), topfighterpilots.end(), comparepilotpointerspairf);//they are sorted
					//if(topfighterpilots.size()>TOPPILOTSMAXSIZE)
					if(topfighterpilots.size()>2*pilotcap)
					{
						//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topfighterpilots.size();i++)
						for(unsigned int i=2*pilotcap-1;topfighterpilots.size()>2*pilotcap;i--)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(topfighterpilots.at(i).second==false)
							{
								if(PILOTSSPEAK)cout<<"delete(topfighterpilots.at(i).first);"<<endl<<flush;
								delete(topfighterpilots.at(i).first);
								topfighterpilots.erase(topfighterpilots.begin()+i);
								//i--;
							}
						}
					}
					//unsigned int pilotnumber=myrandom->randomnormalunsignedintcenteredatzero(topfighterpilots.size());
					//cout<<"Evolving from pilot number "<<pilotnumber<<" out of "<<topfighterpilots.size()<<endl<<flush;
					allfighterpilots.push_back
					(//new pilot is created
						new pilot
						(
							topfighterpilots.at
							(
								//pilotnumber
								myrandom->randomnormalunsignedintcenteredatzero(topfighterpilots.size())
							).first,
							Position,
							Evolve,
							SpecialEvolve
						)
					);
					allfighterpilots.back()->setshiptype(0);
					topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				}
				else
				{//otherwise, a new pilot is created form the basic pilot
					allfighterpilots.push_back
					(
						new pilot
						(
							&basefighterpilot,
							Position,
							Evolve,
							SpecialEvolve
						)
					);
					allfighterpilots.back()->setshiptype(0);
					topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				}
				//setting the pilot up
				allfighterpilots.back()->setgrid(metagrid);
				allfighterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allfighterpilots.back()->setmothership(themothership);
				allfighterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				//putting pilot's ship in the grid
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allfighterpilots.back()->myship));
				else cout<<"void newevolvedpilot2 metagrid==NULL";
			}
		}
	}
	void newbasicpilot2(const point Position=point(0.0, 0.0, 0.0), const bool& Evolve=false, const bool& PilotIsHarvester=false)
	{//new pilot from the basic pilot
		if((allfighterpilots.size()+allharvesterpilots.size())<pilotcap)
		{
			if(PilotIsHarvester)
			{
				//if(topharvesterpilots.size()>TOPPILOTSMAXSIZE)
				if(topharvesterpilots.size()>2*pilotcap)
				{
					sort(topharvesterpilots.begin(), topharvesterpilots.end(), comparepilotpointerspairf);//they are sorted
					//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topharvesterpilots.size();i++)
					for(unsigned int i=2*pilotcap-1;topharvesterpilots.size()>2*pilotcap;i--)
					{
						if(topharvesterpilots.at(i).second==false)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(PILOTSSPEAK)cout<<"delete(topharvesterpilots.at(i).first);"<<endl<<flush;
							delete(topharvesterpilots.at(i).first);
							topharvesterpilots.erase(topharvesterpilots.begin()+i);
							//i--;
						}
					}
				}
				allharvesterpilots.push_back
				(
					new pilot
					(
						&baseharvesterpilot,
						Position,
						Evolve
					)
				);
				allharvesterpilots.back()->setshiptype(1);
				topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				//pilots.back()->myship.velocity(myrandom->randombubbleposition(1.0));
				allharvesterpilots.back()->setgrid(metagrid);
				allharvesterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allharvesterpilots.back()->setmothership(themothership);
				allharvesterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allharvesterpilots.back()->myship));
				else cout<<"void newbasicpilot2 metagrid==NULL";
			}
			else
			{
				//if(topfighterpilots.size()>TOPPILOTSMAXSIZE)
				if(topfighterpilots.size()>2*pilotcap)
				{
					sort(topfighterpilots.begin(), topfighterpilots.end(), comparepilotpointerspairf);//they are sorted
					//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topfighterpilots.size();i++)
					for(unsigned int i=2*pilotcap-1;topfighterpilots.size()>2*pilotcap;i--)
					{
						if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
						if(topfighterpilots.at(i).second==false)
						{
							if(PILOTSSPEAK)cout<<"delete(topfighterpilots.at(i).first);"<<endl<<flush;
							delete(topfighterpilots.at(i).first);
							topfighterpilots.erase(topfighterpilots.begin()+i);
							//i--;
						}
					}
				}
				allfighterpilots.push_back
				(
					new pilot
					(
						&basefighterpilot,
						Position,
						Evolve
					)
				);
				allfighterpilots.back()->setshiptype(0);
				topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				//pilots.back()->myship.velocity(myrandom->randombubbleposition(1.0));
				allfighterpilots.back()->setgrid(metagrid);
				allfighterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allfighterpilots.back()->setmothership(themothership);
				allfighterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allfighterpilots.back()->myship));
				else cout<<"void newbasicpilot2 metagrid==NULL";
			}
		}
	}
	void newbasicpilot2(const point Position=point(0.0, 0.0, 0.0), const bool& Evolve, const bool& SpecialEvolve, const bool& PilotIsHarvester)
	{//new pilot from the basic pilot
	//a function for selective evolution
		if((allfighterpilots.size()+allharvesterpilots.size())<pilotcap)
		{
			if(PilotIsHarvester)
			{
				//if(topharvesterpilots.size()>TOPPILOTSMAXSIZE)
				if(topharvesterpilots.size()>2*pilotcap)
				{
					sort(topharvesterpilots.begin(), topharvesterpilots.end(), comparepilotpointerspairf);//they are sorted
					//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topharvesterpilots.size();i++)
					for(unsigned int i=2*pilotcap-1;topharvesterpilots.size()>2*pilotcap;i--)
					{
						if(topharvesterpilots.at(i).second==false)
						{
							if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
							if(PILOTSSPEAK)cout<<"delete(topharvesterpilots.at(i).first);"<<endl<<flush;
							delete(topharvesterpilots.at(i).first);
							topharvesterpilots.erase(topharvesterpilots.begin()+i);
							//i--;
						}
					}
				}
				allharvesterpilots.push_back
				(
					new pilot
					(
						&baseharvesterpilot,
						Position,
						Evolve,
						SpecialEvolve
					)
				);
				allharvesterpilots.back()->setshiptype(1);
				topharvesterpilots.push_back(pair<pilot*, bool> (allharvesterpilots.back(), true));
				//pilots.back()->myship.velocity(myrandom->randombubbleposition(1.0));
				allharvesterpilots.back()->setgrid(metagrid);
				allharvesterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allharvesterpilots.back()->setmothership(themothership);
				allharvesterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allharvesterpilots.back()->myship));
				else cout<<"void newbasicpilot2 metagrid==NULL";
			}
			else
			{
				//if(topfighterpilots.size()>TOPPILOTSMAXSIZE)
				if(topfighterpilots.size()>2*pilotcap)
				{
					sort(topfighterpilots.begin(), topfighterpilots.end(), comparepilotpointerspairf);//they are sorted
					//for(unsigned int i=TOPPILOTSMAXSIZE-1;i<topfighterpilots.size();i++)
					for(unsigned int i=2*pilotcap-1;topfighterpilots.size()>2*pilotcap;i--)
					{
						if(PILOTSSPEAK)cout<<"i in the loop: "<<i<<endl<<flush;
						if(topfighterpilots.at(i).second==false)
						{
							if(PILOTSSPEAK)cout<<"delete(topfighterpilots.at(i).first);"<<endl<<flush;
							delete(topfighterpilots.at(i).first);
							topfighterpilots.erase(topfighterpilots.begin()+i);
							//i--;
						}
					}
				}
				allfighterpilots.push_back
				(
					new pilot
					(
						&basefighterpilot,
						Position,
						Evolve,
						SpecialEvolve
					)
				);
				allfighterpilots.back()->setshiptype(0);
				topfighterpilots.push_back(pair<pilot*, bool> (allfighterpilots.back(), true));
				//pilots.back()->myship.velocity(myrandom->randombubbleposition(1.0));
				allfighterpilots.back()->setgrid(metagrid);
				allfighterpilots.back()->setgravitatetarget(newpilotgravitatetarget);
				allfighterpilots.back()->setmothership(themothership);
				allfighterpilots.back()->myship.setmothershipcolour(mothershipcolour);
				if(metagrid!=NULL)metagrid->addship(pair<colour, ship*>(mothershipcolour, &allfighterpilots.back()->myship));
				else cout<<"void newbasicpilot2 metagrid==NULL";
			}
		}
	}

	inline
	void setpilotcap(const unsigned int Cap)
	{//setting pilot cap
		pilotcap=Cap;
	}
	void deleteships(vector <ship*> Ships)
	{//deleting pilots and their ships
		if(PILOTSSPEAK)cout<<"pilots::deleteships"<<endl<<flush;
		for(unsigned int i=0;i<Ships.size();i++)
		{
			//Ships.at(i)->iamdead();
			if((Ships.at(i)!=NULL)&&(Ships.at(i)->shiptype==0))
			{//if ship is fighter
				for(unsigned int j=0;j<allfighterpilots.size();j++)
				{
					if(&allfighterpilots.at(j)->myship==Ships.at(i))
					{
						//allpilots.at(j)->myship.iamdead();
						unsigned int k=0;
						for (k=0;k<topfighterpilots.size();k++)
						{
							if (topfighterpilots.at(k).first==allfighterpilots.at(j))
							{
								Ships.at(i)=NULL;
								killtopfighterpilot(k, j);
								//toppilots.at(k).second=false;
								//fp.savepilot(toppilots.at(k).first);
								break;
							}
						}
						if(k==topfighterpilots.size())cout<<"k==topfighterpilots.size()"<<endl<<flush;
						//if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allpilots.at(j)->myship));
						//allpilots.erase(allpilots.begin()+j);
						break;
					}
				}
			}
			if((Ships.at(i)!=NULL)&&(Ships.at(i)->shiptype==1))
			{//if ship is harvester
				for(unsigned int j=0;j<allharvesterpilots.size();j++)
				{
					if(&allharvesterpilots.at(j)->myship==Ships.at(i))
					{
						//allpilots.at(j)->myship.iamdead();
						unsigned int k=0;
						for (k=0;k<topharvesterpilots.size();k++)
						{
							if (topharvesterpilots.at(k).first==allharvesterpilots.at(j))
							{
								Ships.at(i)=NULL;
								killtopharvesterpilot(k, j);
								//toppilots.at(k).second=false;
								//fp.savepilot(toppilots.at(k).first);
								break;
							}
						}
						if(k==topharvesterpilots.size())cout<<"k==topharvesterpilots.size()"<<endl<<flush;
						//if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allpilots.at(j)->myship));
						//allpilots.erase(allpilots.begin()+j);
						break;
					}
				}
			}
		}
		if(PILOTSSPEAK)cout<<"~pilots::deleteships"<<endl<<flush;
	}
	inline
	void killtopharvesterpilot(const unsigned int& TopPilotIndex, const unsigned int& AllPilotsIndex)
	{
		if(PILOTSSPEAK)cout<<"pilots::killtopharvesterpilot"<<endl<<flush;
		topharvesterpilots.at(TopPilotIndex).second=false;
		if(PILOTSSPEAK)cout<<"~topharvesterpilots.at(TopPilotIndex).second=false;"<<endl<<flush;
		topharvesterpilots.at(TopPilotIndex).first->youaredead();
		if(PILOTSSPEAK)cout<<"~topharvesterpilots.at(TopPilotIndex).first->youaredead();"<<endl<<flush;
		if(usefilepilot)
		{
			if(PILOTSSPEAK)cout<<"if(usefilepilot)"<<endl<<flush;
			fp.savepilot(topharvesterpilots.at(TopPilotIndex).first, true);
			if(PILOTSSPEAK)cout<<"~fp.savepilot(topharvesterpilots.at(TopPilotIndex).first, true);"<<endl<<flush;
		}
		if(PILOTSSPEAK)cout<<"~if(usefilepilot)fp.savepilot(topharvesterpilots.at(TopPilotIndex).first, true);"<<endl<<flush;
		if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allharvesterpilots.at(AllPilotsIndex)->myship));
		if(PILOTSSPEAK)cout<<"~if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allharvesterpilots.at(AllPilotsIndex)->myship));"<<endl<<flush;
		allharvesterpilots.erase(allharvesterpilots.begin()+AllPilotsIndex);
		if(PILOTSSPEAK)cout<<"~allharvesterpilots.erase(allharvesterpilots.begin()+AllPilotsIndex);"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"~pilots::killtopharvesterpilot"<<endl<<flush;
	}
	inline
	void killtopfighterpilot(const unsigned int& TopPilotIndex, const unsigned int& AllPilotsIndex)
	{
		if(PILOTSSPEAK)cout<<"pilots::killtopfighterpilot"<<endl<<flush;
		topfighterpilots.at(TopPilotIndex).second=false;
		if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allfighterpilots.at(AllPilotsIndex)->myship));
		if(PILOTSSPEAK)cout<<"~if(metagrid!=NULL)metagrid->removeship(pair<colour, ship*> (mothershipcolour, &allfighterpilots.at(AllPilotsIndex)->myship));"<<endl<<flush;
		topfighterpilots.at(TopPilotIndex).first->youaredead();
		if(PILOTSSPEAK)cout<<"~topfighterpilots.at(TopPilotIndex).first->youaredead();"<<endl<<flush;
		if(usefilepilot)
		{
			if(PILOTSSPEAK)cout<<"if(usefilepilot)"<<endl<<flush;
			fp.savepilot(topfighterpilots.at(TopPilotIndex).first, false);
			if(PILOTSSPEAK)cout<<"~fp.savepilot(topfighterpilots.at(TopPilotIndex).first, false);"<<endl<<flush;
		}
		if(PILOTSSPEAK)cout<<"~if(usefilepilot)fp.savepilot(topfighterpilots.at(TopPilotIndex).first, false);"<<endl<<flush;
		allfighterpilots.erase(allfighterpilots.begin()+AllPilotsIndex);
		if(PILOTSSPEAK)cout<<"~pilots::killtopfighterpilot"<<endl<<flush;
	}
	inline
	void setdefaultgravitatetarget(const point& NewGravitateTarget)
	{
		newpilotgravitatetarget(NewGravitateTarget);
	}
	inline
	void clear()
	{//clearing all data
		//clearing vectors of only living pilots
		allfighterpilots.clear();
		allharvesterpilots.clear();

		for(unsigned int i=0;i<topharvesterpilots.size();i++)
		{//deleted dead pilots
			if(usefilepilot)if(topharvesterpilots.at(i).second)
			{
				topharvesterpilots.at(i).first->youaredead();
				fp.savepilot(topharvesterpilots.at(i).first, true);
			}
			if(PILOTSSPEAK)cout<<"delete(topharvesterpilots.at(i).first);"<<endl<<flush;
			delete(topharvesterpilots.at(i).first);
		}
		topharvesterpilots.clear();
		for(unsigned int i=0;i<topfighterpilots.size();i++)
		{//deleted dead pilots
			if(usefilepilot)if(topfighterpilots.at(i).second)
			{
				topfighterpilots.at(i).first->youaredead();
				fp.savepilot(topfighterpilots.at(i).first, false);
			}
			if(PILOTSSPEAK)cout<<"delete(topfighterpilots.at(i).first);"<<endl<<flush;
			delete(topfighterpilots.at(i).first);
		}
		topfighterpilots.clear();
		//cout<<"Allpilots cleared to size: "<<allpilots.size()<<endl<<flush;
	}
	inline
	void drawme(const unsigned int& ShipDrawingMode=1, const unsigned int& PilotDrawingMode=1)const
	{//drawing all pilots
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			allharvesterpilots.at(i)->drawme(ShipDrawingMode, PilotDrawingMode);
		}
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{
			allfighterpilots.at(i)->drawme(ShipDrawingMode, PilotDrawingMode);
		}
	}
	void setdefaultpilot(const pilot& Pilot, const bool& PilotIsHarvester=false)
	{//setting default pilot
		if(PilotIsHarvester)baseharvesterpilot(Pilot);
		else basefighterpilot(Pilot);
	}
	unsigned int size()const
	{//returns how many pilots are there
		return (allharvesterpilots.size()+allfighterpilots.size());
	}
	steeringpreferences giveaveragesteeringpreferences(const bool& PilotIsHarvester=false)const
	{//returns average steering preferences of the pilots
		if(PilotIsHarvester)
		{
			if(allharvesterpilots.size()==0) return steeringpreferences();
			steeringpreferences anwser(allharvesterpilots.front()->myfsm.getpreferences());
			for(unsigned int i=1;i<allharvesterpilots.size();i++)
			{
				anwser+=allharvesterpilots.at(i)->myfsm.getpreferences();
			}
			anwser/=allharvesterpilots.size();
			return anwser;
		}
		else
		{
			if(allfighterpilots.size()==0) return steeringpreferences();
			steeringpreferences anwser(allfighterpilots.front()->myfsm.getpreferences());
			for(unsigned int i=1;i<allfighterpilots.size();i++)
			{
				anwser+=allfighterpilots.at(i)->myfsm.getpreferences();
			}
			anwser/=allfighterpilots.size();
			return anwser;
		}
	}
	void nexttime()
	{//allowing the piltos to make decisions and move
		if(PILOTSSPEAK)cout<<"pilots::nexttime"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"checkfordeadpilots();"<<endl<<flush;
		checkfordeadpilots();
		if(PILOTSSPEAK)cout<<"~checkfordeadpilots();"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"calculateacceleration();"<<endl<<flush;
		calculateacceleration();
		if(PILOTSSPEAK)cout<<"~calculateacceleration();"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"allfighterpilots moveme, arrived"<<endl<<flush;
		for (unsigned int i=0;i<allfighterpilots.size();i++)
		{
			allfighterpilots.at(i)->moveme();
			allfighterpilots.at(i)->arrived();
		}
		if(PILOTSSPEAK)cout<<"allfighterpilots ~moveme, ~arrived"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"allharvesterpilots moveme, arrived"<<endl<<flush;
		for (unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			allharvesterpilots.at(i)->moveme();
			allharvesterpilots.at(i)->arrived();
		}
		if(PILOTSSPEAK)cout<<"allharvesterpilots ~moveme, ~arrived"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"alignemotions1"<<endl<<flush;
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{//emotional alignment
			for(unsigned int j=i;j<allfighterpilots.size();j++)
			{
				if(allfighterpilots.at(i)->myship.position.distanceto(allfighterpilots.at(j)->myship.position)<RANGEOFSIGHT)
				{
					allfighterpilots.at(i)->myfsm.getemotionalstate()->alignemotions(allfighterpilots.at(j)->myfsm.getemotionalstate());
					allfighterpilots.at(j)->myfsm.getemotionalstate()->alignemotions(allfighterpilots.at(i)->myfsm.getemotionalstate());
				}
			}
			for(unsigned int j=0;j<allharvesterpilots.size();j++)
			{
				if(allfighterpilots.at(i)->myship.position.distanceto(allharvesterpilots.at(j)->myship.position)<RANGEOFSIGHT)
				{
					allfighterpilots.at(i)->myfsm.getemotionalstate()->alignemotions(allharvesterpilots.at(j)->myfsm.getemotionalstate());
					allharvesterpilots.at(j)->myfsm.getemotionalstate()->alignemotions(allfighterpilots.at(i)->myfsm.getemotionalstate());
				}
			}
		}
		if(PILOTSSPEAK)cout<<"~alignemotions1"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"alignemotions2"<<endl<<flush;
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			for(unsigned int j=i;j<allharvesterpilots.size();j++)
			{
				if(allharvesterpilots.at(i)->myship.position.distanceto(allharvesterpilots.at(j)->myship.position)<RANGEOFSIGHT)
				{
					allharvesterpilots.at(i)->myfsm.getemotionalstate()->alignemotions(allharvesterpilots.at(j)->myfsm.getemotionalstate());
					allharvesterpilots.at(j)->myfsm.getemotionalstate()->alignemotions(allharvesterpilots.at(i)->myfsm.getemotionalstate());
				}
			}
		}
		if(PILOTSSPEAK)cout<<"~alignemotions2"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"~pilots::nexttime"<<endl<<flush;
	}
	void calculateacceleration(const unsigned int& Offset=0, const unsigned int& Modulo=1)
	{//allowing the pilots to calculate acceleration
		for (unsigned int i=Offset;i<allfighterpilots.size();i+=Modulo)
		{
			allfighterpilots.at(i)->calculateacceleration();
		}
		for (unsigned int i=Offset;i<allharvesterpilots.size();i+=Modulo)
		{
			allharvesterpilots.at(i)->calculateacceleration();
		}
	}
	inline
	void setgrid(grid* MetaGrid)
	{//sets the meta grid
		metagrid=MetaGrid;
	}
	inline
	void setmothership(mothership* Mothership)
	{//sets the mothership of the pilots
		themothership=Mothership;
	}
	inline
	void setdefaultloopedpath(const path& LoopedPath)
	{//sets the default looped path
		defaultloopedpath(LoopedPath);
	}
	inline
	void setdefaultsinglepath(const path& SinglePath)
	{//sets the default looped path
		defaultsinglepath(SinglePath);
	}
	void assignloopedpath(const bool& PilotIsHarvester=false)
	{//assigning the looped path
		if(PilotIsHarvester)
		{
			for (unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				allharvesterpilots.at(i)->setloopedpath(defaultloopedpath);
			}
		}
		else
		{
			for (unsigned int i=0;i<allfighterpilots.size();i++)
			{
				allfighterpilots.at(i)->setloopedpath(defaultloopedpath);
			}
		}
	}
	void assignsinglepath(const bool& PilotIsHarvester=false)
	{//assigning the looped path
		if(PilotIsHarvester)
		{
			for (unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				allharvesterpilots.at(i)->setsinglepath(defaultsinglepath);
			}
		}
		else
		{
			for (unsigned int i=0;i<allfighterpilots.size();i++)
			{
				allfighterpilots.at(i)->setsinglepath(defaultsinglepath);
			}
		}
	}
	void setallpilotfsm(fsm NewFSM, const bool& PilotIsHarvester=false)
	{//setting all pilots' finite state machine
		if(PilotIsHarvester)
		{
			baseharvesterpilot.setmyfsm(NewFSM);
			for (unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				allharvesterpilots.at(i)->setmyfsm(NewFSM);
			}
		}
		else
		{
			basefighterpilot.setmyfsm(NewFSM);
			for (unsigned int i=0;i<allfighterpilots.size();i++)
			{
				allfighterpilots.at(i)->setmyfsm(NewFSM);
			}
		}
	}
	void printallstates()
	{//prints which states the pilots are in
		for (unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			if(PILOTSSPEAK)cout<<"allharvesterpilots"<<endl<<flush;
			allharvesterpilots.at(i)->myfsm.printme();
		}
		for (unsigned int i=0;i<allfighterpilots.size();i++)
		{
			if(PILOTSSPEAK)cout<<"allfighterpilots"<<endl<<flush;
			allfighterpilots.at(i)->myfsm.printme();
		}
	}
	float averagescore(const bool& PilotIsHarvester=false)
	{//returns pilot's average score
		if(PilotIsHarvester)
		{
			if(allharvesterpilots.empty())return 0.0;
			float result=0.0;
			for (unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				result+=allharvesterpilots.at(i)->score;
			}
			return result/=allharvesterpilots.size();
		}
		else
		{
			if(allfighterpilots.empty())return 0.0;
			float result=0.0;
			for (unsigned int i=0;i<allfighterpilots.size();i++)
			{
				result+=allfighterpilots.at(i)->score;
			}
			return result/=allfighterpilots.size();
		}
	}
	void killoldestpilot(const bool& PilotIsHarvester)
	{//kills oldest boid
		if(PILOTSSPEAK)cout<<"pilots::killoldestpilot(const bool& PilotIsHarvester)"<<endl<<flush;
		if(PilotIsHarvester)if(allharvesterpilots.empty()==false)
		{
			unsigned int oldest=0;
			unsigned int topage=allharvesterpilots.at(0)->age;
			for(unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				//cout<<"killoldestpilot: for(unsigned int i=0;i<allharvesterpilots.size();i++)"<<endl<<flush;
				if(allharvesterpilots.at(i)->age>topage)
				{
					topage=allharvesterpilots.at(i)->age;
					oldest=i;
				}
			}
			for(unsigned int i=0;i<topharvesterpilots.size();i++)
			{
				if(topharvesterpilots.at(i).first==allharvesterpilots.at(oldest))
				{
					if(PILOTSSPEAK)cout<<"if(topharvesterpilots.at(i).first==allharvesterpilots.at(oldest))"<<endl<<flush;
					killtopharvesterpilot(i, oldest);
					i--;
					break;
					//toppilots.at(i).second=false;
				}
			}
			//allpilots.erase(allpilots.begin()+oldest);
		}
		else if(!allfighterpilots.empty())
		{
			unsigned int oldest=0;
			unsigned int topage=allfighterpilots.at(0)->age;
			for(unsigned int i=0;i<allfighterpilots.size();i++)
			{
				//cout<<"killoldestpilot: for(unsigned int i=0;i<allfighterpilots.size();i++)"<<endl<<flush;
				if(allfighterpilots.at(i)->age>topage)
				{
					topage=allfighterpilots.at(i)->age;
					oldest=i;
				}
			}
			for(unsigned int i=0;i<topfighterpilots.size();i++)
			{
				if(topfighterpilots.at(i).first==allfighterpilots.at(oldest))
				{
					if(PILOTSSPEAK)cout<<"if(topfighterpilots.at(i).first==allfighterpilots.at(oldest))"<<endl<<flush;
					killtopfighterpilot(i, oldest);
					i--;
					break;
					//toppilots.at(i).second=false;
				}
			}
			//allpilots.erase(allpilots.begin()+oldest);
		}
		if(PILOTSSPEAK)cout<<"pilots::~killoldestpilot"<<endl<<flush;

	}
	void killoldestpilot()
	{//kills oldest boid
		if(PILOTSSPEAK)cout<<"pilots::killoldestpilot()"<<endl<<flush;
		unsigned int oldesth=0;
		unsigned int tophage=0;
		unsigned int oldestp=0;
		unsigned int toppage=0;
		int ip=-1;
		int ih=-1;
		if(allharvesterpilots.empty()==false)
		{
			unsigned int oldest=0;
			unsigned int topage=allharvesterpilots.at(0)->age;
			for(unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				//cout<<"killoldestpilot: for(unsigned int i=0;i<allharvesterpilots.size();i++)"<<endl<<flush;
				if(allharvesterpilots.at(i)->age>topage)
				{
					tophage=topage=allharvesterpilots.at(i)->age;
					oldesth=oldest=i;
				}
			}
			for(unsigned int i=0;i<topharvesterpilots.size();i++)
			{
				if(topharvesterpilots.at(i).first==allharvesterpilots.at(oldest))
				{
					if(PILOTSSPEAK)cout<<"if(topharvesterpilots.at(i).first==allharvesterpilots.at(oldest))"<<endl<<flush;
					//killtopharvesterpilot(i, oldest);
					//i--;
					ih=(int)i;
					//oldesth=oldest;
					//tophage=topage;
					break;
					//toppilots.at(i).second=false;
				}
			}
			//allpilots.erase(allpilots.begin()+oldest);
		}
		if(!allfighterpilots.empty())
		{
			unsigned int oldest=0;
			unsigned int topage=allfighterpilots.at(0)->age;
			for(unsigned int i=0;i<allfighterpilots.size();i++)
			{
				//cout<<"killoldestpilot: for(unsigned int i=0;i<allfighterpilots.size();i++)"<<endl<<flush;
				if(allfighterpilots.at(i)->age>topage)
				{
					toppage=topage=allfighterpilots.at(i)->age;
					oldestp=oldest=i;
				}
			}
			for(unsigned int i=0;i<topfighterpilots.size();i++)
			{
				if(topfighterpilots.at(i).first==allfighterpilots.at(oldest))
				{
					if(PILOTSSPEAK)cout<<"if(topfighterpilots.at(i).first==allfighterpilots.at(oldest))"<<endl<<flush;
					//killtopfighterpilot(i, oldest);
					//i--;
					ip=(int)i;
					//oldestp=oldest;
					//toppage=oldest;
					break;
					//toppilots.at(i).second=false;
				}
			}
			//allpilots.erase(allpilots.begin()+oldest);
		}
		if(tophage>toppage)
		{
			if(ih>-1)
			{
				if(PILOTSSPEAK)cout<<"if(ih>-1)"<<endl<<flush;
				killtopharvesterpilot((unsigned int)ih, oldesth);
				if(PILOTSSPEAK)cout<<"killtopharvesterpilot((unsigned int)ih, oldesth);"<<endl<<flush;
			}
		}
		else
		{
			if(ip>-1)
			{
				if(PILOTSSPEAK)cout<<"if(ip>-1)"<<endl<<flush;
				killtopfighterpilot((unsigned int)ip, oldestp);
				if(PILOTSSPEAK)cout<<"killtopfighterpilot((unsigned int)ip, oldestp);"<<endl<<flush;
			}
		}
		if(PILOTSSPEAK)cout<<"pilots::~killoldestpilot"<<endl<<flush;

	}
	inline
	float givetopscore(const bool& PilotIsHarvester=false)
	{//returns the best boid score
		if(PilotIsHarvester)
		{
			float score=0.0;
			if(allharvesterpilots.empty()) return score;
			//assume they are sorted
			for(unsigned int i=0;i<allharvesterpilots.size();i++)
				if(allharvesterpilots.at(i)->score>score)
					score=allharvesterpilots.at(i)->score;
			return score;
		}
		else
		{
			float score=0.0;
			if(allfighterpilots.empty()) return score;
			//assume they are sorted
			for(unsigned int i=0;i<allfighterpilots.size();i++)
				if(allfighterpilots.at(i)->score>score)
					score=allfighterpilots.at(i)->score;
			return score;
		}
	}
	void setallpilotastar(const astar& Astar, const bool& PilotIsHarvester=false)
	{
		if(PilotIsHarvester)
		{
			baseharvesterpilot.setastar(Astar);
			for (unsigned int i=0;i<allharvesterpilots.size();i++)
			{
				allharvesterpilots.at(i)->setastar(Astar);
			}
		}
		else
		{
			basefighterpilot.setastar(Astar);
			for (unsigned int i=0;i<allfighterpilots.size();i++)
			{
				allfighterpilots.at(i)->setastar(Astar);
			}
		}
	}

	void preloadtextpilots(const unsigned int& Amount, const bool& PilotIsHarvester=false)
	{
		if(usefilepilot)
		{
			if(PilotIsHarvester)
			{
				vector<pilot> tmppilots=fp.getxtoppilots(Amount, PilotIsHarvester);
				for(unsigned int i=0;i<tmppilots.size();i++)
				{
					//cout<<tmppilots.at(i).myfsm.ces->name<<endl<<flush;
					topharvesterpilots.push_back(pair<pilot*, bool>(new pilot(&tmppilots.at(i), point(0.0, 0.0, 0.0), false), false));
				}
			}
			else
			{
				vector<pilot> tmppilots=fp.getxtoppilots(Amount, PilotIsHarvester);
				for(unsigned int i=0;i<tmppilots.size();i++)
				{
					//cout<<tmppilots.at(i).myfsm.ces->name<<endl<<flush;
					topfighterpilots.push_back(pair<pilot*, bool>(new pilot(&tmppilots.at(i), point(0.0, 0.0, 0.0), false), false));
				}
			}
		}
	}
	void setsubfolderandcolour(const unsigned int& ScenarioNumber, const unsigned int& R, const unsigned int& G, const unsigned int& B)
	{//a function that takes mothership's colour and uses it as a subfolder for storing private boids
		mothershipcolour=colour(R, G, B, 1);
		usefilepilot=true;
		fp.setsubfolder(ScenarioNumber, R, G, B);
	}
	inline
	void setusefilepilot(const bool& UseFilePilot=false)
	{
		usefilepilot=UseFilePilot;
	}
	void checkfordeadpilots()
	{
		if(PILOTSSPEAK)cout<<"pilots::checkfordeadpilots"<<endl<<flush;
		vector<ship*> shipstodelete;
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			if(allharvesterpilots.at(i)->myship.health<=0.0)
			{
				shipstodelete.push_back(&allharvesterpilots.at(i)->myship);
			}
		}
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{
			if(allfighterpilots.at(i)->myship.health<=0.0)
			{
				shipstodelete.push_back(&allfighterpilots.at(i)->myship);
			}
		}
		deleteships(shipstodelete);
		if(PILOTSSPEAK)cout<<"~deleteships(shipstodelete);"<<endl<<flush;
		if(PILOTSSPEAK)cout<<"~pilots::checkfordeadpilots"<<endl<<flush;
	}
	void setdefaultpilotfsm(const fsm& DefaultFSM, const bool& PilotIsHarvester=false)
	{
		if(PilotIsHarvester)baseharvesterpilot.setmyfsm(DefaultFSM);
		else basefighterpilot.setmyfsm(DefaultFSM);
	}
	void increaseanger(const float& HowMuch)
	{
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{
			allfighterpilots.at(i)->myfsm.getemotionalstate()->forcechangeanger(HowMuch);
		}
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			allharvesterpilots.at(i)->myfsm.getemotionalstate()->forcechangeanger(HowMuch);
		}
	}
	void increasefear(const float& HowMuch)
	{
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{
			allfighterpilots.at(i)->myfsm.getemotionalstate()->forcechangefear(HowMuch);
		}
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			allharvesterpilots.at(i)->myfsm.getemotionalstate()->forcechangefear(HowMuch);
		}
	}
	void resetemotions()
	{
		for(unsigned int i=0;i<allfighterpilots.size();i++)
		{
			allfighterpilots.at(i)->myfsm.getemotionalstate()->resetemotions();
		}
		for(unsigned int i=0;i<allharvesterpilots.size();i++)
		{
			allharvesterpilots.at(i)->myfsm.getemotionalstate()->resetemotions();
		}
	}
	inline
	bool arepilotsbelowcap()
	{
		return (allfighterpilots.size()+allharvesterpilots.size())<pilotcap;
	}

};

#endif /* PILOTS_H_ */
