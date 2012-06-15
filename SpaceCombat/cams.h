#ifndef CAMS_H_
#define CAMS_H_

#include "math.h"
//#include "myvector.h"
//#include "mymatrix.h"
//#include "quaternion.h"
#define ROTATIONSPEED 5.0
#define ZOOMSPEED 0.5
#define CAMSMOUSEMOVEMENTRATIO 0.5
//#define RAD2DEG M_PI/180.0
class firstcamera
{
public:
	float pitch, yaw, roll, x, y, z, zoom;
	firstcamera(float Pitch=0.0, float Yaw=0.0, float Roll=0.0, float X=0.0, float Y=0.0, float Z=0.0, float Zoom=15.0):
	pitch(Pitch), yaw(Yaw), roll(Roll), x(X), y(Y), z(Z), zoom(Zoom)
	{
	}
	~firstcamera()
	{
	}
	void pitchcamera(float ForwardBackward=1.0, float Pitch=ROTATIONSPEED)
	{
		pitch+=ForwardBackward*Pitch;
		if (pitch>180.0) pitch-=360.0;
		if (pitch<-180.0) pitch+=360.0;
	}
	void yawcamera(float ForwardBackward=1.0, float Yaw=ROTATIONSPEED)
	{
		yaw+=ForwardBackward*Yaw;
		if (yaw>180.0) yaw-=360.0;
		if (yaw<-180.0) yaw+=360.0;
	}
	void rollcamera(float ForwardBackward=1.0, float Roll=ROTATIONSPEED)
	{
		roll+=ForwardBackward*Roll;
		if (roll>180.0) roll-=360.0;
		if (roll<-180.0) roll+=360.0;
	}
	void zoomcamera(float ForwardBackward=1.0, float Zoom=ZOOMSPEED)
	{
		zoom+=ForwardBackward*Zoom;
	}
};


class secondcamera
{
	void valuecontrol (void)
	{
		if (pitch>180.0) pitch-=360.0;
		if (pitch<-180.0) pitch+=360.0;
		if (yaw>180.0) yaw-=360.0;
		if (yaw<-180.0) yaw+=360.0;
		if (roll>180.0) roll-=360.0;
		if (roll<-180.0) roll+=360.0;
	}
public:
	float pitch, yaw, roll, x, y, z, zoom;
	secondcamera(float Pitch=0.0, float Yaw=0.0, float Roll=0.0, float X=0.0, float Y=0.0, float Z=0.0, float Zoom=15.0):
	pitch(Pitch), yaw(Yaw), roll(Roll), x(X), y(Y), z(Z), zoom(Zoom)
	{
	}
	~secondcamera()
	{
	}
	void pitchcamera(float ForwardBackward=1.0, float Pitch=ROTATIONSPEED)
	{
		pitch+=ForwardBackward*Pitch;//*cos(yaw*RAD2DEG)*cos(roll*RAD2DEG);
		//roll-=ForwardBackward*Pitch*sin(yaw);
		//yaw+=ForwardBackward*Pitch*sin(roll);

		valuecontrol();
	}
	void yawcamera(float ForwardBackward=1.0, float Yaw=ROTATIONSPEED)
	{
		yaw+=ForwardBackward*Yaw;//*cos(yaw*RAD2DEG)*cos(roll*RAD2DEG);

		valuecontrol();
	}
	void rollcamera(float ForwardBackward=1.0, float Roll=ROTATIONSPEED)
	{
		roll+=ForwardBackward*Roll;//*cos(yaw*RAD2DEG)*cos(roll*RAD2DEG);

		valuecontrol();
	}
	void zoomcamera(float ForwardBackward=1.0, float Zoom=ZOOMSPEED)
	{
		zoom+=ForwardBackward*Zoom;

		valuecontrol();
	}
};

