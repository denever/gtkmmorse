# Copyright (C) 2005, 2006, 2007 Giuseppe Martino <denever@users.sf.net>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = gtkmmorse
gtkmmorse_SOURCES = astream.cc blockbox.cc main.cc setupbox.cc checkbox.cc\
		 blocks.cc keyer.cc mainwindow.cc random.cc rhythmexcbox.cc patternexcbox.cc bicheckbuttons.cc
gtkmmorse_CXXFLAGS = -ansi -Wall -pedantic -g -ggdb
gtkmmorse_LDADD = $(AO_LIBS) $(GTKMM_LIBS) $(GCONFMM_LIBS) $(GTHREAD_LIBS)
INCLUDES = -I$(top_srcdir)/include  $(AO_CFLAGS) $(GTKMM_CFLAGS) $(GCONFMM_CFLAGS) $(GTHREAD_CFLAGS)
