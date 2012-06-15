#ifndef PARTICLE_H_
#define PARTICLE_H_
//classes for handling particles
#include "math.h"
//#include "colour.h"
#include <vector>
#include <iostream>

using namespace std;

class particle
{//a single particle
public:
	point location, oldlocation;
	myvector velocity, acceleration;
	colour mycolour;
	float radius;
	particle(const point& Location=point(0.0, 0.0, 0.0), const myvector& Velocity=myvector(0.0, 0.0, 0.0),
			const myvector& Acceleration=myvector(0.0, 0.0, 0.0), const float& Radius=0.0):
		location(Location),oldlocation(location), velocity(Velocity), acceleration(Acceleration),
		mycolour(), radius(Radius)
	{
		mycolour.randomcolour();
	}
	~particle()
	{
	}
	particle& setme(const point& Location=point(0.0, 0.0, 0.0), const myvector& Velocity=myvector(0.0, 0.0, 0.0),
			const myvector& Acceleration=myvector(0.0, 0.0, 0.0), const float& Radius=0.0)
	{//setting the particle
		location=Location;
		velocity=Velocity;
		acceleration=Acceleration;
		radius=Radius;
		return *this;
	}
	void setradius(const float& Radius)
	{
		radius=Radius;
	}
	void drawme(bool DrawSolid=true, bool DrawVelocity=false,
			const unsigned int& Slices=5, const unsigned int& Stacks=5)
	{//drawing the particle, either as point or point and vector
		mycolour.setcolour();
		if (radius==0.0)
		{//point
			glPointSize(1.0);
			location.drawme();
			if (DrawVelocity) velocity.drawme(location);
		}
		else
		{
			if (DrawSolid)
			{
				glPushMatrix();
					glTranslatef(location.x, location.y, location.z);
					glutSolidSphere(radius, Slices, Stacks);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
					glTranslatef(location.x, location.y, location.z);
					glutWireSphere(radius, Slices, Stacks);
				glPopMatrix();
			}
		}
	}
	void moveme()
	{//moving the particle
		velocity+=acceleration;//changing speed
		oldlocation=location;//saving previous locaiton
		location.movemebyvector(velocity);//moving the particle
	}
	void setcolour(const colour& Colour)
	{//setting colour of the particle
		mycolour=Colour;
	}
	bool reflectiveplanecollision (const plane& Plane)
	{//reflective colision with a plane
		//plane tmpplane=Plane+radius;//creates a temporary plane for colision detection
		if ((Plane.ispointabove(oldlocation)&&Plane.ispointabove(location))||
				(Plane.ispointbelow(oldlocation)&&Plane.ispointbelow(location)))
		{//if both positions are on the same side of the plane and new position is far enough from the plane
			return false;//no colision
		}
		else
		{//otherwise colision
			velocity.reflectme(Plane.normal);
			point tmppoint=Plane.projection(location, radius);
			location=tmppoint//new location is equal to projection of the new point onto the plane
									.movemebyvector(//moved moved from the plane by a distance
											-myvector(tmppoint, location));//equal to the distance to the plane in oposite direction
			return true;//colision detected
		}
	}
	bool reflectiveshapecolision (const plane& Shape)
	{//reflective colision with a shape

		if ((Shape.ispointabove(oldlocation, radius)&&Shape.ispointabove(location, radius))//either both are far enough from the plane from the top
				||(Shape.ispointbelow(oldlocation, radius)&&Shape.ispointbelow(location, radius))) return false;//or bottom
		else
		{
			if (Shape.isshapehit(location, radius))
			{
				//plane tmpshape=Shape.movetowwardthepoint(location, radius);
				velocity.reflectme(Shape.normal);
				point tmppoint=Shape.projection(location, radius);
				location=tmppoint//new location is equal to projection of the new point onto the plane
							.movemebyvector(//moved moved from the plane by a distance
									-myvector(tmppoint, location));//equal to the distance to the plane in oposite direction
				return true;
			}
			return false;
		}
	}
	bool reflectivespherecolision (const boundingsphere& Sphere)
	{//reflective colision with a sphere
		line tmpline(oldlocation, location);
		//boundingsphere tmpsphere=Sphere+radius;//creates a temporary sphere for colision detection
		if (Sphere.ishit(tmpline, radius))
		{
			point tmppoint=Sphere.intersection(tmpline, radius);//finding intersection
			velocity=Sphere.reflection(velocity, tmppoint);//reflecting velocity
			location=Sphere.reflection(tmpline, tmppoint);//reflecting position
			return true;
		}
		return false;
	}
	bool colision (const plane& Plane) const
	{//detection of colision that does not reflect the particle
		//plane tmpplane=Plane+radius;//creates a temporary plane for colision detection
		if ((Plane.ispointabove(oldlocation)&&Plane.ispointabove(location))||
				(Plane.ispointbelow(oldlocation)&&Plane.ispointbelow(location))) return false;
		else return true;
	}
	bool shapecolision (const plane& Shape) const
	{//detection of colision that does not reflect the particle
		//plane tmpshape=Shape+radius;//creates a temporary plane for colision detection
		if ((Shape.ispointabove(oldlocation)&&Shape.ispointabove(location))||
				(Shape.ispointbelow(oldlocation)&&Shape.ispointbelow(location))) return false;
		else
		{
			if (Shape.isprojectioninshape(location))
			{
				return true;
			}
			return false;
		}
	}
	bool colision (const boundingsphere& Sphere) const
	{//detection of colision that does not reflect the particle
		return Sphere.ishit(oldlocation, location, radius);
	}
	bool colourchangingplanecolision (const plane& Plane)
	{
		if (colision(Plane))
		{
			mycolour.setme(Plane.mycolour);
			return true;
		}
		return false;
	}
	bool colourchangingshapecolision (const plane& Shape)
	{
		if (shapecolision(Shape))
		{
			mycolour.setme(Shape.mycolour);
			return true;
		}
		return false;
	}
	bool colourchangingspherecolision (const boundingsphere& Sphere)
	{
		if (colision(Sphere))
		{
			mycolour.setme(Sphere.mycolour);
			return true;
		}
		return false;
	}
	bool terminatingspherecollision (const boundingsphere& Sphere)const
	{
		if (colision(Sphere))return true;
		return false;
	}
	bool terminatingplanecollision (const plane& Plane)const
	{
		if (colision(Plane))return true;
		return false;
	}
	bool terminatingshapecollision (const plane& Shape)const
	{
		if (shapecolision(Shape))return true;
		return false;
	}
};



























