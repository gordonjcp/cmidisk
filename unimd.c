/*  vim: set noexpandtab ai ts=4 sw=4 tw=4:

   	(C) 2014 Gordon JC Pearce MM0YEQ <gordon@gjcp.net>
	
	cmidisk.c

	cmidisk is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	any later version.

	cmidisk is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cmidisk.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "imd.h"

// unpacked disk is 77 tracks * 26 sectors * 2 sides * 128 bytes
#define IMGSIZE 512512

void usage() {
	// show a brief message
	printf("\nunimd: Extract a binary image from a .IMD file\n");
	printf("example: $ unimd STRINGS1.IMD # creates a disk image called strings1.bin\n");
	printf("         $ unimd STRINGS1.IMD ~/strings.bin # specify the output filename\n\n");
}

int main (int argc, char **argv) {
	FILE *out;
	unsigned char buffer[IMGSIZE];
	unsigned char *d;

	int fsize, i;

	char out_fn[256];

	if ((argc < 2) || (argc>3)) {
		usage();
		exit(1);	
	}

	i=0;
	i++;

	if (argc == 2) {	// create a filename based on the input
		// note that this rather rudely just replaces the last three letters
		// of the path with "bin", whether that makes sense or not
		
		int sl = strlen(argv[1]);
		strncpy(out_fn, argv[1], sl - 3);
		strncpy(out_fn + sl - 3, "bin", 3);
	} else {
		strncpy(out_fn, argv[2], 256);
	}

	printf("writing to: %s\n", out_fn);

	fsize = imd_read(argv[1], &d);
	printf("%d bytes read\n", fsize);
	imd_unpack(d, buffer);
	free(d);

	out = fopen(out_fn, "w");
	printf("writing %d bytes\n", (int) fwrite(buffer, 1, 512512, out));
	fclose(out);

	return 0;
}
