#ifndef FSM_H_
#define FSM_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#define FSMSPEAK false

#include "FSM/fsme.h"

class fsm
{//finite state machine of the agent
public:
	map <string, fsme*> femotionalstatesm;//vector of all emotional states
	fsme* ces;//current emotional state
	fsme* defaultes;//default emotional state
	ship* boidship;
	emotions emotionalstate;
	fsm(ship* BoidShip=NULL, const emotions& ES=emotions(), const bool& Evolve=false):
		femotionalstatesm(),
		ces(NULL),
		defaultes(NULL),
		boidship(BoidShip),
		emotionalstate(ES, Evolve)
	{
	}
	fsm(const fsm& Parent, ship* BoidShip=NULL, const bool& Evolve=false):
		femotionalstatesm(),
		ces(NULL),
		defaultes(NULL),
		boidship(BoidShip),
		emotionalstate(Parent.emotionalstate, Evolve)
	{
		map <string, fsme*>::const_iterator it;
		for(it=Parent.femotionalstatesm.begin();it!=Parent.femotionalstatesm.end();it++)
		{
			femotionalstatesm.insert(pair<string, fsme*>(it->first, new fsme(it->second, BoidShip, &emotionalstate, Evolve)));
		}
		if (Parent.defaultes==NULL)defaultes=NULL;
		else
		{
			defaultes=femotionalstatesm.find(Parent.defaultes->name)->second;
		}
		ces=defaultes;
	}

	fsm(const fsm& Parent, ship* BoidShip, const bool& Evolve, const bool& SpecialEvolve):
		femotionalstatesm(),
		ces(NULL),
		defaultes(NULL),
		boidship(BoidShip),
		emotionalstate(Parent.emotionalstate, Evolve, SpecialEvolve)
	{//functionn for selective evolution
		map <string, fsme*>::const_iterator it;
		for(it=Parent.femotionalstatesm.begin();it!=Parent.femotionalstatesm.end();it++)
		{
			femotionalstatesm.insert(pair<string, fsme*>(it->first, new fsme(it->second, BoidShip, &emotionalstate, Evolve, SpecialEvolve)));
		}
		if (Parent.defaultes==NULL)defaultes=NULL;
		else
		{
			defaultes=femotionalstatesm.find(Parent.defaultes->name)->second;
		}
		ces=defaultes;
	}
	fsm(const vector<string>& FileFSM):
		femotionalstatesm(),
		ces(NULL),
		defaultes(NULL),
		boidship(NULL),
		emotionalstate()
	{
		fsme* tmpfsme;
		for(unsigned int i=0;i<FileFSM.size();i++)
		{
			if(FileFSM.at(i).find("emotionalstate")==0)
				if(FileFSM.at(i).find("~")==string::npos)
			{
				for(unsigned int j=i;j<FileFSM.size();j++)
				{
					if(FileFSM.at(i).find("~emotionalstate")==0)
					{
						emotionalstate=emotions(vector<string>(FileFSM.begin()+i+1, FileFSM.begin()+j));
						i=j;
						break;
					}
				}
			}

			if(FileFSM.at(i).find("femotionalstatesm")==0)
				//if(FileFSM.at(i).find("~")==string::npos)
			{
				for(unsigned int j=i;j<FileFSM.size();j++)
				{
					if(FileFSM.at(j).find("~femotionalstatesm")==0)
					{
						i=j;
						break;
					}

					if(FileFSM.at(j).find("fsme")==0)
						//if(FileFSM.at(j).find("~")==string::npos)
					{
						for(unsigned int k=j;k<FileFSM.size();k++)
						{
							//cout<<"fsme @"<<k<<" started @"<<j<<" **"<<FileFSM.at(k)<<"**"<<endl<<flush;
							if(FileFSM.at(k).find("~fsme")==0)
							{
								tmpfsme=new fsme(vector<string>(FileFSM.begin()+j+1, FileFSM.begin()+k));
								femotionalstatesm.insert(pair<string, fsme*>(tmpfsme->name, tmpfsme));
								j=k;
								break;
							}
						}
					}
				}
			}
			if(FileFSM.at(i).find("defaultes")==0)
			{
				//cout<<"DEFAULTES looked for: **"<<FileFSM.at(i).substr(FileFSM.at(i).find("\t")+1)<<"**"<<endl<<flush;
				defaultes=femotionalstatesm.find(FileFSM.at(i).substr(FileFSM.at(i).find("\t")+1))->second;
				//cout<<"DEFAULTES found: **"<<defaultes->name<<"**"<<endl<<flush;
				ces=defaultes;
				if(defaultes==NULL)cout<<"DEFAULTES NULL!"<<endl<<flush;
			}
		}
	}
	~fsm()
	{
		clear();
	}
	bool checkstatechange()
	{//a function that based on changes in emotions signals a change in the state
		string newstate;
		newstate=ces->checkstatechange();
		if(newstate!="")
		{
			map<string, fsme*>::iterator it;
			if(FSMSPEAK)cout<<"checkstatechange - Switching to "<<newstate<<endl<<flush;
			it=femotionalstatesm.find(newstate);
			if(it!=femotionalstatesm.end())
			{
				ces->transitionout();
				ces=it->second;
				ces->transitionin();
			}
			else
			{
				cout<<"new state not found in emotionaltransision"<<endl<<flush;
				cout<<"state not found: "<<newstate<<endl<<flush;
			}
			//cout<<emotionalstate.print()<<endl<<flush;
			return true;
		}
		return false;
	}

