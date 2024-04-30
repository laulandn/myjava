
LIBNAME=$(shell basename $(shell pwd))
LDNAME=lib$(LIBNAME)_static.a

####################################################################
# Makefile
####################################################################

PATH_TO_BASE=.

include $(PATH_TO_BASE)/../Makefile.target
include $(PATH_TO_BASE)/../Makefile.common

EXTRA_FLAGS=-I$(PATH_TO_BASE)
EXTRA_LDFLAGS=-L$(PATH_TO_BASE)


####################################################################
# Our objects 
####################################################################

DIRS=$(wildcard */)
OBJS=$(subst .cpp,.$(OFILE),$(wildcard */*.cpp))
#OBJSJ=$(subst .java,.java.cpp.$(OFILE),$(wildcard *.java))
OBJSJ=$(subst .java,.class,$(wildcard *.java))


####################################################################
# The libraries and programs 
####################################################################

SIMPLE_PROGRAMS1=
SIMPLE_PROGRAMS2=
SIMPLE_PROGRAMS3=
SIMPLE_PROGRAMS=$(SIMPLE_PROGRAMS1) $(SIMPLE_PROGRAMS2) $(SIMPLE_PROGRAMS3)
PROGRAMS=$(SIMPLE_PROGRAMS)


# Need for alib and guilib (if using it), for now both are assumed!
PATH_TO_CPP=../cpp
#
CPPLIB_NAME=cpp_static
CPPLIB_L=-L$(PATH_TO_CPP) -l$(CPPLIB_NAME)
CPPLIB_LIB=lib$(CPPLIB_NAME).$(AFILE)
CPPLIB_PATH=$(PATH_TO_CPP)/$(CPPLIB_LIB)
#
CPP_PATHS=$(CPPLIB_PATH)
CPP_LS=$(CPPLIB_L)


PATH_TO_NJAVACLASSLIBRARY=NJavaClassLibrary
#
NJAVACLASSLIBRARY_NAME=NJavaClassLibrary_static
NJAVACLASSLIBRARY_L=-L$(PATH_TO_NJAVACLASSLIBRARY) -l$(NJAVACLASSLIBRARY_NAME)
NJAVACLASSLIBRARY_LIB=lib$(NJAVACLASSLIBRARY_NAME).$(AFILE)
NJAVACLASSLIBRARY_PATH=$(PATH_TO_NJAVACLASSLIBRARY)/$(NJAVACLASSLIBRARY_LIB)
#
NJAVACLASSLIBRARY_PATHS=$(NJAVACLASSLIBRARY_PATH)
NJAVACLASSLIBRARY_LS=$(NJAVACLASSLIBRARY_L)


PATH_TO_NEMUJAVA=nemujava
#
NEMUJAVA_NAME=nemujava_static
NEMUJAVA_L=-L$(PATH_TO_NEMUJAVA) -l$(NEMUJAVA_NAME)
NEMUJAVA_LIB=lib$(NEMUJAVA_NAME).$(AFILE)
NEMUJAVA_PATH=$(PATH_TO_NEMUJAVA)/$(NEMUJAVA_LIB)
#
NEMUJAVA_PATHS=$(NEMUJAVA_PATH)
NEMUJAVA_LS=$(NEMUJAVA_L)


ifeq ($(MSVC),yes)
endif


#.java.cpp:
#	./njavac $*.java


NJAVAC=./njavac.sh


####################################################################
# The targets 
####################################################################

#all:	$(OBJS) $(OBJSJ)
all:
#	$(foreach DIR,$(DIRS),$(MAKE) -C $(DIR) all;)
	$(MAKE) $(LDNAME)
#	$(MAKE) $(PROGRAMS)


all_libs:


#$(LDNAME):	$(OBJS)
$(LDNAME):	$(PATH_TO_NJAVACLASSLIBRARY)	$(NEMUJAVA_PATH)
	make -C myjavac all
	make -C $(PATH_TO_NJAVACLASSLIBRARY) all
	make -C $(PATH_TO_NEMUJAVA) all
#	$(AR_CMD) $(OBJS)
	$(AR_CMD) */*.o */*/*.o */*/*/*.o
	$(RANLIB_CMD) $(LDNAME) 


$(NJAVACLASSLIBRARY_PATH):
	make -C $(PATH_TO_NJAVACLASSLIBRARY)


$(NEMUJAVA_PATH):
	make -C $(PATH_TO_NEMUJAVA)


clean:
	rm -rf *.$(OFILE) *.$(AFILE) *.s *.bak *.log map.f build *Data *.pdb $(PROGRAMS) *.exe *.exe.so *68k *.SYM .DS_Store *.ilk .gdb_history .nautilus-metafile.xml resource.frk RESOURCE.FRK finder.dat FINDER.DAT ._* */._* */*/._* */*/*/._* *~ */*~ */*/*~ */*/*/*~ *.class *.javap *.java.* *.h.? tmp/*
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) clean;)


fix: fix_perm fix_type
	chmod +x njavac */*.pl */*.sh
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) fix;)


# The different Libraries and Programs...


# dependencies
# NOTE: it's ok to see errors when running makedepend
depend:
	makedepend $(DEPENDFLAGS) *.cpp
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) depend;)


remove_depends:
	rm -f Makefile.dep
	touch Makefile.dep
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -ik -C $(DIR) remove_depends;)


include $(PATH_TO_BASE)/../Makefile.tail

include Makefile.dep


# DO NOT DELETE
