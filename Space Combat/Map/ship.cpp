#include "ship.h"

vector<pair<void (ship::*)(void), string> >  givetransitiontasks()
{
	vector<pair<void (ship::*)(void), string> >  anwser;
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::jettison, string("jettison")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::setpath, string("setpath")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::unsetpath, string("unsetpath")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::resetdockingline, string("resetdockingline")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::setendofpathreached, string("setendofpathreached")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::unsetendofpathreached, string("unsetendofpathreached")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::unsetasteroidtarget, string("unsetasteroidtarget")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::healall, string("healall")));
	anwser.push_back(pair<void (ship::*)(void), string>
	(&ship::untarget, string("untarget")));

	return anwser;
}
