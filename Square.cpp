#include "Square.h"
#include <glew.h>
#include <glut.h>

Square::Square() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

Square::Square(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

Square::render() {
    glBegin(GL_TRIANGLES);
    /* Put your vertex list here*/
    glEnd();
}
