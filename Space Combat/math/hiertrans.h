/*
 * hiertrans.h
 *
 *  Created on: 2009-11-25
 *      Author: ThePiachu
 */

#ifndef HIERTRANS_H_
#define HIERTRANS_H_
//class for handling all hierarhical transformations
#include "myvector.h"
#include "mymatrix.h"
#include "quaternion.h"
#include <GL\gl.h>
#include <vector>
class hiertrans
{
	vector <mymatrix> matrices;//vector for pushing and popping matrices
public:
	hiertrans()
	{
	}
	~hiertrans()
	{
	}
	void translatef(const float& X=0.0, const float& Y=0.0, const float& Z=0.0) const
	{//translation
		glMultMatrixf(mymatrix(X, Y, Z));//multiplying by transposition matrix
	}
	void translatef(const myvector& V=myvector(0.0,0.0,0.0)) const
	{//translation
		glMultMatrixf(mymatrix(V.x, V.y, V.z));//multiplying by transposition matrix
	}
	void rotatef(const float& Angle, const float& X=0.0, const float& Y=0.0, const float& Z=0.0) const
	{//rotation
		glMultMatrixf(quaternion(myvector(X, Y, Z), Angle).rotationmatrix());//multiplying by rotation matrix
	}
	void multiply(quaternion& Quat) const
	{
		glMultMatrixf(Quat.rotationmatrix());//multiplying by rotation matrix
	}
	void multiply(mymatrix& Mat) const
	{
		glMultMatrixf(Mat);//multiplying by rotation matrix
	}
	void scalef(const float& X=1.0, const float& Y=1.0, const float& Z=1.0)const
	{//scaling
		glMultMatrixf(mymatrix(X, Y, Z, 1));//multiplying by matrix with diagonal of X, Y, Z, 1
	}
	void scalef(const myvector& V=myvector(1.0,1.0,1.0))const
	{//scalins
		glMultMatrixf(mymatrix(V.x, V.y, V.z, 1));//multiplying by matrix with diagonal of X, Y, Z, 1
	}
	void push(GLenum type=GL_MODELVIEW_MATRIX)
	{//pushing
		matrices.push_back(mymatrix().loadopenglmatrix(type));
	}
	void pop()
	{//popping
		if (matrices.size()>0)
		{
			matrices.back().saveopenglmatrix();
			matrices.pop_back();
		}
	}
	point projection(const point& Point)
	{//prediction of absolute point position
		return mymatrix(Point)*mymatrix().loadopenglmodelviewmatrix();
	}
	myvector projection(const myvector& Vector)
	{//prediction of absolute point position
		return mymatrix(Vector)*mymatrix().loadopenglmodelviewmatrix();
	}

};

#endif /* HIERTRANS_H_ */
