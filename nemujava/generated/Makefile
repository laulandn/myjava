
# Custom Makefile for now

#include ../../../Makefile.common


all:

clean:
	rm -rf *.$(OFILE) *.$(AFILE) *.s *.bak *.log map.f build *Data *.pdb $(PROGRAMS) *.exe *.exe.so *68k *.SYM .DS_Store *.ilk .gdb_history .nautilus-metafile.xml resource.frk RESOURCE.FRK finder.dat FINDER.DAT ._* */._* */*/._* */*/*/._* *~ */*~ */*/*~ */*/*/*~ *.class *.javap *.java.* *.h.? tmp/*
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) clean;)

fix:
	chmod -x Makefile* *.html *.xml *.txt *.zip
	$(REZ_TOOLPATH)/SetFile -c CWIE -t TEXT configure *.h *.cpp *.c Makefile* *.txt
	$(REZ_TOOLPATH)/SetFile -c Gzip -t Gzip *gz

remove_depends:

depends:


include ../../../Makefile.tail

