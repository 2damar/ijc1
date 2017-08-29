#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];
};

struct ppm* ppm_read(const char* filename);

int ppm_write(struct ppm* p, const char* filename);

#endif
