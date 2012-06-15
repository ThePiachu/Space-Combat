#ifndef FSME_H_
#define FSME_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "state.h"
#include "transitions.h"
#include "emotionaltransitions.h"
#include "../steeringpreferences.h"
#include "../../stringhandling.h"

class fsme
{//finite state machine of one emotion
	void clearstates()
	{
		map<string, state*>::iterator it;
		for(it=states.begin();it!=states.end();it++)
		{
			delete(it->second);
			it->second=NULL;
		}
		states.clear();
		cs=NULL;
		defaultstate=NULL;
	}
	inline
	void cleartransitions()
	{
		emotionalstatesandtransisions.clear();
	}
public:
	string name;//name of the emotion
	map <string, state*> states;//vector of all states in current emotion
	state* cs;//current state
	state* defaultstate;//a state that is set by default when transitioning into the emotional state
	ship* boidship;
	steeringpreferences preferences;//steering preferences of the boid
	decisionpreferences decpreferences;//decision preferences of the boid
	emotions* emotionalstate;
	vector<pair<string, bool(*)(const ship*, const emotions*)> > emotionalstatesandtransisions;
	//TODO: implement
	vector<void (ship::*)(void)> etransitionouttasks, etransitionintasks;//functions to be called when the state is entered and exited
	fsme(const string& Name=string("")):
		name(Name),
		states(),
		cs(NULL),
		defaultstate(cs),
		boidship(NULL),
		preferences(),
		decpreferences(),
		emotionalstate(),
		emotionalstatesandtransisions(),
		etransitionouttasks(),
		etransitionintasks()
		//emotionalstate(NULL)
	{
	}
	fsme(const fsme& Parent, ship* BoidShip=NULL, emotions* EmotionalState=NULL, const bool& Evolve=false):
		name(Parent.name),
		states(),
		cs(NULL),
		defaultstate(cs),
		boidship(BoidShip),
		preferences(Parent.preferences, Evolve),
		decpreferences(Parent.decpreferences, Evolve),
		emotionalstate(EmotionalState),
		emotionalstatesandtransisions(Parent.emotionalstatesandtransisions),
		etransitionouttasks(Parent.etransitionouttasks),
		etransitionintasks(Parent.etransitionintasks)
	{
		map <string, state*>::const_iterator it;
		for(it=Parent.states.begin();it!=Parent.states.end();it++)
		{
			states.insert(pair<string, state*>(it->first, new state(it->second, emotionalstate, &preferences, &decpreferences, boidship, Evolve)));
		}
		if(Parent.defaultstate==NULL)
		{
			defaultstate=NULL;
		}
		else
		{
			defaultstate=states.find(Parent.defaultstate->name)->second;
			if(defaultstate==NULL) cout<<"defaultstate not created from: "<<Parent.defaultstate->name<<endl<<flush;
		}
		cs=defaultstate;
	}
	fsme(const fsme* Parent, ship* BoidShip=NULL, emotions* EmotionalState=NULL, const bool& Evolve=false):
		name(Parent->name),
		states(),
		cs(NULL),
		defaultstate(cs),
		boidship(BoidShip),
		preferences(Parent->preferences, Evolve),
		decpreferences(Parent->decpreferences, Evolve),
		emotionalstate(EmotionalState),
		emotionalstatesandtransisions(Parent->emotionalstatesandtransisions),
		etransitionouttasks(Parent->etransitionouttasks),
		etransitionintasks(Parent->etransitionintasks)
	{
		map <string, state*>::const_iterator it;
		for(it=Parent->states.begin();it!=Parent->states.end();it++)
		{
			states.insert(pair<string, state*>(it->first, new state(it->second, emotionalstate, &preferences, &decpreferences, boidship, Evolve)));
		}
		if(Parent->defaultstate==NULL)
		{
			defaultstate=NULL;
		}
		else
		{
			defaultstate=states.find(Parent->defaultstate->name)->second;
			if(defaultstate==NULL) cout<<"defaultstate not created from: "<<Parent->defaultstate->name<<endl<<flush;
		}
		cs=defaultstate;
	}
	fsme(const fsme* Parent, ship* BoidShip, emotions* EmotionalState, const bool& Evolve, const bool& SpecialEvolve):
		//function for selective evolution
		name(Parent->name),
		states(),
		cs(NULL),
		defaultstate(cs),
		boidship(BoidShip),
		preferences(Parent->preferences, Evolve, SpecialEvolve),
		decpreferences(Parent->decpreferences, Evolve, SpecialEvolve),
		emotionalstate(EmotionalState),
		emotionalstatesandtransisions(Parent->emotionalstatesandtransisions),
		etransitionouttasks(Parent->etransitionouttasks),
		etransitionintasks(Parent->etransitionintasks)
	{
		map <string, state*>::const_iterator it;
		for(it=Parent->states.begin();it!=Parent->states.end();it++)
		{
			states.insert(pair<string, state*>(it->first, new state(it->second, emotionalstate, &preferences, &decpreferences, boidship, Evolve, SpecialEvolve)));
		}
		if(Parent->defaultstate==NULL)
		{
			defaultstate=NULL;
		}
		else
		{
			defaultstate=states.find(Parent->defaultstate->name)->second;
			if(defaultstate==NULL) cout<<"defaultstate not created from: "<<Parent->defaultstate->name<<endl<<flush;
		}
		cs=defaultstate;
	}
	fsme(const vector<string>& FileFSME):
		name(),
		states(),
		cs(NULL),
		defaultstate(cs),
		boidship(NULL),
		emotionalstate(NULL),
		emotionalstatesandtransisions(),
		etransitionouttasks(),
		etransitionintasks()
	{
		state* tmpstate;

		vector<pair<void (ship::*)(void), string> > taskv;
		taskv=givetransitiontasks();
		vector<pair<bool(*)(const ship*, const emotions*), string> > statetransv;
		statetransv=giveemotionaltransitionsvector();
		map <string, state*>::iterator it;
		/*cout<<"fsme(const vector<string>& FileFSME):"<<endl<<flush;
		for(unsigned int i=0;i<FileFSME.size();i++)
		{
			cout<<i<<"of"<<FileFSME.size()<<"**"<<FileFSME.at(i)<<"**"<<endl<<flush;
		}*/
		for(unsigned int i=0;i<FileFSME.size();i++)
		{
			//cout<<"i "<<i<<" out of "<<FileFSME.size()<<"**"<<FileFSME.at(i)<<"**"<<endl<<flush;
			if(FileFSME.at(i).find("name")==0)
			{
				name=FileFSME.at(i).substr(FileFSME.at(i).find("\t")+1);
			}
			if(FileFSME.at(i).find("steeringpreferences")==0)
				//if(FileState.at(i).find("~steeringpreferences")==string::npos)
			{
				for(unsigned int j=i;j<FileFSME.size();j++)
					if(FileFSME.at(j).find("~steeringpreferences")==0)
					{
						preferences
							=steeringpreferences(
								vector<string>(FileFSME.begin()+i, FileFSME.begin()+j));
				}
			}
			if(FileFSME.at(i).find("decisionpreferences")==0)
				//if(FileState.at(i).find("~decisionpreferences")==string::npos)
			{
			for(unsigned int j=i;j<FileFSME.size();j++)
				if(FileFSME.at(j).find("~decisionpreferences")==0)
				{
					decpreferences
						=decisionpreferences(
							vector<string>(FileFSME.begin()+i, FileFSME.begin()+j));
				}
			}

			if(FileFSME.at(i).find("states")==0)
				//if(FileFSME.at(i).find("~states")==string::npos)
					if(FileFSME.at(i).find("statesandtransisions")==string::npos)
			{//setting up all the states
				for(unsigned int j=i;j<FileFSME.size();j++)
				{
					if(FileFSME.at(j).find("~states")==0)
						if(FileFSME.at(j).find("~statesandtransisions")==string::npos)//statesandtransitions
					{
						i=j;
						break;
					}
					if(FileFSME.at(j).find("state")==0)
						if(FileFSME.at(j).find("~state")==string::npos)
							if(FileFSME.at(j).find("states")==string::npos)
					{//setting up a single state
						for(unsigned int k=j;k<FileFSME.size();k++)
							if(FileFSME.at(k).find("~state")==0)
								if(FileFSME.at(k).find("~states")==string::npos)
							{//new state initialized with a script
								tmpstate=new state(vector<string>(FileFSME.begin()+j+1, FileFSME.begin()+k));
								//cout<<"Pushed **"<<tmpstate->name<<"**"<<endl<<flush;
								states.insert(pair<string, state*> (tmpstate->name, tmpstate));
								j=k;
								break;
							}
					}
				}
			}
			if(FileFSME.at(i).find("defaultstate")==0)
			{
				//cout<<"1defaultsate"<<endl<<flush;
				//cout<<"Looking for **"<<FileFSME.at(i).substr(FileFSME.at(i).find("\t")+1)<<"**"<<endl<<flush;
				defaultstate=states.find(FileFSME.at(i).substr(FileFSME.at(i).find("\t")+1))->second;
				cs=defaultstate;
				//cout<<"2defaultsate"<<endl<<flush;
			}
			if(FileFSME.at(i).find("emotionalstatesandtransisions")==0)
				if(FileFSME.at(i).find("~emotionalstatesandtransisions")==string::npos)
			{
					//cout<<"emotionalstatesandtransisions"<<endl<<flush;
				for(unsigned int j=i;j<FileFSME.size();j++)
				{
					if(FileFSME.at(j).find("etransitionouttasks")==0)
					//if(FileState.at(i).find("~transitionouttasks")==string::npos)
					{
						//cout<<"looking for etransitionouttasks..."<<endl<<flush;
						for(unsigned int k=j;k<FileFSME.size();k++)
						{
							if(FileFSME.at(k).find("~etransitionouttasks")==0)
							{
								j=k;
								break;
							}
							else
							{
								string task=FileFSME.at(k);//transition name
								//cout<<"FSME Task out name: **"<<task<<"**"<<endl<<flush;
								for(unsigned int l=0;l<taskv.size();l++)
								{
									if(taskv.at(l).second==task)
									{
										etransitionouttasks.push_back(taskv.at(l).first);
										break;
									}
								}
							}
						}
					}
					if(FileFSME.at(j).find("etransitionintasks")==0)
					//if(FileState.at(i).find("~transitionintasks")==string::npos)
					{
						//cout<<"looking for transitionintasks..."<<endl<<flush;
						for(unsigned int k=j;k<FileFSME.size();k++)
						{
							if(FileFSME.at(k).find("~etransitionintasks")==0)
							{
								j=k;
								break;
							}
							else
							{
								string task=FileFSME.at(k);//transition name
								//cout<<"FAME Task in name: **"<<task<<"**"<<endl<<flush;
								for(unsigned int l=0;l<taskv.size();l++)
								{
									if(taskv.at(l).second==task)
									{
										etransitionintasks.push_back(taskv.at(l).first);
										break;
									}
								}
							}
						}
					}
					//cout<<"emotionalstatesandtransisions loop"<<endl<<flush;
					if(FileFSME.at(j).find("~emotionalstatesandtransisions")==0)
					{
						i=j;
						break;
					}
					else if(FileFSME.at(j).find("transition to")==0)
					{
						//cout<<"emotionalstatesandtransisions transition"<<endl<<flush;
						string to=FileFSME.at(j).substr(14);//destinatin name
						string by=FileFSME.at(j+1).substr(3);//transition function name
						for(unsigned int k=0;k<statetransv.size();k++)
						{
							if(statetransv.at(k).second==by)
							{
								emotionalstatesandtransisions.push_back(
										pair<string, bool(*)(const ship*, const emotions*)>
										(to, statetransv.at(k).first));
								break;
							}
						}
					}
				}

			}

			//cout<<"i "<<i<<" out of "<<FileFSME.size()<<endl<<flush;
		}
		//cout<<"out of the loop"<<endl<<flush;
	}
	~fsme()
	{
		clearstates();
		cleartransitions();
	}
	fsme& operator()(const fsme& Other, ship* BoidShip=NULL, const bool& Evolve=false)
	{
		clearstates();
		cleartransitions();

		name=Other.name;
		states.clear();
		boidship=BoidShip;
		map <string, state*>::const_iterator it;
		for(it=Other.states.begin();it!=Other.states.end();it++)
		{
			states.insert(pair<string, state*>(it->first, new state(it->second, emotionalstate, &preferences, &decpreferences, boidship, Evolve)));
		}

		if(Other.defaultstate==NULL)
		{
			defaultstate=NULL;
			cout<<"defaultstate=NULL! from operator(bla bla)"<<endl<<flush;
		}
		else cs=states.find(Other.defaultstate->name)->second;
		defaultstate=cs;
		emotionalstate=NULL;
		emotionalstatesandtransisions=Other.emotionalstatesandtransisions;
		etransitionintasks=Other.etransitionintasks;
		etransitionouttasks=Other.etransitionouttasks;
		return *this;
	}
	void printme()
	{
		cout<<"FSME name: "<<name<<endl<<flush;
		if(cs!=NULL)cs->printme();
	}
	inline
	void addstate(const state& State)
	{
		pair < map<string, state*>::iterator, bool> itp;
		map<string, state*>::const_iterator it;
		state* newstate=new state(State, NULL, NULL, NULL, NULL, false);
		itp=states.insert(pair<string, state*>(State.name, newstate));
		if (itp.second==false)
		{
			delete(newstate);
		}
		else
		{
			it=itp.first;
			it->second->setshipandemotions(boidship, emotionalstate, &preferences, &decpreferences);
			if(cs==NULL)
			{
				cs=it->second;//making the first state the current state
				defaultstate=cs;
			}
		}
	}
	bool connectstates
	(
		const string& StateFromName,
		const string& StateToName,
		bool(*TransitionFunction)(const ship*, const emotions*, const decisionpreferences*)
	)
	{
		map<string, state*>::const_iterator from, to;
		from=states.find(StateFromName);//looks for the first state by its name
		if(from==states.end())
		{
			cout<<"From not found"<<endl<<flush;
			return false;//if not found, error
		}
		//if both are found, they are connected
		from->second->connectto(StateToName, TransitionFunction);
		return true;//success
	}
	inline
	void setshipandemotions(ship* Ship, emotions* Emotions)
	{
		boidship=Ship;
		emotionalstate=Emotions;
	}
	string checkemotionalstatechange()
	{
		for(unsigned int i=0;i<emotionalstatesandtransisions.size();i++)
		{
			if(emotionalstatesandtransisions.at(i).second(boidship, emotionalstate))
				return emotionalstatesandtransisions.at(i).first;
		}
		return string("");
	}
	string checkstatechange()
	{
		string newstate=checkemotionalstatechange();
		if(!newstate.empty()) return newstate; //emotional state change, nothing else happens
		//otherwise, decision state change possible
		newstate=cs->checkstatechange();
		if(!newstate.empty())
		{//if the state shows that it should be changed, the change occurs
			//cout<<"transitioning"<<endl<<flush;
			cs->transitionout();//old state cleans things up
			map<string, state*>::iterator it;
			it=states.find(newstate);
			if(it!=states.end())
			{
				cs=it->second;//change of state
				cs->transitionin();//new state sets things up
			}
			else
			{
				cout<<"new state not found in transision"<<endl<<flush;
				cout<<"state not found: "<<newstate<<endl<<flush;
			}
		}
		return string("");
	}
	state* setcurrentstate(const string& StateName)
	{
		map<string, state*>::const_iterator it;
		it=states.find(StateName);
		if(it==states.end())
		{
			cout<<"setcurrentstate found nothing"<<endl<<flush;
			return NULL;
		}
		return cs=it->second;
	}
	state* setdefaultstate(const string& StateName)
	{
		map<string, state*>::const_iterator it;
		it=states.find(StateName);
		if(it==states.end())
		{
			cout<<"setcurrentstate found nothing"<<endl<<flush;
			return NULL;
		}
		return defaultstate=it->second;
	}
	inline
	void setname(const string& NewName)
	{
		name=NewName;
	}
	inline
	void setship(ship* Ship)
	{
		boidship=Ship;
		map<string, state*>::iterator it;
		for(it=states.begin();it!=states.end();it++)
		{
			it->second->setshipandemotions(boidship, emotionalstate, &preferences, &decpreferences);
		}
	}

