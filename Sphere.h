#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Angel.h"
#include <vector>
#include <Math.h>

using namespace Angel;
using namespace std;

const GLfloat PI = 3.141592653589793238463;
const int numVertices = 684;

vec3 quad_data[numVertices];
vec3 colors[numVertices];

GLint angle = 5;

GLint thetaPosition;
GLint scalePos;
GLint translatePos;

vec3 theta = { 0.0,0.0,0.0 };
vec3 scale = { 1.0,1.0,1.0 };
vec3 translateForAnimate = { 0.0,0.0,0.0 };

void fillSpherePointsAndColors();
void init();
void myDisplay(void);
void animate(int id);
#endif
