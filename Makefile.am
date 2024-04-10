bin_PROGRAMS = revealshapes

AM_CPPFLAGS = -I /home/rmast/djvu-djvulibre-git/libdjvu
AM_CXXFLAGS = $(PTHREAD_CFLAGS)

revealshapes_SOURCES = revealshapes.cpp common.h
revealshapes_LDADD = $(PTHREAD_LIBS) -ldjvulibre

dist_man1_MANS = inhdict.1

EXTRA_DIST = 
