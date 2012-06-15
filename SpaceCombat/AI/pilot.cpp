#include "pilot.h"

bool comparepilotpointersf(const pilot* One, const pilot* Two)
{
	return One->score>Two->score;
}

pilot pilot::examplepilot()
{
	fsm tmpfsm;
	fsme defaultfsme("Default");
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
			orders);
	tmpstate.connectto(string("Dock with Mothership"), shipfull);
	tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setdockwithmothership(true);

	defaultfsme.setname("Default");

	tmpstate=state(string("Dock with Mothership"),
			orders);
	tmpstate.connectto(string("Undock from Mothership"), shipempty);

	defaultfsme.addstate(tmpstate);

	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock from Mothership"),
			orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setlookforasteroid(true);

	tmpstate=state(string("Look for Asteroid"),
			orders);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
	tmpstate.connectto(string("Decide what to do"), asteroidempty);
	tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setdockwithasteroid(true);

	tmpstate=state(string("Dock with Asteroid"),
			orders);
	tmpstate.connectto(string("Undock Asteroid"), shipfull);
	tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
	tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock Asteroid"),
			orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);



	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);


	tmpfsm.addfsme(defaultfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(0.1, 0.2, 0.3));

	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;

	/*
	tmp.score=0.1;
	tmp.age=10;
	tmp.generation=7;
	*/
	return tmp;
}




bool pilot::unittest()
{
	pilot tmp=examplefighter();

	pilot tmp2(separatestrings(tmp.print()));
	if(tmp==tmp2)
	{
		return true;
	}
	if(tmp.mycolour!=tmp2.mycolour)
	{
		cout<<"Colours"<<endl<<flush;
		cout<<"1:"<<tmp.mycolour.print()<<endl<<"2:"<<tmp2.mycolour.print()<<endl<<flush;
	}
	if(tmp.score!=tmp2.score)
	{
		cout<<"Scores"<<endl<<flush;
		cout<<"1:"<<tmp.score<<endl<<" 2:"<<tmp2.score<<endl<<flush;
	}
	if(tmp.age!=tmp2.age)
	{
		cout<<"Ages"<<endl<<flush;
		cout<<"1:"<<tmp.age<<endl<<" 2:"<<tmp2.age<<endl<<flush;
	}
	if(tmp.myastar!=tmp2.myastar)
	{
		cout<<"MyAstars"<<endl<<flush;
		cout<<"1:"<<tmp.myastar.print()<<endl<<" 2:"<<tmp2.myastar.print()<<endl<<flush;
	}
	if(tmp.myfsm!=tmp2.myfsm)
	{
		cout<<"MyFSM"<<endl<<flush;
		tmp.myfsm.showdifferences(tmp2.myfsm);
		//if(tmp.myfsm.comparefsmes(tmp2.myfsm))cout<<"OK"<<endl<<flush;
		/*cout<<"1:"<<tmp.myfsm.print()<<endl<<flush;
		cout<<" 2:"<<tmp2.myfsm.print()<<endl<<flush;*/
	}
	cout<<"Original"<<endl<<flush;
	cout<<tmp.print()<<endl<<flush;
	cout<<"Copy"<<endl<<flush;
	//cout<<pilot(separatestrings(tmp.print())).print()<<endl<<flush;
	cout<<tmp2.print()<<endl<<flush;
	return false;
}

pilot pilot::examplepilot2()
{
	fsm tmpfsm;
	fsme defaultfsme("Contempt");
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


	tmpstate=state(string("Decide what to do"),	orders);
	tmpstate.connectto(string("Dock with Mothership"), shipfull);
	tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setdockwithmothership(true);

	defaultfsme.setname("Default");

	tmpstate=state(string("Dock with Mothership"),orders);
	tmpstate.connectto(string("Undock from Mothership"), shipempty);

	defaultfsme.addstate(tmpstate);

	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock from Mothership"),orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setlookforasteroid(true);

	tmpstate=state(string("Look for Asteroid"),	orders);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
	tmpstate.connectto(string("Decide what to do"), asteroidempty);
	tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setdockwithasteroid(true);

	tmpstate=state(string("Dock with Asteroid"), orders);
	tmpstate.connectto(string("Undock Asteroid"), shipfull);
	tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
	tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock Asteroid"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);



	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);


	tmpfsm.addfsme(defaultfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(0.1, 0.2, 0.3));

	tmp.setshiptype(0);
	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}

