#! /usr/bin/perl

# NOTE: This reads the output of read_gccerrs.pl which is NOT dependent on gcc version


my $NJAVACPATH="./njavac";

my $theLine=0;
my $theColumn=0;
my $theError="no_error";
my $theMember="no_member_name";
my $theType="no_type";
my $theObject="no_object";
my $theValue="no_value";


while(<>) {
  $done=0;
  if(/^\# (\d+)\:(\d+)\: (.*) \"(\S+) (\S+)\[(.*)\]\"$/) {
    $theLine=$1;
    $theColumn=$2;
    $theError=$3;
    $theType=$4;
    $theObject=$5;
    $theValue=$6;
    handleError();
    $done=1;
  }
  if(/^\# (\d+)\:(\d+)\: (.+) \"(.+) (.+)\" in \"(.+)\"$/) {
    $theLine=$1;
    $theColumn=$2;
    $theError=$3;
    $theType=$4;
    $theObject=$5;
    $theMember=$6;
    handleError();
    $done=1;
  }
  if(/gccerrs_njavac skipped (.*)$/) {
    $done=1;
  }
  if(/gccerrs_njavac unhandled (.*)$/) {
    print "\e[31m";
    print "fix_gccerrs unhandled: $1\n";
    print "\e[37m";
    $done=1;
  }
  if($done eq 0) {
    print "\e[31m";
    print "#fix_gccerrs skipped $_";
    print "\e[37m";
  }
}


exit(EXIT_SUCCESS);


sub handleError() {
  my $understood=0;
  $theKind="unknown";
  if($theError =~ /Pointer to non-pointer obj/) {
    print "\e[33m";
    print "# Converting all references to \"$theType $theObject\" to \"$theType *$theObject\"\n";
    print "\e[37m";
    $cmd="sed -i.orig s/$theType\\ $theObject/$theType\\ \\*$theObject/g the_test_file.java.cpp";
    #print "$cmd\n";
    system($cmd);
    $understood=1;
  }
  if($theError =~ /Array declaration should be/) {
    print "\e[33m";
    print "# Fixing array declaration to \"$theType $theObject\[$theValue\]\"\n";
    print "\e[37m";
    $cmd="sed -i.orig \"s/$theType\\[$theValue\\]\\ *$theObject/$theType\\ $theObject\\[$theValue\\]/g\" the_test_file.java.cpp";
    #print "$cmd\n";
    system($cmd);
    $understood=1;
  }
  if($understood eq 0) {
    print "\e[31m";
    print "#fix_gccerrs unhandled error ($theLine:$theColumn): $theError\n";
    print "\e[37m";
  }
}

