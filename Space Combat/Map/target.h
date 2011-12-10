#ifndef TARGET_H_
#define TARGET_H_

#include "../math.h"

class target
{
public:
	point position;
	float radius;
	target(const point& Position=point(), const float& Radius=0.3):
		position(Position), radius(Radius)
	{
	}
	~target()
	{
	}
	target& operator()(const point& Position, const float& Radius=0.3)
	{
		position=Position;
		radius=Radius;
		return *this;
	}
};

#endif /* TARGET_H_ */
