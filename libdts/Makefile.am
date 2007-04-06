AM_CFLAGS = $(OPT_CFLAGS) $(LIBDTS_CFLAGS)

lib_LTLIBRARIES = libdts.la
libdts_la_SOURCES = dts_internal.h tables.h tables_quantization.h \
		    tables_huffman.h tables_fir.h tables_adpcm.h tables_vq.h \
		    bitstream.h bitstream.c \
		    parse.c downmix.c dts_internal.h
libdts_la_LDFLAGS = -no-undefined -version 0:0:0 -export-symbol-regex dts_.*

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdts.pc

EXTRA_DIST = configure.incl
