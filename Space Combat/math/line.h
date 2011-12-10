#ifndef LINE_H_
#define LINE_H_
//class to define a line, also used as a line segment
#include "point.h"
#include "myvector.h"

class line
{
public:
	point one, two;//two points that make up the line
	myvector up;//a vector that is normal to the line,
	//used for checking if a given point is in a plane of the line and below the line
	myvector onetwo;//vector from first point to the second
	line(const point& One=point(0.0, 0.0, 0.0), const point& Two=point(1.0, 0.0, 0.0),
			const myvector& Up=myvector(0.0, 1.0, 0.0)): one(One), two(Two), up(Up.normalise()),
			onetwo(myvector(one, two).normaliseme())
	{
	}
	~line()
	{
	}
	inline
	line& operator()(const point& One=point(0.0, 0.0, 0.0), const point& Two=point(1.0, 0.0, 0.0),
			const myvector& Up=myvector(0.0, 1.0, 0.0))
	{
		one=One;
		two=Two;
		up=Up.normalise();
		onetwo(one, two).normaliseme();
		return *this;
	}
	inline
	line& operator()(const line& Other)
	{
		one=Other.one;
		two=Other.two;
		up=Other.up;
		onetwo=Other.onetwo;
		return *this;
	}
	inline
	line& operator=(const line& Other)
	{
		one=Other.one;
		two=Other.two;
		up=Other.up;
		onetwo=Other.onetwo;
		return *this;
	}
	float distanceto(const point& Point) const
	{//calculating distance from a line to a point
		myvector tmpvector=myvector(one, Point);//vector from one of the poitns to the queried point
		float dotproduct=onetwo.dotproduct(tmpvector);//projection of the dot product onto the line as a vector
		return sqrt(abs(tmpvector.getsquaredmagnitude()-dotproduct*dotproduct));
	}
	point projection(const point& Point) const
	{//projection of a point onto the line (closest point on the line)
		myvector tmpvector=myvector(one, Point);//vector from one of the poitns to the queried point
		return one.movebyvector(//first point moved by a vector
				onetwo. //in the direction of vector onetwo
				setmagnitude( //with distance equal to
						onetwo.dotproduct(tmpvector)));//the dotproduct of the two vectors
	}
	inline
	void drawme(void) const
	{//drawing the line
		//one.printme();
		//two.printme();
		//cout<<endl<<flush;
		glBegin(GL_LINES);
			one.drawingpoint();
			two.drawingpoint();
		glEnd();
		up.drawme(one);
	}
	inline
	void firstdrawingpoint (void) const
	{//function to return one of the points, used for drawing more sophisticated shapes optimally
		one.drawingpoint();
	}
	inline
	void drawvector (void) const
	{//drawing a noral vector
		up.drawme(one);
	}
	inline
	line operator-() const
	{//returning a line in the oposite direction
		return line(two, one);
	}
	bool ispointbelow(const point& Point) const
	{//checking is a point is below the line, with respect to the up vector
		myvector tmpvector=myvector(one, Point);//vector from one of the points to the queried point
		return (up.dotproduct(tmpvector)>0);//projection of the dot product onto the line as a vector
	}
	bool ispointabove(const point& Point) const
	{//checking is a point is above the line, with respect to the up vector
		myvector tmpvector=myvector(one, Point);//vector from one of the points to the queried point
		return (up.dotproduct(tmpvector)<0);//projection of the dot product onto the line as a vector
	}
	bool ispointbetweennodes(const point& Point) const
	{//checking is a point is in the line segment
		return ((Point.distanceto(one)<onetwo.getmagnitude())&&(Point.distanceto(two)<onetwo.getmagnitude()));
	}
	bool ispointbelow(const point& Point, const float& Radius) const
	{//checking sphere colision
		myvector tmpvector=myvector(one, Point);//vector from one of the points to the queried point
		return (up.dotproduct(tmpvector)>=Radius);//projection of the dot product onto the line as a vector
	}
	bool ispointabove(const point& Point, const float& Radius) const
	{//checking sphere colision
		myvector tmpvector=myvector(one, Point);//vector from one of the points to the queried point
		return (up.dotproduct(tmpvector)<-Radius);//projection of the dot product onto the line as a vector
	}
	inline
	void printme()const
	{
		cout<<"Line from: ";
		one.printme();
		cout<<"To: ";
		two.printme();
	}
	inline
	bool operator==(const line& Other) const
	{
		return ((one==Other.one)
				&&two==Other.two
				&&up==Other.up);
	}
};

#endif /* LINE_H_ */
