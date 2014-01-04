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

#include "imd.h"
#include "snd.h"

// unpacked disk is 77 tracks * 26 sectors * 2 sides * 128 bytes
#define IMGSIZE 512512

typedef struct {
	char name[9];
	char type[3];
	unsigned int block;
	unsigned int attr;
} qdos_dirent;

qdos_dirent directory[160];

int qdos_readdir(unsigned char *buffer) {
	// read the disk directory
	// first sector is ID block, second is Cluster Allocation Table, third is lockout table

	int ptr, block, attr, i, ent_ct;

	ptr = 3*128;	// start of directory
	ent_ct = 0;		// no entries yet
	
	for (i=0; i<160; i++) {
		if ((buffer[ptr] != 0) && (buffer[ptr] != 0xff) ) {	// directory entry isn't empty
			memcpy(directory[ent_ct].name, buffer+ptr, 8);
			memcpy(directory[ent_ct].type, buffer+ptr+8, 2);
			directory[ent_ct].block = (buffer[ptr+10]<<8) + buffer[ptr+11];
			directory[ent_ct].attr = (buffer[ptr+12]<<8) + buffer[ptr+13];
			ent_ct++;
		}
		ptr += 16;
	}
	
}

int main (int argc, char **argv) {
	FILE *out;
	unsigned char buffer[IMGSIZE];
	unsigned char *d;
	int fs;
	
	char wr_fn[12]; // eightchr.wav

	int i,j;
	char c;
	
	if (argc != 2) {
		printf("needs a disk image file\n");
		exit(1);
	}

	fs = imd_read(argv[1], &d);
	printf("%d bytes read\n", fs);
	imd_unpack(d, buffer);
	free(d);

	qdos_readdir(buffer);

	for (i=0; i<160; i++) {
		if (directory[i].attr == 0) continue;
		printf("%3d: %s.%s - block %04x\n", i, directory[i].name, directory[i].type, directory[i].block);
		if (strncmp(directory[i].type, "VC", 2) == 0) {
			// lowercase, stop at space or 8 chars
			for (j=0; j < 8; j++) {
				c = directory[i].name[j];
				if (c == ' ') break;
				wr_fn[j] = tolower(c);
			}
			sprintf(wr_fn+j, ".wav");
			snd_write(wr_fn, buffer + 0x1580 + 128*directory[i].block);
		}
	}

	

// uncomment to write out the disk image
#if 0
	out = fopen("test.bin", "w");
	printf("writing %d bytes\n", (int) fwrite(buffer, 1, 512512, out));
	fclose(out);
#endif
}
