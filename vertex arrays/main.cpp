#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>


#define elementsOf(A) (sizeof(A)/sizeof((A)[0]))


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
	glVertexPointer(2,GL_FLOAT,0,vertices1);
	glColorPointer(4,GL_FLOAT,0,colors1);
	glDrawElements(GL_TRIANGLES,elementsOf(indices1),GL_UNSIGNED_INT,indices1);

	// transorm 2nd shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(160,250,0);
	glScalef(75,75,75);

	// draw 2nd shape
	glVertexPointer(2,GL_FLOAT,0,vertices2);
	glColorPointer(4,GL_FLOAT,0,colors2);
	glDrawElements(GL_TRIANGLES,elementsOf(indices2),GL_UNSIGNED_INT,indices2);

	// transorm 3rd shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(350,150,0);
	glScalef(40,40,40);

	// draw 3rd shape
	glVertexPointer(2,GL_FLOAT,0,vertices3);
	glColorPointer(4,GL_FLOAT,0,colors3);
	for(int i = 0 ; i < elementsOf(indices3) ; ++i)
		glDrawElements(GL_TRIANGLE_STRIP,elementsOf(indices3[i]),GL_UNSIGNED_INT,indices3[i]);

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
	glutCreateWindow("Creating Geometry");

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

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main