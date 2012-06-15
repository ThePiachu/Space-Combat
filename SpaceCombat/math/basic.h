#ifndef BASIC_H_
#define BASIC_H_

//two mathematical constants used on ocasion
#define RAD2DEG 180/M_PI
#define DEG2RAD M_PI/180
class basicpoint
{
public:
	float x, y, z;
	basicpoint(float X=0.0, float Y=0.0, float Z=0.0): x(X), y(Y), z(Z)
	{
	}
	basicpoint (const basicpoint& Other): x(Other.x), y(Other.y), z(Other.z)
	{
	}
};
class basicvector
{//class for simplest representation of a vector
public:
	float x, y, z;
	basicvector(float X, float Y, float Z): x(X), y(Y), z(Z)
	{
	}
	basicvector (const basicvector& Other): x(Other.x), y(Other.y), z(Other.z)
	{
	}
};

inline
bool isnok(const float& Number)
{
	return Number!=Number;
}


#endif
