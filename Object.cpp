#include "Kotak.h"
#include "Lingkaran.h"
#include "Segitiga.h"
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include"Box2D/Box2D.h"
#include<stdbool.h>
#include "imageloader.h"

int index_minimal;
int jarak_minimal = 9999;
int temp;
int old_x = 0;
int old_y = 0;
int valid = 0;

const double phi = 3.141592653589793;
using namespace std;
float TX[4];
float TY[4];
int counter = 0;
int status_update = 0;

int dt[100][3];
int counter_data = 0;

GLuint _textureK;


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void initRendering() {
	Image* image = loadBMP("fti.bmp");
	_textureK = loadTexture(image);

	//delete image;
}


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

Lingkaran::Lingkaran() {
	this->lebarpusat = 0;
	this->tinggipusat = 0;
}

Lingkaran::Lingkaran(int lebarpusat, int tinggipusat) {
	this->lebarpusat = lebarpusat;
	this->tinggipusat = tinggipusat;
}

void Lingkaran::gambar_L(int lebarpusat, int tinggipusat) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (a = 0; a <= 500; a++) {
		sudut = a * (2 * phi / 500);
		x = lebarpusat + 25 * cos(sudut);
		y = tinggipusat + 25 * sin(sudut);
		glVertex2f(x, y);
	}
	glEnd();
}

void Segitiga::segi3(float ax, float by) {
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex2f(ax, by + 40);
	glVertex2f(ax - 50, by - 50);
	glVertex2f(ax + 50, by - 50);
	glEnd();
}

void Kotak::gambar_k(float x, float y) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x - 50, y - 50);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x - 50, y + 50);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + 50, y + 50);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x + 50, y - 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void save(int jenis, int x, int y) {
	dt[counter_data][2] = jenis;
	dt[counter_data][0] = x;
	dt[counter_data][1] = y;
	counter_data += 1;
}


float box2d_y(float posisi_saat_ini, float batas_bawah) {
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -9.8f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, posisi_saat_ini);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, batas_bawah);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world.Step(timeStep, velocityIterations, positionIterations);

	// Now print the position and angle of the body.
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	return position.y;
}


void onDisplay() {
	initRendering();
	Kotak object1;
	Segitiga objeknya;
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
			objeknya.segi3(dt[i][0], dt[i][1]);
		}
		else if (dt[i][2] == 3)
		{
			obj1.gambar_L(dt[i][0], dt[i][1]);
		}
		//start Box2D
		dt[i][1] = box2d_y(dt[i][1], 25);
		//printf("%i\n", i);
		//end Box2D
	}
	
	glutSwapBuffers();
}
void tampilkan() {
	if (status_update == 1)
	{
		for (size_t i = 0; i < 30; i++)
		{
			onDisplay();
		}
		status_update = 0;
	}
}
void myKeyboard(unsigned char key, int x, int y) {
	if (key == 'a' || key == 'A') {
		save(1, x, 600 - y);
		status_update = 1;
		tampilkan();
	}
	else if (key == 's' || key == 'S') {
		save(2, x, 600 - y);
		status_update = 1;
		tampilkan();
	}
	else if (key == 'd' || key == 'D') {
		save(3, x, 600 - y);
		status_update = 1;
		tampilkan();
	}
}

void myMouse(int button, int state, int x, int y) {
	old_x = x;
	printf("%i\n", x);
	old_y = y;
	valid = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < counter_data; i++) {
			int variabelx = dt[i][0];
			//int variabely = dt[i][1];
			//int variabelj = dt[i][2];
			temp = variabelx - x;
			if (temp < 0)
			{
				temp = temp * -1;
			}
			if (jarak_minimal > temp)
			{
				jarak_minimal = temp;
				index_minimal = i;
			}
		}
		temp = 0;
		jarak_minimal = 9999;
	}
}

void myMotion(int x, int y) {
	if (valid) {
		printf("Pindah\n");
		int dx = old_x - x;
		int dy = old_y - y;
		dt[index_minimal][0] = x;
		dt[index_minimal][1] = 600 - y;
		onDisplay();
	}
	old_x = x;
	//printf("%i;", x);
	old_y = y;
	//printf("%i\n", y);
	
}

int main(int argc, char* argv[]) {
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("672017095");
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(onDisplay);
	glutMainLoop();
	return 0;
}