	fsm& operator()(const fsm& Parent, ship* BoidShip=NULL, const bool& Evolve=false)
	{
		clear();

		boidship=BoidShip;
		emotionalstate(Parent.emotionalstate, Evolve);
		map <string, fsme*>::const_iterator it;
		for(it=Parent.femotionalstatesm.begin();it!=Parent.femotionalstatesm.end();it++)
		{
			femotionalstatesm.insert(pair<string, fsme*>(it->first, new fsme(it->second, BoidShip, &emotionalstate, Evolve)));
		}
		if (Parent.defaultes==NULL)defaultes=NULL;
		else
		{
			defaultes=femotionalstatesm.find(Parent.defaultes->name)->second;
		}
		ces=defaultes;
		return *this;
	}

	inline
	steeringcontrol* getorders()
	{
		if(ces==NULL)
		{
			cout<<"ces NULL from getorders"<<endl<<flush;
			return NULL;
		}
		if(ces->cs==NULL)
		{
			cout<<"cs NULL from getorders"<<endl<<flush;
			return NULL;
		}
		return &ces->cs->orders;
	}
	inline
	steeringpreferences* getpreferences()
	{
		if(ces==NULL)
		{
			cout<<"ces NULL from getpreferences"<<endl<<flush;
			return NULL;
		}
		if(ces->cs==NULL)
		{
			cout<<"cs NULL from getpreferences"<<endl<<flush;
			return NULL;
		}
		return &ces->preferences;
	}
	inline
	emotions* getemotionalstate()
	{
		if(ces==NULL)
		{
			cout<<"ces NULL from getemotionalstate"<<endl<<flush;
			return NULL;
		}
		return &emotionalstate;
	}
	inline
	decisionpreferences* getdecisionpreferences()
	{
		if(ces==NULL)
		{
			cout<<"ces NULL from getdecisionpreferences"<<endl<<flush;
			return NULL;
		}
		if(ces->cs==NULL)
		{
			cout<<"cs NULL from getdecisionpreferences"<<endl<<flush;
			return NULL;
		}
		return &ces->decpreferences;
	}
	inline
	void printme()
	{
		if(ces==NULL)
		{
			cout<<"CES NULL"<<endl<<flush;
		}
		else
		{
			ces->printme();
		}
	}
	inline
	void setship(ship* Ship)
	{
		boidship=Ship;
		map <string, fsme*>::iterator it;
		for(it=femotionalstatesm.begin();it!=femotionalstatesm.end();it++)
		{
			it->second->setship(boidship);
		}
	}
	inline
	void addfsme(const fsme& FSME)
	{
		pair<map <string, fsme*>::iterator, bool> itp;
		map <string, fsme*>::iterator it;
		fsme* newfsme=new fsme(FSME,boidship,&emotionalstate,false);
		itp=femotionalstatesm.insert(pair<string, fsme*>(FSME.name,newfsme));
		if (itp.second==false)
		{
			delete(newfsme);
		}
		else
		{
			it=itp.first;
			if(defaultes==NULL)
			{
				defaultes=it->second;
			}
			if(ces==NULL) ces=it->second;

		}
	}
	void clear()
	{
		map <string, fsme*>::iterator it;
		for(it=femotionalstatesm.begin();it!=femotionalstatesm.end();it++)
		{
			it->second->clear();
			delete(it->second);
		}
		femotionalstatesm.clear();
		ces=NULL;
		defaultes=NULL;
	}

