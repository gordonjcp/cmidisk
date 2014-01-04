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

#include "imd.h"

// unpacked disk is 77 tracks * 26 sectors * 2 sides * 128 bytes
#define IMGSIZE 512512

int main (int argc, char **argv) {
	FILE *out;
	unsigned char buffer[IMGSIZE];
	unsigned char *d;
	int fs;	
	
	if (argc != 2) {
		printf("needs a disk image file\n");
		exit(1);
	}

	fs = imd_read(argv[1], &d);
	printf("%d bytes read\n", fs);
	imd_unpack(d, buffer);
	free(d);

	out = fopen("test.bin", "w");
	printf("writing %d bytes\n", fwrite(buffer, 1, 512512, out));
	fclose(out);
}
