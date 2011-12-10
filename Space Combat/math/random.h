#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <vector>
#include "basic.h"
#include "myvector.h"
#include "point.h"
#include "quaternion.h"

class random
{
	//a class for better handling of random numbers
	//this class is a singleton, since if a lot of objects
	//would want their own copy of it, srand would be called too many times
	//and some wrong data can be generated

	//example from experiance: all newly generated stars in the stars class
	//had the same position, since the class colour was using a member of this class
	//and it was being created, along with srand, between stars being created

	static random* instance;
	unsigned int tmprand, anwseru;
	int anwser;
	unsigned int randombuffersize;
	vector<unsigned int> randomnumbers;
	random():
		tmprand(0), anwseru(0), anwser(0), randombuffersize(4096)
	{
		srand(time(NULL));
	}
	inline
	unsigned int getrandom(void)
	{
		if (randomnumbers.empty())
		{
			return rand();
		}
		else
		{
			anwseru=randomnumbers.back();
			randomnumbers.pop_back();
			return anwseru;
		}
	}
public:
	~random()
	{
	}
	inline
	void preparerandom(unsigned int Amount=1)
	{
		for (unsigned int i=0; i<Amount; i++)
			if (randomnumbers.size()<randombuffersize)
				randomnumbers.push_back(rand());
	}
	inline
	void setrandombuffersize(const unsigned int NewSize)
	{
		randombuffersize=NewSize;
	}
	inline
	static random* getinstance()//getting instance of the singleton
	{
		if (instance==NULL)
			instance=new random();
		return instance;
	}

	inline
	char randomlowercasechar()
	{
		return (char)97+randomunsignedint('z'-'a');
	}
	inline
	float randomfloatpositive(const float& Range=1.0, const float& Offset=0.0)
	{//random positive float of range Offet - Offset+Range
		return Range*getrandom()/RAND_MAX+Offset;
	}
	inline
	float randomfloatbetween(const float& Min=0.0, const float& Max=1.0)
	{//random positive float of range Offet - Offset+Range
		return (Max-Min)*getrandom()/RAND_MAX+Min;
	}
	inline
	float randomfloatcenteredatzero(const float& Range=1.0,
			const float& Offset=0.0)
	{//random float of range Offset-Range/2 - Offset+Range/2
		return Range*(1.0*getrandom()/RAND_MAX+Offset-0.5)+Offset;
	}
	inline
	float randomnormalcenteredatzero(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of normal distribution centered at 0 with distribution from -Range/2 to Range/2
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples-0.5;//scales anwsers to +-1 range and centers it around 0
		return Range*anwser;
	}
	inline
	float randomnormalpositive(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of normal distribution, center at Range/2
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples;
		return Range*anwser;
	}
	inline
	float randomnormalpositivecenteredatzero(const float& Range=1.0,
			const unsigned int& Samples=4)
	{//random float of half of normal distribution with center at 0
		float anwser=0.0;
		for (unsigned int i=0; i<Samples; i++)
		{
			anwser+=1.0*getrandom()/RAND_MAX;
		}
		anwser=anwser/Samples;
		return Range*fabs(anwser-1);
	}
	inline
	unsigned int randomunsignedint(const unsigned int& Modulo=10)
	{//random unsigned int
		if (tmprand<Modulo)
			tmprand=rand();
		anwseru=tmprand%Modulo;
		tmprand=(int) tmprand/Modulo;
		return anwseru;
	}
	inline
	int randomint(const unsigned int& Modulo=10)
	{//random int
		if (tmprand<2*Modulo)
			tmprand=rand();
		anwser=tmprand%(2*Modulo)-Modulo;
		tmprand=(int) tmprand/(2*Modulo);
		return anwser;
	}
	inline
	unsigned int randomnormalunsignedint(const unsigned int& Modulo=10)
	{//random unsigned int with normal distribution centered at Modulo/2
		return (unsigned int) (Modulo*randomnormalpositive());
	}
	inline
	unsigned int randomnormalunsignedintcenteredatzero(
			const unsigned int& Modulo=10)
	{//random unsigned int of half normal distribution with center at 0
		return (unsigned int) fabs((Modulo*(randomnormalpositive()-0.5)));
	}

	//Random points in space

