#include "allinclude.h"
//#include "dirent.h"
void DisplayScene(void);
void idle(void);
void animate(int value);
void key(unsigned char k, int x, int y);
void reshape(int width, int height);
void init_drawing(void);
#define TIMER 40

//this variable is used to make Eclipse rebuild the project
//the main cpp file needs to be changed to make it do that
#define FOO 1


hud myhud;
random* myrandom;
scenarios myscenarios;
bool timeflow=true;//a variable changing whether the time should flow for the simulation



void passivemouse(int x, int y);
void mouseMovement(int button, int state, int x, int y);

bool keys[256];			//array of pressed keys
bool specialkeys[256];	//array of pressed special keys

//key handling
void keyboardUp(unsigned char key, int x, int y)
{
	keys[(int)key] = false;
	//handlekeys();
}
void keyboardSpecial(int key, int x, int y)
{
	specialkeys[key] = true;
	//handlespecialkeys();
}

void keyboardUpSpecial(int key, int x, int y)
{
	specialkeys[key] = false;
	//handlespecialkeys();
}
//handling keyboard inputs
void keyboard(unsigned char key, int x, int y)
{
	keys[key] = true;
	//handlekeys();
}


//firstcamera cam;
//secondcamera cam;
//quaternioncamera cam;
//matrixcamera cam;
quaternioncamera2 cam;




void handlekeys(void)
{
    if (keys[27])
	{//escape
    	timeflow=false;
    	exit(0);
	}
	if (keys[(int)'q'])
	{
		cam.rollcamera();
	}
	if (keys[(int)'e'])
	{
		cam.rollcamera(-1.0);
	}
	if (keys[(int)'w'])
	{
		cam.pitchcamera();
	}
	if (keys[(int)'s'])
	{
		cam.pitchcamera(-1.0);
	}
	if (keys[(int)'a'])
	{
		cam.yawcamera();
	}
	if (keys[(int)'d'])
	{
		cam.yawcamera(-1.0);
	}
	if (keys[(int)'r'])
	{
		cam.zoomcamera(-1.0);
	}
	if (keys[(int)'f'])
	{
		cam.zoomcamera();
	}

    if (keys[(int)'+'])
    {
    	myhud.handlekey('+');
    }
    if (keys[(int)'-'])
    {
    	myhud.handlekey('-');
    }
    if (keys[(int)'p'])
    {
    	myhud.handlekey('p');
    }
    if (keys[(int)';'])
    {
    	myhud.handlekey(';');
    }
    if (keys[(int)'\t'])
    {
    	timeflow=!timeflow;
    }
    if (keys[(int)'?'])
    {
    	//quaternion(myvector(1.0, 0.0, 0.0).crossproduct(myvector(1.0, 0.0, 0.0))).printme();
    	//quaternion(myvector(10.0, 0.0, 0.0).crossproduct(myvector(1.0, 0.0, 0.0))).printme();
    	//quaternion(myvector(0.0, 1.0, 0.0).crossproduct(myvector(1.0, 0.0, 0.0))).printme();
    	//quaternion(myvector(0.0, 0.0, 1.0).crossproduct(myvector(1.0, 0.0, 0.0))).printme();
    	/*string tmp("qwerty 123\nqwerty 123");
    	vector <string> vtmp=separatestrings(tmp);
    	for(unsigned int i=0;i<vtmp.size();i++)
    	{
    		cout<<vtmp.at(i)<<endl<<flush;
    	}*/
    	//cout<<"asdfas 123.098 == "<<getfloat(string("asdfas 123.098 == "))<<endl<<flush;



    	/*astar tmpastar;
    	if(tmpastar.unittest())
    		cout<<"astar unittest OK"<<endl<<flush;
    	else
    		cout<<"astar unittest !OK"<<endl<<flush;
    	colour tmpcolour;
		if(tmpcolour.unittest()==true)cout<<"Colour OK"<<endl<<flush;
		else cout<<"Colour not OK"<<endl<<flush;
    	emotions tmpemotions;
    	if(tmpemotions.unittest()==true)cout<<"Emotions OK"<<endl<<flush;
    	else cout<<"Emotions not OK"<<endl<<flush;
    	steeringpreferences tmpsteeringpreferences;
    	if(tmpsteeringpreferences.unittest()==true)cout<<"steeringpreferences OK"<<endl<<flush;
    	else cout<<"steeringpreferences not OK"<<endl<<flush;
    	decisionpreferences tmpdecisionpreferences;
    	if(tmpdecisionpreferences.unittest()==true)cout<<"steeringpreferences OK"<<endl<<flush;
    	else cout<<"steeringpreferences not OK"<<endl<<flush;
    	state tmpstate(string("TMP1"));
    	if(tmpstate.unittest())
    		cout<<"state unittest OK"<<endl<<flush;
    	else
    		cout<<"state unittest !OK"<<endl<<flush;*/
    	/*fsme tmpfsme;
    	if(tmpfsme.unittest())
    		cout<<"fsme unittest OK"<<endl<<flush;
		else
			cout<<"fsme unittest !OK"<<endl<<flush;*/
    	/*fsm tmpfsm;
       	if(tmpfsm.unittest())
       		cout<<"fsm unittest OK"<<endl<<flush;
    	else
    		cout<<"fsm unittest !OK"<<endl<<flush;*/
       /*	if(tmpfsm.unittest2())
       		cout<<"fsm unittest2 OK"<<endl<<flush;
    	else
    		cout<<"fsm unittest2 !OK"<<endl<<flush;*/

    	/*pilot tmppilot;
       	if(tmppilot.unittest())
       		cout<<"pilot unittest OK"<<endl<<flush;
    	else
    		cout<<"pilot unittest !OK"<<endl<<flush;*/

       	//vector<pilot> pilotv;

       	/*filepilot fp;
       	fp.testsavepilot();
       	pilotv=fp.getxtoppilots();
       	for(unsigned int i=0;i<pilotv.size();i++)
       	{
       		cout<<pilotv.at(i).print()<<endl<<flush;
       	}*/

       	//cout<<pilot::examplepilot2().print()<<endl<<flush;
    	/*for(unsigned int i=0;i<10000;i++)
    	{
    		cout<<random::getinstance()->randomnormalcenteredatzero(1)<<endl<<flush;
    	}*/


    }
	for (int i=32;i<127;i++) if (keys[i])//from ' ' to the last character
		myscenarios.handlekey(i);
}

