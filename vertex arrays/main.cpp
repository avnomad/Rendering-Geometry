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
	






void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		for(int c = 0 ; c < elementsOf(indices1) ; ++c)
		{
			glColor4fv((GLfloat*)&colors1[indices1[c]]);
			glVertex2fv(&vertices1[indices1[c]][0]);
		} // end for
	glEnd();

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
	gluOrtho2D((GLdouble) -2, (GLdouble) 2, (GLdouble) -2, (GLdouble) 2);
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,160);
	glutCreateWindow("Creating Geometry");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_LINE);
	glShadeModel(GL_SMOOTH);

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main