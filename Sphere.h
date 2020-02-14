#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Angel.h"
#include <vector>
#include <Math.h>

using namespace Angel;
using namespace std;

const GLfloat PI = 3.141592653589793238463;
const int numVertices = 684; // total vertices for drawing two spheres

vec3 quad_data[numVertices]; // holds vertices of spheres
vec3 colors[numVertices]; // holds color of spheres' vertices

GLint angle = 5; // initial angle for rotation 

/* ing position variables for locations of uniform variables */
GLint thetaPosition;
GLint scalePos;
GLint translatePos;

/* vectors for translating, scaling and rotating */
vec3 theta = { 0.0,0.0,0.0 };
vec3 scale = { 1.0,1.0,1.0 };
vec3 translateForAnimate = { 0.0,0.0,0.0 };

/* function prototypes */
void fillSpherePointsAndColors();
void init();
void myDisplay(void);
void animate(int id);

#endif
