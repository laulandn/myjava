#! /bin/bash


NJAVACPATH=$HOME/src/myjava/myjavac


if [ $# -eq 0 ];  then
	>&2 echo "Please pass a C++ source file as an argument."
	exit;
fi
#
if [ ! -f $1 ];  then
	>&2 echo "Couldn't find C++ source file \"$1\"."
	exit;
fi


#>&2 echo -e "\033[1m"
>&2 echo "syms_cppfile.sh \"$1\"..."
#>&2 echo -e "\033[0m"


#echo "#\"parent\",\"what\",\"type\",\"name\",\"args\""


perl $NJAVACPATH/uncomment.pl $1 >$1.0
perl $NJAVACPATH/despace.pl $1.0 >$1.1
perl $NJAVACPATH/isolate_curlies.pl $1.1 >$1.2
perl $NJAVACPATH/syms_cppfile.pl <$1.2

