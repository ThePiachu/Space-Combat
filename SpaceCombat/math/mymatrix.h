#ifndef MYMATRIX_H_
#define MYMATRIX_H_
#include <GL\gl.h>
#include "point.h"
#include "myvector.h"
#include <cmath>
#define MATRIXRAD2DEG M_PI/180
class mymatrix
{//class for 4x4 rotation matrix, same format as OpenGL
public:
	GLfloat matrix[16];//the actual matrix
	mymatrix(void)
	{//initialization with unit matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=1.0;
		matrix[5]=1.0;
		matrix[10]=1.0;
		matrix[15]=1.0;
	}
	mymatrix(const float& X, const float& Y, const float& Z)
	{//initialization with translation matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=1.0;
		matrix[5]=1.0;
		matrix[10]=1.0;
		matrix[15]=1.0;

		matrix[12]=X;
		matrix[13]=Y;
		matrix[14]=Z;
	}
	mymatrix(const myvector& V)
	{//initialization with translation matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=1.0;
		matrix[5]=1.0;
		matrix[10]=1.0;
		matrix[15]=1.0;

		matrix[12]=V.x;
		matrix[13]=V.y;
		matrix[14]=V.z;
	}
	mymatrix(const point& P)
	{//initialization with translation matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=1.0;
		matrix[5]=1.0;
		matrix[10]=1.0;
		matrix[15]=1.0;

		matrix[12]=P.x;
		matrix[13]=P.y;
		matrix[14]=P.z;
	}
	mymatrix(const float& S1, const float& S2, const float& S3, const float& S4)
	{//initialization with scaling matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=S1;
		matrix[5]=S2;
		matrix[10]=S3;
		matrix[15]=S4;

	}
	mymatrix (const GLfloat* Matrix)
	{//initializing with other matrix
		for (int i=0;i<16;i++) matrix[i]=Matrix[i];
	}
	mymatrix (const float& Angle, const char& Axis='z', const bool& UseRad=true)
	{//initializing with rotation around one of the three axis
		float angle;
		if (UseRad)angle=Angle*MATRIXRAD2DEG;
		else angle=Angle;
		for (int i=0;i<16;i++) matrix[i]=0.0;
		switch(Axis)
		{
		case 'x':
			matrix[0]=1.0;
			matrix[5]=cos(angle);
			matrix[6]=sin(angle);
			matrix[9]=-sin(angle);
			matrix[10]=cos(angle);
			break;
		case 'y':
			matrix[0]=cos(angle);
			matrix[2]=-sin(angle);
			matrix[5]=1.0;
			matrix[8]=sin(angle);
			matrix[10]=cos(angle);
			break;
		case 'z':
			matrix[0]=cos(angle);
			matrix[1]=sin(angle);
			matrix[4]=-sin(angle);
			matrix[5]=cos(angle);
			matrix[10]=1.0;
			break;
		default://unit matrix as default
			matrix[0]=1.0;
			matrix[5]=1.0;
			matrix[10]=1.0;
			break;
		}
			matrix[15]=1.0;
	}
	~mymatrix(void)
	{
	}
	void loadidentitymatrix(void)
	{//loads the matrix with identity matrix
		for (int i=0;i<16;i++) matrix[i]=0.0;
		matrix[0]=1.0;
		matrix[5]=1.0;
		matrix[10]=1.0;
		matrix[15]=1.0;
	}
	inline
	mymatrix& loadopenglmatrix(GLenum type)
	{//loads a matrix from OpenGL
		glGetFloatv(type, matrix);
		return *this;
	}
	inline
	mymatrix& loadopenglmodelviewmatrix(void)
	{//loads Modelview Matrix from OpenGL
		return loadopenglmatrix(GL_MODELVIEW_MATRIX);
	}
	inline
	mymatrix& loadprojectionmatrix(void)
	{//loads Projection Matrix from OpenGL
		return loadopenglmatrix(GL_PROJECTION);
	}
	inline
	void saveopenglmatrix (void)
	{//puts the current matrix into OpenGL
		glLoadMatrixf(matrix);
	}
	mymatrix& operator*= (const float& HowMuch)
	{//matrix multiplication
		for (int i=0;i<16;i++) matrix[i]*=HowMuch;
		return *this;
	}
	mymatrix operator* (const float& HowMuch) const
	{//scaling all the numbers in the matrix
		return mymatrix(*this)*=HowMuch;
	}
	mymatrix translate (const float& X=0.0, const float& Y=0.0, const float& Z=0.0) const
	{//translation operation
		return mymatrix(*this).translateme(X, Y, Z);
	}
	mymatrix& translateme (const float& X=0.0, const float& Y=0.0, const float& Z=0.0)
	{//translation of the matrix, which changes only 4 numbers in the matrix
		matrix[12]+=X*matrix[0]+Y*matrix[4]+Z*matrix[8];
		matrix[13]+=X*matrix[1]+Y*matrix[5]+Z*matrix[9];
		matrix[14]+=X*matrix[2]+Y*matrix[6]+Z*matrix[10];
		matrix[15]+=X*matrix[3]+Y*matrix[7]+Z*matrix[11];
		return *this;
	}
	inline
	mymatrix& operator/= (const float& HowMuch)
	{//scaling all the numbers in the matrix
		for (int i=0;i<16;i++) matrix[i]/=HowMuch;
		return *this;
	}
	inline
	mymatrix operator/ (const float& HowMuch) const
	{//scaling all the numbers in the matrix
		return mymatrix(*this)/=HowMuch;
	}
	mymatrix& operator*= (mymatrix Other)
	{//multiplying two matrixes
		GLfloat anwser[16];
		for(int i=0;i<4;i++)for(int j=0;j<4;j++)
		{
			anwser[i+4*j]=0.0;
			for (int k=0;k<4;k++)
			{
				anwser[i+4*j]+=matrix[i+k*4]*Other.matrix[k+4*j];
			}
		}
		for(int i=0;i<16;i++)matrix[i]=anwser[i];//copying the result into the matrix in the class
		return *this;
	}
	mymatrix operator* (mymatrix Other) const
	{//multiplying two matrixes
		GLfloat anwser[16];
		for(int i=0;i<4;i++)for(int j=0;j<4;j++)
		{
			anwser[i+4*j]=0.0;
			for (int k=0;k<4;k++)
			{
				anwser[i+4*j]+=matrix[i+k*4]*Other.matrix[k+4*j];
			}
		}
		return mymatrix(anwser);
	}
	inline
	operator const GLfloat*() const
	{//type casting to GLFloat*, used for glMultMatrixf
		return matrix;
	}
	inline
	operator myvector() const
	{//type casting for a translation
		return myvector(matrix[12], matrix[13], matrix[14]);
	}
	inline
	operator point() const
	{//type casting for a translation
		return point(matrix[12], matrix[13], matrix[14]);
	}

	inline
	void printme()
	{//writing out the contents of the matrix
		cout<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12]<<endl
				<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13]<<endl
				<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14]<<endl
				<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15]<<endl;
	}

};
#endif //MYMATRIX_H_

