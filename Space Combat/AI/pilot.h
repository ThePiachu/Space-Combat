#ifndef PILOT_H_
#define PILOT_H_

#define AGEWEIGHT 0.01
#define SHIPKILLEDWEIGHT 10.0
#define LASERSPREAD 15.0//arch of where the laser can hit
#define LASERRANGE 2.0//how far the laser can hit
#define HARVESTEDREWARD 0.1
#define NOHARVESTERANGER 1.0

#include "steeringpreferences.h"
#include "steering.h"
#include "steeringcontrol.h"
#include "../map.h"
#include "../math.h"
#include "fsm.h"
#include "emotions.h"
#include "decisionpreferences.h"
#include "astar.h"
#include <ctime>

#define PILOTSPEAK false


class pilot
{//the AI of the boid
public:
	random* myrandom;//random class
	steeringpreferences* preferences;//pointer to steering rpeferences
	steering mysteering;//class to calculate all the steering forces
	colour mycolour;//colour of the boid

	float score;//score of the boid

	//Steering targets, paths and what nots
	steeringcontrol* orders;
	target seektarget, fleetarget, arrivetarget;
	target topprioritytarget;

	target gravitateplace;

	//path to follow
	path singlepath;
	path loopedpath;
	bool singlepathvalid, loopedpathvalid;
	unsigned int singlepathlinenumber, loopedpathlinenumber;

	//grid
	grid* mygrid;

	ship myship;//pilot's ship
	mothership* mymothership;//pilot's mothership

	//fsme myfsme;//pilot's FSM
	fsm myfsm;
	emotions* emotionalstate;
	decisionpreferences* decpreferences;
	unsigned int age;//age of the pilot
	unsigned int generation;//generation of the pilot

	astar myastar;
	myvector laser;//a vector simulating a laser
	time_t born;

	pilot
	(
		const point& Position=point(),
		const fsm& FSM=fsm(),
		const colour& Colour=colour(),
		const unsigned int& ShipType=0
	):
		myrandom(random::getinstance()),
		preferences(NULL),
		mysteering(),
		mycolour(Colour),
		score(0.0),

		orders(),
		seektarget(),
		fleetarget(),
		arrivetarget(),
		topprioritytarget(),

		gravitateplace(),
		singlepath(),
		loopedpath(),
		singlepathvalid(false),
		loopedpathvalid(false),
		singlepathlinenumber(0),
		loopedpathlinenumber(0),


		mygrid(NULL),

		myship(Position, mycolour, ShipType),
		mymothership(NULL),
		myfsm(FSM, &myship, false),

		emotionalstate(NULL),
		decpreferences(NULL),
		age(0),
		generation(0),
		myastar(mygrid),
		laser(0.0, 0.0, 0.0),
		born(time(NULL))
	{
		mycolour.inherit(Colour);
	}
	pilot
	(
		const pilot* Parent,
		const point& Position,
		const bool& Evolve=false
	):
		myrandom(random::getinstance()),
		preferences(NULL),
		//mysteering(Parent->mysteering),
		mysteering(),
		mycolour(Parent->mycolour, Evolve),
		score(0.0),

		orders(),
		seektarget(),
		fleetarget(),
		arrivetarget(),
		topprioritytarget(),

		gravitateplace(),
		singlepath(),
		loopedpath(),
		singlepathlinenumber(0),
		loopedpathlinenumber(0),


		mygrid(NULL),

		myship(Position, mycolour, Parent->myship.shiptype),
		mymothership(NULL),
		myfsm(Parent->myfsm, &myship, Evolve),
		//myfsm(),
		emotionalstate(NULL),
		decpreferences(NULL),
		age(0),
		generation(Parent->generation+1),
		myastar(mygrid, Parent->myastar, Evolve),
		laser(0.0, 0.0, 0.0),
		born(time(NULL))
		{
			//mycolour.inherit(Parent->mycolour);
		}
	pilot
		(
			const pilot* Parent,
			const point& Position,
			const bool& Evolve,
			const bool& SpecialEvolve
		)://function for selective evolution
			myrandom(random::getinstance()),
			preferences(NULL),
			//mysteering(Parent->mysteering),
			mysteering(),
			mycolour(Parent->mycolour, Evolve, SpecialEvolve),
			score(0.0),

