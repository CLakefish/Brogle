#pragma once
#ifndef DYNAMIC_ARRAY_PTR

#include <stdio.h>
#include <stdlib.h> 
#include <stddef.h>
#include <stdbool.h>

#define GEN_DYNAMIC_ARRAY_PTR_TYPE(type) \
typedef struct DAP##type { \
	type** data; \
	int count; \
	int capacity; \
} DAP##type; \
\
static inline void DAP##type##_Init(DAP##type* arr, int init) { \
	arr->data = (type**)malloc(init * sizeof(type*)); \
	if (arr->data == NULL) { \
		printf("idfk what happened but it didnt malloc lmao"); \
		return; \
	} \
	arr->count = 0; \
	arr->capacity = init; \
};\
\
static inline void DAP##type##_Push(DAP##type* arr, type* val) { \
	if (arr->count >= arr->capacity) { \
		arr->capacity *= 2; \
		type** t = (type**)realloc(arr->data, arr->capacity * sizeof(type*)); \
		if (t == NULL) { \
			printf("idfk what happened but it didnt realloc lmao"); \
			return; \
		} \
		arr->data = t; \
	} \
	arr->data[arr->count++] = val; \
};\
\
static inline void DAP##type##_Free(DAP##type* arr) { \
	for (int i = 0; i < arr->count; ++i) { \
		free(arr->data[i]); \
	}\
	free(arr->data); \
	arr->data = NULL; \
	arr->count = arr->capacity = 0; \
};\
\

#endif // !DYNAMIC_ARRAY_PTR
