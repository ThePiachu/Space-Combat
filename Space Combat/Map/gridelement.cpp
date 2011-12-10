/*
 * gridelement.cpp
 *
 *  Created on: 2010-01-16
 *      Author: ThePiachu
 */

#include "gridelement.h"

	vector<point> gridelement::givemissingneigbours()
	{//a funcion that returns points corresponding to neighbours this node is missing
		vector <point> anwser;
		anwser.push_back(point(center.x+2.0*width, center.y-2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x+2.0*width, center.y-2.0*width, center.z));
		anwser.push_back(point(center.x+2.0*width, center.y-2.0*width, center.z+2.0*width));
		anwser.push_back(point(center.x+2.0*width, center.y, center.z-2.0*width));
		anwser.push_back(point(center.x+2.0*width, center.y, center.z));
		anwser.push_back(point(center.x+2.0*width, center.y, center.z+2.0*width));
		anwser.push_back(point(center.x+2.0*width, center.y+2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x+2.0*width, center.y+2.0*width, center.z));
		anwser.push_back(point(center.x+2.0*width, center.y+2.0*width, center.z+2.0*width));


		anwser.push_back(point(center.x, center.y-2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x, center.y-2.0*width, center.z));
		anwser.push_back(point(center.x, center.y-2.0*width, center.z+2.0*width));
		anwser.push_back(point(center.x, center.y, center.z-2.0*width));
		//anwser.push_back(point(center.x, center.y, center.z));
		anwser.push_back(point(center.x, center.y, center.z+2.0*width));
		anwser.push_back(point(center.x, center.y+2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x, center.y+2.0*width, center.z));
		anwser.push_back(point(center.x, center.y+2.0*width, center.z+2.0*width));


		anwser.push_back(point(center.x-2.0*width, center.y-2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x-2.0*width, center.y-2.0*width, center.z));
		anwser.push_back(point(center.x-2.0*width, center.y-2.0*width, center.z+2.0*width));
		anwser.push_back(point(center.x-2.0*width, center.y, center.z-2.0*width));
		anwser.push_back(point(center.x-2.0*width, center.y, center.z));
		anwser.push_back(point(center.x-2.0*width, center.y, center.z+2.0*width));
		anwser.push_back(point(center.x-2.0*width, center.y+2.0*width, center.z-2.0*width));
		anwser.push_back(point(center.x-2.0*width, center.y+2.0*width, center.z));
		anwser.push_back(point(center.x-2.0*width, center.y+2.0*width, center.z+2.0*width));


		//deleting neighbours tha already exist

		for (unsigned int i=0;i<this->neighbours.size();i++)
		{
			for (int j=anwser.size()-1;j>=0;j--)
			{
				//cout<<"i"<<i<<"j"<<j<<endl<<flush;
				if (anwser.at(j)==(this->neighbours.at(i)->center))
				{
					anwser.erase(anwser.begin()+j);
					break;
				}
			}
		}
		//cout<<"size:"<<anwser.size()<<endl<<flush;
		return anwser;
	}

	void gridelement::drawme(const unsigned int Mode=1) const
	{//drawing cube
		if(Mode%2==0)
		{
			glColor3f(0.2f,0.2f,0.2f);
			glBegin(GL_LINES);
				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z-this->width);
				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z+this->width);

				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z-this->width);
				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z-this->width);

				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z-this->width);
				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z+this->width);

				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z+this->width);
				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z+this->width);


				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z-this->width);
				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z+this->width);

				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z-this->width);
				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z-this->width);

				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z-this->width);
				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z+this->width);

				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z+this->width);
				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z+this->width);


				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z-this->width);
				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z-this->width);

				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z-this->width);
				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z-this->width);

				glVertex3f(this->center.x-this->width, this->center.y-this->width, this->center.z+this->width);
				glVertex3f(this->center.x+this->width, this->center.y-this->width, this->center.z+this->width);

				glVertex3f(this->center.x-this->width, this->center.y+this->width, this->center.z+this->width);
				glVertex3f(this->center.x+this->width, this->center.y+this->width, this->center.z+this->width);
			glEnd();
		}

		if(Mode%3==0)
		{
			glColor3f(0.7f,0.7f,0.7f);
			//drawing connection between nodes
			glBegin(GL_LINES);
				for (unsigned int i=0;i<this->neighbours.size();i++)
				{
					this->center.drawingpoint();
					this->neighbours.at(i)->center.drawingpoint();
				}
			glEnd();
		}
		/*if(Mode%5==0)
		{
			for(unsigned int i=0;i<asteroidlist.size();i++)
			{
				asteroidlist.at(i)->drawme(1, 1.1);
			}
		}*/
	}