			orders(),
			seektarget(),
			fleetarget(),
			arrivetarget(),
			topprioritytarget(),

			gravitateplace(),
			singlepath(),
			loopedpath(),
			singlepathlinenumber(0),
			loopedpathlinenumber(0),


			mygrid(NULL),

			myship(Position, mycolour, Parent->myship.shiptype),
			mymothership(NULL),
			myfsm(Parent->myfsm, &myship, Evolve, SpecialEvolve),
			//myfsm(),
			emotionalstate(NULL),
			decpreferences(NULL),
			age(0),
			generation(Parent->generation+1),
			myastar(mygrid, Parent->myastar, Evolve, SpecialEvolve),
			laser(0.0, 0.0, 0.0),
			born(time(NULL))
			{
				//mycolour.inherit(Parent->mycolour);
			}
	pilot(const vector<string>& FilePilot):
		myrandom(random::getinstance()),
		preferences(NULL),
		mysteering(),
		mycolour(),
		score(0.0),

		orders(NULL),
		seektarget(),
		fleetarget(),
		arrivetarget(),
		topprioritytarget(),

		gravitateplace(),
		singlepath(),
		loopedpath(),
		singlepathvalid(false),
		loopedpathvalid(false),
		singlepathlinenumber(0),
		loopedpathlinenumber(0),


		mygrid(NULL),//TODO: implement

		myship(),
		mymothership(NULL),
		myfsm(),

		emotionalstate(NULL),
		decpreferences(NULL),
		age(0),
		generation(0),
		myastar(),
		laser(0.0, 0.0, 0.0),
		born(time(NULL))
	{
		for(unsigned int i=0;i<FilePilot.size();i++)
		{
			if(FilePilot.at(i).find("mycolour")==0)
				//if(FilePilot.at(i).find("~mycolour")==string::npos)
			{
				//cout<<"building mycolour"<<endl<<flush;
				for(unsigned int j=i;j<FilePilot.size();j++)
				{
					if(FilePilot.at(j).find("~mycolour")==0)
					{
						//cout<<"built mycolour"<<endl<<flush;
						mycolour=colour(vector<string>(FilePilot.begin()+i+1, FilePilot.begin()+j));
						//cout<<"New colour "<<mycolour.print()<<endl<<flush;
						i=j;
						break;
					}
				}
			}
			if(FilePilot.at(i).find("score")==0)
			{
				//cout<<"building score"<<endl<<flush;
				score=getfloat(FilePilot.at(i));
			}


			if(FilePilot.at(i).find("myfsm")==0)
				//if(FilePilot.at(i).find("~myfsm")==string::npos)
			{
				//cout<<"building myfsm"<<endl<<flush;
				//cout<<"starting myfsm"<<endl<<flush;
				for(unsigned int j=i;j<FilePilot.size();j++)
				{
					//cout<<"."<<flush;
					//cout<<"**"<<FilePilot.at(j)<<"**"<<endl<<flush;
					if(FilePilot.at(j).find("~myfsm")==0)
					{
						//cout<<"built myfsm"<<endl<<flush;
						//cout<<"ready"<<endl<<flush;
						myfsm=fsm(vector<string>(FilePilot.begin()+i+1, FilePilot.begin()+j));
						i=j;
						break;
					}
				}
			}
			if(FilePilot.at(i).find("age")==0)
			{
				//cout<<"building age"<<endl<<flush;
				age=getint(FilePilot.at(i));
			}
			if(FilePilot.at(i).find("shiptype")==0)
			{
				//cout<<"building age"<<endl<<flush;
				myship.setshiptype(getint(FilePilot.at(i)));
			}
			if(FilePilot.at(i).find("generation")==0)
			{
				//cout<<"building age"<<endl<<flush;
				generation=getint(FilePilot.at(i));
			}

			if(FilePilot.at(i).find("myastar")==0)
				//if(FilePilot.at(i).find("~myastar")==string::npos)
			{
				//cout<<"building myastar"<<endl<<flush;
				for(unsigned int j=i;j<FilePilot.size();j++)
				{
					if(FilePilot.at(j).find("~myastar")==0)
					{
						//cout<<"built myastar"<<endl<<flush;
						myastar=astar(vector<string>(FilePilot.begin()+i+1, FilePilot.begin()+j));
						i=j;
						break;
					}
				}
			}
		}
		myfsm.setship(&myship);
	}

