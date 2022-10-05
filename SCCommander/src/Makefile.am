## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(LIBCURL_CFLAGS). \
	$(libcurl_CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = sccommander

sccommander_SOURCES = \
	main.cc \
	s-connector.cc \
	s-connector.h \
	Rijndael.cc \
	Rijndael.h \
	base64.cc \
	base64.h \
	data-getter.cc \
	data-getter.h \
	global.h \
	core.cc \
	core.h \
	cryption.cc \
	cryption.h \
	jsoncpp.cpp \
	file-op.cc \
	file-op.h \
	command-sender.cc \
	command-sender.h

sccommander_LDFLAGS = 

sccommander_LDADD =  \
	$(libcurl_LIBS) \
	$(LIBCURL_LIBS)


