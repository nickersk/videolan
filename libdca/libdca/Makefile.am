AM_CFLAGS = $(OPT_CFLAGS) $(LIBDCA_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/include

lib_LTLIBRARIES = libdca.la
libdca_la_SOURCES = dca_internal.h tables.h tables_quantization.h \
		    tables_huffman.h tables_fir.h tables_adpcm.h tables_vq.h \
		    bitstream.h bitstream.c parse.c downmix.c
libdca_la_LDFLAGS = -no-undefined -version-info 0:0:0 -export-symbols-regex dca_.*
libdca_la_LIBADD = $(LIBDCA_LIBS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdca.pc libdts.pc

install-exec-hook:
	$(LN_S)f "$(DESTDIR)$(libdir)/libdca.a" "$(DESTDIR)$(libdir)/libdts.a"

uninstall-hook:
	unlink "$(DESTDIR)$(libdir)/libdts.a"
