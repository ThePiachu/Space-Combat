#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "../../map.h"
#include "../steeringpreferences.h"
#include "../decisionpreferences.h"
#include "../steeringcontrol.h"
#include "../emotions.h"
#include "transitions.h"

class state
{
public:
	string name;//name of the state
	bool lock;//activity lock is used to lock in certain activities untill they are finished

	ship* boidship;//pointer to the ship used by the boid

	steeringpreferences* preferences;//steering preferences of the boid
	decisionpreferences* decpreferences;//decision preferences of the boid
	steeringcontrol orders;//boid orders, which control what the boid does
	emotions* emotionalstate;//emotional state of the boid, shared between all states

	//list of different states this state can trainsition into and the function used to determine if the transition occurs
	vector<pair<string, bool(*)(const ship*, const emotions*, const decisionpreferences*)> > statesandtransisions;
	vector<void (ship::*)(void)> transitionouttasks, transitionintasks;//functions to be called when the state is entered and exited

	state(const state* Other, const bool& Evolve=false):
		name(Other->name),
		lock(false),
		boidship(NULL),
		preferences(NULL),
		decpreferences(NULL),
		orders(Other->orders),
		emotionalstate(NULL),
		statesandtransisions(Other->statesandtransisions),
		transitionouttasks(Other->transitionouttasks),
		transitionintasks(Other->transitionintasks)
	{
	}
	state(const string& Name,
			//steeringpreferences* Preferences,
			//decisionpreferences* DecPrefs,
			const steeringcontrol& Orders):
		name(Name),
		lock(false),
		boidship(NULL),
		preferences(NULL),
		decpreferences(NULL),
		orders(Orders),
		emotionalstate(NULL),
		statesandtransisions(),
		transitionouttasks(),
		transitionintasks()
	{
	}
	state(const string& Name=string("")):
		name(Name),
		lock(false),
		boidship(NULL),
		preferences(NULL),
		decpreferences(NULL),
		orders(),
		emotionalstate(NULL),
		statesandtransisions(),
		transitionouttasks(),
		transitionintasks()
	{
	}
	state(const state& Other, emotions* EmotionalState=NULL,
			steeringpreferences* SteeringPreferences=NULL, decisionpreferences* DecisionPreferences=NULL,
			ship* BoidShip=NULL, const bool& Evolve=false):
		name(Other.name),
		lock(false),
		boidship(BoidShip),
		preferences(SteeringPreferences),
		decpreferences(DecisionPreferences),
		orders(Other.orders),
		emotionalstate(EmotionalState),
		statesandtransisions(Other.statesandtransisions),
		transitionouttasks(Other.transitionouttasks),
		transitionintasks(Other.transitionintasks)
	{
	}
	state(const state& Other, emotions* EmotionalState,
			steeringpreferences* SteeringPreferences, decisionpreferences* DecisionPreferences,
			ship* BoidShip, const bool& Evolve, const bool& SpecialEvolve)://a function for selective evolution
		name(Other.name),
		lock(false),
		boidship(BoidShip),
		preferences(SteeringPreferences),
		decpreferences(DecisionPreferences),
		orders(Other.orders),
		emotionalstate(EmotionalState),
		statesandtransisions(Other.statesandtransisions),
		transitionouttasks(Other.transitionouttasks),
		transitionintasks(Other.transitionintasks)
	{
	}
	state(const state* Other, emotions* EmotionalState=NULL,
			steeringpreferences* SteeringPreferences=NULL, decisionpreferences* DecisionPreferences=NULL,
			ship* BoidShip=NULL, const bool& Evolve=false):
		name(Other->name),
		lock(false),
		boidship(BoidShip),
		preferences(SteeringPreferences),
		decpreferences(DecisionPreferences),
		orders(Other->orders),
		emotionalstate(EmotionalState),
		statesandtransisions(Other->statesandtransisions),
		transitionouttasks(Other->transitionouttasks),
		transitionintasks(Other->transitionintasks)
	{
	}
	state(const state* Other, emotions* EmotionalState,
			steeringpreferences* SteeringPreferences, decisionpreferences* DecisionPreferences,
			ship* BoidShip, const bool& Evolve, const bool& SpecialEvolve)://a function for selective evolution
		name(Other->name),
		lock(false),
		boidship(BoidShip),
		preferences(SteeringPreferences),
		decpreferences(DecisionPreferences),
		orders(Other->orders),
		emotionalstate(EmotionalState),
		statesandtransisions(Other->statesandtransisions),
		transitionouttasks(Other->transitionouttasks),
		transitionintasks(Other->transitionintasks)
	{
	}
	state(const vector<string>& FileState):
		name(),
		lock(false),
		boidship(NULL),
		preferences(NULL),
		decpreferences(NULL),
		orders(),
		emotionalstate(NULL),
		statesandtransisions(),
		transitionouttasks(),
		transitionintasks()
	{
		vector<pair<void (ship::*)(void), string> > taskv;
		taskv=givetransitiontasks();
		vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string> >transitionsv;
		transitionsv=givetransitionsvector();
		/*cout<<"state(const vector<string>& FileState):"<<endl<<flush;
		for(unsigned int i=0;i<FileState.size();i++)
		{
			cout<<i<<"of"<<FileState.size()<<"**"<<FileState.at(i)<<"**"<<endl<<flush;
		}*/
		for(unsigned int i=0;i<FileState.size();i++)
		{

			//cout<<"FileState at "<<i<<" of "<<FileState.size()<<" :**"<<FileState.at(i)<<"**"<<endl<<flush;
			if(FileState.at(i).find("name")==0)
			{
				name=FileState.at(i).substr(FileState.at(i).find("\t")+1);
			}
			/*if(FileState.at(i).find("steeringpreferences")==0)
				//if(FileState.at(i).find("~steeringpreferences")==string::npos)
			{
				for(unsigned int j=i;j<FileState.size();j++)
					if(FileState.at(j).find("~steeringpreferences")==0)
					{
						preferences
							=steeringpreferences(
								vector<string>(FileState.begin()+i, FileState.begin()+j));
					}
			}*/
			/*if(FileState.at(i).find("decisionpreferences")==0)
				//if(FileState.at(i).find("~decisionpreferences")==string::npos)
			{
				for(unsigned int j=i;j<FileState.size();j++)
					if(FileState.at(j).find("~decisionpreferences")==0)
					{
						decpreferences
							=decisionpreferences(
								vector<string>(FileState.begin()+i, FileState.begin()+j));
					}
			}*/
			if(FileState.at(i).find("steeringcontrol")==0)
				//if(FileState.at(i).find("~steeringcontrol")==string::npos)
			{
				for(unsigned int j=i;j<FileState.size();j++)
					if(FileState.at(j).find("~steeringcontrol")==0)
					{
						orders
							=steeringcontrol(
								vector<string>(FileState.begin()+i, FileState.begin()+j));
					}
			}
			if(FileState.at(i).find("statesandtransisions")==0)
				//if(FileState.at(i).find("~statesandtransisions")==string::npos)
			{

				for(unsigned int j=i;j<FileState.size();j++)
				{
					if(FileState.at(j).find("~statesandtransisions")==0)
					{
						i=j;
						break;
					}
					else if(FileState.at(j).find("transition to")==0)
					{
						string to=FileState.at(j).substr(14);//destinatin name
						string by=FileState.at(j+1).substr(3);//transition function name
						for(unsigned int k=0;k<transitionsv.size();k++)
						{
							if(transitionsv.at(k).second==by)
							{
								statesandtransisions.push_back(
										pair<string, bool(*)(const ship*, const emotions*, const decisionpreferences*)>
											(to, transitionsv.at(k).first));
								break;
							}
						}
					}
				}
			}
			if(FileState.at(i).find("transitionouttasks")==0)
				//if(FileState.at(i).find("~transitionouttasks")==string::npos)
			{
				//cout<<"looking for transitionouttasks..."<<endl<<flush;
				for(unsigned int j=i;j<FileState.size();j++)
				{
					if(FileState.at(j).find("~transitionouttasks")==0)
					{
						i=j;
						break;
					}
					else
					{
						string task=FileState.at(j);//transition name
						//cout<<"Task name: **"<<task<<"**"<<endl<<flush;
						for(unsigned int k=0;k<taskv.size();k++)
						{
							if(taskv.at(k).second==task)
							{
								transitionouttasks.push_back(taskv.at(k).first);
								break;
							}
						}
					}
				}
			}
			if(FileState.at(i).find("transitionintasks")==0)
				//if(FileState.at(i).find("~transitionintasks")==string::npos)
			{
				//cout<<"looking for transitionintasks..."<<endl<<flush;
				for(unsigned int j=i;j<FileState.size();j++)
				{
					if(FileState.at(j).find("~transitionintasks")==0)
					{
						i=j;
						break;
					}
					else
					{
						string task=FileState.at(j);//transition name
						//cout<<"Task name: **"<<task<<"**"<<endl<<flush;
						for(unsigned int k=0;k<taskv.size();k++)
						{
							if(taskv.at(k).second==task)
							{
								transitionintasks.push_back(taskv.at(k).first);
								break;
							}
						}
					}
				}
			}

		}
	}
	~state()
	{
	}
	string print()const
	{
		vector<pair<void (ship::*)(void), string> > taskv;
		taskv=givetransitiontasks();
		vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string> >transitionsv;
		transitionsv=givetransitionsvector();


		string anwser("\nstate");

		anwser+=string("\nname:\t")+name;
		//lock?
		//anwser+=preferences.print();
		//anwser+=decpreferences.print();
		anwser+=orders.print();
		anwser+=string("\nstatesandtransisions");
		for(unsigned int i=0;i<statesandtransisions.size();i++)
		{
			for(unsigned int j=0;j<transitionsv.size();j++)
			{
				if(statesandtransisions.at(i).second==transitionsv.at(j).first)
				{
					anwser+=string("\ntransition to\t")+statesandtransisions.at(i).first;
					anwser+=string("\nby\t")+transitionsv.at(j).second;
				}
			}
		}
		anwser+=string("\n~statesandtransisions");
		anwser+=string("\ntransitionouttasks");
		for(unsigned int i=0;i<transitionouttasks.size();i++)
		{
			for(unsigned int j=0;j<taskv.size();j++)
			{
				if(transitionouttasks.at(i)==taskv.at(j).first)
				{
					anwser+=string("\n")+taskv.at(j).second;
				}
			}
		}
		anwser+=string("\n~transitionouttasks");
		anwser+=string("\ntransitionintasks");
		for(unsigned int i=0;i<transitionintasks.size();i++)
		{
			for(unsigned int j=0;j<taskv.size();j++)
			{
				if(transitionintasks.at(i)==taskv.at(j).first)
				{
					anwser+=string("\n")+taskv.at(j).second;
				}
			}
		}
		anwser+=string("\n~transitionintasks");


		//anwser+=string("");

		anwser+=("\n~state\n");

		return anwser;
	}


