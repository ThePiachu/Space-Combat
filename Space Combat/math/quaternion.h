#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "point.h"
#include "myvector.h"
#include <iostream>
using namespace std;
#define QUATTOLERANCE 0.00001f
#define QUATRAD2DEG M_PI/180
#include "mymatrix.h"
class quaternion
{//class to represent quaternions
public:
	float w;
	myvector v;
	quaternion(const float& W=1.0, const float& X=0.0, const float& Y=0.0, const float& Z=0.0): w(W), v(X, Y, Z)
	{
	}
	quaternion(const float& W, const myvector& V): w(W), v(V)
	{
	}
	quaternion (const myvector& V, const float& Angle, const bool& UseRad=true):
	w(1.0*(float)cos(Angle/2.0*(UseRad?QUATRAD2DEG:1.0))),//initialization from axis angle
		v(V*(float)sin(Angle/2.0*(UseRad?QUATRAD2DEG:1.0)))
	{
	}
	quaternion(const quaternion& Q): w(Q.w), v(Q.v)
	{
	}
	quaternion(const mymatrix& M)://initialization from rotation matrix
		w(0.5*sqrt(1+M.matrix[0]+M.matrix[5]+M.matrix[10])),
		v((M.matrix[6]-M.matrix[9])/(4.0*w),
			(M.matrix[8]-M.matrix[2])/(4.0*w),
			 (M.matrix[1]-M.matrix[4])/(4.0*w))
	{
	}
	quaternion(const myvector& From, const myvector& To)://initialization for transforming from one vector to another
		w(1.0*(float)cos(From.radangle(To)/2.0)),
		v(From.perpenticulartoplane(To).normaliseme()*(float)sin(From.radangle(To)/2.0))
	{
	}
	quaternion(const myvector& CrossProduct)
		//initializing a quaternion using a cross vector of two normalised vectors
		//|cp|=sin(angle)
	:w(1.0*(float)cos(asinf(CrossProduct.getmagnitude())/2.0)),
	 v(CrossProduct.normalise()*(float)sin(asinf(CrossProduct.getmagnitude())))
	{
	}
	~quaternion(void)
	{
	}
	inline
	quaternion& operator()(const quaternion& Other)
	{
		w=Other.w;
		v=Other.v;
		return *this;
	}
	inline
	quaternion& operator= (const quaternion& Other)
	{//assignment from another quaternion
		w=Other.w;
		v=Other.v;
		return *this;
	}
	quaternion& operator= (const mymatrix& M)
	{//assignment from matrix
		w=0.5*sqrt(1+M.matrix[0]+M.matrix[5]+M.matrix[10]);
		v=myvector((M.matrix[6]-M.matrix[9])/(4.0*w),
			(M.matrix[8]-M.matrix[2])/(4.0*w),
			 (M.matrix[1]-M.matrix[4])/(4.0*w));
		return *this;
	}
	inline
	bool operator== (const quaternion& Other) const
	{//comparison
		return ((w==Other.w)&&(v==Other.v));
	}
	inline
	bool operator!= (const quaternion& Other) const
	{//comparison
		return !((w==Other.w)&&(v==Other.v));
	}
	inline
	quaternion setmagnitude(const float& Magnitude) const
	{//setting the magnitude of quaternion vector
		return quaternion(*this).setmymagnitude(Magnitude);
	}
	inline
	quaternion& setmymagnitude(const float& Magnitude)
	{//setting the magnitude of quaternion vector
		float tmp=Magnitude/magnitude();
		w*=tmp;
		v*=tmp;
		return *this;
	}
	inline
	float magnitude() const
	{//returning the magnitude of the quaternion
		return sqrt(w*w+v.getsquaredmagnitude());
	}
	inline
	float getsquaredmagnitude()const
	{//returning the square of the magnitude of the quaternion
		return w*w+v.getsquaredmagnitude();
	}
	quaternion& normaliseme(const float& Tolerance=QUATTOLERANCE)
	{//normalisation of the quaternion
		float squaredmagnitude=w*w+v.x*v.x+v.y*v.y+v.z*v.z;
		if (squaredmagnitude==0)
		{
			//error
			//exit(-1);
			w=1.0;
			v=basicvector(0.0, 0.0, 0.0);
			return *this;
		}
		else if (fabs(squaredmagnitude-1.0f)<Tolerance)
		{//if quaternion is close enough to normal, no operation is performed
			//do nothing
			return *this;
		}
		else
		{
			squaredmagnitude=sqrt(squaredmagnitude);
			w/=squaredmagnitude;
			v/=squaredmagnitude;
			return *this;
		}
	}
	quaternion normalise(const float& Tolerance=QUATTOLERANCE) const
	{//normalisation of the quaternion
		float squaredmagnitude=w*w+v.x*v.x+v.y*v.y+v.z*v.z;
		if (squaredmagnitude==0)
		{
			//error
			//exit(-1);
			return quaternion ();
		}
		else if (fabs(squaredmagnitude-1.0f)<Tolerance)
		{
			//do nothing
			return quaternion (*this);
		}
		else
		{
			squaredmagnitude=sqrt(squaredmagnitude);
			return quaternion (w/squaredmagnitude, v/squaredmagnitude);
		}
	}
	inline
	quaternion conjugate(void) const
	{//quaternion conjugate
		return quaternion (w, -v);
	}
	inline
	quaternion inverse(void) const
	{//inverse of the quaternion
		float tmp=getsquaredmagnitude();
		return conjugate()/tmp;
	}
	inline
	quaternion operator/ (const float& HowMuch) const
	{//scaling of the quaternion
		return quaternion (w/HowMuch, v/HowMuch);
	}
	inline
	quaternion& operator/= (const float& HowMuch)
	{//scaling of the quaternion
		w/=HowMuch;
		v/=HowMuch;
		return *this;
	}
	inline
	quaternion unit() const
	{//returning a unit vector in the direction of this quaternion
		float tmp=magnitude();
		if (tmp==0.0)
		{
			return quaternion();
		}
		else
		{
			return (*this)/tmp;
		}
	}
	inline
	quaternion& unitme()
	{//making the quaternion unit
		float tmp=magnitude();
		if (tmp==0.0)
		{
			w=1.0;
			v=myvector(0.0, 0.0, 0.0);
			return *this;
		}
		else
		{
			return (*this)/=tmp;
		}
	}
	inline
	quaternion identitymult(void) const
	{//returning unit multiplication quaternion
		return quaternion (1.0, 0.0, 0.0, 0.0);
	}
	inline
	quaternion identityadd(void) const
	{//returning unit addition quaternion
		return quaternion (0.0, 0.0, 0.0, 0.0);
	}
	inline
	quaternion& identitymultme(void)
	{//making the quaternion unit multiplication
		w=1.0;
		v=myvector(0.0, 0.0, 0.0);
		return *this;
	}
	inline
	quaternion& identityaddme(void)
	{//making the quaternion unit addition
		w=0.0;
		v=myvector(0.0, 0.0, 0.0);
		return *this;
	}
	quaternion& rotationbetweentwovectorsme(const myvector& From, const myvector& To)
	{
		w=1.0*(float)cos(From.radangle(To)/2.0);
		v=From.perpenticulartoplane(To).normaliseme()*(float)sin(From.radangle(To)/2.0);
		return *this;
	}
	inline
	quaternion rotationbetweentwovectors(const myvector& From, const myvector& To)
	{
		return quaternion(From, To);
	}
	quaternion operator* (const quaternion& Other) const
	{//multiplying two quaternions
		return quaternion(w * Other.w - v.x * Other.v.x - v.y * Other.v.y - v.z * Other.v.z,
							w * Other.v.x + v.x * Other.w + v.y * Other.v.z - v.z * Other.v.y,
								w * Other.v.y - v.x * Other.v.z + v.y * Other.w + v.z * Other.v.x,
									w * Other.v.z + v.x * Other.v.y - v.y * Other.v.x + v.z * Other.w);
	}
	quaternion& operator*= (const quaternion& Other)
	{//multiplying two quaternions
		float tmpw=w * Other.w - v.x * Other.v.x - v.y * Other.v.y - v.z * Other.v.z;
		v=myvector(w * Other.v.x + v.x * Other.w + v.y * Other.v.z - v.z * Other.v.y,
						w * Other.v.y - v.x * Other.v.z + v.y * Other.w + v.z * Other.v.x,
							w * Other.v.z + v.x * Other.v.y - v.y * Other.v.x + v.z * Other.w);
		w=tmpw;
		return *this;
	}
	inline
	quaternion operator* (const float& Amount) const
	{//scaling the quaternion
		return quaternion(w*Amount, v*Amount);
	}
	inline
	quaternion& operator*= (const float& Amount)
	{//scaling the quaternion
		w*=Amount;
		v*=Amount;
		return *this;
	}
	inline
	quaternion& pitchme(const float& Angle)
	{//rotating around x axis
		(*this)*=quaternion(myvector(1.0, 0.0, 0.0), Angle);
		return *this;
	}
	inline
	quaternion& yawme(const float& Angle)
	{//rotating around y axis
		(*this)*=quaternion(myvector(0.0, 1.0, 0.0), Angle);
		return *this;
	}
	inline
	quaternion& rollme(const float& Angle)
	{//rotating around z axis
		(*this)*=quaternion(myvector(0.0, 0.0, 1.0), Angle);
		return *this;
	}
	inline
	quaternion pitch(const float& Angle) const
	{//rotating around x axis
		return quaternion(*this)*quaternion(myvector(1.0, 0.0, 0.0), Angle);
	}
	inline
	quaternion yaw(const float& Angle) const
	{//rotating around y axis
		return quaternion(*this)*quaternion(myvector(0.0, 1.0, 0.0), Angle);
	}
	inline
	quaternion roll(const float& Angle) const
	{//rotating around z axis
		return quaternion(*this)*quaternion(myvector(0.0, 0.0, 1.0), Angle);
	}
	mymatrix rotationmatrix(void)
	{//turning the quaternion into the rotation matrix
		normaliseme();
		static quaternion copy;
		static mymatrix anwser;

		if(copy!=(*this))
		{//only performing calculations when they are needed (quaternion has changed)
			float wx = w * v.x;
			float wy = w * v.y;
			float wz = w * v.z;

			float xx = v.x * v.x;
			float xy = v.x * v.y;
			float xz = v.x * v.z;

			float yy = v.y * v.y;
			float yz = v.y * v.z;

			float zz = v.z * v.z;

			anwser.matrix[0] = 1.0 - 2.0 * (yy + zz);
			anwser.matrix[1] = 2.0 * (xy + wz);
			anwser.matrix[2] = 2.0 * (xz - wy);
			anwser.matrix[3] = 0.0;

			anwser.matrix[4] = 2.0 * (xy - wz);
			anwser.matrix[5] = 1.0 - 2.0 * (xx + zz);
			anwser.matrix[6] = 2.0 * (yz + wx);
			anwser.matrix[7] = 0.0;

			anwser.matrix[8] = 2.0 * (xz +  wy);
			anwser.matrix[9] = 2.0 * (yz - wx);
			anwser.matrix[10] = 1.0 - 2.0 * (xx + yy);
			anwser.matrix[11] = 0.0;

			anwser.matrix[12] = 0.0;
			anwser.matrix[13] = 0.0;
			anwser.matrix[14] = 0.0;
			anwser.matrix[15] = 1.0;

			copy(*this);
		}

		return anwser;
	}
	inline
	myvector rotatevector(const myvector& Vector) const
	{//p'=q*p*q^-1 rotating a vector using quaternions
		return ((*this)*
					quaternion(0.0, Vector)
						*inverse()).v;
	}
	inline
	point rotatepoint(const point& Point, const point& RotationOrigin=point(0.0, 0.0, 0.0)) const
	{//p'=q*p*q^-1 rotating a point like a vector using quaternions

		return (RotationOrigin+((*this)*
				quaternion(0.0, myvector(RotationOrigin, Point))
					*inverse()).v.topoint());
	}
	inline
	void printme(void) const
	{//printing the qaternion into the console
		cout<<"W "<<w<<" X "<<v.x<<" Y "<<v.y<<" Z "<<v.z<<endl<<flush;
	}
	inline
	string print(void)
	{//printing the qaternion into a string
		static char Chars[100];
		string result("W ");
		sprintf(Chars, "%.1f", w);
		result+=Chars+v.print();
		return result;
	}
	inline
	myvector returnvector()
	{//useful if quaternion is representing a vector, not a rotation
		return v;
	}
	myvector lerpv (const myvector& First, const myvector& Second, const float& Ratio) const
	{//lerping vectors
		return quaternion(quaternion(0.0, First).lerp(quaternion(0.0, Second), Ratio)).v;
	}
	myvector nonnormalisedlerpv (const myvector& First, const myvector& Second, const float& Ratio) const
	{//lerping vectors without normalisation
		return quaternion(quaternion(0.0, First).nonnormalisedlerp(quaternion(0.0, Second), Ratio)).v;
	}
	quaternion nonnormalisedlerp (const myvector& First, const myvector& Second, const float& Ratio) const
	{//lerping vectors with normalisation
		return quaternion(quaternion(0.0, First).nonnormalisedlerp(quaternion(0.0, Second), Ratio));
	}
	quaternion lerp (const myvector& First, const myvector& Second, const float& Ratio) const
	{//lerping
		return quaternion(quaternion(0.0, First).lerp(quaternion(0.0, Second), Ratio));
	}
	quaternion nonnormalisedlerpme (const myvector& First, const myvector& Second, const float& Ratio)
	{//turning the quaternion into non normalised lerp of two vectors
		*this=quaternion(quaternion(0.0, First).nonnormalisedlerp(quaternion(0.0, Second), Ratio));
		return *this;
	}
	quaternion lerpme (const myvector& First, const myvector& Second, const float& Ratio)
	{//turning the quaternion into a lerp of two vectors
		*this=quaternion(quaternion(0.0, First).lerp(quaternion(0.0, Second), Ratio));
		return *this;
	}
	quaternion nonnormalisedlerp(const quaternion& Other, const float& Ratio) const
	{//non normalised lerping with another quaternion
		return quaternion (w+Ratio*(Other.w-w), v+(Other.v-v)*Ratio);
	}
	quaternion lerp(const quaternion& Other, const float& Ratio) const
	{//normalised lerping with another quaternion
		return quaternion (w+Ratio*(Other.w-w), v+(Other.v-v)*Ratio).normaliseme();
	}
	myvector slerpv (const myvector& First, const myvector& Second, const float& Ratio) const
	{//slerping two vectors
		return quaternion(quaternion(0.0, First).slerp(quaternion(0.0, Second), Ratio)).v;
	}
	quaternion slerp (const myvector& First, const myvector& Second, const float& Ratio) const
	{//slerping two vectors
		return quaternion(quaternion(0.0, First).slerp(quaternion(0.0, Second), Ratio));
	}
	quaternion slerpme (const myvector& First, const myvector& Second, const float& Ratio)
	{//turning the quaternion into a slerp of two vectors
		*this=quaternion(quaternion(0.0, First).slerp(quaternion(0.0, Second), Ratio));
		return *this;
	}
	float radangle (const quaternion& Other)const
	{
		return acosf(normalise().dotproduct(Other.normalise()));
	}
	float dotproduct(const quaternion& Other)const
	{
		return w*Other.w+v.dotproduct(Other.v);
	}
	quaternion slerp(const quaternion& Other, const float& Ratio) const
	{//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
		//slerping a quaternion with another
		float coshalftheta=cos(radangle(Other));

		// if qa=qb or qa=-qb then theta = 0 and we can return qa
		if (abs(coshalftheta) >= 1.0)
		{
			return quaternion(*this);
		}
		if (coshalftheta < 0)
		{ //using uposite values to slerp around the shortest angle, not the longest
			coshalftheta=-coshalftheta;

			// Calculate temporary values.
			float halftheta = acos(coshalftheta);
			float sinhalftheta = sqrt(1.0 - coshalftheta*coshalftheta);

			float ratioa = sin((1 - Ratio) * halftheta) / sinhalftheta;
			float ratiob = sin(Ratio * halftheta) / sinhalftheta;
			//calculate Quaternion.
			return quaternion((-w * ratioa + Other.w * ratiob),
								(-v.x * ratioa + Other.v.x * ratiob),
									(-v.y * ratioa + Other.v.y * ratiob),
										(-v.z * ratioa + Other.v.z * ratiob))
											//changing magnitude, should one of those quaternions be nonunit
											.setmymagnitude(magnitude()+(Other.magnitude()-magnitude())*Ratio);
		}
		// Calculate temporary values.
		float halftheta = acos(coshalftheta);
		float sinhalftheta = sqrt(1.0 - coshalftheta*coshalftheta);
		// if theta = 180 degrees then result is not fully defined
		// we could rotate around any axis normal to qa or qb
		/*if (fabs(sinHalfTheta) < 0.001){ // fabs is floating point absolute
			qm.w = (qa.w * 0.5 + qb.w * 0.5);
			qm.x = (qa.x * 0.5 + qb.x * 0.5);
			qm.y = (qa.y * 0.5 + qb.y * 0.5);
			qm.z = (qa.z * 0.5 + qb.z * 0.5);
			return qm;
		}*/
		float ratioa = sin((1 - Ratio) * halftheta) / sinhalftheta;
		float ratiob = sin(Ratio * halftheta) / sinhalftheta;
		//calculate Quaternion.
		return quaternion((w * ratioa + Other.w * ratiob),
							(v.x * ratioa + Other.v.x * ratiob),
								(v.y * ratioa + Other.v.y * ratiob),
									(v.z * ratioa + Other.v.z * ratiob))
									//changing magnitude, should one of those quaternions be nonunit
									.setmymagnitude(magnitude()+(Other.magnitude()-magnitude())*Ratio);
	}
	operator mymatrix()const
		{//typecasting into rotation matrix
		static quaternion copy;
		static mymatrix anwser;

		if(copy!=(*this))
		{//only performing calculations when they are needed (quaternion has changed)
			float wx = w * v.x;
			float wy = w * v.y;
			float wz = w * v.z;

			float xx = v.x * v.x;
			float xy = v.x * v.y;
			float xz = v.x * v.z;

			float yy = v.y * v.y;
			float yz = v.y * v.z;
			float zz = v.z * v.z;

			anwser.matrix[0] = 1.0 - 2.0 * (yy + zz);
			anwser.matrix[1] = 2.0 * (xy + wz);
			anwser.matrix[2] = 2.0 * (xz - wy);
			anwser.matrix[3] = 0.0;

			anwser.matrix[4] = 2.0 * (xy - wz);
			anwser.matrix[5] = 1.0 - 2.0 * (xx + zz);
			anwser.matrix[6] = 2.0 * (yz + wx);
			anwser.matrix[7] = 0.0;

			anwser.matrix[8] = 2.0 * (xz +  wy);
			anwser.matrix[9] = 2.0 * (yz - wx);
			anwser.matrix[10] = 1.0 - 2.0 * (xx + yy);
			anwser.matrix[11] = 0.0;

			anwser.matrix[12] = 0.0;
			anwser.matrix[13] = 0.0;
			anwser.matrix[14] = 0.0;
			anwser.matrix[15] = 1.0;

			copy(*this);
		}
		return anwser;
	}
};
#endif
