#ifndef MYVECTOR_H_
#define MYVECTOR_H_
//#include "point.h"
#include "basic.h"
#include <cmath>
#include <string>
#include <iostream>
#include <GL\gl.h>
#include <stdio.h>
using namespace std;


class myvector: public basicvector
{//class for storing a vector
public:
	//float x, y, z;
	myvector(const float& X=0, const float& Y=0, const float& Z=0): basicvector (X, Y, Z)
	{
	}
	myvector (basicpoint Start, basicpoint End): basicvector(End.x-Start.x, End.y-Start.y, End.z-Start.z)
	{
	}
	myvector (basicpoint OriginToEnd): basicvector(OriginToEnd.x, OriginToEnd.y, OriginToEnd.z)
	{
	}
	myvector (const basicvector& Other): basicvector (Other)
	{
	}
	~myvector(void)
	{
	}
	inline
	myvector& operator()(basicpoint Start, basicpoint End)
	{
		x=End.x-Start.x;
		y=End.y-Start.y;
		z=End.z-Start.z;
		return *this;
	}
	inline
	myvector& operator()(const float& X=0, const float& Y=0, const float& Z=0)
	{
		x=X;
		y=Y;
		z=Z;
		return *this;
	}
	inline
	myvector& operator()(const basicvector& Basic)
	{
		x=Basic.x;
		y=Basic.y;
		z=Basic.z;
		return *this;
	}
	inline
	myvector operator+ (const myvector& Other) const
	{//adding vectors
		return myvector (x+Other.x, y+Other.y, z+Other.z);
	}
	inline
	myvector& operator+= (const myvector& Other)
	{//adding vectors
		x+=Other.x;
		y+=Other.y;
		z+=Other.z;
		return *this;
	}
	inline
	myvector operator* (float HowMuch) const
	{//scaling vector
		return myvector (x*HowMuch, y*HowMuch, z*HowMuch);
	}
	inline
	myvector& operator*= (float HowMuch)
	{//scaling vecotr
		x*=HowMuch;
		y*=HowMuch;
		z*=HowMuch;
		return *this;
	}
	inline
	myvector& operator/= (const float& HowMuch)
	{//scaling vector
		x/=HowMuch;
		y/=HowMuch;
		z/=HowMuch;
		return *this;
	}
	inline
	myvector operator/ (const float& HowMuch) const
	{//scaling vector
		return myvector (x/HowMuch, y/HowMuch, z/HowMuch);
	}
	inline
	myvector operator- (const myvector& Other) const
	{//vector subtraction
		return myvector (x-Other.x, y-Other.y, z-Other.z);
	}
	inline
	myvector& operator-= (const myvector& Other)
	{//vector subtraction
		x-=Other.x;
		y-=Other.y;
		z-=Other.z;
		return *this;
	}
	inline
	myvector operator-() const
	{//opposite vector
		return myvector(-x, -y, -z);
	}
	inline
	myvector& operator= (const myvector& Other)
	{//assigment
		x=Other.x;
		y=Other.y;
		z=Other.z;
		return *this;
	}
	inline
	bool operator== (const myvector& Other) const
	{//comparison
		return ((x==Other.x)&&(y==Other.y)&&(z==Other.z));
	}
	inline
	myvector& scaleme (const float& Magnitude)
	{//scaling vector
		x*=Magnitude;
		y*=Magnitude;
		z*=Magnitude;
		return *this;
	}
	inline
	myvector scale (const float& Magnitude) const
	{//scaling vector
		return myvector (x*Magnitude, y*Magnitude, z*Magnitude);
	}
	inline
	float getmagnitude() const
	{//magnitude of the vector
		return sqrt(x*x+y*y+z*z);
	}
	inline
	float getsquaredmagnitude() const
	{//square of the magnitude of the vector
		return x*x+y*y+z*z;
	}
	myvector setmagnitude (const float& Magnitude) const
	{//setting the magnitude of the vector
		float tmp=getmagnitude();
		if (tmp==Magnitude)
		{
			return myvector (*this);
		}
		if (tmp==0)
		{
			//error
			return myvector (*this);
		}
		else
		{
			tmp=Magnitude/tmp;
			return myvector (x*tmp, y*tmp, z*tmp);
		}
	}
	myvector& setmymagnitude (const float& Magnitude)
	{//setting the magnitude of the vector
		float tmp=getmagnitude();
		if (tmp==Magnitude)
		{
			return *this;
		}
		if (tmp==0.0)
		{
			//error
			return *this;
		}
		else
		{
			tmp=Magnitude/tmp;
			x*=tmp;
			y*=tmp;
			z*=tmp;
			return *this;
		}
	}
	inline
	float dotproduct (const basicvector& Other) const
	{//dot product of two vectors
		return x*Other.x+y*Other.y+z*Other.z;
	}
	inline
	myvector crossproduct (const basicvector& Other) const
	{//cross product of two vectors
		return myvector(y*Other.z-Other.y*z,
							z*Other.x-Other.z*x,
								x*Other.y-Other.x*y);
	}
	inline
	myvector normalise() const
	{//normalisation
		return setmagnitude(1.0);
	}
	inline
	myvector& normaliseme()
	{//normalisation
		return setmymagnitude(1.0);
	}
	inline
	float angle(const myvector& Other) const
	{//angle between two vectors in degrees
		return degangle(Other);
	}
	float radangle(const myvector& Other) const
	{//angle between two vectors in radians
		return acosf(normalise().dotproduct(Other.normalise()));
	}
	float degangle(const myvector& Other) const
	{//angle between two vectors in degrees
		return RAD2DEG*acosf(normalise().dotproduct(Other.normalise()));
	}
	inline
	void printme(void) const
	{//printing the details of the vector into the console
		cout<<"X "<<x<<" Y "<<y<<" Z "<<z<<endl<<flush;
	}
	inline
	string print(void)const
	{//printing the details of the vector into a string
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
	myvector lerp (const myvector& Other, const float& Ratio)
	{//lerp of two vectors
		return myvector(x-(x-Other.x)*Ratio, y-(y-Other.y)*Ratio, z-(z-Other.z)*Ratio);
	}
	/*
	myvector operator- (void) const
	{
		return myvector(-x, -y, -z);
	}
	*/
	inline
	basicpoint topoint()
	{//a point from a vector
		return basicpoint(x, y, z);
	}
	inline
	basicvector tobasicvector()
	{//basic vector
		return basicvector(x, y, z);
	}
	inline
	void drawme(const basicpoint& Origin=basicpoint(0.0, 0.0, 0.0)) const
	{//drawing the vector
		glBegin(GL_LINES);
			glVertex3f(Origin.x, Origin.y, Origin.z);
			glVertex3f(Origin.x+x, Origin.y+y, Origin.z+z);
		glEnd();
	}
	inline
	operator basicvector()const
	{//typecasting onto basicvector
		return basicvector(x, y, z);
	}
	inline
	operator basicpoint()const
	{//typecasting onto basicvector
		return basicpoint(x, y, z);
	}
	myvector reflect(const myvector& ReflectionVector) const
	{//reflecting the vector from another vector
		return myvector(*this).reflectme(ReflectionVector);
	}
	myvector& reflectme(const myvector& ReflectionVector)
	{//reflecting the vector from another vector
		myvector normalised=ReflectionVector.normalise();//normalising the normal vector
		myvector cross=normalised.crossproduct(*this);//vector at the right angle to both of the vectors
		if(cross.getmagnitude()==0)
		{//in case they are facing the same direction
			return *this=-*this;
		}
		cross.normaliseme();//normalising the cross product
		cross=cross.crossproduct(normalised);//second vector at the right angle to the normal vector
		myvector x=cross.setmagnitude(dotproduct(cross));//part of the vector perpenticular to the normal vector
		myvector y=normalised.setmagnitude(normalised.dotproduct(*this));//part of the vector paralel to the normal vector
		*this=x-y;//saving the new vector
		return *this;
	}
	myvector perpenticulartoplane(const myvector& Other) const
	{
		if (crossproduct(Other).getsquaredmagnitude()>0.0) return crossproduct(Other);
		else if (crossproduct(myvector(1.0, 0.0, 0.0)).getsquaredmagnitude()>0.0)
			return crossproduct(myvector(1.0, 0.0, 0.0));
		else return crossproduct(myvector(0.0, 1.0, 0.0));
	}
	bool isnok()
	{
		if(x!=x||y!=y||z!=z)return true;//NANs
		return false;
	}
};
#endif //MYVECTOR_H_