pilot pilot::exampleangrypilot()
{
	//TODO: test
	fsm tmpfsm;
	fsme defaultfsme("Anger");
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;

	defaultsteering.reset();
	defaultsteering.setseek(1.0);
	//defaultsteering.setdockradius(0.6, 0.2);
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
	tmpstate.connectto("Look for Enemy", shipnottargeted);
	tmpstate.connectto("Attack Ship", shiptargeted);


	defaultfsme.addstate(tmpstate);





	orders.reset();
	orders.setgo(true);
	orders.setlookforboid(true);


	tmpstate=state(string("Look for Enemy"),orders);
	tmpstate.connectto("Attack Ship", shiptargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setattackboid(true);


	tmpstate=state(string("Attack Ship"),orders);
	tmpstate.connectto("Decide what to do", shipnottargeted);
	tmpstate.addtransitionouttask(&ship::untarget);//making sure the ship target is dropped, in case emotionchanges


	defaultfsme.addstate(tmpstate);





	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);


	tmpfsm.addfsme(defaultfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(0.1, 0.2, 0.3));

	tmp.setshiptype(1);
	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}

pilot pilot::exampleminer()
{
	//TODO: test
	fsm tmpfsm;
	fsme defaultfsme("Miner Contempt");
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;

	defaultsteering.reset();
	defaultsteering.setseek(1.0);
	defaultsteering.setdockradius(0.6, 0.2);
	defaultsteering.setwander(0.5);
	defaultsteering.setalignment(0.15);
	defaultsteering.setseparation(0.1);
	defaultsteering.setcohesion(0.15);
	defaultsteering.setavoid(0.1, 0.5);
	defaultsteering.setasteroidavoid(0.5, 0.5);
	defaultsteering.setgravitate(0.1, 25.0);



	orders.reset();
	orders.setgo(true);


	tmpstate=state(string("Decide what to do"),	orders);
	tmpstate.connectto(string("Dock with Mothership"), shipfull);
	tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setdockwithmothership(true);

	tmpstate=state(string("Dock with Mothership"), orders);
	tmpstate.connectto(string("Undock from Mothership"), shipempty);

	defaultfsme.addstate(tmpstate);

	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock from Mothership"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setlookforasteroid(true);

	tmpstate=state(string("Look for Asteroid"), orders);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
	tmpstate.connectto(string("Decide what to do"), asteroidempty);
	tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setdockwithasteroid(true);

	tmpstate=state(string("Dock with Asteroid"), orders);
	tmpstate.connectto(string("Undock Asteroid"), shipfull);
	tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
	tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock Asteroid"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);



	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);

	defaultfsme.connectto("Miner Fear", switchtofearfromcontempt);

	defaultfsme.addtransitionouttask(&ship::resetdockingline);
	defaultfsme.addtransitionouttask(&ship::unsetasteroidtarget);

	tmpfsm.addfsme(defaultfsme);




	fsme fearfsme("Miner Fear");



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


	tmpstate=state(string("Decide what to do"), orders);
	tmpstate.connectto(string("Dock with Mothership"), shipdamaged);
	tmpstate.connectto(string("Gravitate Mothership"), shiphealthy);


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

	tmpstate=state(string("Gravitate Mothership"), orders);
	tmpstate.connectto(string("Decide what to do"), shipdamaged);

	fearfsme.addstate(tmpstate);




	fearfsme.setcurrentstate("Decide what to do");
	fearfsme.setdefaultstate("Decide what to do");


	fearfsme.setalldecisions(decprefs);
	fearfsme.setallsteering(defaultsteering);


	fearfsme.connectto("Miner Contempt", switchtocontemptfromfear);

	fearfsme.addtransitionouttask(&ship::resetdockingline);

	tmpfsm.addfsme(fearfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(1.0, 1.0, 1.0), 1);
	tmp.setshiptype(1);

	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}