	inline
	basicvector randomboxposition(const float& Side,//box side length
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{
		int tmp=randomunsignedint(6);
		switch (tmp)
		{
		case 0:
			return basicvector(-Side*dx,
					randomfloatcenteredatzero(2.0*Side)*dy,
					randomfloatcenteredatzero(2.0*Side)*dz);
			//universe.push_back(star(-Side, 2*Side*rand()/RAND_MAX-Side, 2*Side*rand()/RAND_MAX-Side));
			break;
		case 1:
			return basicvector(Side*dx,
					randomfloatcenteredatzero(2.0*Side)*dy,
					randomfloatcenteredatzero(2.0*Side)*dz);
			break;
		case 2:
			return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
					-Side*dy,
					randomfloatcenteredatzero(2.0*Side)*dz);
			break;
		case 3:
			return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
					Side*dy,
					randomfloatcenteredatzero(2.0*Side)*dz);
			break;
		case 4:
			return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
					randomfloatcenteredatzero(2.0*Side)*dy,
					-Side*dz);
			break;
		case 5:
			return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
					randomfloatcenteredatzero(2.0*Side)*dy,
					Side*dz);
			break;
		}
		return basicvector(0.0, 0.0, 0.0);
	}

	inline
	basicvector randomcubeposition(const float& Side,//cube side length
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{
		return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
				randomfloatcenteredatzero(2.0*Side)*dy,
				randomfloatcenteredatzero(2.0*Side)*dz);
	}
	inline
	basicvector randomdiscposition(const float& Radius,//disc radius
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{
		//TODO: Put at arbitrary angle?
		float r=sqrt(randomfloatpositive(1))*Radius;
		float angle=randomfloatcenteredatzero(2.0*M_PI);
		float x=cos(angle)*r;
		float y=sin(angle)*r;

		return basicvector(x*dx, y*dy, 0.0*dz);
	}
	inline
	basicvector randomsquareposition(const float& Side,//square side length
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{
		//TODO: Put at arbitrary angle?
		return basicvector(randomfloatcenteredatzero(2.0*Side)*dx,
				randomfloatcenteredatzero(2.0*Side)*dy,
				0*dz);
	}
	inline
	basicvector randomsphereposition(const float& Radius,//sphere radius
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{
		float r=2.0*sqrt(randomfloatpositive(2.0*Radius));
		float angle1=randomfloatcenteredatzero(2.0*M_PI);
		float angle2=asin(randomfloatcenteredatzero(2));

		return basicvector(cos(angle2)*cos(angle1)*r*dx, cos(angle2)*sin(angle1)*r*dy, sin(angle2)*r*dz);
	}

	inline
	myvector randomdomeposition(const myvector& Direction=myvector(0.0, 1.0,
			0.0), const float& DegAngleSpread=0.0)
	{//for creating a spray of particles
		float angle1=randomfloatcenteredatzero(DegAngleSpread)*DEG2RAD;
		float angle2=randomfloatcenteredatzero(360)*DEG2RAD;
		float x=sin(angle1)*cos(angle2);
		float y=cos(angle1);
		float z=sin(angle1)*sin(angle2);

		myvector tmpvector(x, y, z);

		quaternion rotation(myvector(0.0, 1.0, 0.0), Direction.normalise());
		return rotation.rotatevector(tmpvector).setmymagnitude(
				Direction.getmagnitude());
	}
	inline
	myvector randomsprayposition(const myvector& Direction=myvector(0.0, 1.0,
			0.0), const float& AngleSpread=0.0)
	{
		return randomdomeposition(Direction, AngleSpread).setmymagnitude(
				randomfloatpositive(0.5, 0.5));
	}
	inline
	basicvector randombubbleposition(const float& Radius,//bubble radius
			const float& dx=1.0,//scaling
			const float& dy=1.0,//in
			const float& dz=1.0)//3D
	{//for creating a uniformly distributed bubble of points
		float angle1=randomfloatcenteredatzero(2.0*M_PI);
		float angle2=asin(randomfloatcenteredatzero(2));
		float x=cos(angle2)*cos(angle1)*Radius*dx;
		float y=cos(angle2)*sin(angle1)*Radius*dy;
		float z=sin(angle2)*Radius*dz;
		return basicvector(x, y, z);
	}

	inline
	myvector randomarchposition(const float& DegAngleSpread=0.0)
	{//to be tested before using
		float angle1=randomfloatpositive(DegAngleSpread/2.0)*DEG2RAD;
		float y=cos(angle1);
		float x=sin(angle1);
		return myvector(x, y);
	}


	//infinity symbol!
	/*	inline
	myvector randomdomeposition(const myvector& Direction=myvector(0.0, 1.0,
			0.0), const float& DegAngleSpread=0.0)
	{//for creating a spray of particles
		float angle1=randomfloatpositive(DegAngleSpread/2.0)*DEG2RAD;
		float angle2=randomfloatpositive(360)*DEG2RAD;
		//float x=sin(angle1)*cos(angle2);
		//float y=cos(angle1);
		//float z=sin(angle1)*sin(angle2);
		float x=cos(angle2)*cos(angle1);
		float y=cos(angle2)*sin(angle1);
		float z=sin(angle2);
		myvector tmpvector(x, y, z);
		myvector cross=myvector(0.0, 1.0, 0.0).crossproduct(Direction);
		if (cross.getsquaredmagnitude()==0)
		{
			if (Direction.y>0)
				return tmpvector.setmymagnitude(Direction.getmagnitude());
			else
				return -tmpvector.setmymagnitude(Direction.getmagnitude());
		}
		quaternion rotation=quaternion(cross.normaliseme(), tmpvector.angle(
				Direction));
		return rotation.rotatevector(tmpvector).setmymagnitude(
				Direction.getmagnitude());
	}	 */
};

#endif /* RANDOM_H_ */
