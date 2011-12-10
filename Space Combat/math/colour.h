#ifndef COLOUR_H_
#define COLOUR_H_

#include <GL\gl.h>
#include "random.h"
#include "evolution.cpp"
#include "../stringhandling.h"
#include <iostream>

//#define COLOUREVOLUTIONSPEED 0.1
#define COLOURACCURACY 0.1

using namespace std;

class colour
{//class for handling colour
	random* myrandom;
	GLfloat r, g, b;
public:
	colour(const GLfloat& R, const GLfloat& G, const GLfloat& B):
		myrandom(random::getinstance()),
		r(R),
		g(G),
		b(B)
	{
	}
	colour():
		myrandom(random::getinstance()),
		r(myrandom->randomfloatpositive()),
		g(myrandom->randomfloatpositive()),
		b(myrandom->randomfloatpositive())
	{
	}
	colour(const float& Length)://creating a 'unit length colour'
		myrandom(random::getinstance()),
		r(myrandom->randomfloatpositive()),
		g(myrandom->randomfloatpositive()),
		b(myrandom->randomfloatpositive())
	{
		float length=sqrt(r*r+g*g+b*b);
		//making the colour 'unit length vector'
		r=r*Length/length;
		g=g*Length/length;
		b=b*Length/length;
	}
	colour(const GLfloat& R, const GLfloat& G, const GLfloat& B, const float& Length):
		myrandom(random::getinstance()),
		r(R),
		g(G),
		b(B)
	{
		float length=sqrt(r*r+g*g+b*b);
		//making the colour 'unit length vector'
		r=r*Length/length;
		g=g*Length/length;
		b=b*Length/length;
	}
	colour(const colour& Other):
		myrandom(random::getinstance()),
		r(Other.r),
		g(Other.g),
		b(Other.b)
	{
	}
	colour(const colour& Parent, const float& Evolve):
		myrandom(random::getinstance()),
		r(evolve(Parent.r, Evolve)),
		g(evolve(Parent.g, Evolve)),
		b(evolve(Parent.b, Evolve))
	{
		if(Evolve)
		{
			if(r<0)r=-r;
			if(g<0)g=-g;
			if(b<0)b=-b;

			float length=sqrt(r*r+g*g+b*b);
			//making the colour 'unit length vector'
			r=r/length;
			g=g/length;
			b=b/length;
		}
	}
	colour(const colour& Parent, const float& Evolve, const bool& SpecialEvolve):
		myrandom(random::getinstance()),
		r(evolve(Parent.r, Evolve)),
		g(evolve(Parent.g, Evolve)),
		b(evolve(Parent.b, Evolve))
	{//function for selective evolution
		if(Evolve)
		{
			if(r<0)r=-r;
			if(g<0)g=-g;
			if(b<0)b=-b;

			float length=sqrt(r*r+g*g+b*b);
			//making the colour 'unit length vector'
			r=r/length;
			g=g/length;
			b=b/length;
		}
	}
	colour(const vector<string>& FileColour):
		myrandom(random::getinstance()),
		r(0.0),
		g(0.0),
		b(0.0)
	{
		for(unsigned int i=0;i<FileColour.size();i++)
		{
			//cout<<"FileColour at "<<i<<" out of "<<FileColour.size()<<" : **"<<FileColour.at(i)<<"**"<<endl<<flush;
			if(FileColour.at(i).find("~colour")==0)
				break;
			if(FileColour.at(i).find("r")==0)
				r=getfloat(FileColour.at(i));
			if(FileColour.at(i).find("g")==0)
				g=getfloat(FileColour.at(i));
			if(FileColour.at(i).find("b")==0)
				b=getfloat(FileColour.at(i));
		}
	}
	~colour()
	{
	}
	inline
	bool operator!=(const colour& Other)const
	{
		return !operator==(Other);
	}
	inline
	bool operator== (const colour& Other)const
	{
		float tmp=((r-Other.r)*(r-Other.r)+
		(g-Other.g)*(g-Other.g)+
		(b-Other.b)*(b-Other.b));
		return tmp<COLOURACCURACY;
	}
	/*inline
	bool operator== (const colour& Other)const
	{
		return((r==Other.r)&&
		(g==Other.g)&&
		(b==Other.b));
	}*/
	inline
	void changecolour(const GLfloat& R=0.0, const GLfloat& G=0.0, const GLfloat& B=0.0)
	{//changing colour
		r=R;
		g=G;
		b=B;
	}
	inline
	void randomcolour()
	{//randomizing colour
		r=myrandom->randomfloatpositive();
		g=myrandom->randomfloatpositive();
		b=myrandom->randomfloatpositive();
	}
	inline
	void setcolour()const
	{//setting OpenGL to draw using this colour
		glColor3f(r, g, b);
	}
	inline
	void setme(const colour& Other)
	{//setting OpenGL to draw using this colour
		r=Other.r;
		g=Other.g;
		b=Other.b;
	}
	inline
	colour& operator()(const colour& Other)
	{//setting OpenGL to draw using this colour
		r=Other.r;
		g=Other.g;
		b=Other.b;
		return *this;
	}
	inline
	colour& operator()(const GLfloat& R, const GLfloat& G, const GLfloat& B)
	{//setting OpenGL to draw using this colour
		r=R;
		g=G;
		b=B;
		return *this;
	}
	inline
	colour& operator= (const colour& Other)
	{
		r=Other.r;
		g=Other.g;
		b=Other.b;
		return *this;
	}
	colour& operator()(const colour& Parent, const bool& Evolve=false)
	{//inherit function for use with boids
		r=evolve(Parent.r, Evolve);
		g=evolve(Parent.g, Evolve);
		b=evolve(Parent.b, Evolve);

		if(Evolve)
		{
			if(r<0)r=-r;
			if(g<0)g=-g;
			if(b<0)b=-b;

			float length=sqrt(r*r+g*g+b*b);
			//making the colour 'unit length vector'
			r=r/length;
			g=g/length;
			b=b/length;
		}
		return *this;
	}
	void inherit(const colour& Parent)
	{//inherit function for use with boids
		r=evolve(Parent.r, true);
		g=evolve(Parent.g, true);
		b=evolve(Parent.b, true);

		if(r<0)r=-r;
		if(g<0)g=-g;
		if(b<0)b=-b;

		float length=sqrt(r*r+g*g+b*b);
		//making the colour 'unit length vector'
		r=r/length;
		g=g/length;
		b=b/length;
	}
	float distanceto(const colour& Other) const
	{
		return (r-Other.r)*(r-Other.r)+
					(g-Other.g)*(g-Other.g)+
						(b-Other.b)*(b-Other.b);
	}
	inline
	void printme(void) const
	{
		cout<<"R "<<r<<" G "<<g<<" B "<<b<<endl;
	}
	string print()const
	{
		char Chars[100];
		string anwser("\ncolour");

		sprintf(Chars, "%f", r);
		anwser+=string("\nr\t")+Chars;
		sprintf(Chars, "%f", g);
		anwser+=string("\ng\t")+Chars;
		sprintf(Chars, "%f", b);
		anwser+=string("\nb\t")+Chars;

		anwser+=string("\n~colour\n");
		return anwser;
	}
	bool unittest()
	{
		colour tmp(0.1, 0.01, 0.001);
		if(tmp==colour(separatestrings(tmp.print())))
		{
			return true;
		}
		tmp.printme();
		colour(separatestrings(tmp.print())).printme();
		return false;
	}
	bool operator<(const colour& Other)const
	{
		if(r<Other.r) return true;
		if(r>Other.r) return false;

		if(g<Other.g) return true;
		if(g>Other.g) return false;

		if(b<Other.b) return true;
		return false;
	}
};

#endif /* COLOUR_H_ */
