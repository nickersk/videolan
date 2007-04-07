AM_CFLAGS = $(OPT_CFLAGS) $(LIBDCA_CFLAGS)

lib_LTLIBRARIES = libdca.la
libdca_la_SOURCES = dca_internal.h tables.h tables_quantization.h \
		    tables_huffman.h tables_fir.h tables_adpcm.h tables_vq.h \
		    bitstream.h bitstream.c \
		    parse.c downmix.c dts_internal.h
libdca_la_LDFLAGS = -no-undefined -version 0:0:0 -export-symbol-regex dts_.*

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdca.pc libdts.pc

EXTRA_DIST = configure.incl
