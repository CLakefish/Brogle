#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "DynamicArray.h"

#ifndef SPARSE_SET
#define SPARSE_SET

GEN_DYNAMIC_ARRAY_TYPE(DAint);
static inline int DADAint_Equivalent(DAint a, DAint b) {
	return a.count == b.count && a.capacity == b.capacity;
}

#define GEN_SPARSE_SET_TYPE(type, index) \
typedef struct SP##type { \
	DADA##index sparse; \
	DA##type dense; \
	int capacity; \
	int count; \
	int pageSize; \
} SP##type; \
\
static inline SP##type SP##type##_Init(int pageSize, int capacity) { \
	SP##type t; \
	int pages = capacity / pageSize; \
	DADA##index##_Init(&t.sparse, pages); \
	for (int i = 0; i < pages; ++i) { \
		t.sparse.data[i].data = NULL; \
		t.sparse.data[i].count = 0; \
		t.sparse.data[i].capacity = pageSize; \
	} \
	DA##type##_Init(&t.dense, 2); \
	t.count	   = 0; \
	t.capacity = capacity; \
	t.pageSize = pageSize; \
	return t; \
}; \
\
static inline void SP##type##_Free(SP##type* set) { \
	int pageTotal = set->capacity / set->pageSize; \
	for (int i = 0; i < pageTotal; ++i) { \
		DA##index##_Free(&set->sparse.data[i]); \
	} \
	DADA##index##_Free(&set->sparse); \
	DA##type##_Free(&set->dense); \
	set->count = 0; \
}; \
\
static inline void SP##type##_Expand(SP##type* set) { \
	set->capacity *= 2; \
	DA##index* temp = (DA##index*)realloc(set->sparse.data, set->capacity * sizeof(DA##index)); \
	if (temp == NULL) { \
		perror("UNABLE TO EXPAND SET! MEMORY DID NOT REALLOC!"); \
		return; \
	} \
	set->sparse.capacity *= 2; \
	set->sparse.data = temp; \
	int pageTotal = set->capacity / set->pageSize;\
	int half = (set->capacity / 2) / set->pageSize; \
	for (int i = half; i < pageTotal; ++i) { \
		set->sparse.data[i].data = NULL; \
		set->sparse.data[i].count = 0; \
		set->sparse.data[i].capacity = set->pageSize; \
	} \
}; \
\
static inline int SP##type##_Contains(SP##type* set, index ID) { \
	if (ID >= set->capacity) return 0; \
	int page = ID / set->pageSize; \
	int ind  = ID % set->pageSize; \
	if (page >= set->sparse.capacity || set->sparse.data[page].data == NULL || ind >= set->sparse.data[page].capacity) return 0; \
	int denseInd = set->sparse.data[page].data[ind]; \
	if (denseInd < 0 || denseInd >= set->dense.count) return 0; \
	return set->dense.data[denseInd].ID == ID ? 1 : 0; \
}; \
\
static inline type* SP##type##_Get(SP##type* set, index ID) { \
	if (ID >= set->capacity) return 0; \
	int page = ID / set->pageSize; \
	int ind  = ID % set->pageSize; \
	if (page >= set->sparse.capacity || set->sparse.data[page].data == NULL || ind >= set->sparse.data[page].capacity) return 0; \
	int denseInd = set->sparse.data[page].data[ind]; \
	if (denseInd < 0 || denseInd >= set->dense.count) return 0; \
	return &set->dense.data[denseInd]; \
}; \
static inline void SP##type##_Insert(SP##type* set, type* item, index ID) { \
	if (SP##type##_Contains(set, ID)) { \
		assert("Sparse Set already contains ID of " && ID); \
		return; \
	} \
	if (set->count >= set->capacity) SP##type##_Expand(set); \
	int page = ID / set->pageSize; \
	int ind  = ID % set->pageSize; \
	if (set->sparse.data[page].data == NULL) { \
		DA##index##_Init(&set->sparse.data[page], set->pageSize); \
		if (set->sparse.data[page].data == NULL) { \
			assert("Sparse Set initialization through insertion failed"); \
			return; \
		} \
	} \
	item->ID = ID; \
	DA##type##_Push(&set->dense, item); \
	set->sparse.data[page].data[ind] = set->count; \
	set->count++; \
}; \
\
static inline void SP##type##_Remove(SP##type* set, index ID) { \
	if (!SP##type##_Contains(set, ID)) { \
		assert("Sparse Set does not contain ID of " && ID); \
		return; \
	} \
	int page	 = ID / set->pageSize; \
	int ind		 = ID % set->pageSize; \
	int denseInd = set->sparse.data[page].data[ind]; \
	type last = set->dense.data[set->dense.count - 1]; \
	set->dense.data[set->dense.count - 1] = set->dense.data[denseInd]; \
	set->dense.data[denseInd]			  = last; \
	set->dense.count--; \
	int lastPage = last.ID / set->pageSize; \
	int lastInd  = last.ID % set->pageSize; \
	set->sparse.data[page].data[ind] = set->sparse.data[lastPage].data[lastInd]; \
	set->sparse.data[lastPage].data[lastInd] = denseInd; \
	set->count--; \
};\


#endif // !SPARSE_SET