	state& operator()(const state& Other, const bool& Evolve=false)
	{
		name=Other.name;
		lock=false;

		boidship=NULL;
		preferences=NULL;
		decpreferences=NULL;
		//preferences(Other.preferences,Evolve);
		//decpreferences(Other.decpreferences,Evolve);
		orders(Other.orders);

		emotionalstate=NULL;

		statesandtransisions=Other.statesandtransisions;

		transitionouttasks=Other.transitionouttasks;
		transitionintasks=Other.transitionintasks;

		return *this;
	}
	inline
	void connectto(const string& OtherStateName, bool(*TransitionFunction)(const ship*, const emotions*, const decisionpreferences*))
	{//connects the state to another one
		statesandtransisions.push_back(
			pair<string, bool(*)(const ship*, const emotions*, const decisionpreferences*)>
			(OtherStateName, TransitionFunction));
	}
	inline
	void setshipandemotions(ship* Ship, emotions* Emotions, steeringpreferences* Preferences, decisionpreferences* DecisionPreferences)
	{//sets up the pointers to the ship and emotions of the boid
		boidship=Ship;
		emotionalstate=Emotions;
		preferences=Preferences;
		decpreferences=DecisionPreferences;
	}

	inline
	void setsteering(steeringpreferences* NewSteering)
	{
		preferences=NewSteering;
	}


