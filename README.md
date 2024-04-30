Extremely trivial, clean room, minimal, "JDK" kind of monstrous abomination
===============

Work in progress...

Does not use GNU autotools for configure, instead goofy shell script...sorry!

Very dumb. Very crazy.  Only works on very simple examples, if at all!

+ njavac.sh: Compile Java to native binary.
+ njtrans.sh: Translate Java to C++
+ syms_cppfile.sh: Create symbol table from C++ source.
çsyms_javafile.sh: Create symbol table frm Java source.

myjavac:
+ Insane Java source to C++ translator/compiler.
+ Includes code to read and create simple symbol tables from Java and C++.
+ Barely works, if at all.
+ Gets tripped up by code formatting/style/spacing all the time. 
+ Symbol table format is plain text and minimal.
+ Writen in Perl(!!!)...mostly...

nemujava:
+ Plugins for my "nemu" emulator.
+ Not usable standalone.
+ JVM byte code cpu.
+ Java class file format reader.

NJavaCLassLibrary:
+ C++ library that attempts to mimic standard Java Class library.
+ Allows you to write C++ code that uses the same class names as Java.
+ Includes Applet and AWT support.
+ Very limited, single window, single thread etc.
+ Tries, but fails, to support OOP for atomic types.
+ Cheats and is hacked horribly, as far as strings are concerned.
+ Built on top of, and requires, alib/guilib, my own cross platform app framework.
+ classlib_test.cpp is trivial tester.
