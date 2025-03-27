#pragma once

#include "Vector3.h"

#ifndef CAMERA
#define CAMERA

typedef struct {
	Vector3 pos;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
} Camera_t;

#endif