	string print()const
	{
		string anwser("\nfsm");

		if (FSMSPEAK) cout<<"emotionalstate"<<endl<<flush;
		anwser+=string("\nemotionalstate");
		anwser+=emotionalstate.print();
		anwser+=string("\n~emotionalstate");



		anwser+=string("\nfemotionalstatesm");
		map <string, fsme*>::const_iterator it;
		if (FSMSPEAK) cout<<"map <string, fsme*>::const_iterator it;"<<endl<<flush;
		for(it=femotionalstatesm.begin();it!=femotionalstatesm.end();it++)
		{
			if (FSMSPEAK) cout<<"for(it=femotionalstatesm.begin();it!=femotionalstatesm.end();it++)"<<endl<<flush;
			anwser+=it->second->print();
		}
		anwser+=string("\n~femotionalstatesm");


		if (FSMSPEAK) cout<<"defaultes"<<endl<<flush;
		anwser+=("\ndefaultes\t")+defaultes->name;

		anwser+=string("\n~fsm\n");
		return anwser;
	}

	bool comparefsmes(const fsm& Other)const
	{
		if(femotionalstatesm.size()!=Other.femotionalstatesm.size())
		{
			cout<<"femotionalstatesm.size()!=Other.femotionalstatesm.size()"<<endl<<flush;
			cout<<femotionalstatesm.size()<<" vs "<<Other.femotionalstatesm.size()<<endl<<flush;
		}
		else
		{
			bool tmp=true;
			map <string, fsme*>:: const_iterator it, it2;
			it=femotionalstatesm.begin();
			it2=Other.femotionalstatesm.begin();
			while(it!=femotionalstatesm.end())
			{//a for loop working on 2 iterators
				if(it->first!=it2->first)
				{
					cout<<"it->first==it2->first"<<endl<<flush;
				}
				tmp*=it->first==it2->first;
				tmp*=it->second->operator==(it2->second);
				if(it->second->operator!=(it2->second))
				{
					cout<<"it->second->operator!=(it2->second)"<<endl<<flush;
				}
				if(tmp==false)cout<<"comparefsmes false"<<endl<<flush;
				++it;
				++it2;
			}
			return tmp;
		}
		return false;
	}
	void showdifferences(const fsm& Other)const
	{
		if(emotionalstate!=Other.emotionalstate)cout<<"emotionalstates"<<endl<<flush;
		if(ces==NULL&&Other.ces==NULL)cout<<"ces'es NULL"<<endl<<flush;
		else if(ces==NULL)cout<<"ces 1 NULL"<<endl<<flush;
		else if(Other.ces==NULL)cout<<"ces 2 NULL"<<endl<<flush;

		if(defaultes==NULL&&Other.defaultes==NULL)cout<<"defaultes'es NULL"<<endl<<flush;
		else if(defaultes==NULL)cout<<"defaultes 1 NULL"<<endl<<flush;
		else if(Other.defaultes==NULL)cout<<"defaultes 2 NULL"<<endl<<flush;

		if(boidship==NULL&&Other.boidship==NULL)cout<<"boidships NULL"<<endl<<flush;
		else if(boidship==NULL)cout<<"boidship 1 NULL"<<endl<<flush;
		else if(Other.boidship==NULL)cout<<"boidship 2 NULL"<<endl<<flush;

		if(defaultes->name!=Other.defaultes->name)
		{
			cout<<"defaultes->name!=Other.defaultes->name"<<endl<<flush;
			cout<<"**"<<defaultes->name<<"** vs **"<<Other.defaultes->name<<"**"<<endl<<flush;
		}
		if(emotionalstate!=Other.emotionalstate)
		{
			cout<<"emotionalstate!=Other.emotionalstate"<<endl<<flush;
			cout<<"**"<<emotionalstate.print()<<"** vs **"<<Other.emotionalstate.print()<<"**"<<endl<<flush;
		}
		if(femotionalstatesm.size()==Other.femotionalstatesm.size())
		{
			map <string, fsme*>:: const_iterator it, it2;
			it=femotionalstatesm.begin();
			it2=Other.femotionalstatesm.begin();
			while(it!=femotionalstatesm.end())
			{//a for loop working on 2 iterators
				if(it->first!=it2->first)
				{
					cout<<"it->first!=it2->first"<<endl<<flush;
					cout<<"it->first **"<<it->first<<"**"<<endl<<flush;
					cout<<"it2->first **"<<it2->first<<"**"<<endl<<flush;
				}
				if(it->second->operator!=(it2->second))
				//if((*(it->second))!=(*(it2->second)))
				{
					cout<<"it->second->operator ==(it2->second)"<<endl<<flush;
					cout<<"it->first **"<<it->first<<"**"<<endl<<flush;
					cout<<"it2->first **"<<it2->first<<"**"<<endl<<flush;
					cout<<"*(it->second) **"<<it->second->name<<"**"<<endl<<flush;
					cout<<"*(it2->second) **"<<it2->second->name<<"**"<<endl<<flush;
					cout<<"Comparing:"<<endl<<flush;
					it->second->comparestates(it2->second);
				}
				++it;
				++it2;
			}
		}
		else
		{
			cout<<"femotionalstatesm.size()==Other.femotionalstatesm.size()"<<endl<<flush;
			cout<<femotionalstatesm.size()<<" vs "<<Other.femotionalstatesm.size()<<endl<<flush;
		}
		if(emotionalstate!=Other.emotionalstate)
		{
			cout<<"emotionalstate!=Other.emotionalstate"<<endl<<flush;
		}
	}

