#include "FileIO.h"

char* fileToString(const char* fileName)
{
	FILE* file = NULL;
	// Read in binary mode
	fopen_s(&file, fileName, "rb");

	if (!file)
	{
		perror("Unable to open file!");
		return NULL;
	}

	// Get the end of the file
	fseek(file, 0, SEEK_END);
	// Get last index
	unsigned long len = ftell(file);
	// Set it back to the end of the file
	rewind(file);

	char* buff = (char*)malloc((size_t)len + 1);
	if (!buff)
	{
		fclose(file);
		perror("Unable to allocate buffer");
		return NULL;
	}

	fread(buff, 1, len, file);
	buff[len] = '\0';
	fclose(file);
	return buff;
}