	void setallsteering(const steeringpreferences& NewSteering)
	{
		preferences=NewSteering;
		/*map<string, state*>::iterator it;
		for(it=states.begin();it!=states.end();it++)
		{
			it->second->setsteering(NewSteering);
		}*/
	}
	void setalldecisions(const decisionpreferences& DecisionPreferences)
	{
		decpreferences=DecisionPreferences;
		/*map<string, state*>::iterator it;
		for(it=states.begin();it!=states.end();it++)
		{
			it->second->setsteering(NewSteering);
		}*/
	}




	//functions for fetching current preferences and so forth
	inline
	steeringpreferences* getpreferences()
	{
		if(cs==NULL)
		{
			cout<<"cs NULL from getpreferences"<<endl<<flush;
			return NULL;
		}
		return &preferences;
	}
	inline
	emotions* getemotionalstate()
	{
		return emotionalstate;
	}
	inline
	decisionpreferences* getdecisionpreferences()
	{
		if(cs==NULL)
		{
			cout<<"cs NULL from getdecisionpreferences"<<endl<<flush;
			return NULL;
		}
		return &decpreferences;
	}
	inline
	steeringcontrol* getorders()
	{
		if(cs==NULL)
		{
			cout<<"cs NULL from getorders"<<endl<<flush;
			return NULL;
		}
		return &cs->orders;
	}
	inline
	void transitionin()
	{
		cs=defaultstate;
		cs->transitionin();
		for(unsigned int i=0;i<etransitionintasks.size();i++)
		{
			(boidship->*etransitionintasks.at(i))();
		}
		//TODO:check
		//TODO:change here
		//cs->transitionout();
	}
	inline
	void transitionout()
	{
		cs->transitionout();
		for(unsigned int i=0;i<etransitionouttasks.size();i++)
		{
			(boidship->*etransitionouttasks.at(i))();
		}
		//TODO:check
		//TODO:change here
		//cs=defaultstate;
	}
	void clear()
	{
		clearstates();
		cleartransitions();
	}
	inline
	void addtransitionouttask(void (ship::*Task)(void))
	{//adds a task to be performed on exiting the task
		etransitionouttasks.push_back(Task);
	}
	inline
	void addtransitionintask(void (ship::*Task)(void))
	{//adds a task to be performed on entering the task
		etransitionintasks.push_back(Task);
	}
	inline
	void cleartransitionouttasks()
	{//clears tasks to be performed on exiting the task
		etransitionouttasks.clear();
	}
	inline
	void cleartransitionintasks()
	{//clears tasks to be performed on entering the task
		etransitionintasks.clear();
	}