class particles
{
	//volatile unsigned int amount;

	volatile unsigned int raintoadd, spraytoadd;

	float rainheight;
	point raincenter;
	float rainsidelength;
	myvector raindirection;
	float rainanglespread;

	point sprayorigin;
	myvector spraydirection;
	float sprayanglespread;

	random* myrandom;
	myvector gravity;
	float particleradius;
public:
	vector <particle> cluster;
	vector <plane> reflectiveplanes, terminatingplanes, colourchangingplanes;
	vector <plane> reflectiveshapes, terminatingshapes, colourchangingshapes;
	vector<boundingsphere> colourchangingspheres;
	vector<boundingsphere> reflectivespheres;
	vector<boundingsphere> terminatingspheres;
	particles(const float& ParticleRadius=0.1):
		myrandom(random::getinstance()), gravity(0.0, -0.1, 0.0), particleradius(ParticleRadius)
	{
	}/*
	particles():
		amount(0), myrandom(random::getinstance()), gravity(0.0, -0.1, 0.0)
	{
	}*/
	void setrain(const float& Height=5.0, const myvector& Direction=myvector(0.0, -1.0, 0.0), const float& AngleSpread=10)
	{
		rainheight=Height;
		raindirection=Direction;
		rainanglespread=AngleSpread;
		/*
		if (amount)for (unsigned int i=0;i<amount;i++)
		{
			cluster.at(i).setme(
				//position
				point(myrandom->randomfloatcenteredatzero(2.0*distance), Height, myrandom->randomfloatcenteredatzero(2.0*distance)),
				//initial speed
				myvector(0.0, myrandom->randomfloatpositive(1.0, -1.0), 0.0),
				//acceleration
				myvector(0.0, -0.1,0.0));
		}*/
	}
	void setspray(const point& Origin=point(0.0, 0.0, 0.0),
			const myvector& Direction=myvector(0.0, 0.5, 0.0),
			const float& AngleSpread=30)
	{
		sprayorigin=Origin;
		spraydirection=Direction;
		sprayanglespread=AngleSpread;
		/*
		if (amount)for (unsigned int i=0;i<amount;i++)
		{
			cluster.at(i).setme(
					//position
				point(Origin),
				//initial speed
				myvector(Direction+myvector(myrandom->randomfloatpositive(2.0*Spread, -Spread), 0.0, myrandom->randomfloatpositive(Spread, -Spread))).setmymagnitude(0.1),
				//acceleration
				myvector(0.0, -0.01, 0.0));
		}*/
	}