	string checkstatechange()
	{//checks if the state needs to be changed
		for(unsigned int i=0;i<statesandtransisions.size();i++)
		{
			if(statesandtransisions.at(i).second(boidship, emotionalstate, decpreferences))
				return statesandtransisions.at(i).first;
		}
		return string("");
	}



	void printme()
	{//prints the state name
		cout<<"State name: "<<name<<endl<<flush;
	}

	inline
	void addtransitionouttask(void (ship::*Task)(void))
	{//adds a task to be performed on exiting the task
		transitionouttasks.push_back(Task);
	}
	inline
	void addtransitionintask(void (ship::*Task)(void))
	{//adds a task to be performed on entering the task
		transitionintasks.push_back(Task);
	}
	inline
	void cleartransitionouttasks()
	{//clears tasks to be performed on exiting the task
		transitionouttasks.clear();
	}
	inline
	void cleartransitionintasks()
	{//clears tasks to be performed on entering the task
		transitionintasks.clear();
	}

	//functions that might or might not alter any boid's states
	//for example, making it forget what asteroid it was mining from once it is done
	void transitionout()
	{
		for(unsigned int i=0;i<transitionouttasks.size();i++)
		{
			(boidship->*transitionouttasks.at(i))();
		}
	}
	void transitionin()
	{
		for(unsigned int i=0;i<transitionintasks.size();i++)
		{
			(boidship->*transitionintasks.at(i))();
		}
	}

