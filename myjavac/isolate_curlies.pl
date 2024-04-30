#! /usr/bin/perl


$insideComment=0;


while(<>) {
  $done=0;
  #if(/^\s+(\S.*)/) {
  #  $_ =~ s/^\s+//g;
  #}
  if(/(.*)\{(.*)/) {
    if($1 eq "") { } else { print "$1\n"; }
    print "{\n";
    if($2 eq "") { } else { print "$2\n"; }
    $done=1;
  }
  if(/(.*)\}(.*)/) {
    if($1 eq "") { } else { print "$1\n"; }
    print "}\n";
    if($2 eq "") { } else { print "$2\n"; }
    $done=1;
  }
  if($done eq 0) {
   print "$_";
  }
}