	void addspray(unsigned int Amount=1)
	{
		//spraytoadd+=Amount;
		addsprayparticles(Amount);
	}
	void addrain(unsigned int Amount=1)
	{
		//raintoadd+=Amount;
		addrainparticles(Amount);
	}

	void addsprayparticles(unsigned int Amount=1)
	{
		for (unsigned int i=0;i<Amount;i++)
		{
		cluster.push_back(particle(sprayorigin,
				myrandom->randomsprayposition(spraydirection, sprayanglespread), gravity, particleradius
				));
		}
	}
	void addrainparticles(unsigned int Amount=1)
	{
		for (unsigned int i=0;i<Amount;i++)
		{
		cluster.push_back(particle(point(myrandom->randomfloatcenteredatzero(10.0), rainheight, myrandom->randomfloatcenteredatzero(10.0)),
				myrandom->randomsprayposition(myvector(0.0, -1.0, 0.0), rainanglespread), gravity, particleradius
				));
		}
	}




	void addreflectiveplane(plane Plane)
	{
		reflectiveplanes.push_back(Plane);
	}
	void addterminatingplane(plane Plane)
	{
		terminatingplanes.push_back(Plane);
	}
	void addcolourchangingplane(plane Plane)
	{
		colourchangingplanes.push_back(Plane);
	}


	void addreflectiveshape(plane Shape)
	{
		reflectiveshapes.push_back(Shape);
	}
	void addterminatingshape(plane Shape)
	{
		terminatingshapes.push_back(Shape);
	}
	void addcolourchangingshape(plane Shape)
	{
		colourchangingshapes.push_back(Shape);
	}


	void addreflectivesphere(boundingsphere Sphere)
	{
		reflectivespheres.push_back(Sphere);
	}
	void addcolourchangingsphere(boundingsphere Sphere)
	{
		colourchangingspheres.push_back(Sphere);
	}
	void addterminatingsphere(boundingsphere Sphere)
	{
		terminatingspheres.push_back(Sphere);
	}


