#ifndef PLANE_H_
#define PLANE_H_

#include "point.h"
#include "myvector.h"
#include "colour.h"
#include "line.h"
#include <cmath>
#include <vector>
#include <GL\gl.h>
#include "random.h"
#define PLANERAD2DEG M_PI/180

#include <iostream>
using namespace std;

class plane
{//class to represent a plane and a shape on a plane
public:
	point planepoint;
	myvector normal;
	random* myrandom;
	colour mycolour;
	point one;//, two;//two other points laying on the plane
	vector <line> shape;//enclosing convex shape
	plane(const point& Point=point(0.0, 0.0, 0.0), const myvector& NormalVector=myvector(0.0, 1.0, 0.0),
			const colour& Colour=colour(1.0, 1.0, 1.0)):
		planepoint(Point), normal(NormalVector.normalise()),
		myrandom(random::getinstance()),
		mycolour(Colour)
	{
		do
		{//calculating an additional point on the plane
			one=normal.crossproduct(myvector(myrandom->randomfloatcenteredatzero(10),
				myrandom->randomfloatcenteredatzero(10),
				myrandom->randomfloatcenteredatzero(10))).topoint();
		}
		while(one==planepoint);//if the point generated is the same as the original one
	}
	plane (const point& Point, const myvector& NormalVector, const point& SecondPoint, const vector<line> Shape):
		planepoint(Point), normal(NormalVector), one(SecondPoint), shape(Shape)
	{
	}
	plane(const point& One, const point& Two, const point& Three):
		planepoint(One),normal(myvector(One, Two).crossproduct(myvector(Two, Three)).normaliseme()), one(Two)
	{//creating a plane from arbitrary 3 points
	}
	plane(const plane& Other):planepoint(Other.planepoint), normal(Other.normal), myrandom(Other.myrandom),
			mycolour(Other.mycolour), one(Other.one), shape(Other.shape)
	{
	}
	~plane()
	{
	}
	plane& operator()(const point& Point, const myvector& NormalVector)
	{
		planepoint=Point;
		normal=NormalVector.normalise();
		do
		{//calculating an additional point on the plane
			one=normal.crossproduct(myvector(myrandom->randomfloatcenteredatzero(10),
				myrandom->randomfloatcenteredatzero(10),
				myrandom->randomfloatcenteredatzero(10))).topoint();
		}
		while(one==planepoint);//if the point generated is the same as the original one
		return *this;
	}
	inline
	float distanceto(const point& Point) const
	{//distance from the plane to a point
		myvector tmpvector(planepoint, Point);
		//float angle=tmpvector.angle(normal);
		//cout<<angle<<endl<<flush;
		//return cos(angle*PLANERAD2DEG)*tmpvector.getmagnitude();
		return abs(tmpvector.dotproduct(normal));
	}
	point projection(const point& Point) const
	{//projection of a point onto a plane (closest point on a plane to the point)
		myvector tmpvector(planepoint, Point);
		myvector cross=tmpvector.crossproduct(normal);
		//cout<<angle<<endl<<flush;
		return planepoint.movebyvector(normal.crossproduct(cross));
	}
	point projection(const point& Point, const float& Radius) const
	{//projection of a point onto a plane and moved from it by radius
		myvector tmpvector(planepoint, Point);
		myvector cross=tmpvector.crossproduct(normal);
		//cout<<angle<<endl<<flush;
		if (ispointabove(Point)) return planepoint.movebyvector(normal.crossproduct(cross)+normal.setmagnitude(Radius));
		else return planepoint.movebyvector(normal.crossproduct(cross)+normal.setmagnitude(-Radius));
	}
	bool ispointabove(const point& Point) const
	{//checking if a point is above the plane
		if (normal.dotproduct(myvector(projection(Point), Point)//vector from projection of the point to the point
				)//angle with respect to the normal vector
				>0.0) return true;//if it's close to 0, they are facing in the same direction
		else return false;//otherwise false
	}
	bool ispointabove(const point& Point, const float& Radius) const
	{//checking if a point is above the plane
		if (normal.dotproduct(myvector(projection(Point), Point)
				)
				>Radius) return true;
		else return false;
	}
	bool ispointbelow(const point& Point) const
	{//checking if a point is below the plane
		if (normal.dotproduct(myvector(projection(Point), Point)//vector from projection of the point to the point
				)//angle with respect to the normal vector
				<0.0) return true;//if it's close to 0, they are facing in the same direction
		else return false;//otherwise false
	}
	bool ispointbelow(const point& Point, const float& Radius) const
	{//checking if a point is below the plane
		if (normal.dotproduct(myvector(projection(Point), Point)
				)
				<-Radius) return true;
		else return false;
	}
	bool isprojectioninshape(const point& Point)const
	{//checking if a projection of a given point is inside the shape
		//Point.printme();
		if (shape.size()<3) return true;//if the shape is too small, the whole plane is used
		else
		{
			//creating projection of the point
			point projectionpoint=projection(Point);
			bool inside=true;
			for (unsigned int i=0;i<shape.size();i++)
			{//if the point is 'under' all lines
				inside*=shape.at(i).ispointbelow(projectionpoint);
				//cout<<inside<<endl<<flush;
			}
			return inside;
		}
	}
	bool isshapehit(const point& Point, const float& Radius) const
	{//simple colision detection, based on position of point projection
		if (shape.size()<3) return true;//if the shape is too small, the whole plane is used
		else
		{
			bool inside1=true;
			bool inside2=true;
			point closestpoint=projection(Point);//closest point on the plane
			for (unsigned int i=0;i<shape.size();i++)
			{//if the point is 'under' all lines
				inside1*=(shape.at(i).ispointbelow(closestpoint, Radius));
				inside2*=(shape.at(i).ispointabove(closestpoint, Radius));
			}
			return inside1+inside2;
		}
	}
	void drawplane(const float& SquareSideLength=100.0) const
	{//drawing the plane as a square
		myvector v1=myvector(planepoint, one).setmymagnitude(SquareSideLength/2);
		myvector v2=v1.crossproduct(normal);
		point a, b, c, d;
		a=planepoint.movebyvector(v1).movemebyvector(v2);
		b=planepoint.movebyvector(-v1).movebyvector(v2);
		c=planepoint.movebyvector(v1).movebyvector(-v2);
		d=planepoint.movebyvector(-v1).movebyvector(-v2);
		mycolour.setcolour();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);
			glVertex3f(c.x, c.y, c.z);
			glVertex3f(d.x, d.y, d.z);
		glEnd();
	}
	void drawboundshapelines()const
	{//drawing the bounding shape
		if (shape.size()>2)
		{
			mycolour.setcolour();
			glBegin(GL_LINE_STRIP);
				for (unsigned int i=0;i<shape.size();i++)
				{
					shape.at(i).firstdrawingpoint();
				}
				shape.at(0).firstdrawingpoint();
			glEnd();
			//colour(1.0, 1.0, 1.0).setcolour();
			//for (unsigned int i=0;i<shape.size();i++)shape.at(i).drawvector();
		}
	}
	void drawboundshapetriangles()const
	{//drawing the bounding shape
		if (shape.size()>2)
		{
			mycolour.setcolour();
			glBegin(GL_TRIANGLE_STRIP);
				for (unsigned int i=0;i<shape.size();i++)
				{
					shape.at(i).firstdrawingpoint();
				}
				shape.at(0).firstdrawingpoint();
			glEnd();
		}
	}
	inline
	void drawboundshape()const
	{//drawing the bounding shape
		drawboundshapelines();
	}
	inline
	void setshape(const vector<line> Shape)
	{//setting the shape
		shape=Shape;
	}
	void setshape(const vector<point> Points)
	{//creates a convex shape
		if (Points.size()<3) shape.clear();//if there are less than 3 points, no shape can be created
		else
		{
			myvector tmpvector;
			unsigned int size=Points.size();
			for (unsigned i=0;i<size;i++)
			{
				//tmpvector is set so it would be pointing outside of the shape
				//still being coplanar to the shape
				//modulos are used to loop the creation of the shape to use the first two points for the last two lines
				tmpvector=myvector(Points.at(i), Points.at((i+1)%size))//vector from point i to i+1
						.crossproduct(myvector(Points.at((i+1)%size), Points.at((i+2)%size)))//cross product with vector i+1, i+2 (perpenticular to both)
						.crossproduct(myvector(Points.at(i),Points.at((i+1)%size)))//cross product of previous cross product and vector betwee i and i+1 (pointing outside the shape)
						.normaliseme();//normalised
				shape.push_back(line(Points.at(i), Points.at((i+1)%size), tmpvector));
			}
		}
	}
	void setprojectedshape(const vector<point> Points)
	{//creates a convex shape using projections of set of points
		if (Points.size()<3) shape.clear();//if there are less than 3 points, no shape can be created
		else
		{
			//cout<<"setshape is setting shape"<<endl<<flush;
			myvector tmpvector;
			unsigned int size=Points.size();
			vector<point> projectedpoints;
			for (unsigned int i=0;i<size;i++)
			{
				projectedpoints.push_back(projection(Points.at(i)));
			}
			for (unsigned i=0;i<size;i++)
			{
				//tmpvector is set so it would be pointing outside of the shape
				//still being coplanar to the shape
				//modulos are used to loop the creation of the shape to use the first two points for the last two lines
				tmpvector=myvector(projectedpoints.at(i), projectedpoints.at((i+1)%size))//vector from point i to i+1
						.crossproduct(myvector(projectedpoints.at((i+1)%size), projectedpoints.at((i+2)%size)))//cross product with vector i+1, i+2 (perpenticular to both)
						.crossproduct(myvector(projectedpoints.at(i),projectedpoints.at((i+1)%size)))//cross product of previous cross product and vector betwee i and i+1 (pointing outside the shape)
						.normaliseme();//normalised
				shape.push_back(line(projectedpoints.at(i), projectedpoints.at((i+1)%size), tmpvector));
			}
		}
	}
	inline
	void setcolour(colour Colour)
	{
		mycolour=Colour;
	}
	inline
	bool operator==(const plane& Other)const
	{
		return((normal==Other.normal)//if the normal vectors are in the same direction
				&&(projection(Other.planepoint)==Other.planepoint));//and the point lies on the plane
	}
	bool unittest()
	{//to be finished if needed
		plane a, b;



		return true;
	}

	inline
	void printme()const
	{
		cout<<"Point: ";
		planepoint.printme();
		cout<<"Vector: ";
		normal.printme();
	}

	/*bool operator==(const plane& Other)const
	{
		return((normal==Other.normal)//if the normal vectors are in the same direction
				&&(Other.one==Other.one));//and the point lies on the plane
	}*/
};

#endif /* PLANE_H_ */
