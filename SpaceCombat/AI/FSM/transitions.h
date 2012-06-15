#ifndef TRANSITIONS_H_
#define TRANSITIONS_H_

//a set of functions used for changing states

//#include "state.h"
#include <vector>
#include <string>
#include "../emotions.h"
#include "../../map.h"
#include "../../math.h"
#include "../decisionpreferences.h"

using namespace std;


inline
bool shipnotbeingtargeted
(//whether the ship is not targeted by another ship
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shipstargetingme.empty()==false) return false;
	return true;
}
inline
bool shipbeingtargeted
(//whether the ship is targeted by another ship
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shipstargetingme.empty()==true) return false;
	return true;
}
inline
bool friendlyshiptargeted
(//whether the ship has another ship targeted
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shiptoprotect==NULL) return false;
	return true;
}
inline
bool friendlyshipnottargeted
(//whether the ship has another ship targeted
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shiptoprotect==NULL) return true;
	return false;
}
inline
bool shiphealthy
(//whether the ship is healthy
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->health==100.0;
}
inline
bool shipdamaged
(//whether the ship is damaged
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->health<100.0;
}
inline
bool shipfull
(//whether the ship is full
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	static float fullness;
	fullness=Ship->howfull();
	if (fullness<DecisionPrefs->minloadp) return false;
	if (fullness>DecisionPrefs->maxloadp) return true;
	return (random::getinstance()->randomfloatbetween(DecisionPrefs->minloadp, DecisionPrefs->maxloadp)<=fullness);
}
inline
bool shipempty
(//whether the ship is empty
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->isempty();
}
inline
bool shipdocked
(//whether the ship is completely docked
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->docked();
}
inline
bool shipundocked
(//whether the ship is completely undocked
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->undocked();
}
inline
bool asteroidtargeted
(//whether the ship has targeted an asteroid
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->asteroidtarget==NULL) return false;
	return true;
}
inline
bool asteroidnottargeted
(//whether the ship does not have an asteroid tatget
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->asteroidtarget==NULL) return true;
	return false;
}
inline
bool shiptargeted
(//whether the ship has another ship targeted
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shiptarget==NULL) return false;
	return true;
}
inline
bool shipnottargeted
(//whether the ship has another ship targeted
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->shiptarget==NULL) return true;
	return false;
}
inline
bool asteroidempty
(//whether the asteroid the ship has targeted is empty
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	if(Ship->asteroidtarget==NULL) return true;
	return Ship->asteroidtarget->empty();
}
inline
bool returntrue
(//always true
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return true;
}
inline
bool returnfalse
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return false;
}
inline
bool endofpathreached
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->wasendofpathreached();
}
inline
bool endofpathnotreached
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return !Ship->wasendofpathreached();
}
inline
bool shippathset
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return Ship->ispathset();
}
inline
bool shippathnotset
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences* DecisionPrefs
)
{
	return !Ship->ispathset();
}
inline
vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string> > givetransitionsvector()
{
	vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string> > anwser;
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(friendlyshipnottargeted, string("friendlyshipnottargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(friendlyshiptargeted, string("friendlyshiptargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shiphealthy, string("shiphealthy")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipdamaged, string("shipdamaged")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipfull, string("shipfull")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipempty, string("shipempty")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipdocked, string("shipdocked")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipundocked, string("shipundocked")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(asteroidtargeted, string("asteroidtargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(asteroidnottargeted, string("asteroidnottargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shiptargeted, string("shiptargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipnottargeted, string("shipnottargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(asteroidempty, string("asteroidempty")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(returntrue, string("returntrue")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(returnfalse, string("returnfalse")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(endofpathreached, string("endofpathreached")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(endofpathnotreached, string("endofpathnotreached")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shippathset, string("shippathset")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shippathnotset, string("shippathnotset")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipnotbeingtargeted, string("shipnotbeingtargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences*), string>
	(shipbeingtargeted, string("shipbeingtargeted")));
	return anwser;
}

#endif //TRANSITIONS_H_


