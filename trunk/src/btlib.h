/***************************************************************************
 *            btlib.h
 *
 *  Mon Jul  4 10:59:38 2005
 *  Copyright  2005  Charles
 *  charles@sourcecode.za.net
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef _BTLIB_H
#define _BTLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

struct btdev_name{
	char addr[18];
	char name[256];
};

extern struct btdev_name * dev_names;

int btdev_scan(int num_rsp);

#ifdef __cplusplus
}
#endif

#endif /* _BTLIB_H */