class quaternioncamera
{
public:
	quaternion quat;
	float x, y, z, zoom;
	quaternioncamera(float X=0.0, float Y=0.0, float Z=0.0, float Zoom=15.0):
	quat(1.0, 0.0, 0.0, 0.0), x(X), y(Y), z(Z), zoom(Zoom)
	{
	}
	~quaternioncamera()
	{
	}
	void pitchcamera(float ForwardBackward=1.0, float Pitch=ROTATIONSPEED)
	{
		quat.pitchme(ForwardBackward*Pitch);
	}
	void yawcamera(float ForwardBackward=1.0, float Yaw=ROTATIONSPEED)
	{
		quat.yawme(ForwardBackward*Yaw);
	}
	void rollcamera(float ForwardBackward=1.0, float Roll=ROTATIONSPEED)
	{
		quat.rollme(ForwardBackward*Roll);
	}
	void zoomcamera(float ForwardBackward=1.0, float Zoom=ZOOMSPEED)
	{
		zoom+=ForwardBackward*Zoom;
	}
	void rotatecamera(void)
	{
		//quat.normaliseme();
		/*cout<<quat.w<<" "<<quat.v.x<<" "<<quat.v.y<<" "<<quat.v.z<<" Vector Magnitude:"<<quat.v.getmagnitude()<<endl
			<<"Quat magnitude: "<<quat.magnitude()<<endl<<flush;*/
		//?!?!?!
		quat.normaliseme();
		//cout<<"rotatecamera"<<endl<<flush;
		/*float scale=sqrt(quat.v.x*quat.v.x+quat.v.y*quat.v.y+quat.v.z*quat.v.z);
		float length=sqrt(scale*scale+quat.w*quat.w);
		cout<<"Scale: "<<scale<<" Length: "<<length<<endl<<flush;*/
		//cout<<scale<<" X"<<quat.v.x/scale<<" Y"<<quat.v.y/scale<<" Z"<<quat.v.z/scale<<endl<<flush;
		//glRotatef(acos(quat.w)*2.0/M_PI*180, quat.v.x/scale, quat.v.y/scale, quat.v.z/scale);
		//myvector v=quat.v.normalise();
		//gluLookAt(v.x*zoom, v.y*zoom, v.z*zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		//glMultMatrixf(quat);
		glMultMatrixf(quat.rotationmatrix().matrix);
		//glTranslatef(0.0, 0.0, zoom);
	}
};
class matrixcamera
{
	public:
	mymatrix rotationmatrix, xrotationf, yrotationf, zrotationf,
		xrotationb, yrotationb, zrotationb,
		zoommatrix;
	float x, y, z, zoom;
	matrixcamera(float X=0.0, float Y=0.0, float Z=0.0, float Zoom=15.0):
	xrotationf(ROTATIONSPEED, 'x'), yrotationf(ROTATIONSPEED, 'y'), zrotationf(ROTATIONSPEED, 'z'),
		xrotationb(-ROTATIONSPEED, 'x'), yrotationb(-ROTATIONSPEED, 'y'), zrotationb(-ROTATIONSPEED, 'z'), zoommatrix(),
				x(X), y(Y), z(Z), zoom(Zoom)
	{
		zoommatrix.matrix[14]=-zoom;
	}
	~matrixcamera()
	{
	}
	void pitchcamera(float ForwardBackward=1.0)
	{
		if (ForwardBackward==1.0)rotationmatrix*=xrotationf;
		else rotationmatrix*=xrotationb;
	}
	void yawcamera(float ForwardBackward=1.0)
	{
		if (ForwardBackward==1.0)rotationmatrix*=yrotationf;
		else rotationmatrix*=yrotationb;
	}
	void rollcamera(float ForwardBackward=1.0)
	{
		if (ForwardBackward==1.0)rotationmatrix*=zrotationf;
		else rotationmatrix*=zrotationb;
	}
	void zoomcamera(float ForwardBackward=1.0, float Zoom=ZOOMSPEED)
	{
		zoom+=ForwardBackward*Zoom;
		zoommatrix.matrix[14]=-zoom;
	}
	void rotatecamera(void)
	{
		//glMultMatrixf(zoommatrix.matrix);
		//glMultMatrixf(rotationmatrix.matrix);
		glMultMatrixf((zoommatrix*rotationmatrix).matrix);
		//glMultMatrixf(quaternion(zoommatrix*rotationmatrix));
	}
};


class quaternioncamera2
{
	int lastx;
	int lasty;
public:
	quaternion rotation;
	myvector camera, up;
	point center;
	float zoom;
	quaternioncamera2(float X=0.0, float Y=0.0, float Z=0.0, float Zoom=15.0):
	camera(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0), center(X, Y, Z), zoom(Zoom)
	{
	}
	~quaternioncamera2()
	{
	}
	void pitchcamera(float ForwardBackward=1.0, float Pitch=ROTATIONSPEED)
	{//pitching camera
		rotation=quaternion(up.crossproduct(camera).normalise(), ForwardBackward*Pitch);
		camera=rotation.rotatevector(camera).normaliseme();
		up=rotation.rotatevector(up).normaliseme();
	}
	void yawcamera(float ForwardBackward=1.0, float Yaw=ROTATIONSPEED)
	{//yawing camera
		rotation=quaternion(up, ForwardBackward*Yaw);
		camera=rotation.rotatevector(camera).normaliseme();
		up=rotation.rotatevector(up).normaliseme();
	}
	void rollcamera(float ForwardBackward=1.0, float Roll=ROTATIONSPEED)
	{//rolling camera
		rotation=quaternion(-camera, ForwardBackward*Roll);
		camera=rotation.rotatevector(camera).normaliseme();
		up=rotation.rotatevector(up).normaliseme();
	}
	void zoomcamera(float ForwardBackward=1.0, float Zoom=ZOOMSPEED)
	{//zooming camera
		zoom+=ForwardBackward*Zoom;
	}
	void rotatecamera(void) const
	{//setting camera to look at center position
		gluLookAt(camera.x*zoom, camera.y*zoom, camera.z*zoom, center.x, center.y, center.z, up.x, up.y, up.z);
	}
	void setzoom(const float& Zoom)
	{//setting zoom
		zoom=Zoom;
	}
	void lookatpoint(const point& Point) const
	{//looking at a set point
		gluLookAt(camera.x*zoom, camera.y*zoom, camera.z*zoom, Point.x, Point.y, Point.z, up.x, up.y, up.z);
	}

	void mouseMovement(int button, int state, int x, int y)
	{//handling mouse button presses
		if (state==GLUT_DOWN)
		{//the moment a button is pressed, the new value of x and y are recorded, so the display won`t 'jump'
			lastx=x;
			lasty=y;
		}
	}
	void passivemouse(int x, int y)
	{//handling mouse movement
		int diffx=(x-lastx); //check the difference between the current x and the last x position
		int diffy=(y-lasty); //check the difference between the current y and the last y position
		lastx=x; //set lastx to the current x position
		lasty=y; //set lasty to the current y position
		yawcamera(1.0, -CAMSMOUSEMOVEMENTRATIO*(float) diffx);
		pitchcamera(1.0, -CAMSMOUSEMOVEMENTRATIO*(float) diffy);
	}
};

#endif /* CAMS_H_ */
