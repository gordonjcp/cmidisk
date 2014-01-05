/*  vim: set noexpandtab ai ts=4 sw=4 tw=4:

   	(C) 2014 Gordon JC Pearce MM0YEQ <gordon@gjcp.net>
	
	sndfile.c

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

#include <sndfile.h>

#include "snd.h"

int snd_write(char *filename, unsigned char *buffer) {
	// write a 16384-frame long mono .wav file

	SNDFILE *snd;
	SF_INFO info;
	int i;

	short sf_buffer[16384];

	info.samplerate = 16000;
	info.channels = 1;
	info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_U8;
	
	snd = sf_open(filename, SFM_WRITE, &info);
	if (!snd) {
		printf("Couldn't open %s", filename);
		sf_perror(NULL);
		return -1;
	}
	
	for (i=0; i < 16384; i++) {
		sf_buffer[i] = (buffer[i]-128)<<8;
	}

	sf_write_short(snd, sf_buffer, 16384);
	sf_close(snd);
	return 0;
}
