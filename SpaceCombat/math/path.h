#ifndef PATH_H_
#define PATH_H_

#include "point.h"
#include "line.h"
#include "plane.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;
#include <GL\gl.h>


class pathsegment
{//a class to represent a segment of the path - a line between two points and a plane at the end point (for steering)
public:
	line myline;
	plane myplane;
	pathsegment(const line& Line=line()):
		myline(Line),
		myplane(Line.two, -(Line.onetwo.getsquaredmagnitude()!=0.0?Line.onetwo:myvector(1.0, 0.0, 0.0)))
	{
	}
	~pathsegment()
	{
	}
	inline
	pathsegment& operator()(const line& Line)
	{
		myline=Line;
		myplane(Line.two, -Line.onetwo);
		return *this;
	}
	inline
	bool operator==(const pathsegment& Other) const
	{
		return((myline==Other.myline)&&
				(myplane==Other.myplane));
	}
	inline
	float distancetoend(const point& Position)const
	{//returns the distance to the destination
		return distancetoendofline(Position);
	}
	inline
	float distancetoplane(const point& Position)const
	{//returns the distance to the destination
		return myplane.distanceto(Position);
		//return Position.distanceto(myline.two);
	}
	inline
	float distancetoendofline(const point& Position)const
	{//returns the distance to the destination
		return Position.distanceto(myline.two);
	}
	inline
	void printme()
	{
		cout<<"Plane: ";
		myplane.printme();
		myline.printme();
	}
	inline
	float strongdistancetoend(const point& Position)const
	{//returns the distance to the destination or the line, whichever is greater
		float tmpdistance(myplane.distanceto(Position));
		float tmpdistance2(myline.distanceto(Position));

		/*myplane.printme();
		myline.printme();

		cout<<"d1 "<<tmpdistance<<endl;
		cout<<"d2 "<<tmpdistance<<endl<<endl<<flush;*/

		if (tmpdistance>tmpdistance2) return tmpdistance;
		return tmpdistance2;
	}
};



class path
{
	line tmpline;
	point tmppoint;
	vector <point> points;
	vector <line> lines;
public:
	vector <pathsegment> segments;
	path():
		tmpline(),
		tmppoint(),
		points(),
		lines(),
		segments()
	{
	}
	path(vector<point> Points):
			tmpline(),
			tmppoint(),
			points(),
			lines(),
			segments()
	{
		for (unsigned int i=0;i<Points.size();i++)
		{
			points.push_back(Points.at(i));
		}
		for (unsigned int i=0;i<points.size();i++)
		{
			lines.push_back(line(points.at(i), points.at((i+1)%points.size())));
			segments.push_back(pathsegment(lines.at(i)));
		}
	}
	path(const path& Other):
		points(Other.points),
		lines(Other.lines),
		segments(Other.segments)

