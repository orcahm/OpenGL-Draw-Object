#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <fstream>
# define M_PI           3.14159265358979323846f  /* pi */

#include "Shader_Loader.h"

using namespace Core;

GLuint program;

GLfloat vertices[] = { 0.4f, 0.132f,
-0.4f, 0.132f,
0.0f, -0.168f,

/*Ýlk üçgeni oluþturan noktalarýn 72 derece pozitif ve negatif yönler de döndürülür */
0.4f*cos(72 * 2 * M_PI / 360) - 0.132f*sin(72 * 2 * M_PI / 360), 0.132f*cos(72 * 2 * M_PI / 360) + 0.4f*sin(72 * 2 * M_PI / 360),
-0.4f*cos(72 * 2 * M_PI / 360) - 0.132f*sin(72 * 2 * M_PI / 360), 0.132f*cos(72 * 2 * M_PI / 360) - 0.4f*sin(72 * 2 * M_PI / 360),
0.168f*sin(72 * 2 * M_PI / 360) , -0.168f*cos(72 * 2 * M_PI / 360) ,

0.4f*cos(-72 * 2 * M_PI / 360) - 0.132f*sin(-72 * 2 * M_PI / 360), 0.132f*cos(-72 * 2 * M_PI / 360) + 0.4f*sin(-72 * 2 * M_PI / 360),
-0.4f*cos(-72 * 2 * M_PI / 360) - 0.132f*sin(-72 * 2 * M_PI / 360), 0.132f*cos(-72 * 2 * M_PI / 360) - 0.4f*sin(-72 * 2 * M_PI / 360),
0.168f*sin(-72 * 2 * M_PI / 360) , -0.168f*cos(-72 * 2 * M_PI / 360)
};

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);						//ekraný kýrmýzý yapar

															//3 tane üçgen çizerek yýldýzý basar
	glDrawArrays(GL_TRIANGLES, 0, 9);

	glutSwapBuffers();
}

void Init()
{

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("vertshader.glsl", "fragshader.glsl");

	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Star");
	glewInit();

	glutInitContextVersion(3, 1);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glewExperimental = true;

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutMainLoop();
	glDeleteProgram(program);
	return 0;

}