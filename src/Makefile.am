AM_CFLAGS = $(DCADEC_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = dcadec extract_dca
dcadec_SOURCES = dcadec.c getopt.h getopt.c gettimeofday.h gettimeofday.c
dcadec_LDADD = $(top_builddir)/libdca/libdca.la \
	       $(top_builddir)/libao/libao.la $(LIBAO_LIBS)
extract_dca_SOURCES = extract_dca.c getopt.c

man_MANS = dtsdec.1 extract_dts.1
EXTRA_DIST = configure.incl $(man_MANS)

bin_SCRIPTS = dtsdec extract_dts
dtsdec extract_dts: Makefile
	{ \
		echo '#! /bin/sh' ; \
		echo 'exec "$$(dirname "$$0")/$$(basename "$$0" | sed -e 's/ts/ca/')" "$$@"' ; \
	} > $@.tmp
	chmod +x $@.tmp
	mv -f $@.tmp $@
