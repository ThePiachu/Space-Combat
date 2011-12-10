#ifndef EMOTIONS_H_
#define EMOTIONS_H_

#include "../math.h"
#include "../stringhandling.h"

#define CHANGECAP 10.0

class emotions
{//a function holding the emotions of the boid
public:
	float angerlevel;
	float fearlevel;

	float angerproneness;
	float fearproneness;

	float angercooldown;
	float fearcooldown;

	float emotionalalignment;
	random* myrandom;
	emotions(const float& AngerProneness=1.0, const float& FearProneness=1.0,
			const float& AngerCooldown=0.1, const float& FearCooldown=0.1,
			const float& EmotionalAlignment=0.02):
		angerlevel(0.0),fearlevel(0.0),
		angerproneness(AngerProneness), fearproneness(FearProneness),
		angercooldown(AngerCooldown), fearcooldown(FearCooldown),
		emotionalalignment(EmotionalAlignment),
		myrandom(random::getinstance())
	{
	}
	emotions(const emotions& Other, const bool& Evolve=false):
		angerlevel(0.0),fearlevel(0.0),
		angerproneness(evolve(Other.angerproneness, Evolve)), fearproneness(evolve(Other.fearproneness, Evolve)),
		angercooldown(evolve(Other.angercooldown, Evolve)), fearcooldown(evolve(Other.fearcooldown, Evolve)),
		emotionalalignment(evolve(Other.emotionalalignment, Evolve)),
		myrandom(random::getinstance())
	{
	}
	emotions(const emotions& Other, const bool& Evolve, const bool& SpecialEvolve)://a function for selective evolution
		angerlevel(0.0),fearlevel(0.0),
		angerproneness(evolve(Other.angerproneness, Evolve)), fearproneness(evolve(Other.fearproneness, Evolve)),
		angercooldown(evolve(Other.angercooldown, Evolve)), fearcooldown(evolve(Other.fearcooldown, Evolve)),
		emotionalalignment(evolve(Other.emotionalalignment, Evolve)),
		myrandom(random::getinstance())
	{
	}
	emotions(const vector<string>& FileEmotions):
		angerlevel(0.0),fearlevel(0.0),
		angerproneness(0.0), fearproneness(0.0),
		angercooldown(0.0), fearcooldown(0.0),emotionalalignment(0.0), myrandom(random::getinstance())
	{
		for(unsigned int i=0;i<FileEmotions.size();i++)
		{
			if(FileEmotions.at(i).find("angerproneness")==0)
				angerproneness=getfloat(FileEmotions.at(i));
			if(FileEmotions.at(i).find("fearproneness")==0)
				fearproneness=getfloat(FileEmotions.at(i));
			if(FileEmotions.at(i).find("angercooldown")==0)
				angercooldown=getfloat(FileEmotions.at(i));
			if(FileEmotions.at(i).find("fearcooldown")==0)
				fearcooldown=getfloat(FileEmotions.at(i));
			if(FileEmotions.at(i).find("emotionalalignment")==0)
				emotionalalignment=getfloat(FileEmotions.at(i));
		}
	}
	~emotions()
	{
	}
	string print()const
	{
		char Chars[100];
		string anwser("\nemotions");

		sprintf(Chars, "%f", angerlevel);
		anwser+=string("\nangerlevel\t")+Chars;
		sprintf(Chars, "%f", fearlevel);
		anwser+=string("\nfearlevel\t")+Chars;
		sprintf(Chars, "%f", angerproneness);
		anwser+=string("\nangerproneness\t")+Chars;
		sprintf(Chars, "%f", fearproneness);
		anwser+=string("\nfearproneness\t")+Chars;
		sprintf(Chars, "%f", angercooldown);
		anwser+=string("\nangercooldown\t")+Chars;
		sprintf(Chars, "%f", fearcooldown);
		anwser+=string("\nfearcooldown\t")+Chars;
		sprintf(Chars, "%f", emotionalalignment);
		anwser+=string("\nemotionalalignment\t")+Chars;

		anwser+=string("\n~emotions\n");
		return anwser;
	}
	inline
	bool operator!=(const emotions& Other)const
	{
		return !operator==(Other);
	}

	inline
	bool operator== (const emotions& Other)const
	{//for comparing the base only

		return
		(
			(angerproneness==Other.angerproneness)&&
			(fearproneness==Other.fearproneness)&&

			(angercooldown==Other.angercooldown)&&
			(fearcooldown==Other.fearcooldown)&&
			(emotionalalignment==Other.emotionalalignment)
		);
	}