	string print()const
	{
		vector<pair<void (ship::*)(void), string> > taskv;
		taskv=givetransitiontasks();
		vector<pair<bool(*)(const ship*, const emotions*), string> > statetransv;
		statetransv=giveemotionaltransitionsvector();
		map <string, state*>::const_iterator it;
		string anwser("\nfsme");

		anwser+=("\nname\t")+name;

		anwser+=preferences.print();
		anwser+=decpreferences.print();

		anwser+=("\nstates");
		for(it=states.begin();it!=states.end();it++)
		{
			anwser+=it->second->print();
		}
		anwser+=("\n~states");
		anwser+=("\ndefaultstate\t")+defaultstate->name;

		anwser+=("\nemotionalstatesandtransisions");
		for(unsigned int i=0;i<emotionalstatesandtransisions.size();i++)
		{
			for(unsigned int j=0;j<statetransv.size();j++)
			{
				if(emotionalstatesandtransisions.at(i).second
						==statetransv.at(j).first)
				{
					anwser+=string("\ntransition to\t")+emotionalstatesandtransisions.at(i).first;
					anwser+=string("\nby\t")+statetransv.at(j).second;
				}
			}
		}
		anwser+=string("\netransitionouttasks");
		for(unsigned int i=0;i<etransitionouttasks.size();i++)
		{
			for(unsigned int j=0;j<taskv.size();j++)
			{
				if(etransitionouttasks.at(i)==taskv.at(j).first)
				{
					anwser+=string("\n")+taskv.at(j).second;
				}
			}
		}
		anwser+=string("\n~etransitionouttasks");
		anwser+=string("\netransitionintasks");
		for(unsigned int i=0;i<etransitionintasks.size();i++)
		{
			for(unsigned int j=0;j<taskv.size();j++)
			{
				if(etransitionintasks.at(i)==taskv.at(j).first)
				{
					anwser+=string("\n")+taskv.at(j).second;
				}
			}
		}
		anwser+=("\n~emotionalstatesandtransisions");

		//anwser+=("\n");
		anwser+=string("\n~fsme\n");
		return anwser;
	}
	bool comparestates(const fsme& Other)const
	{
		if(states.size()!=Other.states.size())
		{
			cout<<"states.size()!=Other.states.size()"<<endl<<flush;
			cout<<states.size()<<" vs "<<Other.states.size()<<endl<<flush;
		}
		else
		{
			vector<pair<void (ship::*)(void), string> > taskv;
			taskv=givetransitiontasks();
			bool tmp=true;
			map <string, state*>:: const_iterator it, it2;
			it=states.begin();
			it2=Other.states.begin();
			while(it!=states.end())
			{//a for loop working on 2 iterators
				tmp*=it->first==it2->first;
				tmp*=it->second->operator==(it2->second);
				//tmp*=*(it->second)==*(it2->second);
				//if(*(it->second)!=*(it2->second))
				if(it->second->operator!=(it2->second))
				{
					if((it->second->name)!=(it2->second->name))
					{
						cout<<"(it->second->name)"<<endl<<flush;
					}
					if((it->second->orders)!=(it2->second->orders))
					{
						cout<<"(it->second->orders)"<<endl<<flush;
					}
					if((it->second->statesandtransisions)!=(it2->second->statesandtransisions))
					{
						cout<<"(it->second->statesandtransisions)"<<endl<<flush;
					}
					if(it->second->transitionintasks!=it2->second->transitionintasks)
					{
						cout<<"(it->second->transitionintasks)"<<endl<<flush;
						cout<<"it:"<<endl<<flush;
						for(unsigned int i=0;i<it->second->transitionintasks.size();i++)
						{
							cout<<i<<" out of "<<it->second->transitionintasks.size()<<endl<<flush;
							for(unsigned int j=0;j<taskv.size();j++)
							{
								if(it->second->transitionintasks.at(i)==taskv.at(j).first)
								{
									cout<<taskv.at(j).second<<endl<<flush;
								}
							}
						}
						cout<<"it2:"<<endl<<flush;
						for(unsigned int i=0;i<it2->second->transitionintasks.size();i++)
						{
							cout<<i<<" out of "<<it2->second->transitionintasks.size()<<endl<<flush;
							for(unsigned int j=0;j<taskv.size();j++)
							{
								if(it2->second->transitionintasks.at(i)==taskv.at(j).first)
								{
									cout<<taskv.at(j).second<<endl<<flush;
								}
							}
						}
					}
					if((it->second->transitionouttasks)!=(it2->second->transitionouttasks))
					{
						cout<<"(it->second->transitionouttasks)"<<endl<<flush;
						cout<<"it:"<<endl<<flush;
						for(unsigned int i=0;i<it->second->transitionouttasks.size();i++)
						{
							cout<<i<<" out of "<<it->second->transitionouttasks.size()<<endl<<flush;
							for(unsigned int j=0;j<taskv.size();j++)
							{
								if(it->second->transitionouttasks.at(i)==taskv.at(j).first)
								{
									cout<<taskv.at(j).second<<endl<<flush;
								}
							}
						}
						cout<<"it2:"<<endl<<flush;
						for(unsigned int i=0;i<it2->second->transitionouttasks.size();i++)
						{
							cout<<i<<" out of "<<it2->second->transitionouttasks.size()<<endl<<flush;
							for(unsigned int j=0;j<taskv.size();j++)
							{
								if(it2->second->transitionouttasks.at(i)==taskv.at(j).first)
								{
									cout<<taskv.at(j).second<<endl<<flush;
								}
							}
						}
					}

					if(decpreferences!=Other.decpreferences)
					{
						cout<<"decpreferences!=Other.decpreferences"<<endl<<flush;
					}
					if(preferences!=Other.preferences)
					{
						cout<<"preferences!=Other.preferences"<<endl<<flush;
					}


					cout<<"state!=state"<<endl<<flush;
					cout<<"state1"<<endl<<flush;
					cout<<it->second->print()<<endl<<flush;
					cout<<"state2"<<endl<<flush;
					cout<<it2->second->print()<<endl<<flush;
					it->second->comparestates(it2->second);
				}
				++it;
				++it2;
			}
			return tmp;
		}//TODO: update with transition tasks?
		return false;
	}
	inline
	bool operator!=(const fsme& Other)const
	{
		return !operator==(Other);
	}
	inline
	bool operator!=(const fsme* Other)const
	{
		return !operator==(Other);
	}
	inline
	bool operator==(const fsme& Other)const
	{
		return ((name==Other.name)&&(comparestates(Other))&&
				(preferences==Other.preferences)&&
				(decpreferences==Other.decpreferences)&&
				(defaultstate->name==Other.defaultstate->name)&&
				(etransitionintasks==Other.etransitionintasks)&&
				(etransitionouttasks==Other.etransitionouttasks)&&
				(emotionalstatesandtransisions==Other.emotionalstatesandtransisions));
	}
	inline
	bool operator==(const fsme* Other)const
	{
		return ((name==Other->name)&&(comparestates(Other))&&
				(preferences==Other->preferences)&&
				(decpreferences==Other->decpreferences)&&
				(defaultstate->name==Other->defaultstate->name)&&
				(etransitionintasks==Other->etransitionintasks)&&
				(etransitionouttasks==Other->etransitionouttasks)&&
				(emotionalstatesandtransisions==Other->emotionalstatesandtransisions));
	}
	fsme& operator=(const fsme& Other)
	{
		return operator()(Other);
	}

