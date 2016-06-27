#include <stdio.h>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/freeglut.h>

void onDisplay()
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
	//glFlush();
};

int main(int argc, char ** argv)
{
	glutInit(&argc	, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300,100);
	glutCreateWindow("Hello OpenGL, This is first Window");
	glutDisplayFunc(onDisplay);

	glutMainLoop();
	return EXIT_SUCCESS;
}