	emotions& operator= (const emotions& Other)
	{
		angerlevel=Other.angerlevel;
		fearlevel=Other.fearlevel;

		angerproneness=Other.angerproneness;
		fearproneness=Other.fearproneness;

		angercooldown=Other.angercooldown;
		fearcooldown=Other.fearcooldown;
		emotionalalignment=Other.emotionalalignment;
		return *this;
	}
	void inherit(const emotions& Other)
	{
		angerlevel=0.0;
		fearlevel=0.0;
		angerproneness=evolve(Other.angerproneness, true);
		fearproneness=evolve(Other.fearproneness, true);
		angercooldown=evolve(Other.angercooldown, true);
		fearcooldown=evolve(Other.fearcooldown, true);
		emotionalalignment=evolve(Other.emotionalalignment, true);
	}
	float changeanger(float HowMuch)
	{
		HowMuch=cap(HowMuch);
		angerlevel+=HowMuch*angerproneness;
		if(angerlevel<0.0)
		{
			float tmp=-angerlevel;
			angerlevel=0.0;
			return HowMuch*angerproneness-tmp;
		}
		return HowMuch*angerproneness;
	}
	float forcechangeanger(float HowMuch)
	{
		angerlevel+=HowMuch*angerproneness;
		//cout<<"angerlevel "<<angerlevel<<endl<<flush;
		if(angerlevel<0.0)
		{
			float tmp=-angerlevel;
			angerlevel=0.0;
			return HowMuch*angerproneness-tmp;
		}
		return HowMuch*angerproneness;
	}
	float forcechangefear(float HowMuch)
	{
		fearlevel+=HowMuch*fearproneness;
		//cout<<"angerlevel "<<angerlevel<<endl<<flush;
		if(fearlevel<0.0)
		{
			float tmp=-fearlevel;
			fearlevel=0.0;
			return HowMuch*fearproneness-tmp;
		}
		return HowMuch*fearproneness;
	}
	void resetemotions()
	{
		angerlevel=0.0;
		fearlevel=0.0;
	}
	float changefear(float HowMuch)
	{
		HowMuch=cap(HowMuch);
		fearlevel+=HowMuch*fearproneness;
		if(fearlevel<0.0)
		{
			float tmp=-fearlevel;
			fearlevel=0.0;
			return HowMuch*fearproneness-tmp;
		}
		return HowMuch*fearproneness;
	}
	float lowerfear(float HowMuch)
	{
		HowMuch=cap(HowMuch);
		fearlevel-=HowMuch*fearproneness;
		if(fearlevel<0.0)
		{
			float tmp=fearlevel;
			fearlevel=0.0;
			return -HowMuch*fearproneness-tmp;
		}
		return -HowMuch*fearproneness;
	}
	void cooldown()
	{
		cooldownanger();
		cooldownfear();
	}
	float cooldownanger()
	{
		if (angerlevel>0.0)
		{
			angerlevel-=angercooldown;
			if (angerlevel<0.0) angerlevel=0.0;
		}
		return angerlevel;
	}
	float cooldownfear()
	{
		if (fearlevel>0.0)
		{
			fearlevel-=fearcooldown;
			if (fearlevel<0.0) fearlevel=0.0;
		}
		return fearlevel;
	}

	void alignemotions(const emotions& Other)
	{
		angerlevel+=(angerlevel-Other.angerlevel)*emotionalalignment;
		fearlevel+=(fearlevel-Other.fearlevel)*emotionalalignment;
	}
	void alignemotions(const emotions* Other)
	{
		angerlevel+=(angerlevel-Other->angerlevel)*emotionalalignment;
		fearlevel+=(fearlevel-Other->fearlevel)*emotionalalignment;
	}

	emotions& operator()(const emotions& Parent, const bool& Evolve=false)
	{
		angerlevel=0.0;
		fearlevel=0.0;

		angerproneness=evolve(Parent.angerproneness, Evolve);
		fearproneness=evolve(Parent.fearproneness, Evolve);

		angercooldown=evolve(Parent.angercooldown, Evolve);
		fearcooldown=evolve(Parent.fearcooldown, Evolve);

		emotionalalignment=evolve(Parent.emotionalalignment, Evolve);

		return *this;
	}
	float cap(const float& Number)
	{
		//cout<<Number<<" vs "<<CHANGECAP<<endl<<flush;
		if (abs(Number)<CHANGECAP) return Number;
		else
		{
			if(Number<0.0)return -CHANGECAP;
			else return CHANGECAP;
		}
	}

	bool unittest()
	{
		emotions tmp(1.0, 0.1, 0.01, 0.001, 0.0001);
		if(tmp==emotions(separatestrings(tmp.print())))
		{
			return true;
		}
		return false;
	}
};

#endif /* EMOTIONS_H_ */