	bool unittest()
	{

		fsme tmp("qwertyuio");
		steeringpreferences defaultsteering;
		decisionpreferences decprefs;
		state tmpstate;
		steeringcontrol orders;


				defaultsteering.reset();
				defaultsteering.setseek(1.0);
				defaultsteering.setdockradius(0.6, 0.2);
				defaultsteering.setwander(1.0);
				defaultsteering.setalignment(0.3);
				defaultsteering.setseparation(0.2);
				defaultsteering.setcohesion(0.3);
				defaultsteering.setavoid(0.1, 0.5);
				defaultsteering.setasteroidavoid(0.1, 0.5);
				defaultsteering.setgravitate(0.1, 25.0);



				orders.reset();
				orders.setgo(true);


				tmpstate=state(string("Decide what to do"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Dock with Mothership"), shipfull);
				tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
				tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
				tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);
				tmpstate.addtransitionintask(&ship::resetdockingline);


				tmp.addstate(tmpstate);



				orders.reset();
				orders.setgo(true);
				orders.setdockwithmothership(true);

				tmp.setname("Default");

				tmpstate=state(string("Dock with Mothership"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Undock from Mothership"), shipempty);

				tmp.addstate(tmpstate);

				orders.reset();
				orders.setgo(true);
				orders.setundock(true);

				tmpstate=state(string("Undock from Mothership"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Decide what to do"), shipundocked);
				tmpstate.addtransitionouttask(&ship::resetdockingline);

				tmp.addstate(tmpstate);


				orders.reset();
				orders.setgo(true);
				orders.setlookforasteroid(true);

				tmpstate=state(string("Look for Asteroid"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
				tmpstate.connectto(string("Decide what to do"), asteroidempty);
				tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

				tmp.addstate(tmpstate);


				orders.reset();
				orders.setgo(true);
				orders.setdockwithasteroid(true);

				tmpstate=state(string("Dock with Asteroid"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Undock Asteroid"), shipfull);
				tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
				tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);
				tmpstate.addtransitionintask(&ship::resetdockingline);

				tmp.addstate(tmpstate);


				orders.reset();
				orders.setgo(true);
				orders.setundock(true);

				tmpstate=state(string("Undock Asteroid"),
						//defaultsteering, decprefs,
						orders);
				tmpstate.connectto(string("Decide what to do"), shipundocked);
				tmpstate.addtransitionouttask(&ship::resetdockingline);

				tmp.addstate(tmpstate);



				tmp.setcurrentstate("Decide what to do");
				tmp.setdefaultstate("Decide what to do");


				tmp.setalldecisions(decprefs);
				tmp.setallsteering(defaultsteering);


		if(tmp==fsme(separatestrings(tmp.print())))
		{
			return true;
		}
		//cout<<tmp.print()<<endl<<flush;
		cout<<fsme(separatestrings(tmp.print())).print()<<endl<<flush;
		return false;
	}
	void connectto(const string& OtherStateName, bool(*TransitionFunction)(const ship*, const emotions*))
	{//connects the fsme to another one
		emotionalstatesandtransisions.push_back(
				pair<string, bool(*)(const ship*, const emotions*)>
				(OtherStateName, TransitionFunction));
	}

};



#endif /* FSME_H_ */