	bool operator!=(const state& Other)const
	{
		return !operator==(Other);
	}
	bool operator!=(const state* Other)const
	{
		return !operator==(Other);
	}

	bool operator==(const state& Other)const
	{
		return ((name==Other.name)&&
				//(preferences==Other.preferences)&&
				//(decpreferences==Other.decpreferences)&&
				(orders==Other.orders)&&
				(statesandtransisions==Other.statesandtransisions)&&
				(transitionouttasks==Other.transitionouttasks)&&
				(transitionintasks==Other.transitionintasks));
	}
	bool operator==(const state* Other)const
	{
		return ((name==Other->name)&&
				//(preferences==Other->preferences)&&
				//(decpreferences==Other->decpreferences)&&
				(orders==Other->orders)&&
				(statesandtransisions==Other->statesandtransisions)&&
				(transitionouttasks==Other->transitionouttasks)&&
				(transitionintasks==Other->transitionintasks));
	}
	bool comparestates(const state* Other)
	{
		bool ok=true;
		if (name!=Other->name)
		{
			cout<<"name!=Other->name"<<endl<<flush;
			cout<<"**"<<name<<"** vs **"<<Other->name<<"**"<<endl<<flush;
			ok=false;
		}
		if(orders!=Other->orders)
		{
			cout<<"orders!=Other->orders"<<endl<<flush;
			cout<<"**"<<orders.print()<<"** vs **"<<Other->orders<<"**"<<endl<<flush;
			ok=false;
		}
		if(statesandtransisions!=Other->statesandtransisions)
		{
			cout<<"statesandtransisions!=Other.statesandtransisions"<<endl<<flush;
			//TODO: expand
			//cout<<"**"<<<<"** vs **"<<Other-><<"**"<<endl<<flush;
			ok=false;
		}
		if(transitionouttasks!=Other->transitionouttasks)
		{
			cout<<"transitionouttasks!=Other.transitionouttasks"<<endl<<flush;
			//TODO: expand
			//cout<<"**"<<<<"** vs **"<<Other-><<"**"<<endl<<flush;
			ok=false;

		}
		if(transitionintasks!=Other->transitionintasks)
		{
			cout<<"transitionintasks!=Other.transitionintasks"<<endl<<flush;
			//TODO: expand
			//cout<<"**"<<<<"** vs **"<<Other-><<"**"<<endl<<flush;
			ok=false;
		}
		return ok;
	}
	state& operator=(const state& Other)
	{
		return operator()(Other);
	}

	bool unittest()
	{
		string Name=string("qweRTYUI(*&^%$");
		/*steeringpreferences Preferences(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
				1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
				2.1, 2.2);
		decisionpreferences DecPrefs(0.1, 0.2, 0.3, 0.4, 0.5, 0.6);*/
		steeringcontrol Orders;
		Orders.setdockwithmothership(true);
		Orders.setsinglepathfollow(true);
		Orders.setgo(true);
		state tmp(Name, Orders);
		tmp.connectto(string("Decide what to do"), shipundocked);
		tmp.addtransitionouttask(&ship::resetdockingline);
		tmp.connectto(string("Undock Asteroid"), shipfull);
		tmp.connectto(string("Undock Asteroid"), asteroidempty);
		tmp.addtransitionouttask(&ship::unsetasteroidtarget);
		if(tmp==state(separatestrings(tmp.print())))
		{
			return true;
		}
		cout<<tmp.print()<<endl<<flush;
		cout<<state(separatestrings(tmp.print())).print()<<endl<<flush;
		return false;
	}
};

#endif /* STATE_H_ */
