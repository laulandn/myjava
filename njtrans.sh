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


echo "#njtrans (doing preprocessing)"
echo "#njtrans uncomment.pl..."
perl $NJAVACPATH/uncomment.pl $1 >$1.0
echo "#njtrans despace.pl..."
perl $NJAVACPATH/despace.pl $1.0 >$1.1
echo "#njtrans isolate_curlies.pl..."
perl $NJAVACPATH/isolate_curlies.pl $1.1 >$1.2
echo "#njtrans pp_njtrans.pl..."
perl $NJAVACPATH/pp_javafile.pl <$1.2 >$1.3


echo "#njtrans going to call main.pl..."
cp $1.3 $1.final
perl $NJAVACPATH/main.pl $1.final


if [ ! -f $1.cpp.syms ];  then
	echo "Problem processing syms file for \"$1\"!"
	exit 1
fi


perl $NJAVACPATH/uncomment.pl <$1.cpp >$1.4
cp $1.4 $1.cpp

