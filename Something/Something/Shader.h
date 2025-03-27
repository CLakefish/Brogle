#pragma once

#include <stdbool.h>

#ifndef SHADER
#define SHADER

typedef void (*ShaderFunction)(void);

typedef struct {
	unsigned int ID;
} Shader;

Shader* ShaderInit(char* vertex, char* fragment);
void	ShaderUse(Shader* shader);
void	ShaderClear(Shader* shader);

inline void ShaderSetBool(const Shader* shader, const char* name, const bool value);
inline void ShaderSetInt(const Shader* shader, const char* name, const int value);
inline void ShaderSetFloat(const Shader* shader, const char* name, const float value);

#endif // !SHADER
