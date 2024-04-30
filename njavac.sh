#! /bin/bash


NJAVACPATH=$HOME/src/myjava/myjavac


if [ $# -eq 0 ];  then
	echo "Please pass a Java source file as an argument."
	exit 1
fi
#
if [ ! -f $1 ];  then
	echo "Couldn't find Java source file \"$1\"."
	exit 1
fi


echo "#njavac (doing preprocessing)"
echo "#njavac uncomment.pl..."
perl $NJAVACPATH/uncomment.pl $1 >$1.0
echo "#njavac despace.pl..."
perl $NJAVACPATH/despace.pl $1.0 >$1.1
echo "#njavac isolate_curlies.pl..."
perl $NJAVACPATH/isolate_curlies.pl $1.1 >$1.2
echo "#njavac pp_njavac.pl..."
perl $NJAVACPATH/pp_javafile.pl <$1.2 >$1.pre

echo "#njavac going to call main.pl..."
perl $NJAVACPATH/main.pl $1.pre
mv $1.pre.cpp.syms $1.syms
if [ ! -f $1.syms ];  then
	echo "Problem generating syms file for \"$1\"!"
	exit 1
fi

echo "#njavac going to call syms_javafile..."
$NJAVACPATH/../syms_javafile.sh $1 >>$1.syms

perl $NJAVACPATH/uncomment.pl <$1.pre.cpp >$1.4
mv $1.4 $1.cpp

echo "#njavac going to gcc the results, $1.cpp..."
#g++ -c $1.cpp &>$1.gccoutput
g++ -c $1.cpp
#make $1.o &>$1.gccoutput
#echo "#njavac read_gccerrs.pl..."
#perl $NJAVACPATH/read_gccerrs.pl <$1.gccoutput >$1.gccerrs
#echo "#njavac fix_gccerrs.pl..."
#cp $1.cpp the_test_file.java.cpp
# NOTE: test_test_file.java.cpp name hardcoded into fix_gccerrs...
#perl $NJAVACPATH/fix_gccerrs.pl <$1.gccerrs
#cp $1.cpp $1.cpp.prefixes
#cp the_test_file.java.cpp $1.cpp

# NOTE: One idea here would be to repeat the cycle of gcc...read_gccerrs...fix_gccerrs...gcc...etc until there were NO errors
# Of course, that assumes fix_gccerrs actually fixes them all!  Otherwise infinite loop!

#echo "#njavac going to try to gcc the fixed results, $1.cpp..."
#make $1.o
# TODO: Some more testing goes here...

