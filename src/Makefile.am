AM_CFLAGS = $(DTSDEC_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = dtsdec extract_dts
dtsdec_SOURCES = dcadec.c getopt.h getopt.c gettimeofday.h gettimeofday.c
dtsdec_LDADD = $(top_builddir)/libdca/libdca.la \
	       $(top_builddir)/libao/libao.la $(LIBAO_LIBS)
extract_dts_SOURCES = extract_dca.c getopt.c

man_MANS = dtsdec.1 extract_dts.1
EXTRA_DIST = configure.incl $(man_MANS)
