#include "Kotak.h"
#include "Lingkaran.h"
#include <iostream>
#include <stdio.h>
#include <glew.h>
#include <glut.h>
using namespace std;
float TX[4];
float TY[4];
int counter = 0;

Kotak::Kotak() {
    this->x = 0;
    this->y = 0;
}

Kotak::Kotak(int x, int y) {
    this->x = x;
    this->y = y;
}

void Kotak::gambar_k() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glVertex2f(0, 200);
	glVertex2f(200, 200);
	glVertex2f(200, 0);
	glEnd();
}
void onDisplay() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	Kotak object1;
	object1.gambar_k();
	Lingkaran obj1;
	obj1.gambar_L(25, 500, 300, 300);
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//printf("Mouse Event: %d %d %d %d\n", button, state, x, y);
		if (counter == 0) {
			TX[0] = x;
			TY[0] = 500 - y;
			counter += 1;
		}
		else if (counter == 1) {
			TX[1] = x;
			TY[1] = 500 - y;
			counter += 1;
		}
		else if (counter == 2) {
			TX[2] = x;
			TY[2] = 500 - y;
			counter += 1;
		}
		else if (counter == 3) {
			TX[3] = x;
			TY[3] = 500 - y;
			counter += 1;
		}
		else if (counter == 4) {
			counter -= 4;
		}
		onDisplay();
	}
}

int main(int argc, char* argv[]) {
	Kotak ls;
	int wile = 0;
	while (wile < 4) {
		TX[wile] = -1;
		TY[wile] = -1;
		wile++;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("672017095");
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);

	glutMouseFunc(myMouse);

	glutDisplayFunc(onDisplay);
	glutMainLoop();
	return 0;
}

