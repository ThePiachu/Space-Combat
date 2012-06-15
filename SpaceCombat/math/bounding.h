#ifndef BOUNDING_H_
#define BOUNDING_H_
//file for storing all bounding volumes, for now only a sphere is used
#include "point.h"
#include "ray.h"
#include "line.h"
#include "colour.h"
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>

class boundingsphere
{//class for a bounding sphere
public:
	point center;//center of the sphere
	float radius;//it's radius
	colour mycolour;
	boundingsphere(const float& X=0.0, const float& Y=0.0, const float& Z=0.0, const float& R=0.0,
			const colour& Colour=colour(1.0, 1.0, 1.0)):center(X, Y, Z), radius(R), mycolour(Colour)
	{
	}
	boundingsphere(const point& Center, const float& R=0.0,
			const colour& Colour=colour(1.0, 1.0, 1.0)): center(Center), radius(R), mycolour(Colour)
	{
	}
	boundingsphere(const boundingsphere& Other): center(Other.center), radius(Other.radius), mycolour(Other.mycolour)
	{
	}
	boundingsphere& operator= (const boundingsphere& Other)
	{
		center=Other.center;
		radius=Other.radius;
		return *this;
	}
	~boundingsphere()
	{
	}
	bool ishit (const float& X=0.0, const float& Y=0.0, const float& Z=0.0) const
	{//checking if a point is inside the bounding sphere
		return (sqrt((X-center.x)*(X-center.x)+(Y-center.y)*(Y-center.y)+(Z-center.z)*(Z-center.z))<radius);
	}
	bool ishit (const point& Location) const
	{//checking if a point is inside the bounding sphere
		return (sqrt((Location.x-center.x)*(Location.x-center.x)
				+(Location.y-center.y)*(Location.y-center.y)
				+(Location.z-center.z)*(Location.z-center.z))<radius);
	}
	bool ishit (const ray& Ray) const
	{//checking if the ray is intersecting the bounding sphere
	//based on http://www.devmaster.net/wiki/Ray-sphere_intersection
		myvector oc=myvector (center, Ray.origin);
		float distance=oc.getmagnitude();
		if (distance<radius)
		{//ray shoots from inside the sphere
			return true;
		}
		else
		{
			float closestapproach=oc.dotproduct(Ray.direction);
			if (closestapproach<0)
			{//ray points away from the sphere
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	bool ishit (const line& Line, const float& ParticleRadius=0.0) const
	{//checking if the line is intersecting the bounding sphere
		point tmppoint=closestpoint(Line.one, Line.two);
		return ((center.distanceto(closestpoint(Line))<radius+ParticleRadius)&&(Line.ispointbetweennodes(tmppoint)));
	}
	bool ishit (const point& Start, const point& End, const float& ParticleRadius=0.0) const
	{//checking if a line segment is intersecting the bounding sphere
		point tmppoint=closestpoint(Start, End);
		return ((center.distanceto(Start)<radius+ParticleRadius)||
				(center.distanceto(End)<radius+ParticleRadius)||
				((center.distanceto(tmppoint)<radius+ParticleRadius)&&(line(Start, End).ispointbetweennodes(tmppoint))));
	}
	point intersection(const line& Line, const float& ParticleRadius=0.0) const
	{//function to return one of the points of intersection of the line and the sphere
		//point returned is the one closest to the first point that defines the line
		point tmppoint=closestpoint(Line);//finding the closest point to the center of the sphere on the line
		return tmppoint.movebyvector(//the intersection point is the closest point to the center
				(-Line.onetwo).//moved by the line towwards the first point defining the line
				setmagnitude(//by a vector of magnitude (R+x)*(R+x)-d*d,
							//R - sphere radius, x - radius of the particle, d - distance between the line and center of the sphere
				sqrt((radius+ParticleRadius)*(radius+ParticleRadius)
						-tmppoint.distanceto(center)*tmppoint.distanceto(center))));
	}
	point reflection(const line& Line, const float& ParticleRadius=0.0) const
	{//function to reflect the second point defining the line intersecting with the sphere
		point tmppoint=intersection(Line, ParticleRadius);//intersection point
		myvector normalvector=myvector(center, tmppoint);//vector from the center of the sphere to intersection point
		return tmppoint.movemebyvector(//second point is created from intersection point
				myvector(tmppoint, Line.two)//it's distance is equal to how far in the sphere the second point is
				.reflectme(normalvector));//direction is based on reflection from the sphere
	}
	point reflection(const line& Line, const point& IntersectionPoint) const
	{//function like the previous reflection, but using a precalculated intersection point to speed the process up
		myvector normalvector=myvector(center, IntersectionPoint);
		return IntersectionPoint.movebyvector(myvector(IntersectionPoint, Line.two).reflectme(normalvector));
	}
	myvector reflection(const myvector& Vector, const point& PointOnSphere) const
	{//reflecting a vector (for example speed) in the same direction as the line point was reflected
		return Vector.reflect(myvector(center, PointOnSphere));
	}
	point closestpoint(const point& One, const point& Two) const
	{
		return closestpoint(line(One, Two));
	}
	point closestpoint(const line& Line)const
	{//function to calculate a closest point to the center of the sphere on a line
		myvector tmpvector(Line.one, center);//line from one of line points to the center of sphere
		//Line.one.printme();
		//center.printme();
		//Line.onetwo.printme();
		//cout<<tmpvector.dotproduct(Line.onetwo.normalise())<<endl;
		//point tmppoint=Line.one
		return Line.one
					//creates a point from one of the line points
					.movebyvector//moved by vector
						(Line.onetwo//in the direction of vector from one of the points of the line to the second
								.setmagnitude//with the magnitude equal to
								(tmpvector.dotproduct(Line.onetwo.normalise())));//the dot product of the two above mentioned vectors
		//cout<<"Closest point: ";
		//tmppoint.printme();
		//return tmppoint;
	}
	void setcolour(const colour& Colour)
	{
		mycolour=Colour;
	}
	void drawme(bool UseColour=false, bool WireOrNot=true, unsigned int Slices=10, unsigned int Stacks=10) const
	{//drawing the sphere
		if (UseColour)mycolour.setcolour();
		if (WireOrNot)
		{//as a set of wires
			glPushMatrix();
				glTranslatef(center.x, center.y, center.z);
				glutWireSphere(radius, Slices, Stacks);
			glPopMatrix();
		}
		else
		{//as a solid
			glPushMatrix();
				glTranslatef(center.x, center.y, center.z);
				glutSolidSphere(radius, Slices, Stacks);
			glPopMatrix();
		}
	}
	boundingsphere operator+ (const float& HowMuch) const
	{//creates a sphere of radius bigger by HowMuch
		return boundingsphere(center, radius+HowMuch);
	}
};

#endif /* BOUNDING_H_ */
