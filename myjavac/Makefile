
# Custom Makefile for now


include ../../Makefile.common


############


all:	main.pl syms_javafile.pl syms_cppfile.pl


############


lex.yy.c:	njc.l
	lex njc.l

njc:	lex.yy.c
	gcc -o njc lex.yy.c


############

# Yep, a stupid way to do this as there are (many) ways in perl for this
# But for now, does the trick


main.pl:	parts/*.part
	cat parts/body.pl.part parts/add.pl.part parts/new.pl.part parts/output.pl.part parts/validate.pl.part >main.pl

syms_javafile.pl:	parts/*.part
	cat parts/javafile_body.pl.part parts/add.pl.part parts/new.pl.part parts/output.pl.part parts/validate.pl.part >syms_javafile.pl

syms_cppfile.pl:	parts/*.part
	cat parts/cppfile_body.pl.part parts/add.pl.part parts/new.pl.part parts/output.pl.part parts/validate.pl.part >syms_cppfile.pl


############


clean:
	rm -f main.pl syms_javafile.pl syms_cppfile.pl lex.yy.c njc
	rm -rf *.$(OFILE) *.$(AFILE) *.s *.bak *.log map.f build *Data *.pdb $(PROGRAMS) *.exe *.exe.so *68k *.SYM .DS_Store *.ilk .gdb_history .nautilus-metafile.xml resource.frk RESOURCE.FRK finder.dat FINDER.DAT ._* */._* */*/._* */*/*/._* *~ */*~ */*/*~ */*/*/*~ *.class *.javap *.java.* *.h.? tmp/*


fix:
	chmod -x Makefile* *.html *.xml *.txt *.zip *.part
	chmod +x *.pl *.sh
	$(REZ_TOOLPATH)/SetFile -c CWIE -t TEXT configure *.h *.cpp *.c Makefile* *.txt
	$(REZ_TOOLPATH)/SetFile -c Gzip -t Gzip *gz


remove_depends:


depends:


include ../../Makefile.tail
