#pragma once
#ifndef DYNAMIC_ARRAY

#include <stdio.h>
#include <stdlib.h> 
#include <stddef.h>
#include <stdbool.h>

#include "Vector3.h"

#define GEN_DYNAMIC_ARRAY_TYPE(type) \
typedef struct DA##type { \
	type* data; \
	int count; \
	int capacity; \
} DA##type; \
\
static inline void DA##type##_Init(DA##type* arr, int init) { \
	arr->data = (type*)malloc(init * sizeof(type)); \
	if (arr->data == NULL) { \
		printf("idfk what happened but it didnt malloc lmao"); \
		return; \
	} \
	arr->count = 0; \
	arr->capacity = init; \
};\
\
static inline int DA##type##_Equivalent(type a, type b); \
\
static inline void DA##type##_Push(DA##type* arr, type* val) { \
	if (arr->count >= arr->capacity) { \
		arr->capacity *= 2; \
		type* t = (type*)realloc(arr->data, arr->capacity * sizeof(type)); \
		if (t == NULL) { \
			printf("idfk what happened but it didnt realloc lmao"); \
			return; \
		} \
		arr->data = t; \
	} \
	arr->data[arr->count++] = *val; \
};\
\
static inline void DA##type##_Remove(DA##type* arr, type val) { \
	for (int i = 0; i < arr->count; ++i) { \
		if (DA##type##_Equivalent(val, arr->data[i]) == 1) { \
			for (int j = i; j < arr->count - 1; ++j) { \
				arr->data[j] = arr->data[j + 1]; \
			} \
			arr->count--; \
			return; \
		} \
	}\
};\
\
static inline void DA##type##_Free(DA##type* arr) { \
	if (arr->data == NULL || arr->count < 0 || arr->capacity < 0) return; \
	free(arr->data); \
	arr->data = NULL; \
	arr->count = arr->capacity = 0; \
};\
\

GEN_DYNAMIC_ARRAY_TYPE(int);
GEN_DYNAMIC_ARRAY_TYPE(Vector3);

static inline int DAint_Equivalent(int a, int b) {
	return (a == b) ? 1 : 0;
}

static inline int DAVector3_Equivalent(Vector3 a, Vector3 b) {
	return vec3_Equals(a, b);
}

#endif // !DYNAMIC_ARRAY
