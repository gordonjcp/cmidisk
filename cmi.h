/*  vim: set noexpandtab ai ts=4 sw=4 tw=4:

   	(C) 2014 Gordon JC Pearce MM0YEQ <gordon@gjcp.net>
	
	cmi.h

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

#ifndef __CMI_H
#define __CMI_H

typedef struct {
	unsigned char mode;
	unsigned char dummy0[159];
	char cofile[8];
	unsigned char dummy1[4720];
	// should now be up to offset + 0x1330, Mode 4 loop params
	unsigned char dummy2[2];
	
	// incomplete
	

} cmi_vc_file;

#endif
