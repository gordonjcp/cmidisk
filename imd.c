/*  vim: set noexpandtab ai ts=4 sw=4 tw=4:

   	(C) 2014 Gordon JC Pearce MM0YEQ <gordon@gjcp.net>
	
	imd.c

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

// parse IMD files, making certain assumptions that pertain to Fairlight
// disks.  In particular, double-sided, 77 tracks of 26 sectors of 128 bytes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imd.h"

int imd_read(char *filename, unsigned char **diskbuff) {
	// open the .imd file, with minimal checking
	// allocates a buffer containing the raw .IMD
	// returns the number of bytes read

	FILE *in;	
	int filesize, rc;
	unsigned char *buffer;
	
	in = fopen(filename, "r");
	if (!in) {
		perror("Couldn't open image file");
		exit(1);
	}
	
	// seek to end of file, to determine length
	fseek(in, 0, SEEK_END);
	filesize = ftell(in);
	rewind(in);
	
	buffer = malloc(filesize);
	if (!buffer) {
		perror("failed to allocate disk buffer");
		exit(1);
	}

	rc = fread(buffer, 1, filesize, in);
	if (!rc) {
		perror("Failed to read");
		exit(1);
	}
	
	fclose(in);

	*diskbuff = buffer;
	return filesize;
}

static int parse_sector(unsigned char *buffer, int ptr, unsigned char *sector) {
	// decode an IMD sector into a 128-byte sector
	
	int length;
	
	//printf("Sector type %d, ptr %05x\n", buffer[ptr], ptr);
	
	switch(buffer[ptr]) {
		case UNAVAIL:   // invalid sector, return zeros
			memset(sector, 0, 128);
			length = 0x01;
			printf("error sector\n");
			exit(1);
			break;
		case NORMAL:	// normal sector, just copy it
		case NORMALDEL:
		case NORMALERR:
			memcpy(sector, buffer + ptr + 1, 128);
			length = 0x81;
			break;
		case COMPRESSED:
		case COMPDEL:
		case COMPERR:
			memset(sector, *(buffer + ptr + 1), 128);
			length = 0x02;
			break;
		default:
			printf("unhandled, and everything following is likely to be bogus\n");
			length = 0;
			exit(1);
		}
	return length;
}


static int imd_parse_track(unsigned char *buffer, int ptr, unsigned char *track) {
	// walk along the track data

	int i, j, l, offset = 5;
	unsigned char sector[128];
	unsigned char sectormap[26];
	unsigned char cylindermap[26];
	unsigned char headmap[26];
	
	int head = buffer[ptr+2];
	
	//printf("track start %05x, cylinder=%02d, head=%02x\n", ptr, buffer[ptr+1], head);
	memcpy(sectormap, buffer+ptr+offset, 26);   // get the 26-byte sector map
	offset +=  26; // 26 byte sector map

	if (head & 0x80) {
		memcpy(cylindermap, buffer+ptr+offset, 26);   // get the 26-byte sector map
		offset +=  26; // 26 byte sector map
	}

	// VOICES.IMD has head 1 represented as 0x41, meaning that physical head 1 is
	// recorded as head 0.  I don't think we need to care about this, just skip the data
	if (head & 0x40) {
		memcpy(headmap, buffer+ptr+offset, 26);   // get the 26-byte head map
		offset +=  26; // 26 byte sector map
	}

	for (j=0; j<26; j++) {
		l = parse_sector(buffer, ptr+offset, sector);
		memcpy(track + 128*(sectormap[j]-1), sector, 128);
		offset += l;
	}

	return offset;
}

int imd_unpack(unsigned char *diskbuff, unsigned char *imgbuff) {
	// work through the .imd file and unpack it into the image buffer

	int ptr, i;
	unsigned char track[128*26];

	// skip to the end of the header
	for (ptr = 0;diskbuff[ptr] != 0x1a; ptr++ );
	ptr++;

	// ptr now points to the first byte of the first track block
	// loop over all 154 tracks (hopefully)
	for (i=0; i<77*2; i++) {
		ptr += imd_parse_track(diskbuff, ptr, track);
		memcpy(imgbuff + (3328*i), track, 3328);
	}

}
