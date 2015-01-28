/* Copyright: (c) Kayne Ruse 2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/

/* DOCS: A simple license header update utility written in C.
 * 
 * This may require tailoring, as it checks for C++ files using the last two
 * characters of the filename. In addition, the line that is replaced is only
 * the first line, which is replaced with a hardcoded alternative.
 * 
 * The update() function is applied to (almost) all files in a directory tree.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//update the specified file
int update(char* fname) {
	//get the length
	int len = strlen(fname);

	//check to see if this is a C++ source file
	if(strcmp(fname + len - 2, "pp") != 0) {
		return 0;
	}

	//open the file
	FILE* fptr = fopen(fname, "r");
	if (!fptr) {
		return 1;
	}

	//DO STUFF

	//read and ignore the first line
	fscanf(fptr, "%*[^\n]", 0);

	//determine the space needed for the rest of the file
	int bufferStart = ftell(fptr);
	fseek(fptr, 0, SEEK_END);
	int bufferSize = ftell(fptr) + 1;
	fseek(fptr, bufferStart, SEEK_SET);

	//make a buffer with enough space
	char* buffer = (char*)malloc(bufferSize);
	memset(buffer, 0, bufferSize);

	//read in the remainder of the file
	fscanf(fptr, "%[^\0]", buffer);

	//close and reopen the file (clears the content)
	fclose(fptr);
	fptr = fopen(fname, "w");

	//overwrite the existing file with the new content
	fprintf(fptr, "/* Copyright: (c) Kayne Ruse 2015");
	fprintf(fptr, "%s", buffer);

	//close the file
	fclose(fptr);
	free((void*)buffer);
	return 0;
}

//iterate over the directory and all sub directories
int directory(char* dirname, int (*func)(char*)) {
	//open this directory
	DIR* dir = opendir(dirname);
	struct dirent* ent = NULL;
	int ret = 0;
	char pathname[FILENAME_MAX];

	//iterate through this directory
	while ((ent = readdir(dir)) && ent->d_name) {
		//skip parent directories, and anything starting with '.'
		if (strncmp(ent->d_name, ".", 1) == 0) {
			continue;
		}

		//a usable version of the file name
		sprintf(pathname, "%s/%s", dirname, ent->d_name);

		switch(ent->d_type) {
			case DT_DIR:
				//recursion
				if (ret = directory(pathname, func)) {
					//returning errors
					return ret;
				}
			break;
			case DT_REG:
				if (ret = func(pathname)) {
					//returning errors
					return ret;
				}
			break;
		}
	}

	return closedir(dir);
}

int main(int argc, char* argv[]) {
	return directory(".", update);
}