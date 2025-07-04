
bin_PROGRAMS = revealshapes

AM_CPPFLAGS = -Iexternal
AM_CXXFLAGS = $(PTHREAD_CFLAGS) -std=c++2a

revealshapes_SOURCES = revealshapes.cpp common.h
revealshapes_LDADD = $(PTHREAD_LIBS) -ldjvulibre

# dist_man1_MANS = inhdict.1

EXTRA_DIST = 