pilot pilot::exampleminer2()
{
	//TODO: test
	fsm tmpfsm;
	fsme defaultfsme("Miner Contempt");
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;

	defaultsteering.reset();
	defaultsteering.setseek(1.0);
	defaultsteering.setdockradius(0.5, 0.3);
	defaultsteering.setavoid(0.1, 0.5);
	defaultsteering.setasteroidavoid(0.5, 0.5);
	defaultsteering.setgravitate(0.1, 25.0);



	orders.reset();
	orders.setgo(true);


	tmpstate=state(string("Decide what to do"),	orders);
	tmpstate.connectto(string("Dock with Mothership"), shipfull);
	tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setdockwithmothership(true);

	tmpstate=state(string("Dock with Mothership"), orders);
	tmpstate.connectto(string("Undock from Mothership"), shipempty);

	defaultfsme.addstate(tmpstate);

	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock from Mothership"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setlookforasteroid(true);

	tmpstate=state(string("Look for Asteroid"), orders);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
	tmpstate.connectto(string("Decide what to do"), asteroidempty);
	tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setdockwithasteroid(true);

	tmpstate=state(string("Dock with Asteroid"), orders);
	tmpstate.connectto(string("Undock Asteroid"), shipfull);
	tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
	tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock Asteroid"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);



	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);

	defaultfsme.connectto("Miner Fear", switchtofearfromcontempt);

	defaultfsme.addtransitionouttask(&ship::resetdockingline);
	defaultfsme.addtransitionouttask(&ship::unsetasteroidtarget);

	tmpfsm.addfsme(defaultfsme);




	fsme fearfsme("Miner Fear");



	defaultsteering.reset();
	defaultsteering.setseek(1.0);
	defaultsteering.setdockradius(0.6, 0.2);
	defaultsteering.setavoid(0.1, 0.5);
	defaultsteering.setasteroidavoid(0.1, 0.5);
	defaultsteering.setgravitate(0.1, 15.0);



	orders.reset();
	orders.setgo(true);


	tmpstate=state(string("Decide what to do"), orders);
	tmpstate.connectto(string("Dock with Mothership"), shipdamaged);
	tmpstate.connectto(string("Gravitate Mothership"), shiphealthy);


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

	tmpstate=state(string("Gravitate Mothership"), orders);
	tmpstate.connectto(string("Decide what to do"), shipdamaged);

	fearfsme.addstate(tmpstate);




	fearfsme.setcurrentstate("Decide what to do");
	fearfsme.setdefaultstate("Decide what to do");


	fearfsme.setalldecisions(decprefs);
	fearfsme.setallsteering(defaultsteering);


	fearfsme.connectto("Miner Contempt", switchtocontemptfromfear);
	fearfsme.addtransitionouttask(&ship::resetdockingline);

	tmpfsm.addfsme(fearfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(1.0, 1.0, 1.0), 1);

	tmp.setshiptype(1);

	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}