void handlespecialkeys(void)
{

	for (int i=0;i<256;i++) if (specialkeys[i])
		myscenarios.handlespecialkey(i);
}



int main(int argc, char *argv[])
{
	try
	{
		//Initialise Glut and create a window
		glutInit(&argc, argv);
		//sets up our display mode
		//here we've selected an RGBA display with depth testing
		//and double buffering enabled
		glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
		//create a window and pass through the windows title
		glutCreateWindow("Space Combat");

		//run our own drawing initialisation routine
		init_drawing();
		//then when you setup GLUT, put these along with the others
		glutKeyboardFunc(keyboard);
		glutKeyboardUpFunc(keyboardUp);

		glutSpecialFunc(keyboardSpecial);
		glutSpecialUpFunc(keyboardUpSpecial);

		glutMouseFunc(mouseMovement);
		glutMotionFunc(passivemouse);

		//tell glut the names of our callback functions point to our
		//functions that we defined at the start of this file
		glutReshapeFunc(reshape);
		//glutKeyboardFunc(key);
		glutIdleFunc(idle);
		glutTimerFunc(TIMER, animate, 0);
		glutDisplayFunc(DisplayScene);

		//request a window size of 600 x 600
		glutInitWindowSize(600,600);
		glutReshapeWindow(600,600);
		myhud.reshape(600, 600);

		myscenarios.setscenarios(&cam, &myhud);



		myrandom=random::getinstance();
		myrandom->setrandombuffersize(4096);
		myrandom->preparerandom(4096);
		//myboid.setdisplay(&myhud.topleft);
		//go into the main loop
		//this loop won't terminate until the user exits the
		//application
		glutMainLoop();
	}
	catch(exception& e)
	{
		cout<<"Exception "<<e.what()<<endl<<flush;
	}

	return 0;
}



/*****************************************************************************
 DisplayScene()

 The work of the application is done here. This is called by glut whenever the
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	myhud.drawme();
	cam.rotatecamera();//using glulookat
	//cam.lookatboid(myboid.position);

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);


	//rotatebymouse();
	//draw a white point at the origin
	/*glPointSize(2.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(0.0,0.0);
		glEnd();
	glPopMatrix();*/
	myscenarios.drawme();



	//flush what we've drawn to the buffer
	glFlush();
	//swap the back buffer with the front buffer
	glutSwapBuffers();
}

//idle callback function - this is called when there is nothing
//else to do
void idle(void)
{
	myrandom->preparerandom(2);
}

void animate(int value)
{
	glutTimerFunc(TIMER, animate, 0);

	//cout<<myrandom->randomnumbers.size()<<endl<<flush;

	handlespecialkeys();
	handlekeys();
	if(timeflow)myscenarios.nexttime();
	glutPostRedisplay();


	//DisplayScene();

	//this is a good place to do animation
	//since there are no animations in this test, we can leave
	//idle() empty
	//cam.yawcamera();


	//DisplayScene();


}



//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
	//set the viewport to be the same width and height as the window
	glViewport(0,0,width, height);
	//make changes to the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	myhud.reshape(width, height);

	//set up our projection type
	//we'll be using a perspective projection, with a 90 degree
	//field of view
	gluPerspective(45.0, (float) width / (float) height, 1.0, 100.0);
	//redraw the view during resizing
	DisplayScene();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
/*void init_drawing(void)
{
	//blend colours across the surface of the polygons
	//another mode to try is GL_FLAT which is flat shading
	glShadeModel(GL_SMOOTH);
	//turn lighting off
	glDisable(GL_LIGHTING);
	//glEnable(GL_LIGHTING);
	//enable OpenGL hidden surface removal
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
}*/
void init_drawing(void)
{
  //blend colours across the surface of the polygons
  //another mode to try is GL_FLAT which is flat shading
  glShadeModel(GL_SMOOTH);
  //turn lighting off
  glDisable(GL_LIGHTING);
  //enable OpenGL hidden surface removal
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);


  GLfloat specular[] = {0.2,0.2,0.2,1.0};
  GLfloat ambient[] = {0.5,0.5,0.5,0.5};
  GLfloat diffuse[] = {1.0,1.0,1.0,1.0};
  GLfloat position[] = {0.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);

  GLfloat position1[] = {10.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);



  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
}


void mouseMovement(int button, int state, int x, int y)
{
	cam.mouseMovement(button, state, x, y);
}
void passivemouse(int x, int y)
{
	cam.passivemouse(x, y);
}
