#ifndef HUD_H_
#define HUD_H_

#include <iostream>
#include <string>
#include <vector>

#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>
//#include "colour.h"
#include "math.h"
using namespace std;

#define TOPLEFT 1
#define BOTTOMLEFT 2
#define TOPRIGHT 3
#define BOTTOMRIGHT 4

class hud
{//class for Heads Up Display of information
	float width, height;
	float depth;
	void renderBitmapString(
			float x,
			float y,
			float z,
			void *font,
			const char *string,
			unsigned short int Mode=TOPLEFT)
	{//http://www.lighthouse3d.com/opengl/glut/index.php?bmpfont, modified
		//function for drawing simple text
		unsigned int newlines=0;
		switch (Mode)
		{//changes the colour of the line of text
		case TOPLEFT:
			if (newlines<topleftc.size())
				topleftc.at(newlines).setcolour();
			break;
		case BOTTOMLEFT:
			if (newlines<bottomleftc.size())
				bottomleftc.at(newlines).setcolour();
			break;
		case TOPRIGHT:
			if (newlines<toprightc.size())
				toprightc.at(newlines).setcolour();
			break;
		case BOTTOMRIGHT:
			if (newlines<bottomrightc.size())
				bottomrightc.at(newlines).setcolour();
			break;
		}
		glRasterPos3f(x,y,z);//setting the position
		for (int i=0; string[i]!= '\0'; i++)
		{
			if (string[i]=='\n')
			{//handling newline characters
				newlines++;
				switch (Mode)
				{//changes the colour of the line of text
				case TOPLEFT:
					if (newlines<topleftc.size())
						topleftc.at(newlines).setcolour();
					break;
				case BOTTOMLEFT:
					if (newlines<bottomleftc.size())
						bottomleftc.at(newlines).setcolour();
					break;
				case TOPRIGHT:
					if (newlines<toprightc.size())
						toprightc.at(newlines).setcolour();
					break;
				case BOTTOMRIGHT:
					if (newlines<bottomrightc.size())
						bottomrightc.at(newlines).setcolour();
					break;
				}
				if (font==GLUT_BITMAP_8_BY_13) glRasterPos3f(x, y-0.15*newlines, z);
				continue;
			}
			else if (string[i]=='\t')
			{
				glutBitmapCharacter(font, ' ');
				glutBitmapCharacter(font, ' ');
				glutBitmapCharacter(font, ' ');
				glutBitmapCharacter(font, ' ');
				glutBitmapCharacter(font, ' ');
			}
			else glutBitmapCharacter(font, string[i]);
		}
	}
public:
	string topleft, topright, bottomleft, bottomright;
	vector <colour> topleftc, bottomleftc, toprightc, bottomrightc;
	hud(unsigned int Width=0, unsigned int Height=0): width(1.0*Width/100.0), height(1.0*Height/100.0), depth(-7.5)
	{
		bottomleft="Hello World!";
		topleft="Top here!\nNewline!";
		bottomright=".";
		topright=".";
		topleftc.push_back(colour(1.0, 0.0, 0.0));
		topleftc.push_back(colour(0.0, 1.0, 0.0));
		topleftc.push_back(colour(0.0, 0.0, 1.0));
	}
	~hud()
	{
	}



	//setting the strings
	void settopleft(const string& Text)
	{
		topleft=Text;
	}
	void settopright(const string& Text)
	{
		topright=Text;
	}
	void setbottomleft(const string& Text)
	{
		bottomleft=Text;
	}
	void setbottomright(const string& Text)
	{
		bottomright=Text;
	}


	//drawing the strings
	void drawme(void)
	{
		unsigned int newlines;
		glColor3f(1.0, 1.0, 1.0);
		if (!topleft.empty())
		{
			renderBitmapString(-3.0, 3.0, depth, GLUT_BITMAP_8_BY_13, topleft.c_str());
		}
		if (!bottomleft.empty())
		{
			newlines=0;
			for (unsigned int i=0;i<topleft.size();i++)
			{
				if (topleft.at(i)==0) newlines++;
			}
			renderBitmapString(-3.0, -3.0, depth, GLUT_BITMAP_8_BY_13, bottomleft.c_str());
		}
	}
	void reshape (int Width, int Height)
	{//window reshaping
		width=1.0*Width/100.0;
		height=1.0*Height/100.0;
	}
	void handlekey (const int& Key)
	{
	}


	//setting colours
	void settopleftcolour(vector<colour> Vec)
	{
		topleftc=Vec;
	}
};

#endif /* HUD_H_ */
