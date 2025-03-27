#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

Shader* ShaderInit(char* vertex, char* fragment)
{
	GLuint success;

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("VERTEX SHADER FAIL: %s", infoLog);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("FRAGMENT SHADER FAIL: %s", infoLog);
	}

	free(vertex);
	free(fragment);

	Shader* shader = (Shader*)malloc(sizeof(Shader));

	if (!shader)
	{
		perror("Unable to initialize shader!");
		return NULL;
	}

	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, vertexShader);
	glAttachShader(shader->ID, fragmentShader);
	glLinkProgram(shader->ID);

	glGetProgramiv(shader->ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shader->ID, 512, NULL, infoLog);
		printf("%s\n", infoLog);
		return NULL;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shader;
}

void ShaderUse(Shader* shader)
{
	glUseProgram(shader->ID);
}

void ShaderClear(Shader* shader)
{
	glDeleteProgram(shader->ID);
	free(shader);
}

static inline void ShaderSetBool(const Shader* shader, const char* name, const bool value)
{
	glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

static inline void ShaderSetInt(const Shader* shader, const char* name, const int value)
{
	glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

static inline void ShaderSetFloat(const Shader* shader, const char* name, const float value)
{
	glUniform1f(glGetUniformLocation(shader->ID, name), value);
}