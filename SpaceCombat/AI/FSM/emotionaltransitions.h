#ifndef EMOTIONALTRANSITIONS_H_
#define EMOTIONALTRANSITIONS_H_

#include <string>
#include <vector>
#include "../emotions.h"
#include "../../map.h"
#include "../../math.h"
using namespace std;

#define STARTINGTRIGGER 100.0 //how high an emotion has to be in order to trigger switch
#define ENDINGTRIGGER 80.0 //how low an emotion has to be in order to trigger switch
#define DIFFERENCESWITCH 50.0 //what the difference between two emotions must be in order to trigger the switch


inline
bool switchtofearfromcontempt
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if(EmotionalState->fearlevel>STARTINGTRIGGER) return true;
	return false;
}
inline
bool switchtoangerfromcontempt
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if(EmotionalState->angerlevel>STARTINGTRIGGER) return true;
	return false;
}
inline
bool switchtofearfromanger
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->fearlevel>(EmotionalState->angerlevel+DIFFERENCESWITCH)) return true;
	return false;
}
inline
bool switchtoangerfromfear
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->angerlevel>(EmotionalState->fearlevel+DIFFERENCESWITCH)) return true;
	return false;
}



/*
inline
bool switchtofearfromcontempt
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->fearlevel>EmotionalState->angerlevel)
		if(EmotionalState->fearlevel>STARTINGTRIGGER) return true;
	return false;
}
inline
bool switchtoangerfromcontempt
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->angerlevel>EmotionalState->fearlevel)
		if(EmotionalState->angerlevel>STARTINGTRIGGER) return true;
	return false;
}
inline
bool switchtofearfromanger
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->fearlevel>(EmotionalState->angerlevel+DIFFERENCESWITCH)) return true;
	if (EmotionalState->angerlevel<ENDINGTRIGGER) if(EmotionalState->fearlevel>STARTINGTRIGGER) return true;
	return false;
}
inline
bool switchtoangerfromfear
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->angerlevel>(EmotionalState->fearlevel+DIFFERENCESWITCH)) return true;
	if (EmotionalState->fearlevel<ENDINGTRIGGER) if(EmotionalState->angerlevel>STARTINGTRIGGER) return true;
	return false;
}*/
inline
bool switchtocontemptfromanger
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->angerlevel<ENDINGTRIGGER) return true;
	return false;
}
inline
bool switchtocontemptfromfear
(
	const ship* Ship,
	const emotions* EmotionalState
)
{
	if (EmotionalState->fearlevel<ENDINGTRIGGER) return true;
	return false;
}
inline
vector<pair<bool(*)(const ship*, const emotions*), string> > giveemotionaltransitionsvector()
{
	vector<pair<bool(*)(const ship*, const emotions*), string> >anwser;

	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtofearfromcontempt, string("switchtofearfromcontempt")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtoangerfromcontempt, string("switchtoangerfromcontempt")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtofearfromanger, string("switchtofearfromanger")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtoangerfromfear, string("switchtoangerfromfear")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtocontemptfromanger, string("switchtocontemptfromanger")));
	anwser.push_back(pair<bool(*)(const ship*, const emotions*), string>
		(switchtocontemptfromfear, string("switchtocontemptfromfear")));

	return anwser;
}

#endif /* EMOTIONALTRANSITIONS_H_ */
