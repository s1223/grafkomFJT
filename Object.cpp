#include "Kotak.h"
#include "Lingkaran.h"
#include "Segitiga.h"
#include <iostream>
#include <stdio.h>
#include <Gl/glew.h>
#include <GL/glut.h>
using namespace std;
float TX[4];
float TY[4];
int counter = 0;

int dt[100][3];
int counter_data = 0;


Kotak::Kotak() {
	this->x = 0;
	this->y = 0;
}

Kotak::Kotak(int x, int y) {
	this->x = x;
	this->y = y;
}

Segitiga::Segitiga() {
	this->x = 0;
	this->y = 0;
}

Segitiga::Segitiga(int x, int y) {
	this->x = x;
	this->y = y;
}

void Segitiga::segi3(float ax, float by) {
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex2f(ax, by+40);
	glVertex2f(ax-50, by-50);
	glVertex2f(ax+50, by-50);
	glEnd();
}

void Kotak::gambar_k(float x, float y) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 0);
	glVertex2f(x-50, y-50);
	glVertex2f(x-50, y+50);
	glVertex2f(x+50, y+50);
	glVertex2f(x+50, y-50);
	glEnd();
}

void save(int jenis, int x, int y) {
	dt[counter_data][2] = jenis;
	dt[counter_data][0] = x;
	dt[counter_data][1] = y;
	counter_data += 1;
}

void onDisplay() {
	Kotak object1;
	Segitiga objeknya;
	objeknya.segi3(200,250);
	Lingkaran obj1; 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 100; i++)
	{
		if (dt[i][2] == 1)
		{
			object1.gambar_k(dt[i][0], dt[i][1]);
		}
		else if (dt[i][2] == 2)
		{
			object1.gambar_k(dt[i][0], dt[i][1]);
		}
		else if (dt[i][2] == 3)
		{
			obj1.gambar_L(50, 500, dt[i][0], dt[i][1]);
		}
	}
	
	//objeknya.segi3();
	
	
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'a' || key == 'A') {
		save(1, x, 500 - y);
		onDisplay();
	}
	else if (key == 's' || key == 'S') {
		save(2, x, 500 - y);
		onDisplay();
	}
	else if (key == 'd' || key == 'D') {
		save(3, x, 500 - y);
		onDisplay();
	}
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
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(onDisplay);
	glutMainLoop();
	return 0;
}
