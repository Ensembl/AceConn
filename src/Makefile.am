
AM_CPPFLAGS = -I../include @GLIB_CFLAGS@
LDADD = @GLIB_LIBS@

lib_LTLIBRARIES = libAceConn.la libmd5.la

libAceConn_la_SOURCES = aceconn.c aceconnsock.c aceconnutils.c
libAceConn_la_DEPENDENCIES = libmd5.la

libmd5_la_SOURCES = md5c.c

noinst_HEADERS = aceconn_.h global.h md5.h

libAceConn_la_LDFLAGS = -version-info 0:0:0