	~pilot()
	{
		//cout<<"~pilot()"<<endl<<flush;
		myship.unsetasteroidtarget();
		myship.iamdead();
	}
	//setting up the grid
	void youaredead()
	{//telling the pilot to cleanup
		myship.unsetasteroidtarget();
		myship.iamdead();
	}
	inline
	void setgrid(grid& Grid)
	{
		mygrid=&Grid;
		myastar.setgrid(mygrid);
	}
	inline
	void setgrid(grid* Grid)
	{
		mygrid=Grid;
		myastar.setgrid(mygrid);
	}

	//sets the position of the boid
	inline
	void setposition(const point& NewPosition)
	{
		myship.position=NewPosition;
	}

	inline
	void accelerateme()
	{
		calculateacceleration();
	}

	void calculateacceleration()
	{//function to calculate the steering force
		orders=myfsm.getorders();
		preferences=myfsm.getpreferences();
		decpreferences=myfsm.getdecisionpreferences();
		emotionalstate=myfsm.getemotionalstate();

		if(orders->go)
		{//if the boid is ordered to fly
			myvector newacceleration(0.0, 0.0, 0.0), tmp(0.0, 0.0, 0.0);

			if(preferences->wander())
			{//wandering
				tmp=mysteering.wander(myship.velocity, 45)*=preferences->wanderp;
				if(tmp.isnok())
				{
					cout<<"wander"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->seekingtarget&&preferences->seek())
			{//seeking target
				tmp=mysteering.seek(myship.position, myship.velocity, seektarget.position)*=preferences->seekp;
				if(tmp.isnok())
				{
					cout<<"seektarget"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->seekingtoppriority&&preferences->seek())
			{//top priority seek
				tmp=mysteering.seek(myship.position, myship.velocity, topprioritytarget.position)*=preferences->tpseekp;
				if(tmp.isnok())
				{
					cout<<"seektoppriority"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->seekingtargetship&&preferences->seek())
			{//seeking target ship
				if(myship.shiptarget!=NULL)
				{
					tmp=mysteering.seek(myship.position, myship.velocity, myship.shiptarget->position)*preferences->seekp;
					if(tmp.isnok())
					{
						cout<<"seektargetship"<<endl<<flush;
						exit(0);
					}
					newacceleration+=tmp;
				}
			}
			if(orders->attackboid&&preferences->seek())
			{//attacking another boid
				if(myship.shiptarget!=NULL)
				{
					tmp=mysteering.seek(myship.position, myship.velocity, myship.shiptarget->position)*preferences->seekp;
					if(tmp.isnok())
					{
						cout<<"attackboid"<<endl<<flush;
						exit(0);
					}
					newacceleration+=tmp;
				}
			}
			if(preferences->flee())
			{//fleeing
				tmp=mysteering.flee(myship.position, myship.velocity, fleetarget.position);
				if(tmp.isnok())
				{
					cout<<"flee"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(preferences->arrive())
			{//arriving
				tmp=mysteering.arrive(
						myship.position,
						myship.velocity,
						arrivetarget.position,
						preferences->arriveslowingdistance//,
						//preferences->arrivefcoeff
						)*=preferences->arrivep;
				if(tmp.isnok())
				{
					cout<<"arrive"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->loopedpathfollow&&preferences->follow()&&loopedpathvalid)
			{//following a looped path
				tmp=mysteering.followpathsegment
						(
							myship.position,
							myship.velocity,
							loopedpath.givesegmentloop(loopedpathlinenumber),
							preferences->followmaxdistance
						)*=preferences->followp;
				if(tmp.isnok())
				{
					cout<<"loopedpathfollow"<<endl<<flush;
					cout<<"boid position: ";
					myship.position.printme();
					cout<<"force: ";
					tmp.printme();

					loopedpath.givesegmentloop(loopedpathlinenumber).printme();
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->singlepathfollow&&preferences->follow()&&singlepathvalid)
			{//following a single path
				tmp=mysteering.followpathsegment
						(
							myship.position,
							myship.velocity,
							singlepath.givesegment(singlepathlinenumber),
							preferences->followmaxdistance
						)*=preferences->followp;
				if(tmp.isnok())
				{
					cout<<"singlepathfollow"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->gravitateplace&&preferences->gravitateplace())
			{//gravitating in place
				tmp=mysteering.gravitate
					(
						myship.position,
						myship.velocity,
						gravitateplace.position,
						preferences->gravitateplacemaxdistance
					)*=preferences->gravitateplacep;
				if(tmp.isnok())
				{
					cout<<"gravitateplace"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if(orders->gravitatemothership&&preferences->gravitateplace())
			{//gravitating in place
				tmp=mysteering.gravitate
					(
						myship.position,
						myship.velocity,
						mymothership->position,
						preferences->gravitateplacemaxdistance
					)*=preferences->gravitateplacep;
				if(tmp.isnok())
				{
					cout<<"gravitatemothership"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}


			if (mygrid!=NULL)if(preferences->separation()
									||preferences->alignment()
										||preferences->cohesion()
											||preferences->avoid())
			{//operations requiring the grid
				//vector<ship*> nearestships=mygrid->findfriendlyships(myship.position, myship.rangeofsight);
				vector<pair<colour, ship*> > nearestships=mygrid->findships(myship.position, myship.rangeofsight);
				if(nearestships.size()>1)
				{//if there are any other ships nearby
					myvector avgvelocity(0.0, 0.0, 0.0);
					point avgposition(0.0, 0.0, 0.0);
					for(unsigned int i=0;i<nearestships.size(); i++)
					{
						//TODO: distinguish friendly form enemy
						if(nearestships.at(i).second->velocity.isnok())
						{
							cout<<"Bad velocity at"<<nearestships.at(i).second<<endl<<flush;
							nearestships.at(i).second->velocity.printme();
						}
						if((mymothership==NULL)||(nearestships.at(i).first==mymothership->mycolour))avgvelocity+=nearestships.at(i).second->velocity;
						if(nearestships.at(i).second->position.isnok())
						{
							cout<<"Bad position at"<<nearestships.at(i).second<<endl<<flush;
							nearestships.at(i).second->position.printme();
						}
						//avoiding them
						if((mymothership==NULL)||(nearestships.at(i).first==mymothership->mycolour))avgposition+=nearestships.at(i).second->position;
						tmp=
								mysteering.avoidcolision(myship.position, myship.boundingradius,
										nearestships.at(i).second->position,
											nearestships.at(i).second->boundingradius,
													preferences->avoidtriggerdistance)
											*=preferences->avoidp;
						if(tmp.isnok())
						{
							cout<<"avoidcolision"<<endl<<flush;
							cout<<"boid position: ";
							myship.position.printme();
							cout<<"force: ";
							tmp.printme();
						}
						newacceleration+=tmp;
						//TODO: move to decision making
						if(mymothership!=NULL)if(nearestships.at(i).first!=mymothership->mycolour)
						{
							//cout<<"emotionalstate->changefear(1.0/(nearestships.at(i).second->position.distanceto(myship.position)));"<<endl<<flush;
							emotionalstate->changeanger(1.0/(nearestships.at(i).second->position.distanceto(myship.position)));
							emotionalstate->changefear(1.0/(nearestships.at(i).second->position.distanceto(myship.position)));
						}
					}
					avgvelocity/=nearestships.size();
					avgposition/=nearestships.size();
					if(preferences->separation())
					{//separation
						tmp=
								mysteering.separation(myship.position, myship.velocity,avgposition)
								*=preferences->separationp;
						if(tmp.isnok())
						{
							cout<<"avgvelocity: ";
							avgvelocity.printme();
							cout<<"avgposition: ";
							avgposition.printme();
							cout<<"nearestships.size(): "<<nearestships.size()<<endl<<flush;
							cout<<"separation"<<endl<<flush;
							cout<<"boid position: ";
							myship.position.printme();
							cout<<"force: ";
							tmp.printme();
						}
						newacceleration+=tmp;
					}
					if(preferences->alignment())
					{//alignment
						tmp=
								mysteering.alignment(myship.velocity, avgvelocity)
								*=preferences->alignmentp;
						if(tmp.isnok())
						{
							cout<<"avgvelocity: ";
							avgvelocity.printme();
							cout<<"avgposition: ";
							avgposition.printme();
							cout<<"nearestships.size(): "<<nearestships.size()<<endl<<flush;
							cout<<"alignment"<<endl<<flush;
							cout<<"boid position: ";
							myship.position.printme();
							cout<<"force: ";
							tmp.printme();
							exit(0);
						}
						newacceleration+=tmp;
					}
					if(preferences->cohesion())
					{//cohesion
						tmp=
								mysteering.cohesion(myship.position, myship.velocity,avgposition)
								*=preferences->cohesionp;
						if(tmp.isnok())
						{
							cout<<"avgvelocity: ";
							avgvelocity.printme();
							cout<<"avgposition: ";
							avgposition.printme();
							cout<<"nearestships.size(): "<<nearestships.size()<<endl<<flush;
							cout<<"cohesion"<<endl<<flush;
							cout<<"boid position: ";
							myship.position.printme();
							cout<<"force: ";
							tmp.printme();
							exit(0);
						}
						newacceleration+=tmp;
					}
				}
				vector<asteroid*> nearestasteroids=mygrid->findasteroids(myship.position, myship.rangeofsight);
				for(unsigned int i=0;i<nearestasteroids.size();i++)
				{//avoiding asteroids
					tmp=
							mysteering.avoidcolision(myship.position, myship.boundingradius,
								nearestasteroids.at(i)->position,
									nearestasteroids.at(i)->radius,
										preferences->avoidasteroidtriggerdistance)
												*=preferences->avoidasteroidp;
					if(tmp.isnok())
					{
						cout<<"avoidcolision for asteroids"<<endl<<flush;
						cout<<"boid position: ";
						myship.position.printme();
						cout<<"force: ";
						tmp.printme();
					}
					newacceleration+=tmp;
				}
			}
			if(orders->dockwithmothership&&mymothership)
			{//docking with mothership to unload cargo
				tmp=mysteering.seek(myship.position, myship.velocity, mymothership->position, mymothership->boundingradius+myship.boundingradius+preferences->mothershipdockradius)*=preferences->seekp;
				if(tmp.isnok())
				{
					cout<<"dockwithmothership"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if((orders->dockwithasteroid)&&(myship.asteroidtarget!=NULL))
			{//docing with asteroid to mine
				tmp=mysteering.seek(myship.position,
						myship.velocity,
						myship.asteroidtarget->position,
						myship.asteroidtarget->radius+myship.boundingradius+preferences->asteroiddockradius
						)*=preferences->seekp;
				if(tmp.isnok())
				{
					cout<<"dockwithasteroid"<<endl<<flush;

					if(myship.position.isnok())cout<<"myship.position"<<endl<<flush;
					if(myship.velocity.isnok())cout<<"myship.velocity"<<endl<<flush;
					if(myship.asteroidtarget->position.isnok())
					{
						cout<<"myship.asteroidtarget->position"<<endl<<flush;
						myship.asteroidtarget->position.printme();
					}

					if(isnok(myship.asteroidtarget->volume))cout<<"myship.asteroidtarget->volume"<<endl<<flush;
					if(isnok(myship.boundingradius))cout<<"myship.boundingradius"<<endl<<flush;
					if(isnok(preferences->asteroiddockradius))cout<<"preferences->asteroiddockradius"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}
			if((orders->protectharvester)&&(preferences->gravitateplace())&&(myship.shiptoprotect!=NULL))
			{//gravitate around harvester
				tmp=mysteering.gravitate
				(
					myship.position,
					myship.velocity,
					myship.shiptoprotect->position,
					preferences->gravitateplacemaxdistance
				)*=preferences->gravitateplacep;
				if(tmp.isnok())
				{
					cout<<"protectharvester"<<endl<<flush;
					exit(0);
				}
				newacceleration+=tmp;
			}



			if (newacceleration.getsquaredmagnitude()>1.0)newacceleration.normaliseme();
			myship.setacceleration(newacceleration);
		}
		else
		{//stopping the ship if the orders are not to fly
			myship.setacceleration(mysteering.stop(myship.velocity));
		}
	}


	void arrived()
	{
		myfsm.checkstatechange();
		orders=myfsm.getorders();
		preferences=myfsm.getpreferences();
		decpreferences=myfsm.getdecisionpreferences();
		emotionalstate=myfsm.getemotionalstate();
		age++;
		score+=AGEWEIGHT;
		score+=myship.getreward();

		if ((orders->loopedpathfollow)&&loopedpathvalid)
			if (loopedpath.givesegmentloop(loopedpathlinenumber)
					.distancetoplane(myship.position)<preferences->followgoalprecision)
		{//moving to the next point in the path
			loopedpathlinenumber++;
		}
		if ((orders->singlepathfollow)&&singlepathvalid)
			if (singlepath.givesegment(singlepathlinenumber)
					.distancetoplane(myship.position)<preferences->followgoalprecision)
		{//moving to the next point in the path
			singlepathlinenumber++;
			if(singlepathlinenumber==singlepath.size()-1)
			{
				singlepathvalid=false;
				myship.setendofpathreached();
			}
		}
		if((orders->dockwithmothership)&&(mymothership!=NULL))
		{//docking with mothership
			if(myship.docked()!=true)
			{
				if(myship.position.distanceto(mymothership->position)<
						(myship.boundingradius+mymothership->boundingradius+DOCKINGLINELENGTH))
				{//starting to dock
					myship.dock(mymothership->position);
				}
			}
			else
			{
				float unloaded=mymothership->loadresources(myship.unload());
				for(unsigned int i=0;i<myship.shipsprotectingme.size();i++)
				{
					if(myship.shipsprotectingme.at(i)!=NULL)
					{//rewarding proteting ships
						myship.shipsprotectingme.at(i)->addreward(unloaded);
					}
				}
				score+=unloaded;
				myship.heal();
			}
		}
		if(orders->undock)
		{//undocking asteroid or mothership
			if(myship.undocked()!=true)
			{
				myship.undock();
			}
		}
		if((orders->dockwithasteroid)&&(myship.asteroidtarget!=NULL))
		{//docking with asteroid
			if(myship.docked()!=true)
			{
				if(myship.position.distanceto(myship.asteroidtarget->position)<
					(myship.boundingradius+myship.asteroidtarget->radius+DOCKINGLINELENGTH))
				{//starting to dock
					myship.dock(myship.asteroidtarget->position);
				}
			}
			else
			{//ship is gathering resources
				float loaded=myship.loadfromtargetasteroid();
				for(unsigned int i=0;i<myship.shipsprotectingme.size();i++)
				{//rewarding protecting ships
					if(myship.shipsprotectingme.at(i)!=NULL)
					{
						myship.shipsprotectingme.at(i)->addreward(loaded*HARVESTEDREWARD);
					}
				}
				score+=loaded*HARVESTEDREWARD;
			}
		}
		if((orders->lookforasteroid)&&(mygrid!=NULL))
		{//finding the asteroid

			myship.setasteroidtarget(mygrid->findbestasteroid
					(myship,
						decpreferences->asteroidcolourweight,
							decpreferences->asteroiddistanceweight,
									decpreferences->maxboidsququetoasteroid,
										decpreferences->infiniteasteroidweight));
			if(myship.asteroidtarget!=NULL)
			{
				setsinglepath(myastar.findpath(myship.position, myship.asteroidtarget->position));
				myship.unsetendofpathreached();
				myship.setpath();
			}
		}
		if((orders->lookformothership)&&(mymothership!=NULL)&&(mygrid!=NULL))
		{//finding the asteroid
			setsinglepath(myastar.findpath(myship.position, mymothership->position));
			myship.unsetendofpathreached();
			myship.setpath();
		}
		if((orders->lookforboid)&&(mygrid!=NULL))
		{//looking for another boid to attack
			myship.setshiptarget(mygrid->findclosestenemyship(myship.position, mymothership->mycolour, decpreferences->maxboidsququetoenemy));
		}
		if(orders->defendyourself)//if the ships is told to defend itself
		{
			if(myship.shipstargetingme.empty()==false)//if there are any ships targeting this ship
			{
				//the ship attacks random attacker
				myship.setshiptarget(myship.shipstargetingme.at(myrandom->randomunsignedint(myship.shipstargetingme.size())));
			}
		}
		if(orders->attackboid)
		{//attacking another boid
			if(myship.shiptarget!=NULL)
			{
				if(myship.position.distanceto(myship.shiptarget->position)<LASERRANGE)//if enemy ship is close enough to fire
				if(myvector(myship.position, myship.shiptarget->position).angle(myship.velocity)<LASERSPREAD)//if the angle is correct
				{
					laser(myship.position, myship.shiptarget->position);//setting the laser shot
					if(myship.shiptarget->makehit(myship.position))//if enemy ship was killed by the shot (true)
						score+=SHIPKILLEDWEIGHT;//the pilot scores
				}
			}
		}//lookforharvester, protectharvester
		if(orders->lookforharvester&&mygrid)
		{//looking for harvester to protect
			myship.setfriendlyshiptarget(mygrid->findclosestharvester(myship.position, mymothership->mycolour, decpreferences->maxboidsququetoharvester));
			if(myship.shiptoprotect==NULL)
			{//if there is no free harvester, the pilot gets angry
				emotionalstate->changeanger(NOHARVESTERANGER);
			}
		}
		if((orders->protectharvester)&&(myship.shiptoprotect!=NULL))
		{//looking for another boid attacking harvester
			if(myship.shiptarget==NULL)if(myship.shiptoprotect->shipstargetingme.size()!=0)
			{//a ship is attacking the harvester, it needs to be destroyed
				myship.setshiptarget//setting new target
				(myship.shiptoprotect->shipstargetingme.at//one of the attackers
						(myrandom->randomunsignedint(myship.shiptoprotect->shipstargetingme.size())));//chosen at random
			}
		}
		if(myship.shiptarget!=NULL)
		{//getting revved up before attacking
			emotionalstate->changeanger(1.0);
		}
		if(myship.shipstargetingme.empty()==false)
		{//fearing incoming ships
			emotionalstate->changefear(1.0*myship.shipstargetingme.size());
			//cout<<"emotionalstate->changefear(myship.shipstargetingme.size());"<<endl<<flush;
		}
		if(myship.shipsprotectingme.empty()==false)
		{//feeling safer around friendly ships
			//cout<<"emotionalstate->changefear(myship.shipsprotectingme.size());"<<endl<<flush;
			emotionalstate->lowerfear(1.0*myship.shipsprotectingme.size());
		}
		if(myship.shiptoprotect!=NULL)
		{
			if(myship.shiptoprotect->asteroidtarget!=NULL)
			{
				//if the harvester the ship is protecting is getting ready to harvest an asteroid
				//and enemy ships also want that asteroid, the boid gets angry
				emotionalstate->changeanger(1.0*(myship.shiptoprotect->asteroidtarget->lockeduis()
					-myship.shiptoprotect->asteroidtarget->lockedui(myship.shiptoprotect->mothershipcolour)));
			}
		}
		if(mymothership!=NULL)
		{//feeling safer around mothership
			//cout<<"emotionalstate->changefear(myship.position.distanceto(mymothership->position));"<<endl<<flush;
			emotionalstate->lowerfear(1.0/myship.position.distanceto(mymothership->position));
		}
		emotionalstate->cooldown();//cooling emotions down
	}
	inline
	void setloopedpath(const path& Path)
	{//setting the looped path
		loopedpathvalid=true;
		loopedpath.clear();
		loopedpath=Path;
		loopedpathlinenumber=singlepath.giveclosestpathsegmentnumber(myship.position);
		myship.setpath();
	}
	inline
	void setsinglepath(const path& Path)
	{//setting the single path
		singlepathvalid=true;
		singlepath.clear();
		singlepath=Path;
		singlepathlinenumber=0;//singlepath.giveclosestpathsegmentnumber(myship.position);
		myship.setpath();
	}
	inline
	void setgravitatetarget(const target& Target)
	{//setting gravitate target
		gravitateplace=Target;
	}





	inline
	void setaccelerationstep(unsigned int AccelerationStep=1)
	{//sets the acceleration step of the ship
		myship.setaccelerationstep(AccelerationStep);
	}
	inline
	void moveme(const unsigned int & AverageAccelerationOverFrames=1)
	{//moves the ship
		orders=myfsm.getorders();

		//two special movements for docking
		if((orders->dockwithmothership)&&(mymothership!=NULL))
		{
			myship.dockingmoveme(mymothership->velocity*mymothership->speed);
		}
		else if((orders->dockwithasteroid)&&(myship.asteroidtarget!=NULL))
		{
			myship.dockingmoveme(myship.asteroidtarget->velocity);
		}
		//normal movement
		else myship.moveme(AverageAccelerationOverFrames);
	}
	inline
	void drawme(const unsigned int& ShipDrawingMode=1, const unsigned int& PilotDrawingMode=1)
	{//draws the boid
		static colour lasercolour(1.0, 1.0, 1.0);
		myship.drawme(ShipDrawingMode);
		lasercolour.setcolour();
		laser.drawme(myship.position);//drawing laser shot
		laser.setmymagnitude(0.0);//clearing laser shot
		if(PilotDrawingMode%2==0)if(singlepathvalid&&myship.ispathset())singlepath.drawme(1);
	}

	void printme()const
	{//prints boid information
		cout<<"Pilot"<<endl;
		cout<<"My ship:"<<endl;
		myship.printme();
		cout<<"My preferences:"<<endl;
		preferences->printme();
		cout<<endl<<flush;
	}
	string print()const
	{
		char Chars[100];
		string anwser("\npilot");
		sprintf(Chars, "%ld", born);
		anwser+=string("\nborn\t")+Chars;

		sprintf(Chars, "%i", myship.shiptype);
		anwser+=string("\nshiptype\t")+Chars;

		if(PILOTSPEAK)cout<<"mycolour"<<endl<<flush;

		anwser+=string("\nmycolour");
		anwser+=mycolour.print();
		anwser+=string("\n~mycolour");

		if(PILOTSPEAK)cout<<"score"<<endl<<flush;

		sprintf(Chars, "%f", score);
		anwser+=string("\nscore\t")+Chars;

		if(PILOTSPEAK)cout<<"myfsm"<<endl<<flush;


		anwser+=string("\nmyfsm");
		anwser+=myfsm.print();
		anwser+=string("\n~myfsm");

		if(PILOTSPEAK)cout<<"age"<<endl<<flush;


		sprintf(Chars, "%i", age);
		anwser+=string("\nage\t")+Chars;
		sprintf(Chars, "%i", generation);
		anwser+=string("\ngeneration\t")+Chars;

		if(PILOTSPEAK)cout<<"myastar"<<endl<<flush;



		anwser+=string("\nmyastar");
		anwser+=myastar.print();
		anwser+=string("\n~myastar");

		anwser+=string("\n~pilot\n");
		return anwser;
	}
	bool operator==(const pilot& Other)const
	{
		return(//(mycolour==Other.mycolour)
				//&&
				(score==Other.score)
				&&
				(myfsm==Other.myfsm)
				&&
				(age==Other.age)
				&&
				(generation==Other.generation)
				&&
				(myastar==Other.myastar)
				);
	}
	pilot& operator()(const pilot& Parent, const bool& Evolve=false)
	{//inheritance
		preferences=NULL;
		mycolour(Parent.mycolour, Evolve);
		score=0.0;

		emotionalstate=NULL;
		decpreferences=NULL;
		myfsm(Parent.myfsm, &myship, Evolve);
		//myfsme.setship(&myship);
		age=0;
		generation=Parent.generation+1;

		return *this;
	}
	inline
	void setmothership(mothership* Mothership)
	{//sets the mothership
		mymothership=Mothership;
	}
	inline
	void setmyfsm(const fsm& FSM)
	{//sets the FSM
		myfsm(FSM, &myship);
		//myfsme.setship(&myship);
	}
	inline
	float givescore()const
	{//returns pilot's score
		return score;
	}
	inline
	void setastar(const astar& NewAstar)
	{
		myastar=NewAstar;
	}
	inline
	void setshiptype(const unsigned int& Type=0)
	{
		myship.setshiptype(Type);
	}

	static
	bool unittest();

	static
	pilot examplepilot();


	static
	pilot examplepilot2();

	static
	pilot examplefighter();
	static
	pilot examplefighter2();


	static
	pilot exampleangrypilot();


	static
	pilot exampleminer();

	static
	pilot exampleminer2();
	static
	pilot exampleminer3();

};
class comparepilots
{//a class to compare two pilots based on ther score
public:
	comparepilots()
	{
	}
	~comparepilots()
	{
	}
	inline
	bool operator()(const pilot& One, const pilot& Two)const
	{
		return One.score<Two.score;
	}
};
struct comparepilotpointers
{//a class to compare poiners to pilots
public:
	comparepilotpointers()
	{
	}
	~comparepilotpointers()
	{
	}
	inline
	bool operator()(const pilot* One, const pilot* Two)const
	{
		return One->score<Two->score;
	}
};
//a function to compare pilot pointers
bool comparepilotpointersf(const pilot*, const pilot*);

#endif /* PILOT_H_ */
