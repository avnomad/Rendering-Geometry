//	Copyright (C) 2009, 2011-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Rendering Geometry.
 *
 *	Rendering Geometry is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Rendering Geometry is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Rendering Geometry.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>


#define elementsOf(A) (sizeof(A)/sizeof((A)[0]))
#define offset(A) ((GLubyte*)0 + (A))

struct Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
}; // end structure Color

Color red = {1.0,0.0,0.0,1.0};
Color yellow = {1.0,1.0,0.0,1.0};
Color quarterOrange = {1.0,0.75,0.0,0.25};
Color blue = {0.0,0.0,1.0,1.0};
Color cyan = {0.0,1.0,1.0,1.0};


GLfloat vertices1[][2] = {
	{-1.0,1.0}, {0.0,1.0}, {1.0,1.0},
	{-1.0,0.0}, {0.0,0.0}, {1.0,0.0},
	{-1.0,-1.0}, {0.0,-1.0}, {1.0,-1.0}
};

Color colors1[] = {
	yellow,quarterOrange,yellow,
	quarterOrange,red,quarterOrange,
	yellow,quarterOrange,yellow
};

GLuint indices1[] = {
	0,4,1,
	1,4,2,
	0,3,4,
	2,4,5,
	3,6,4,
	4,8,5,
	4,6,7,
	4,7,8
};
	
GLfloat vertices2[][2] = {
	{-0.50,0.50}, {0.0,2.0}, {0.50,0.50},
	{-2.0,0.0}, {0.0,0.0}, {2.0,0.0},
	{-0.50,-0.50}, {0.0,-2.0}, {0.50,-0.50}
};

Color colors2[] = {
	quarterOrange,yellow,quarterOrange,
	yellow,red,yellow,
	quarterOrange,yellow,quarterOrange,
};

GLuint indices2[] = {
	0,4,1,
	1,4,2,
	0,3,4,
	2,4,5,
	3,6,4,
	4,8,5,
	4,6,7,
	4,7,8
};

GLfloat vertices3[][2] = {
	{-2,2},{-1,2},{0,2},{1,2},{2,2},
	{-2,1},{-1,1},{0,1},{1,1},{2,1},
	{-2,0},{-1,0},{0,0},{1,0},{2,0},
	{-2,-1},{-1,-1},{0,-1},{1,-1},{2,-1},
	{-2,-2},{-1,-2},{0,-2},{1,-2},{2,-2}
};

Color colors3[] = {
	blue,cyan,blue,cyan,blue,
	cyan,blue,cyan,blue,cyan,
	blue,cyan,blue,cyan,blue,
	cyan,blue,cyan,blue,cyan,
	blue,cyan,blue,cyan,blue
};

GLuint indices3[][10] = {
	{0,5,1,6,2,7,3,8,4,9},
	{5,10,6,11,7,12,8,13,9,14},
	{10,15,11,16,12,17,13,18,14,19},
	{15,20,16,21,17,22,18,23,19,24}
};


enum {g1,g2,g3,geometries};
enum {vertex,color,index,arrays};
GLuint buffers[geometries][arrays];


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// transorm 1st shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(350,350,0);
	glScalef(75,75,75);
	glRotatef(45,0,0,1);

	// draw 1st shape
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g1][vertex]);
	glVertexPointer(2,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g1][color]);
	glColorPointer(4,GL_FLOAT,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g1][index]);
	glDrawElements(GL_TRIANGLES,elementsOf(indices1),GL_UNSIGNED_INT,offset(0));

	// transorm 2nd shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(160,250,0);
	glScalef(75,75,75);

	// draw 2nd shape
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g2][vertex]);
	glVertexPointer(2,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g2][color]);
	glColorPointer(4,GL_FLOAT,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g2][index]);
	glDrawElements(GL_TRIANGLES,elementsOf(indices2),GL_UNSIGNED_INT,offset(0));

	// transorm 3rd shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(350,150,0);
	glScalef(40,40,40);

	// draw 3rd shape
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g3][vertex]);
	glVertexPointer(2,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g3][color]);
	glColorPointer(4,GL_FLOAT,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g3][index]);
	for(int i = 0 ; i < elementsOf(indices3) ; ++i)
		glDrawElements(GL_TRIANGLE_STRIP,elementsOf(indices3[i]),GL_UNSIGNED_INT,offset(i*sizeof(indices3[0])));

	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:	// escape key
			exit(0);
	} // end switch
} // end function keyboard


void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble) w, 0, (GLdouble) h);
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(700,160);
	glutCreateWindow("Rendering Geometry");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_LINE);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);	// enable vertex arrays
	glEnableClientState(GL_COLOR_ARRAY);
	glGenBuffers(geometries*arrays,&buffers[0][0]);	// create buffer identifiers
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g1][vertex]);	// send information to the server (g1)
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g1][color]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors1),colors1,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g1][index]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices1),indices1,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g2][vertex]);	// send information to the server (g2)
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g2][color]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors2),colors2,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g2][index]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices2),indices2,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g3][vertex]);	// send information to the server (g3)
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices3),vertices3,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[g3][color]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors3),colors3,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[g3][index]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices3),indices3,GL_STATIC_DRAW);

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main