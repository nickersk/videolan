/*
 * This file is part of libaacs
 * Copyright (C) 2010-2022  npzacs
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _AACS_INFO_UDF_FS_H
#define _AACS_INFO_UDF_FS_H

#include <libaacs/aacs.h>
#include "file/filesystem.h"

void close_udf(void *p);
void *open_udf(const char *path);

AACS_FILE_H *open_udf_file(void *udf, const char *filename);

#endif // _AACS_INFO_UDF_FS_H
