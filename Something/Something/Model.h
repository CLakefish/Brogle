#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Vector3.h"
#include "MeshComponent.h"

#ifndef MODEL
#define MODEL

typedef struct Model {
	DAMesh mesh;
	unsigned int ID;
} Model;

GEN_DYNAMIC_ARRAY_TYPE(char);
static inline int DAchar_Equivalent(char a, char b) {
	return a == b;
}

GEN_DYNAMIC_ARRAY_TYPE(Model);
// Fix this
static inline int DAModel_Equivalent(Model a, Model b) {
	a.mesh.capacity == b.mesh.capacity && a.mesh.count == b.mesh.count;
}

static Model Model_Init(Mesh* mesh, unsigned int ID) {
	Model model = {0};
	model.ID = ID;

	DAMesh_Init(&model.mesh, 1);
	DAMesh_Push(&model.mesh, mesh);
	return model;
}

static Model Model_Load(const char* fileName, unsigned int ID) {
	printf("Loading model with filename %s\n", fileName);
	LARGE_INTEGER start, end, freq, fileOpen, fileClose;

	if (!QueryPerformanceFrequency(&freq)) {
		perror("QueryPerformanceFrequency failed!\n");
		return;
	}

	QueryPerformanceCounter(&start);
	QueryPerformanceCounter(&fileOpen);

	FILE* file;
	fopen_s(&file, fileName, "r");
	if (file == NULL) {
		assert("MODEL FILE UNABLE TO BE LOADED! FILE PATH INVALID. PATH GIVEN WAS" && fileName);
		return (Model) { 0 };
	}

	DAVector3 positions;
	DAVector3 normals;
	DAVector3 texCoords;
	Texture tex;

	Mesh mesh;
	mesh.refCount = 1;
	DAVertex_Init(&mesh.vertices, 32);
	DAint_Init(&mesh.indices, 32);

	DAVector3_Init(&positions, 32);
	DAVector3_Init(&normals,   32);
	DAVector3_Init(&texCoords, 32);

	QueryPerformanceCounter(&end);
	double elapsed_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("Elapsed in ms for init: %.25f\n", elapsed_time * 1000.0f);

	char buf[256];
	int index = 0;
	while (fgets(buf, 256, file)) {
		if (buf[0] == 'v') {
			if (buf[1] == ' ') {
				Vector3 pos;
				if (sscanf_s(buf, "v %f %f %f", &pos.x, &pos.y, &pos.z) == 3) {
					DAVector3_Push(&positions, &pos);
				}
				else {
					assert("Error reading v line in .obj file!");
				}
			}
			else if (buf[1] == 'n') {
				Vector3 normal;
				if (sscanf_s(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z) == 3) {
					DAVector3_Push(&normals, &normal);
				}
				else {
					assert("Error reading vn line in .obj file!");
				}
			}
			else if (buf[1] == 't') {
				Vector3 tex;
				if (sscanf_s(buf, "vt %f %f", &tex.x, &tex.y) == 2) {
					DAVector3_Push(&texCoords, &tex);
				}
				else {
					assert("Error reading vt line in .obj file!");
				}
			}
		}
		else if (buf[0] == 'f')	{
			int pA, pB, pC;
			int nA, nB, nC;
			int tA, tB, tC;

			// Could swap to sscanf_s, but then I'd need sizeof(int) which is boring lol
			if (sscanf_s(buf, "f %i/%i/%i %i/%i/%i %i/%i/%i", &pA, &tA, &nA, &pB, &tB, &nB, &pC, &tC, &nC) != 9) {
				assert("Error reading f line in .obj file!");
				continue;
			}

			Vertex vertA, vertB, vertC;
			vertA = (Vertex){ positions.data[pA - 1], normals.data[nA - 1], texCoords.data[tA - 1].x, texCoords.data[tA - 1].y };
			vertB = (Vertex){ positions.data[pB - 1], normals.data[nB - 1], texCoords.data[tB - 1].x, texCoords.data[tB - 1].y };
			vertC = (Vertex){ positions.data[pC - 1], normals.data[nC - 1], texCoords.data[tC - 1].x, texCoords.data[tC - 1].y };

			DAVertex_Push(&mesh.vertices, &vertA);
			DAVertex_Push(&mesh.vertices, &vertB);
			DAVertex_Push(&mesh.vertices, &vertC);

			DAint_Push(&mesh.indices, &index);
			index++;
			DAint_Push(&mesh.indices, &index);
			index++;
			DAint_Push(&mesh.indices, &index);
			index++;
		}
		// FIX THIS!
		else if (buf[0] == 'm') {
			QueryPerformanceCounter(&start);

			int endIndex = 0;
			for (int i = (int)strlen(fileName) - 1; i >= 0; --i) {
				if (fileName[i] == '/') {
					endIndex = i;
					break;
				}
			}

			char initPath[256];
			for (int i = 0; i < endIndex; ++i) {
				initPath[i] = fileName[i];
			}
			initPath[endIndex] = '/';
			initPath[endIndex + 1] = '\0';

			QueryPerformanceCounter(&end);
			double e = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
			printf("Elapsed in ms for mtl init path: %.25f\n", e * 1000.0f);

			QueryPerformanceCounter(&start);

			char mtlPath[256];
			strcpy_s(mtlPath, sizeof(mtlPath), initPath);
			strcat_s(mtlPath, sizeof(mtlPath), buf + 7);
			mtlPath[strlen(mtlPath) - 1] = '\0';

			QueryPerformanceCounter(&end);
			e = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
			printf("Elapsed in ms for mtl path: %.25f\n", e * 1000.0f);

			QueryPerformanceCounter(&start);

			FILE* mtl;
			fopen_s(&mtl, mtlPath, "r");

			if (mtl == NULL) {
				assert("MODEL FILE MTL UNABLE TO BE LOADED! FILE PATH INVALID");
				return (Model) {0};
			}

			// Swap this to getting the last line 
			char mtlBuf [256] = {0};
			while (fgets(mtlBuf, sizeof(mtlBuf), mtl)) {
				if (mtlBuf[0] == 'm') {
					break;
				}
			}

			if (mtlBuf[strlen(mtlBuf)] != '\0') mtlBuf[strlen(mtlBuf)] = '\0';

			QueryPerformanceCounter(&end);
			e = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
			printf("Elapsed in ms for mtl buff: %.25f\n", e * 1000.0f);

			char texPath[256];
			strcpy_s(texPath, sizeof(texPath), initPath);
			strcat_s(texPath, sizeof(texPath), mtlBuf + 7);

			QueryPerformanceCounter(&start);

			tex = Texture_Init(texPath);

			QueryPerformanceCounter(&end);
			e = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
			printf("Elapsed in ms for mtl tex load: %.25f\n", e * 1000.0f);

			mesh.texture = tex;
			fclose(mtl);
		}
	}

	if (fclose(file) == EOF) {
		assert("ERROR CLOSING FILE!");
		return (Model) { 0 };
	}

	QueryPerformanceCounter(&fileClose);
	elapsed_time = (double)(fileClose.QuadPart - fileOpen.QuadPart) / freq.QuadPart;
	printf("Elapsed in ms for file loading: %.25f\n", elapsed_time * 1000.0f);

	DAVector3_Free(&positions);
	DAVector3_Free(&normals);
	DAVector3_Free(&texCoords);

	Mesh_Calculate(&mesh);
	Model model = Model_Init(&mesh, ID);

	return model;
}

#endif // !MODEL
