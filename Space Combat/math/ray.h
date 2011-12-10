#ifndef RAY_H_
#define RAY_H_

#include "point.h"
#include "myvector.h"

class ray
{//class to represent a ray
public:
	point origin;
	myvector direction;
	ray(const point& Origin, const myvector& Direction): origin(Origin), direction(Direction)
	{
	}
	ray(const point& Origin, const point& Direction): origin(Origin), direction(Origin, Direction)
	{
	}
	ray(const ray& Other): origin(Other.origin), direction(Other.direction)
	{
	}
	~ray();
	ray& operator= (const ray& Other)
	{
		origin=Other.origin;
		direction=Other.direction;
		return *this;
	}
};

#endif /* RAY_H_ */