pilot pilot::exampleminer3()
{
	//TODO: test
	fsm tmpfsm;
	fsme defaultfsme("Miner Contempt");
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;

	defaultsteering.reset();
	defaultsteering.setseek(1.0);
	defaultsteering.setdockradius(0.5, 0.3);
	defaultsteering.setavoid(0.1, 0.5);
	defaultsteering.setasteroidavoid(0.5, 0.5);
	defaultsteering.setgravitate(0.1, 25.0);



	orders.reset();
	orders.setgo(true);


	tmpstate=state(string("Decide what to do"),	orders);
	tmpstate.connectto(string("Dock with Mothership"), shipfull);
	tmpstate.connectto(string("Look for Asteroid"), asteroidnottargeted);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);


	defaultfsme.addstate(tmpstate);



	orders.reset();
	orders.setgo(true);
	orders.setdockwithmothership(true);

	tmpstate=state(string("Dock with Mothership"), orders);
	tmpstate.connectto(string("Undock from Mothership"), shipempty);

	defaultfsme.addstate(tmpstate);

	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock from Mothership"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setlookforasteroid(true);

	tmpstate=state(string("Look for Asteroid"), orders);
	tmpstate.connectto(string("Dock with Asteroid"), asteroidtargeted);
	tmpstate.connectto(string("Decide what to do"), asteroidempty);
	tmpstate.connectto(string("Decide what to do"), asteroidnottargeted);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setdockwithasteroid(true);

	tmpstate=state(string("Dock with Asteroid"), orders);
	tmpstate.connectto(string("Undock Asteroid"), shipfull);
	tmpstate.connectto(string("Undock Asteroid"), asteroidempty);
	tmpstate.addtransitionouttask(&ship::unsetasteroidtarget);

	defaultfsme.addstate(tmpstate);


	orders.reset();
	orders.setgo(true);
	orders.setundock(true);

	tmpstate=state(string("Undock Asteroid"), orders);
	tmpstate.connectto(string("Decide what to do"), shipundocked);
	tmpstate.addtransitionouttask(&ship::resetdockingline);

	defaultfsme.addstate(tmpstate);



	defaultfsme.setcurrentstate("Decide what to do");
	defaultfsme.setdefaultstate("Decide what to do");


	defaultfsme.setalldecisions(decprefs);
	defaultfsme.setallsteering(defaultsteering);

	tmpfsm.addfsme(defaultfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(1.0, 1.0, 1.0), 1);

	tmp.setshiptype(1);
	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}
pilot pilot::examplefighter()
{
	//TODO: test
	fsm tmpfsm;
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;


	fsme defaultfsme("Fighter Contempt");

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

	defaultfsme.connectto("Fighter Fear", switchtofearfromcontempt);
	defaultfsme.connectto("Fighter Anger", switchtoangerfromcontempt);

	defaultfsme.addtransitionouttask(&ship::untarget);

	tmpfsm.addfsme(defaultfsme);







	fsme fearfsme("Fighter Fear");



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




	fearfsme.connectto("Fighter Contempt", switchtocontemptfromfear);
	fearfsme.connectto("Fighter Anger", switchtoangerfromfear);


	fearfsme.addtransitionouttask(&ship::untarget);

	tmpfsm.addfsme(fearfsme);




	fsme angerfsme("Fighter Anger");

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


	angerfsme.connectto("Fighter Contempt", switchtocontemptfromanger);
	angerfsme.connectto("Fighter Fear", switchtofearfromanger);


	angerfsme.addtransitionouttask(&ship::untarget);

	tmpfsm.addfsme(angerfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(0.1, 0.2, 0.3));

	tmp.setshiptype(0);
	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}
pilot pilot::examplefighter2()
{
	//TODO: test
	fsm tmpfsm;
	steeringpreferences defaultsteering;
	decisionpreferences decprefs;
	state tmpstate;
	steeringcontrol orders;


	fsme defaultfsme("Fighter Contempt");

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




	defaultfsme.addstate(tmpstate);
	/*tmpstate.connectto("Look for Harvester", friendlyshipnottargeted);
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
*/

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

	//defaultfsme.connectto("Fear", switchtofearfromcontempt);
	defaultfsme.connectto("Fighter Anger", switchtoangerfromcontempt);

	defaultfsme.addtransitionouttask(&ship::untarget);
	defaultfsme.addtransitionintask(&ship::untarget);

	tmpfsm.addfsme(defaultfsme);







	/*fsme fearfsme("Fear");



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

	tmpfsm.addfsme(fearfsme);*/




	fsme angerfsme("Fighter Anger");

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


	angerfsme.connectto("Fighter Contempt", switchtocontemptfromanger);
	//angerfsme.connectto("Fear", switchtofearfromanger);


	angerfsme.addtransitionouttask(&ship::untarget);
	angerfsme.addtransitionintask(&ship::untarget);

	tmpfsm.addfsme(angerfsme);


	pilot tmp(point(0.1, 0.2, 0.3), tmpfsm, colour(0.1, 0.2, 0.3));

	tmp.setshiptype(0);
	tmp.score=0.0;
	tmp.age=0;
	tmp.generation=0;
	return tmp;
}