	inline
	bool operator!=(const fsm& Other)const
	{
		return !operator==(Other);
	}
	inline
	bool operator==(const fsm& Other)const
	{
		return(comparefsmes(Other)&&
				(defaultes->name==Other.defaultes->name)&&
				(emotionalstate==Other.emotionalstate));
	}
	fsm& operator=(const fsm& Other)
	{
		return operator()(Other);
	}

	bool unittest()
	{
		fsm tmpfsm;
		steeringpreferences defaultsteering;
		decisionpreferences decprefs;
		state tmpstate;
		steeringcontrol orders;


		fsme defaultfsme("Contempt");

		defaultsteering.reset();
		defaultsteering.setseek(1.0);
		defaultsteering.setdockradius(0.6, 0.2);
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(0.1, 0.5);
		defaultsteering.setasteroidavoid(0.5, 0.5);
		defaultsteering.setgravitate(0.1, 5.0);



		orders.reset();
		orders.setgo(true);


		tmpstate=state(string("Decide what to do"), orders);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Look for Harvester", friendlyshipnottargeted);
		tmpstate.connectto("Protect Harvester", friendlyshiptargeted);
		tmpstate.connectto("Attack Enemy", shiptargeted);



		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setlookforharvester(true);


		tmpstate=state(string("Look for Harvester"), orders);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Protect Harvester", friendlyshiptargeted);



		defaultfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setprotectharvester(true);


		tmpstate=state(string("Protect Harvester"), orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Decide what to do", friendlyshipnottargeted);



		defaultfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setdefendyourself(true);


		tmpstate=state(string("Defent Yourself"), orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);
		tmpstate.connectto("Decide what to do", shipnotbeingtargeted);



		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setattackboid(true);


		tmpstate=state(string("Attack Enemy"), orders);
		tmpstate.connectto("Decide what to do", shipnottargeted);



		defaultfsme.addstate(tmpstate);




		defaultfsme.setcurrentstate("Decide what to do");
		defaultfsme.setdefaultstate("Decide what to do");


		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);

		defaultfsme.connectto("Fear", switchtofearfromcontempt);
		defaultfsme.connectto("Anger", switchtoangerfromcontempt);

		defaultfsme.addtransitionouttask(&ship::untarget);

		tmpfsm.addfsme(defaultfsme);







		fsme fearfsme("Fear");



		defaultsteering.reset();
		defaultsteering.setseek(1.0);
		defaultsteering.setdockradius(0.6, 0.2);
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(0.1, 0.5);
		defaultsteering.setasteroidavoid(0.1, 0.5);
		defaultsteering.setgravitate(0.1, 15.0);



		orders.reset();
		orders.setgo(true);


		tmpstate=state(string("Decide what to do"), orders);
		tmpstate.connectto(string("Dock with Mothership"), shipdamaged);
		tmpstate.connectto(string("Gravitate Mothership"), shiphealthy);
		tmpstate.addtransitionintask(&ship::untarget);


		fearfsme.addstate(tmpstate);



		orders.reset();
		orders.setgo(true);
		orders.setdockwithmothership(true);

		tmpstate=state(string("Dock with Mothership"), orders);
		tmpstate.connectto(string("Undock from Mothership"), shiphealthy);

		fearfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setundock(true);

		tmpstate=state(string("Undock from Mothership"), orders);
		tmpstate.connectto(string("Decide what to do"), shipundocked);
		tmpstate.addtransitionouttask(&ship::resetdockingline);

		fearfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setgravitatemothership(true);

		tmpstate=state(string("Gravitate Mothership"),orders);
		tmpstate.connectto(string("Decide what to do"), shipdamaged);

		fearfsme.addstate(tmpstate);




		fearfsme.setcurrentstate("Decide what to do");
		fearfsme.setdefaultstate("Decide what to do");


		fearfsme.setalldecisions(decprefs);
		fearfsme.setallsteering(defaultsteering);




		fearfsme.connectto("Contempt", switchtocontemptfromfear);
		fearfsme.connectto("Anger", switchtoangerfromfear);


		fearfsme.addtransitionouttask(&ship::untarget);

		tmpfsm.addfsme(fearfsme);




		fsme angerfsme("Anger");

		defaultsteering.reset();
		defaultsteering.setseek(1.0);
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(0.1, 0.5);
		defaultsteering.setasteroidavoid(0.1, 0.5);
		defaultsteering.setgravitate(0.1, 25.0);



		orders.reset();
		orders.setgo(true);


		tmpstate=state(string("Decide what to do"),	orders);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Look for Enemy", shipnottargeted);
		tmpstate.connectto("Attack Enemy", shiptargeted);


		angerfsme.addstate(tmpstate);





		orders.reset();
		orders.setgo(true);
		orders.setlookforboid(true);


		tmpstate=state(string("Look for Enemy"),orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);


		angerfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setdefendyourself(true);


		tmpstate=state(string("Defent Yourself"), orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);
		tmpstate.connectto("Decide what to do", shipnotbeingtargeted);

		angerfsme.addstate(tmpstate);



		orders.reset();
		orders.setgo(true);
		orders.setattackboid(true);


		tmpstate=state(string("Attack Enemy"),orders);
		tmpstate.connectto("Decide what to do", shipnottargeted);
		tmpstate.addtransitionouttask(&ship::untarget);//making sure the ship target is dropped, in case emotionchanges


		angerfsme.addstate(tmpstate);





		angerfsme.setcurrentstate("Decide what to do");
		angerfsme.setdefaultstate("Decide what to do");


		angerfsme.setalldecisions(decprefs);
		angerfsme.setallsteering(defaultsteering);


		angerfsme.connectto("Contempt", switchtocontemptfromanger);
		angerfsme.connectto("Fear", switchtofearfromanger);


		angerfsme.addtransitionouttask(&ship::untarget);

		tmpfsm.addfsme(angerfsme);

		//TODO: error here
		fsm copy(separatestrings(tmpfsm.print()));
		//cout<<"Copy: "<<copy.print();
		if(tmpfsm==copy)
		{
			return true;
		}
		cout<<"Showing differences"<<endl<<flush;
		tmpfsm.showdifferences(copy);
		cout<<"fsm unittest not OK"<<endl<<flush;
		cout<<"Original"<<endl<<flush;
		cout<<tmpfsm.print()<<endl<<flush;
		cout<<"Copy"<<endl<<flush;
		cout<<copy.print()<<endl<<flush;



		cout<<"****Line by line comparison****"<<endl<<flush;

		vector <string> tmp1=separatestrings(tmpfsm.print());
		vector <string> tmp2=separatestrings(copy.print());
		comparestringvestors(tmp1, tmp2);
		return false;
	}

