//a set of functions used for changing states

#include "transitions.h"

using namespace std;

/*
inline
bool shipfull
(//whether the ship is full
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	static float fullness;
	fullness=Ship->howfull();
	if (fullness<DecisionPrefs.minloadp) return false;
	if (fullness>DecisionPrefs.maxloadp) return true;
	return (random::getinstance()->randomfloatbetween(DecisionPrefs.minloadp, DecisionPrefs.maxloadp)<=fullness);
}
inline
bool shipempty
(//whether the ship is empty
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return Ship->isempty();
}
inline
bool shipdocked
(//whether the ship is completely docked
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return Ship->docked();
}
inline
bool shipundocked
(//whether the ship is completely undocked
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return Ship->undocked();
}
inline
bool asteroidtargeted
(//whether the ship has targeted an asteroid
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
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
	const decisionpreferences& DecisionPrefs
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
	const decisionpreferences& DecisionPrefs
)
{
	if(Ship->shiptarget==NULL) return false;
	return true;
}
inline
bool asteroidempty
(//whether the asteroid the ship has targeted is empty
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
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
	const decisionpreferences& DecisionPrefs
)
{
	return true;
}
inline
bool returnfalse
(//always false
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return false;
}
inline
bool endofpathreached
(
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return Ship->wasendofpathreached();
}
inline
bool endofpathnotreached
(
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return !Ship->wasendofpathreached();
}
inline
bool shippathset
(
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return Ship->ispathset();
}
inline
bool shippathnotset
(
	const ship* Ship,
	const emotions* EmotionalState,
	const decisionpreferences& DecisionPrefs
)
{
	return !Ship->ispathset();
}*/
/*
inline
vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string> > givetransitionsvector()
{
	vector<pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string> > anwser;
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shipfull, string("shipfull")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shipempty, string("shipempty")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shipdocked, string("shipdocked")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shipundocked, string("shipundocked")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(asteroidtargeted, string("asteroidtargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(asteroidnottargeted, string("asteroidnottargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shiptargeted, string("shiptargeted")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(asteroidempty, string("asteroidempty")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(returntrue, string("returntrue")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(returnfalse, string("returnfalse")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(endofpathreached, string("endofpathreached")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(endofpathnotreached, string("endofpathnotreached")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shippathset, string("shippathset")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*, const decisionpreferences&), string>
	(shippathnotset, string("shippathnotset")));
	return anwser;
}*/
