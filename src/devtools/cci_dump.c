/*
 * This file is part of libaacs
 * Copyright (C) 2020  VideoLAN
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

#include "util/strutl.h"
#include "util/macro.h"
#include "libaacs/cci.h"
#include "libaacs/cci_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_file.h"

static void _cci_dump(const AACS_CCI *cci)
{
    const AACS_BASIC_CCI *bcci = cci_get_basic_cci(cci);
    unsigned title;

    if (!bcci) {
        fprintf(stderr, "No AACS Basic CCI found\n");
        return;
    }

    printf("Encrypted CPS unit: %s\n\n", (!cci_is_unencrypted(cci)) ? "Yes" : "No");
    if (bcci->cci == 0)
        printf("Encryption Plus Non-assertion                                   %d\n", bcci->epn);
    printf("Copy Control Information                                        %d (0 = copy freely)\n", bcci->cci);
    printf("High Definition Analog Output in High Definition Analog Form    %d\n", bcci->image_constraint);
    printf("Output of decrypted content is allowed only for Digital Outputs %d\n", bcci->digital_only);
    printf("Analog copy protection information                              %d\n", bcci->apstb);
    printf("\nTitles: %d\n", bcci->num_titles);

    printf("Basic titles: ");
    for (title = 0; title < bcci->num_titles; title++)
        if (!(bcci->title_type[title >> 3] & (1 << (title & 7))))
            printf("%d ", title);
    printf("\nEnhanced titles: ");
    for (title = 0; title < bcci->num_titles; title++)
        if (bcci->title_type[title >> 3] & (1 << (title & 7)))
            printf("%d ", title);
    printf("\n");
}

static void _raw_dump(const uint8_t *data, size_t size)
{
    uint32_t mask = 0;
    size_t   l, b;

    printf("Raw data:\n");

    for (l = 0; l < size; l += 16) {

        /* skip large empty areas */
        mask <<= 8;
        for (b = 0; b < 32 && l+b < size; b++)
            mask |= data[l + b];
        if (!mask)
            continue;

        printf("%04lx: ", (long)l);
        for (b = 0; b < 8 && l+b < size; b++)
            printf("%02x ", data[l + b]);
        printf(" ");
        for (b = 8; b < 16 && l+b < size; b++)
            printf("%02x ", data[l + b]);
        printf("        ");
        for (b = 0; b < 8 && l+b < size; b++)
            if (data[l+b]) printf("%02x ", data[l + b]); else printf("   ");
        printf(" ");
        for (b = 8; b < 16 && l+b < size; b++)
            if (data[l+b]) printf("%02x ", data[l + b]); else printf("   ");
        printf("\n");
    }
}

int main (int argc, char **argv)
{
    AACS_CCI *cci;
    uint8_t  *data;
    size_t    size;

    if (argc < 2) {
        fprintf(stderr, "usage: cci_dump <CPSUnit?????.cci>\n");
        exit(-1);
    }

    size = _read_file(argv[1], 16, 1024*1024, &data);
    if (!size) {
        exit(-1);
    }

    printf("CCI file size:      %zu bytes\n", size);
    cci = cci_parse(data, size);

    if (!cci) {
        fprintf(stderr, "Parsing failed\n");
        exit(-1);
    }

    _cci_dump(cci);

    _raw_dump(data, size);

    cci_free(&cci);
    free(data);

    return 0;
}