	{
	}
	~path()
	{
	}
	void addpoint(const point& Point)
	{
		points.push_back(Point);
		if (!lines.empty())
		{//if lines exist, the last one has to be changed to be 'hooked' to the new point
			lines.back()(points.at((points.size()-2)%points.size()), points.back());
			segments.back()(lines.back());
		}
		//adding new line from the end point to the first one
		lines.push_back(line(points.back(), points.front()));
		segments.push_back(lines.back());
	}
	void addpoints(const vector<point>& Points)
	{
		for (unsigned int i=0;i<Points.size();i++)
		{
			points.push_back(Points.at(i));
		}
		if (!lines.empty())
		{
			lines.back()(points.at((lines.size()-2)%lines.size()), points.at((lines.size()-1)%lines.size()));
			segments.back()(lines.back());
			for (unsigned int i=0;i<Points.size();i++)
			{
				lines.push_back(line(points.at(lines.size()), points.at(lines.size()%points.size())));
				segments.push_back(lines.back());
			}
		}
		else
		{
			buildlinesandsegments();
		}
	}
	point popfrontpoint()
	{
		if (!points.empty())
		{
			tmppoint=points.front();
			points.erase(points.begin());
			lines.erase(lines.begin());
			segments.erase(segments.begin());
			if (!points.empty())
			{
				lines.back()(points.back(), points.front());
				segments.back()(lines.back());
			}
			return tmppoint;
		}
		else return point();
	}
	void buildlinesandsegments()
	{
		for (unsigned int i=0;i<points.size();i++)
		{
			lines.push_back(line(points.at(i), points.at((i+1)%points.size())));
			segments.push_back(lines.back());
		}
	}
	line popfrontline()
	{
		if (lines.size()>0)
		{
			tmpline(lines.front());

			points.erase(points.begin());
			lines.erase(lines.begin());
			segments.erase(segments.begin());
			if(lines.size()>0)
			{
				lines.back()(points.back(), points.front());
				segments.back()(lines.back());
			}

			return tmpline;
		}
		else return line();
	}
	line givelineloop(const unsigned int Number=0)const
	{
		if (lines.size()>0)
		{
			return lines.at(Number%lines.size());
		}
		else return line();
	}
	line giveline(const unsigned int Number=0)const
	{
		if(lines.size()>0)if(Number<lines.size())
		{
			return lines.at(Number);
		}
		return line();
	}
	pathsegment givesegmentloop(const unsigned int Number=0)const
	{
		//cout<<"Size: "<<segments.size()<<endl<<flush;
		if (segments.size()>0)
		{
			return segments.at(Number%segments.size());
		}
		else return pathsegment();
	}
	pathsegment givesegment(const unsigned int Number=0)const
	{
		if(segments.size()>0)if(Number<segments.size())
		{
			return segments.at(Number);
		}
		return pathsegment();
	}
	void setpath(vector<point> Points)
	{
		points=Points;
		lines.clear();
		segments.clear();
		buildlinesandsegments();
	}
	path& operator()(vector<point> Points)
	{//just like setpath
		points=Points;
		lines.clear();
		segments.clear();
		buildlinesandsegments();
		return *this;
	}
	path& operator()(const path& Other)
	{
		points=Other.points;
		lines=Other.lines;
		segments=Other.segments;
		return *this;
	}
	path operator-()const
	{
		vector<point> tmppoints;
		for (unsigned int i=points.size()-1;i>0;i--)
		{
			tmppoints.push_back(points.at(i));
		}
		return path(tmppoints);
	}
	path operator+(const path& Other)
	{
		vector<point>tmp(points);
		tmp.insert(tmp.end(),Other.points.begin(),Other.points.end());
		return path(tmp);
	}
	path& operator+=(const path& Other)
	{
		points.insert(points.end(),Other.points.begin(),Other.points.end());
		return *this;
	}
	bool empty()
	{
		return points.empty();
	}
	void drawme(const unsigned int Mode=0) const
	{
		if(points.size()>1)
		{
			glBegin(GL_LINE_STRIP);
			for (unsigned int i=0;i<points.size();i++)
			{
				points.at(i).drawingpoint();
			}
			if (Mode==0)points.at(0).drawingpoint();
			glEnd();
		}
	}
	void drawmelooped() const
	{
		if(points.size()>1)
		{
			glBegin(GL_LINE_STRIP);
			for (unsigned int i=0;i<points.size();i++)
			{
				points.at(i).drawingpoint();
			}
			points.at(0).drawingpoint();
			glEnd();
		}
	}
	void drawmesingle() const
	{
		if(points.size()>1)
		{
			glBegin(GL_LINE_STRIP);
			for (unsigned int i=0;i<points.size();i++)
			{
				points.at(i).drawingpoint();
			}
			glEnd();
		}
	}
	void clear()
	{
		points.clear();
		lines.clear();
		segments.clear();
	}

	void printme()const
	{
		for (unsigned int i=0;i<points.size();i++)
		{
			points.at(i).printme();
		}
	}

	unsigned int giveclosestpathsegmentnumber(const point& Position=point(0.0, 0.0, 0.0))
	{
		unsigned int anwser=0;
		float distance=10000.0, tmpdistance=0;
		for(unsigned int i=0;i<segments.size();i++)
		{
			tmpdistance=segments.at(i).distancetoendofline(Position);
			if(tmpdistance<distance)
			{
				anwser=i;
				distance=tmpdistance;
			}
		}
		if(anwser==segments.size()-1)return anwser;
		else return anwser+1;
	}
	unsigned int size()
	{//returns how many segments there are in the path
		return segments.size();
	}

	bool unittest();
};

#endif /* PATH_H_ */
