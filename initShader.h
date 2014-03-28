#ifndef INITSHADERS_H_
#define INITSHADERS_H_

//#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"

#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

//function prototypes
const GLchar* loadShader(const char* filename);
GLuint createShader(GLenum type, const GLchar* source);
GLuint createProgram(const vector<GLuint> shadeList);

typedef struct{
  GLenum type;
  const char* file;
} ShaderInfo;

void initShader(ShaderInfo* shaders)
{
	ShaderInfo* shade = shaders;
	vector<GLuint> Shadelist;

	while(shade->type != GL_NONE)
	{
		Shadelist.push_back(createShader(shade->type, loadShader(shade->file)));
		++shade;
	}

	GLuint program = createProgram(Shadelist);
	glUseProgram(program);
}

const GLchar* loadShader(const char* filename)
{
	FILE* file = fopen(filename, "rb");

	if(file == NULL)
	{
	     return NULL;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	GLchar* buf = new GLchar[size+1];
	fread(buf, 1, size, file);

	buf[size] = '\0';
	fclose(file);

	return const_cast<const GLchar*>(buf);
}

GLuint createShader(GLenum type, const GLchar* source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	return shader;
}

GLuint createProgram(const vector<GLuint> shadeList)
{
	GLuint program = glCreateProgram();

	for(GLuint i=0; i<shadeList.size(); i++)
	{
		glAttachShader(program,shadeList[i]);
	}

	glBindAttribLocation(program, 0, "in_position");
	glBindAttribLocation(program, 1, "in_color");
	glLinkProgram(program);

	for(GLuint i=0;i<shadeList.size();i++)
	{
		glDeleteShader(shadeList[i]);
	}

	return program;
}



#endif
