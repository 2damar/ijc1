#include "ppm.h"
#include "error.h"

struct ppm* ppm_read(const char* filename) {
	FILE* fh = fopen(filename, "r");
	if(fh == NULL) {
		warning_msg("Cannot open file: %s", filename);
		return NULL;
	}

	char header[3] = {0};
	int c;
	fgets(header, 3, fh);

	//first line in PPM file P6 format must start with line P6 <ws>+
	if(header[0] != 'P' || header[1] != '6') {
		warning_msg("Wrong format of the ppm file: %s - 1st line", filename);
		return NULL; 
	}
	//skip ws
	while((((c = fgetc(fh)) != '\n')) && isspace(c) && (c != EOF));
	if(c != '\n') {
		warning_msg("Wrong format of the ppm file: %s - 1st line", filename);
		return NULL;
	}

	//second line xsize<ws>+ ysize<ws>+
	int xsz = 0;
	if(((c = fgetc(fh)) != EOF) && (isdigit(c))) {
		xsz = c - '0'; //first digit
		while(((c = fgetc(fh)) != EOF) && (isdigit(c))) 
			xsz = 10*xsz + (c - '0');
	}
	// skip ws between xsize and ysize
	while((isspace(c)) && c != '\n') 
		c = fgetc(fh);
	if(!isdigit(c)) {  // nonws before ysize on the 2nd line
		warning_msg("Wrong format of the ppm file: %s - 2nd line", filename);
		return NULL;
	}

	// read ysize
	int ysz = c - '0'; //first digit
	while(((c = fgetc(fh)) != EOF) && (isdigit(c)))
		ysz = 10*ysz + (c - '0');
	//skip ws after ysize
	while((isspace(c)) && c != '\n')
		c = fgetc(fh);
	if(c != '\n') { //nonws after ysize on the 2nd line
		warning_msg("Wrong format of the ppm file: %s - 2nd line", filename);
		return NULL;
	}

	// TODO fix -  3rd line "256"
	while(((c = fgetc(fh)) != EOF) && c != '\n');
	if(c != '\n') {
		warning_msg("Wrong format of the ppm file: %s - 3rd line", filename);
		return NULL;
	}
   // end TODO

	unsigned long data_size = 3 * xsz * ysz;
	struct ppm* pic = (struct ppm*)malloc(sizeof(struct ppm) + data_size*sizeof(char));
	if(pic == NULL) {
		warning_msg("malloc for struct ppm failed");
		return NULL;
	}

	pic->xsize = (unsigned)xsz;
	pic->ysize = (unsigned)ysz;
	
	// read data
	unsigned long i;
	for(i = 0; i < data_size; i++) {
		c = fgetc(fh);
		if(c == EOF)
			break;
		pic->data[i] = c;
	}

	if((i != data_size) || (fgetc(fh) != EOF)) { //incorrect amount of data
		free(pic);
		warning_msg("Incorrect amount of data");
		return NULL;
	}

	return pic;
}

int ppm_write(struct ppm* p, const char* filename) {
	if(p == NULL || p->data == NULL) 
		return -1;

	FILE* f = fopen(filename, "w");
	if(f == NULL)
		return -1;

	fprintf(f, "P6\n%d %d\n255\n", p->xsize, p->ysize);
	unsigned i = 0;
	for(i = 0; i < 3U*p->xsize*p->ysize; i++) 
		fprintf(f, "%02x", (char)p->data[i]);

	return i;

}
