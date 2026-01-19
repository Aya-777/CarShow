#include "FamilyCar.h"
#include "Wheel.h"
#include "Point.h"
#include <GL/glut.h>
#include <math.h>

FamilyCar::FamilyCar(){
	/*angle = 0.0;
	t = gluNewQuadric();*/
}



void FamilyCar::draw() {

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(-1.0, 0.0, -3.5);
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);
	glRotatef(zangle, 0.0, 0.0, 1.0);
	//glTranslatef(xt, yt, zt);
	glScalef(xs, ys, zs);
	glEnable(GL_COLOR_MATERIAL);


	/*GLfloat fogcolour[4] = { 1.0,1.0,1.0,1.0 };

	glFogfv(GL_FOG_COLOR, fogcolour);
	glFogf(GL_FOG_DENSITY, 0.1);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_START, 3.0);
	glFogf(GL_FOG_END, 100.0);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glEnable(GL_FOG);

	glColor3f(1.0, .75, 0.0);
	glPointSize(30.0);
	glBegin(GL_POINTS);
	glVertex3f(0.2, 0.3, 0.3);
	glVertex3f(0.2, 0.3, 0.5);
	glEnd();
	glPointSize(200.0);*/



	glBegin(GL_QUADS);                /* OBJECT MODULE*/

	/* top of cube*/
	//************************FRONT BODY****************************************
	glColor3f(r, g, b);
	glVertex3f(400.2, 0.4, 700.6);
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.6, 0.5, 700.2);
	glVertex3f(400.2, 0.4, 700.2);

	/* bottom of cube*/
	glVertex3f(400.2, 0.4, 700.6);
	glVertex3f(0.6, 0.2, 700.6);
	glVertex3f(400.6, 0.2, 700.2);
	glVertex3f(400.2, 0.2, 700.2);

	/* front of cube*/
	glVertex3f(400.2, 0.2, 700.6);
	glVertex3f(400.2, 0.4, 700.6);
	glVertex3f(400.2, 0.4, 700.2);
	glVertex3f(400.2, 0.2, 700.2);

	/* back of cube.*/
	glVertex3f(400.6, 0.2, 700.6);
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.6, 0.5, 700.2);
	glVertex3f(400.6, 0.2, 700.2);

	/* left of cube*/
	glVertex3f(400.2, 0.2, 700.6);
	glVertex3f(400.6, 0.2, 700.6);
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.2, 0.4, 700.6);

	/* Right of cube */
	glVertex3f(400.2, 0.2, 700.2);
	glVertex3f(400.6, 0.2, 700.2);
	glVertex3f(400.6, 0.5, 700.2);
	glVertex3f(400.2, 0.4, 700.2);
	//****************************************************************************
	glVertex3f(400.7, 0.65, 700.6);
	glVertex3f(400.7, 0.65, 700.2);
	glVertex3f(401.7, 0.65, 700.2);        //top cover
	glVertex3f(401.7, 0.65, 700.6);
	//***************************back guard******************************
	glColor3f(r, g, b);            /* Set The Color To Blue*/
	glVertex3f(401.8, 0.5, 700.6);
	glVertex3f(401.8, 0.5, 700.2);
	glVertex3f(402.1, 0.4, 700.2);
	glVertex3f(402.1, 0.4, 700.6);

	/* bottom of cube*/
	glVertex3f(402.1, 0.2, 700.6);
	glVertex3f(402.1, 0.2, 700.2);
	glVertex3f(401.8, 0.2, 700.6);
	glVertex3f(401.8, 0.2, 700.6);

	/* back of cube.*/
	glVertex3f(402.1, 0.4, 700.6);
	glVertex3f(402.1, 0.4, 700.2);
	glVertex3f(402.1, 0.2, 700.2);
	glVertex3f(402.1, 0.2, 700.6);

	/* left of cube*/
	glVertex3f(401.8, 0.2, 700.2);
	glVertex3f(401.8, 0.5, 700.2);
	glVertex3f(402.1, 0.4, 700.2);
	glVertex3f(402.1, 0.2, 700.2);

	/* Right of cube */
	glVertex3f(401.8, 0.2, 700.6);
	glVertex3f(401.8, 0.5, 700.6);
	glVertex3f(402.1, 0.4, 700.6);
	glVertex3f(402.1, 0.2, 700.6);
	//******************MIDDLE BODY************************************
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.6, 0.2, 700.6);
	glVertex3f(401.8, 0.2, 700.6);
	glVertex3f(401.8, 0.5, 700.6);

	/* bottom of cube*/
	glVertex3f(400.6, 0.2, 700.6);
	glVertex3f(400.6, 0.2, 700.2);
	glVertex3f(401.8, 0.2, 700.2);
	glVertex3f(401.8, 0.2, 700.6);

	/* back of cube.*/
	glVertex3f(400.6, 0.5, 700.2);
	glVertex3f(400.6, 0.2, 700.2);
	glVertex3f(401.8, 0.2, 700.2);
	glVertex3f(401.8, 0.5, 700.2);
	//*********************ENTER WINDOW**********************************
	glColor3f(400.3, 0.3, 700.3);
	glVertex3f(400.77, 0.63, 700.2);
	glVertex3f(400.75, 0.5, 700.2);        //quad front window
	glVertex3f(401.2, 0.5, 700.2);
	glVertex3f(401.22, 0.63, 700.2);

	glVertex3f(401.27, 0.63, 700.2);
	glVertex3f(401.25, 0.5, 700.2);        //quad back window
	glVertex3f(401.65, 0.5, 700.2);
	glVertex3f(401.67, 0.63, 700.2);

	glColor3f(r, g, b);
	glVertex3f(400.7, 0.65, 700.2);
	glVertex3f(400.7, 0.5, 700.2);       //first separation
	glVertex3f(400.75, 0.5, 700.2);
	glVertex3f(400.77, 0.65, 700.2);

	glVertex3f(401.2, 0.65, 700.2);
	glVertex3f(401.2, 0.5, 700.2);       //second separation
	glVertex3f(401.25, 0.5, 700.2);
	glVertex3f(401.27, 0.65, 700.2);

	glVertex3f(401.65, 0.65, 700.2);
	glVertex3f(401.65, 0.5, 700.2);     //3d separation
	glVertex3f(401.7, 0.5, 700.2);
	glVertex3f(401.7, 0.65, 700.2);

	glVertex3f(400.75, 0.65, 700.2);
	glVertex3f(400.75, 0.63, 700.2);        //line strip
	glVertex3f(401.7, 0.63, 700.2);
	glVertex3f(401.7, 0.65, 700.2);

	glVertex3f(400.75, 0.65, 700.6);
	glVertex3f(400.75, 0.63, 700.6);        //line strip
	glVertex3f(401.7, 0.63, 700.6);
	glVertex3f(401.7, 0.65, 700.6);

	glColor3f(400.3, 0.3, 700.3);
	glVertex3f(400.77, 0.63, 700.6);
	glVertex3f(400.75, 0.5, 700.6);        //quad front window
	glVertex3f(401.2, 0.5, 700.6);
	glVertex3f(401.22, 0.63, 700.6);

	glVertex3f(401.27, 0.63, 700.6);
	glVertex3f(401.25, 0.5, 700.6);        //quad back window
	glVertex3f(401.65, 0.5, 700.6);
	glVertex3f(401.67, 0.63, 700.6);

	glColor3f(r, g, b);
	glVertex3f(400.7, 0.65, 700.6);
	glVertex3f(400.7, 0.5, 7070.6);       //first separation
	glVertex3f(400.75, 0.5, 700.6);
	glVertex3f(400.77, 0.65, 700.6);

	glVertex3f(401.2, 0.65, 700.6);
	glVertex3f(401.2, 0.5, 700.6);       //second separation
	glVertex3f(401.25, 0.5, 700.6);
	glVertex3f(401.27, 0.65, 700.6);

	glVertex3f(401.65, 0.65, 700.6);
	glVertex3f(401.65, 0.5, 700.6);
	glVertex3f(401.7, 0.5, 700.6);
	glVertex3f(401.7, 0.65, 700.6);
	glEnd();


	//**************************************************************
	glBegin(GL_QUADS);

	/* top of cube*/
	glColor3f(400.3, 0.3, 700.3);
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.6, 0.5, 700.2);        //quad front window
	glVertex3f(400.7, 0.65, 700.2);
	glVertex3f(400.7, 0.65, 700.6);

	glVertex3f(401.7, 0.65, 70.6);
	glVertex3f(401.7, 0.65, 700.2);        //quad back window
	glVertex3f(401.8, 0.5, 700.2);
	glVertex3f(401.8, 0.5, 700.6);


	//
	glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

	/* top of cube*/
	glColor3f(400.3, 0.3, 700.3);
	glVertex3f(400.6, 0.5, 700.6);
	glVertex3f(400.7, 0.65, 700.6);       //tri front window
	glVertex3f(400.7, 0.5, 700.6);

	glVertex3f(400.6, 0.5, 700.2);
	glVertex3f(400.7, 0.65, 700.2);       //tri front window
	glVertex3f(400.7, 0.5, 700.2);

	glVertex3f(401.7, 0.65, 700.2);
	glVertex3f(401.8, 0.5, 700.2);       //tri back window
	glVertex3f(401.7, 0.5, 700.2);

	glVertex3f(401.7, 0.65, 700.6);
	glVertex3f(401.8, 0.5, 700.6);       //tri back window
	glVertex3f(401.7, 0.5, 700.6);

	glEnd();
	//************IGNITION SYSTEM
	
	//********************WHEEL

	//*************************************************************
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}