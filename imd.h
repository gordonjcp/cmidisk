/*  vim: set noexpandtab ai ts=4 sw=4 tw=4:

   	(C) 2014 Gordon JC Pearce MM0YEQ <gordon@gjcp.net>
	
	imd.h

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

#ifndef __IMD_H
#define __IMD_H

enum {UNAVAIL, NORMAL, COMPRESSED, NORMALDEL, COMPDEL, NORMALERR, COMPERR, COMPDELERR };

int imd_read(char *filename, unsigned char **diskbuff);
int imd_unpack(unsigned char *diskbuff, unsigned char *imgbuff);

#endif