	void moveparticles()
	{
		/*addrainparticles(raintoadd);
		raintoadd=0;
		addsprayparticles(spraytoadd);
		spraytoadd=0;*/
		vector <unsigned int> checkagain;
		bool check=false;
		if (cluster.size()>0)cluster.erase(cluster.begin());//erasing old particles one per clock cycle
		unsigned int j;
		for (unsigned int i=0;i<cluster.size();i++)
		{
			cluster.at(i).moveme();
		}
		for (unsigned int i=0;i<cluster.size();i++)
		{
			for (j=0;j<terminatingplanes.size();j++)if(cluster.at(i).terminatingplanecollision
					(terminatingplanes.at(j)))
		{
				cluster.erase(cluster.begin()+i);
				i--;
				break;
		}
			if (i>=cluster.size())break;
		}
		for (unsigned int i=0;i<cluster.size();i++)
		{
			for (j=0;j<terminatingshapes.size();j++)if(cluster.at(i).terminatingshapecollision
					(terminatingshapes.at(j)))
			{
				cluster.erase(cluster.begin()+i);
				j--;
				if (i==cluster.size())break;
			}
		}
		for (unsigned int i=0;i<cluster.size();i++)
		{
			for (j=0;j<terminatingspheres.size();j++)if(cluster.at(i).terminatingspherecollision
					(terminatingspheres.at(j)))
			{
				cluster.erase(cluster.begin()+i);
				//cout<<amount--<<endl<<flush;
				j--;
				if (i==cluster.size())break;
			}
		}
		for (unsigned int i=0;i<cluster.size();i++)
		{
			check=false;
			for(j=0;j<reflectiveplanes.size();j++) check+=cluster.at(i).reflectiveplanecollision
					(reflectiveplanes.at(j));
			for(j=0;j<reflectiveshapes.size();j++) check+=cluster.at(i).reflectiveshapecolision
					(reflectiveshapes.at(j));
			for(j=0;j<reflectivespheres.size();j++) check+=cluster.at(i).reflectivespherecolision
					(reflectivespheres.at(j));
			if (check==true) checkagain.push_back(i);
		}

		if (checkagain.size()>0)
		{
			short unsigned int iterations=0;
			do
			{
				vector<unsigned int> tmpcheckagain;
				for (unsigned int i=0;i<checkagain.size();i++)
				{
					check=false;
					for(j=0;j<reflectiveplanes.size();j++) check+=cluster.at(checkagain.at(i)).reflectiveplanecollision
							(reflectiveplanes.at(j));
					for(j=0;j<reflectiveshapes.size();j++) check+=cluster.at(checkagain.at(i)).reflectiveshapecolision
							(reflectiveshapes.at(j));
					for(j=0;j<reflectivespheres.size();j++) check+=cluster.at(checkagain.at(i)).reflectivespherecolision
							(reflectivespheres.at(j));
					if (check==true) tmpcheckagain.push_back(checkagain.at(i));
				}
				checkagain=tmpcheckagain;
				iterations++;
			}while ((iterations<20)&&(checkagain.size()>0));
		}

		/*if (checkagain.size()>0)
		{//if there are still some particles coliding, they are deleted
			sort(checkagain.begin(), checkagain.end());
			for (unsigned int i=0;i<checkagain.size();i++)
			{//erases remaining particles, from the last to the first one
				cluster.erase(cluster.begin()+checkagain.at(i));
			}
		}*/

		for (unsigned int i=0;i<cluster.size();i++)
		{
			for(j=0;j<colourchangingplanes.size();j++) cluster.at(i).colourchangingplanecolision
					(colourchangingplanes.at(j));
			for(j=0;j<colourchangingshapes.size();j++) cluster.at(i).colourchangingshapecolision
					(colourchangingshapes.at(j));
			for(j=0;j<colourchangingspheres.size();j++) cluster.at(i).colourchangingspherecolision
					(colourchangingspheres.at(j));
		}
	}
	unsigned int particlecount (void) const
	{//returning the number of particles
		return cluster.size();
	}
	void setparticleradius(const float& Radius)
	{
		particleradius=Radius;
		for (unsigned int i=0;i<cluster.size();i++)
		{
			cluster.at(i).setradius(Radius);
		}
	}
	void drawme()
	{

		for (unsigned int i=0;i<cluster.size();i++)
		{
			cluster.at(i).drawme();
			//reflectiveplanes.at(0).projection(cluster.at(i).location).drawme();
			//myvector(reflectiveplanes.at(0).projection(cluster.at(i).location), cluster.at(i).location)
			//	.drawme(reflectiveplanes.at(0).projection(cluster.at(i).location));
		}
	}
	void clear(void)
	{
		cluster.clear();
	}
};

#endif /* PARTICLE_H_ */
