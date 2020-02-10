#include "Sphere.h"

void fillSpherePointsAndColors() {
	int k = 0;
	for (float phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		float phir = phi * PI / 180;
		float phir20 = (phi + 20.0)* PI / 180;
		for (float theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			float thetar = theta * PI / 180;
			quad_data[k] = vec3(sin(thetar)*cos(phir),
				cos(thetar)*cos(phir), sin(phir));
			colors[k] = { 0.0,0.0,1.0 };
			k++;
			quad_data[k] = vec3(sin(thetar)*cos(phir20),
				cos(thetar)*cos(phir20), sin(phir20));
			colors[k] = { 0.0,0.0,1.0 };
			k++;
		}
	}
	for (float phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		float phir = phi * PI / 180;
		float phir20 = (phi + 20.0)* PI / 180;
		for (float theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			float thetar = theta * PI / 180;
			quad_data[k] = vec3(sin(thetar)*cos(phir),
				cos(thetar)*cos(phir), sin(phir));
			colors[k] = { 1.0,1.0,0.0 };
			k++;
			quad_data[k] = vec3(sin(thetar)*cos(phir20),
				cos(thetar)*cos(phir20), sin(phir20));
			colors[k] = { 1.0,1.0,0.0 };
			k++;
		}
	}
}
void init()
{
	fillSpherePointsAndColors();
	
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data) + sizeof(colors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad_data), quad_data);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(quad_data), sizeof(colors), colors);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(quad_data)));

	thetaPosition = glGetUniformLocation(program, "theta");
	scalePos = glGetUniformLocation(program, "scale");
	translatePos = glGetUniformLocation(program, "translateForAnimate");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform3fv(thetaPosition, 1,theta);
	glUniform3fv(scalePos, 1, scale);
	glUniform3fv(translatePos, 1, translateForAnimate);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices/2);

	theta = { -90.0,0.0,-50.0 };
	translateForAnimate = { 0.0,0.0,0.0 };
	scale = { 0.3,0.3,0.3 };

	glUniform3fv(thetaPosition, 1, theta);
	glUniform3fv(scalePos, 1, scale);
	glUniform3fv(translatePos, 1, translateForAnimate);

	glDrawArrays(GL_TRIANGLE_FAN, numVertices / 2, numVertices / 2);
	glutSwapBuffers();
	
}


void animate(int id) {
	angle = angle + 5;
	theta.x += angle;
	theta.z += angle;
	translateForAnimate.x = -sin(theta.x * 2 * PI / 360) / 1.3;
	translateForAnimate.y = cos(theta.x * 2 * PI / 360) / 1.3;
	translateForAnimate.z = 0.0;
	scale = { 0.18,0.18,0.18 };
	glutPostRedisplay();
	glutTimerFunc(200, animate, 0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800,800 );
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sphere");
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(myDisplay);
	glutTimerFunc(100, animate, 0);
	glutMainLoop();
	return 0;
}