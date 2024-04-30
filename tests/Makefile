
LIBNAME=$(shell basename $(shell pwd))
LDNAME=lib$(LIBNAME)_static.a

####################################################################
# Makefile
####################################################################

PATH_TO_BASE=..

include $(PATH_TO_BASE)/../Makefile.target
include $(PATH_TO_BASE)/../Makefile.common

EXTRA_FLAGS=-I$(PATH_TO_BASE)
EXTRA_LDFLAGS=-L$(PATH_TO_BASE)


NJAVAC=$(PATH_TO_BASE)/njavac.sh


####################################################################
# Our objects 
####################################################################

DIRS=$(wildcard */)
OBJS=$(subst .cpp,.$(OFILE),$(wildcard */*.cpp))
#
OBJSJ=$(subst .java,.java.cpp.$(OFILE),$(wildcard *.java))
#OBJSJ=$(subst .java,.class,$(wildcard *.java))


####################################################################
# The libraries and programs 
####################################################################

SIMPLE_PROGRAMS1=bounce BytecodeExample environs fib2 hanoi hello102 HelloWorld
SIMPLE_PROGRAMS2=lines Matrix3D mintest
SIMPLE_PROGRAMS3=scribble test2 ThreeD webcolors
SIMPLE_PROGRAMS=$(SIMPLE_PROGRAMS1) $(SIMPLE_PROGRAMS2) $(SIMPLE_PROGRAMS3)
PROGRAMS=$(SIMPLE_PROGRAMS)


# Needed for alib and guilib (if using it), for now both are assumed!
PATH_TO_CPP=$(PATH_TO_BASE)/../cpp
#
CPPLIB_NAME=cpp_static
CPPLIB_L=-L$(PATH_TO_CPP) -l$(CPPLIB_NAME)
CPPLIB_LIB=lib$(CPPLIB_NAME).$(AFILE)
CPPLIB_PATH=$(PATH_TO_CPP)/$(CPPLIB_LIB)
#
CPP_PATHS=$(CPPLIB_PATH)
CPP_LS=$(CPPLIB_L)


PATH_TO_NJAVACLASSLIBRARY=$(PATH_TO_BASE)/NJavaClassLibrary
#
NJAVACLASSLIBRARY_NAME=NJavaClassLibrary_static
NJAVACLASSLIBRARY_L=-L$(PATH_TO_NJAVACLASSLIBRARY) -l$(NJAVACLASSLIBRARY_NAME)
NJAVACLASSLIBRARY_LIB=lib$(NJAVACLASSLIBRARY_NAME).$(AFILE)
NJAVACLASSLIBRARY_PATH=$(PATH_TO_NJAVACLASSLIBRARY)/$(NJAVACLASSLIBRARY_LIB)
#
NJAVACLASSLIBRARY_PATHS=$(NJAVACLASSLIBRARY_PATH)
NJAVACLASSLIBRARY_LS=$(NJAVACLASSLIBRARY_L)


ifeq ($(MSVC),yes)
endif


####################################################################
# The targets 
####################################################################

all:	$(PROGRAMS)
#all:	$(OBJS) $(OBJSJ)
#all:
#	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) all;)
#	$(MAKE) $(LDNAME)
#	$(MAKE) -i $(PROGRAMS)


all_libs:


#$(LDNAME):	$(OBJS)
$(LDNAME):
	make -C NJCLIB all
	make -C NJLoaderLib all
	make -C NJVMLib all
#	$(AR_CMD) $(OBJS)
	$(AR_CMD) */*.o */*/*.o */*/*/*.o
	$(RANLIB_CMD) $(LDNAME)


clean:
	rm -rf *.$(OFILE) *.$(AFILE) *.s *.bak *.log map.f build *Data *.pdb $(PROGRAMS) *.exe *.exe.so *68k *.SYM .DS_Store *.ilk .gdb_history .nautilus-metafile.xml resource.frk RESOURCE.FRK finder.dat FINDER.DAT ._* */._* */*/._* */*/*/._* *~ */*~ */*/*~ */*/*/*~ *.class *.javap *.java.* *.h.? tmp/*
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) clean;)


fix: fix_perm fix_type
	chmod +x njavac */*.pl */*.sh
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) fix;)


# The different Libraries and Programs...

# NOTE: These are for my njavac translator and not a real JDK.

bounce:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) bounce.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

BytecodeExample:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) BytecodeExample.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

environs:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) environs.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

fib2:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) fib2.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

hanoi:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) hanoi.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

hello102:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) hello102.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

HelloWorld:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) HelloWorld.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

lines:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) lines.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

mintest:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) mintest.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

Matrix3D:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) Matrix3D.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

scribble:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) scribble.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

test2:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) test2.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

ThreeD:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) ThreeD.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)

webcolors:	$(NJAVACLASSLIBRARY_PATH)
	$(NJAVAC) webcolors.java
	$(CLXX) $@.java.o -o $@ $(NJAVACLASSLIBRARY_PATHS) $(CPP_PATHS) $(LIBS)


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
