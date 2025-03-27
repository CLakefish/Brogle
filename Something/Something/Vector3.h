#pragma once

#include <math.h>

#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct Vector3 {
	float x;
	float y;
	float z;

	float w;
} Vector3;

static inline Vector3 vec3_Add(const Vector3 a, const Vector3 b) {
	return (Vector3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

static inline Vector3 vec3_Subtract(const Vector3 a, const Vector3 b) {
	return (Vector3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

static inline Vector3 vec3_Multiply(const Vector3 a, const float b) {
	return (Vector3) { a.x * b, a.y * b, a.z * b };
}

static inline Vector3 vec3_Divide(const Vector3 a, const float b) {
	return (Vector3) { a.x / b, a.y / b, a.z / b };
}

static inline float vec3_Magnitude(const Vector3 a) {
	return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

static inline Vector3 vec3_Normalize(const Vector3 a) {
	float mag = vec3_Magnitude(a);
	if (mag == 0) return (Vector3) { 0, 0, 0 };

	return vec3_Divide(a, mag);
}

static inline float vec3_Dot(const Vector3 a, const Vector3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

static inline Vector3 vec3_Cross(const Vector3 a, const Vector3 b) {
	return (Vector3) { (a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x) };
}

static inline float vec3_Distance(const Vector3 a, const Vector3 b) {
	return vec3_Magnitude(vec3_Subtract(a, b));
}

static inline Vector3 vec3_Print(const Vector3 vec) {
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
}

static inline int vec3_Equals(const Vector3 a, const Vector3 b) {
	return (a.x == b.x && a.y == b.y && a.z == b.z) ? 1 : 0;
}

#endif // !VECTOR3_H