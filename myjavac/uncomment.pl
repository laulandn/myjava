#! /usr/bin/perl


$insideComment=0;


while(<>) {
  $done=0;
  # single line
  if(/(.*)\/\/(.*)/) {
    $left=$1;
    $right=$2;
    $skip=0;
    if($left =~ /^$/) { $skip=1; }
    if($left =~ /^\ +$/) { $skip=1; }  # WHY ISN'T THIS WORKING?
    if($skip eq 0) { if($insideCOmment eq 0) { print "$left\n"; } }
    $done=1;
  }
  # open
  if(/(.*)\/\*(.*)/) {
    if($insideComment eq 0) {
      $left=$1;
      $right=$2;
      $insideComment=1;
      print "$left\n";
      $done=1;
    }
  }
  # close
  if(/(.*)\*\/(.*)/) {
    if($insideComment eq 1) {
      $left=$1;
      $right=$2;
      $insideComment=0;
      print "$right\n"; 
      $done=1;
    }
  }
  if($done eq 0) {
    if($insideComment eq 0) {
      print "$_";
    }
  }
}
