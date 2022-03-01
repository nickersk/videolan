/*
 * This file is part of libaacs
 * Copyright (C) 2010-2022  VideoLAN
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

#include "udf_fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <udfread/udfread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void _udf_file_close(AACS_FILE_H *fp)
{
    udfread_file_close(fp->internal);
    free(fp);
}

static int64_t _udf_file_seek(AACS_FILE_H *fp, int64_t offset, int32_t origin)
{
    return udfread_file_seek(fp->internal, offset, origin);
}

static int64_t _udf_file_tell(AACS_FILE_H *fp)
{
    return udfread_file_tell(fp->internal);
}

static int64_t _udf_file_read(AACS_FILE_H *fp, uint8_t *buf, int64_t size)
{
    return udfread_file_read(fp->internal, buf, size);
}

AACS_FILE_H *open_udf_file(void *udf, const char *filename)
{
    AACS_FILE_H *fp = calloc(1, sizeof(*fp));
    if (!fp) {
        return NULL;
    }
    fp->close    = _udf_file_close;
    fp->seek     = _udf_file_seek;
    fp->read     = _udf_file_read;
    fp->tell     = _udf_file_tell;
    fp->internal = udfread_file_open(udf, filename);
    if (!fp->internal) {
        fprintf(stderr, "udfread_file_open('%s') failed\n", filename);
        free(fp);
        fp = NULL;
    }
    return fp;
}

void *open_udf(const char *path)
{
    struct stat sb;
    if (stat(path, &sb) == -1)
        return NULL;
    if (!S_ISBLK(sb.st_mode))
        return NULL;

    udfread *udf = udfread_init();
    if (!udf) {
        fprintf(stderr, "udfread_init() failed\n");
        return NULL;
    }
    if (udfread_open(udf, path) < 0) {
        fprintf(stderr, "udfread_open(%s) failed\n", path);
        udfread_close(udf);
        return NULL;
    }
    return udf;
}

void close_udf(void *p)
{
    if (p)
        udfread_close(p);
}
