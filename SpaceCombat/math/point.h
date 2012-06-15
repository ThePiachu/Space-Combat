#ifndef POINT_H_
#define POINT_H_

//#include "myvector.h"
#include "basic.h"
#include <string>
#include <iostream>
#include <cmath>
#include <GL\gl.h>
#include <stdio.h>
using namespace std;



class point: public basicpoint
{//class to represent a point in the space
public:
	point(float X=0.0, float Y=0.0, float Z=0.0): basicpoint(X, Y, Z)
	{
	}
	point (const basicpoint& Other): basicpoint(Other)
	{
	}
	point (const basicvector& Vector): basicpoint(Vector.x, Vector.y, Vector.z)
	{
	}
	~point(void)
	{
	}
	inline
	point& lerpme (const point& Other, const float& Ratio=0.5)
	{//lerping between two points
		x=x-(x-Other.x)*Ratio;
		y=y-(y-Other.y)*Ratio;
		z=z-(z-Other.z)*Ratio;
		return *this;
	}
	inline
	point lerp (const point& Other, const float& Ratio=0.5) const
	{//lerping between two points
		return point(x-(x-Other.x)*Ratio, y-(y-Other.y)*Ratio, z-(z-Other.z)*Ratio);
	}
	inline
	point movebyvector (const basicvector& Vector) const
	{//moving a point by a vector
		return basicpoint (x+Vector.x, y+Vector.y, z+Vector.z);
	}
	inline
	point& movemebyvector (const basicvector& Vector)
	{//moving a point by a vector
		x+=Vector.x;
		y+=Vector.y;
		z+=Vector.z;
		return *this;
	}
	inline
	point& setposition (const float& X=0.0, const float& Y=0.0, const float& Z=0.0)
	{//setting the point
		x=X;
		y=Y;
		z=Z;
		return *this;
	}
	inline
	void printme(void) const
	{//printing the poitn details into the console
		cout<<"X "<<x<<" Y "<<y<<" Z "<<z<<endl<<flush;
	}
	inline
	string print(void) const
	{//printing the poitn details into a string
		static char Chars[100];
		string result("X ");
		sprintf(Chars, "%.1f", x);
		result+=Chars+string(" Y ");
		sprintf(Chars, "%.1f", y);
		result+=Chars+string(" Z ");
		sprintf(Chars, "%.1f", z);
		result+=Chars;
		return result;
	}
	inline
	float distanceto(const point& Other) const
	{//distance between two points
		//printme();
		//cout<<"vs"<<endl;
		//Other.printme();
		//cout<<endl<<flush;
		return sqrt((x-Other.x)*(x-Other.x)
						+(y-Other.y)*(y-Other.y)
							+(z-Other.z)*(z-Other.z));
	}
	inline
	float squareddistanceto(const point& Other) const
	{//distance between two points
		return (x-Other.x)*(x-Other.x)+(y-Other.y)*(y-Other.y)+(z-Other.z)*(z-Other.z);
	}
	inline
	point operator+ (const point& Other) const
	{//adding two points like vectors
		return point(x+Other.x, y+Other.y, z+Other.z);
	}
	inline
	point operator+= (const point& Other)
	{//adding two points like vectors
		x+=Other.x;
		y+=Other.y;
		z+=Other.z;
		return *this;
	}
	inline
	point operator/ (const float& HowMuch)const
	{//adding two points like vectors
		return point(x/HowMuch, y/HowMuch, z/HowMuch);
	}
	inline
	point operator/= (const float& HowMuch)
	{//adding two points like vectors
		x/=HowMuch;
		y/=HowMuch;
		z/=HowMuch;
		return *this;
	}
	inline
	point operator- (const point& Other) const
	{//subtracting two points like vectors
		return point(x-Other.x, y-Other.y, z-Other.z);
	}
	inline
	void drawme (void) const
	{//drawing a point
		glBegin(GL_POINTS);
			glVertex3f(x, y, z);
		glEnd();
	}
	inline
	point& operator=(const basicpoint& Other)
	{
		x=Other.x;
		y=Other.y;
		z=Other.z;
		return *this;
	}
	inline
	bool operator==(const basicpoint& Other) const
	{//comparison
		return((x==Other.x)&&(y==Other.y)&&(z==Other.z));
	}
	inline
	bool operator!=(const basicpoint& Other) const
	{//comparison
		return (!((x==Other.x)&&(y==Other.y)&&(z==Other.z)));
	}
	inline
	void drawingpoint(void)const
	{//returning the position of the point to be used for drawing
		glVertex3f(x, y, z);
	}
	inline
	point& operator()(const basicpoint& Other)
	{
		x=Other.x;
		y=Other.y;
		z=Other.z;
		return *this;
	}
	inline
	point& operator()(const float& X=0.0, const float& Y=0.0, const float& Z=0.0)
	{
		x=X;
		y=Y;
		z=Z;
		return *this;
	}
	inline
	float manhattandistance(const point& Other)
	{
		return abs(x-Other.x)+abs(y-Other.y)+abs(z-Other.z);
	}
	inline
	float biggestaxisdistance(const point& Other)
	{
		//cout<<"X "<<abs(x-Other.x)<<" Y "<<abs(y-Other.y)<<" Z "<<abs(z-Other.z)<<endl<<flush;
		//cout<<"Max "<<max(max(abs(x-Other.x), abs(y-Other.y)), abs(z-Other.z))<<endl;
		return max(max(abs(x-Other.x), abs(y-Other.y)), abs(z-Other.z));
	}
	inline
	point operator%(const float& Base) const
	{//an approximation of point's position, for map class use
		return point(
		int(x/Base)*Base,
		int(y/Base)*Base,
		int(z/Base)*Base
		);
	}
	inline
	point approx(const float& Resolution) const
	{
		return roundtonearest(Resolution);
	}
	inline
	point roundtonearest(const float& Resolution) const
		{//an approximation of point's position, for map class use
		return point(
		round(x/Resolution)*Resolution,
		round(y/Resolution)*Resolution,
		round(z/Resolution)*Resolution
		);
	}


	bool isnok()
	{
		if(x!=x||y!=y||z!=z)return true;//NANs
		return false;
	}

	bool unittest()
	{

		point tmppoint(1.1, 3.2, 5.5);

		cout<<tmppoint.biggestaxisdistance(point(0.0, 0.0, 0.0))<<endl<<flush;
		cout<<tmppoint.biggestaxisdistance(point(0.0, 0.0, 3.0))<<endl<<flush;
		cout<<tmppoint.biggestaxisdistance(point(0.0, 3.0, 5.0))<<endl<<flush;
		cout<<tmppoint.biggestaxisdistance(point(1.0, 1.0, 1.0))<<endl<<flush;
		cout<<tmppoint.biggestaxisdistance(point(2.1, 3.3, 5.4))<<endl<<flush;
		if(tmppoint%1.0!=point(1.0, 3.2, 5.5)) return false;

		return true;
	}
};
struct pointcompare
{
	inline
	bool operator() (const point& One, const point& Two) const
	{//comparison operator for map class use
		//return One<Two;
		if (One.x<Two.x)return true;
		if (One.x>Two.x)return false;

		if (One.y<Two.y)return true;
		if (One.y>Two.y)return false;

		if (One.z<Two.z)return true;
		return false;
	}
};
#endif //POINT_H_
