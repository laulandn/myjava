#! /usr/bin/perl


# WARNING WARNING WARNING
# WARNING WARNING WARNING
#
# This script is known to grok ONLY the output of g++ 5.4.0
# Older AND new versions will probably NOT WORK!!!!!!!
#
# WARNING WARNING WARNING
# WARNING WARNING WARNING


my $theLine=0;
my $theColumn=0;
my $theError="no_error";
my $theMember="no_member_name";
my $theType="no_type";
my $theKind="no_kind";
my $theObject="no_object";


while(<>) {
  $done=0;
  # Pointing to the actual error place in the line
  if(/^(\s+)\^\s*$/) {
    # NOTE: $1 is the column at which the error occurred
    $done=1;
  }
  if(/^(\s+)(.*)\-\>/) {
    $theObject=$2;
    print "# $theLine:$theColumn: Pointer to non-pointer obj \"$theType $theObject\" in \"$theMember\"\n";
    $done=1;
  }
  if(/ +(\S+) *\[(.*)\] *(\S+)/) {
    $theType=$1;
    $theKind=$2; # NOTE: not a kind, just using that variable
    $theObject=$3;
    print "# $theLine:$theColumn: Array declaration should be \"$theType $theObject\[$theKind\]\"\n";
    $done=1;
  }
  # Quoting the line with the error
  if(/^\s+/) {
    $done=1;
  }
  if(/cpp\:(\d+)\:(\d+)\: error\: (.*)$/) {
    $theLine=$1;
    $theColumn=$2;
    $theError=$3;
    handleError();
    $done=1;
  }
  # Stupid smart quotes...
  if(/cpp\: In member function ...(.*)...\:$/) {
    $theMember=$1;
    #print "# in member $theMember\n";
    $done=1;
  }
  if($done eq 0) {
   print "#gccerrs_njavac skipped $_";
  }
}


exit(EXIT_SUCCESS);


sub handleError() {
  my $understood=0;
  $theKind="unknown";
  if($theError =~ /base operand of (.*) has non-pointer type ...(.*)...$/) {
    $theType=$2;
    $theKind="pointer";
    $understood=1;
  }
  if($theError =~ /expected unqualified-id before ...(.*)... token$/) {
    $theType=$2;
    if($theType eq "[") { $theKind="array declaration"; }
    else { $theKind="syntax"; }
    $understood=1;
  }
  if($understood eq 0) {
    print "#gccerrs_njavac unhandled ($theLine:$theColumn): $theError\n";
  }
}