	bool unittest2()
	{
		fsm tmpfsm;
		steeringpreferences defaultsteering;
		decisionpreferences decprefs;
		state tmpstate;
		steeringcontrol orders;


		fsme defaultfsme("Contempt");

		defaultsteering.reset();
		defaultsteering.setseek(1.0);
		defaultsteering.setdockradius(0.6, 0.2);
		defaultsteering.setwander(1.0);
		defaultsteering.setalignment(0.3);
		defaultsteering.setseparation(0.2);
		defaultsteering.setcohesion(0.3);
		defaultsteering.setavoid(0.1, 0.5);
		defaultsteering.setasteroidavoid(0.5, 0.5);
		defaultsteering.setgravitate(0.1, 5.0);



		orders.reset();
		orders.setgo(true);


		tmpstate=state(string("Decide what to do"), orders);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Look for Harvester", friendlyshipnottargeted);
		tmpstate.connectto("Protect Harvester", friendlyshiptargeted);
		tmpstate.connectto("Attack Enemy", shiptargeted);



		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setlookforharvester(true);


		tmpstate=state(string("Look for Harvester"), orders);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Protect Harvester", friendlyshiptargeted);



		defaultfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setprotectharvester(true);


		tmpstate=state(string("Protect Harvester"), orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);
		tmpstate.connectto("Defent Yourself", shipbeingtargeted);
		tmpstate.connectto("Decide what to do", friendlyshipnottargeted);



		defaultfsme.addstate(tmpstate);

		orders.reset();
		orders.setgo(true);
		orders.setdefendyourself(true);


		tmpstate=state(string("Defent Yourself"), orders);
		tmpstate.connectto("Attack Enemy", shiptargeted);
		tmpstate.connectto("Decide what to do", shipnotbeingtargeted);



		defaultfsme.addstate(tmpstate);


		orders.reset();
		orders.setgo(true);
		orders.setattackboid(true);


		tmpstate=state(string("Attack Enemy"), orders);
		tmpstate.connectto("Decide what to do", shipnottargeted);



		defaultfsme.addstate(tmpstate);




		defaultfsme.setcurrentstate("Decide what to do");
		defaultfsme.setdefaultstate("Decide what to do");


		defaultfsme.setalldecisions(decprefs);
		defaultfsme.setallsteering(defaultsteering);

		defaultfsme.connectto("Fear", switchtofearfromcontempt);
		defaultfsme.connectto("Anger", switchtoangerfromcontempt);

		defaultfsme.addtransitionouttask(&ship::untarget);

		tmpfsm.addfsme(defaultfsme);





		fsm copy(separatestrings(tmpfsm.print()));
		//cout<<"Copy: "<<copy.print();
		if(tmpfsm==copy)
		{
			return true;
		}
		cout<<"Showing differences"<<endl<<flush;
		tmpfsm.showdifferences(copy);
		cout<<"fsm unittest not OK"<<endl<<flush;
		/*cout<<"Original"<<endl<<flush;
		cout<<tmpfsm.print()<<endl<<flush;
		cout<<"Copy"<<endl<<flush;
		cout<<copy.print()<<endl<<flush;*/



		cout<<"****Line by line comparison****"<<endl<<flush;

		vector <string> tmp1=separatestrings(tmpfsm.print());
		vector <string> tmp2=separatestrings(copy.print());
		comparestringvestors(tmp1, tmp2);
		return false;
	}
};

#endif /* FSM_H_ */
