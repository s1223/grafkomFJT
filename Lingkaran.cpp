#include "Lingkaran.h"
#include <math.h>
#include <glew.h>		//ganti dengan <GL/glew.h> sesuai dgn library masing-masing
#include <glut.h>		//ganti dengan <GL/glut.h> sesuai dgn library masing-masing

Lingkaran :: Lingkaran() {
	this->jari2 = 0;
	this->lebarpusat = 0;
	this->tinggipusat = 0;
	this->titik = 0;
	this->x = 0;
	this->y = 0;
	this->a = 0;
}

Lingkaran::Lingkaran(int jari2, int titik, int lebarpusat, int tinggipusat) {
	this->jari2 = jari2;
	this->lebarpusat = lebarpusat;
	this->tinggipusat = tinggipusat;
	this->titik = titik;
	this->x = x;
	this->y = y;
}

void Lingkaran ::gambar_L (int jari2, int titik, int lebarpusat, int tinggipusat) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (a = 0; a <= titik; a++) {
		sudut = a * (2 * phi / titik);
		x = lebarpusat + jari2 * cos(sudut);
		y = tinggipusat + jari2 * sin(sudut);
		glVertex2f(x, y);
	}
	glEnd();
}