#! /usr/bin/perl


# output language, can be cpp, java, objc, csharp, etc
$theLang="java";

# can be cpp, h, java, m, cs, etc
$theFiletype="java";


$theClass="UNKNOWN";

$inVars=0;


if($theLang eq "cpp") { printHeader(); }


while(<>) {
  my $handled=0;
  if(/\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\",\"(.*)\"/) {
    $symParent=$1;
    $symWhat=$2;
    $symType=$3;
    $symName=$4;
    $symArgs=$5;
    #print "// \"$symParent\",\"$symWhat\",\"$symType\",\"$symName\",\"$symArgs\"\n";
    # catch stupid parse error in syms_cpp
    if($symType eq "return") { $symWhat="ERROR"; }
    #
    $isVirtual=0;
    $isConst=0;
    $isPointer=0;
    if($symWhat eq "CLASS") { doClass(); }
    if($symWhat eq "CONST") { if($theFiletype eq "cpp") { } else { $isConst=1; doVar(); } }
    if($symWhat eq "METHOD_0") { doMethod(); }
    if($symWhat eq "METHOD_A") { doMethod(); }
    if($symWhat eq "VMETHOD_0") { $isVirtual=1; doMethod(); }
    if($symWhat eq "VMETHOD_A") { $isVirtual=1; doMethod(); }
    if($symWhat eq "VAR") { if($theFiletype eq "cpp") { } else { doVar(); } }
    if($symWhat eq "ARRAY") { doArray(); }
    if($symWhat eq "POINTER") { if($theFiletype eq "cpp") { } else { $isPointer=1; doVar(); } }
  }
  else {
    if(/^\#skipped line\:/) { }
    else {
      print "# missed line: \"$_\"...\n";
    }
  }
}


if($theFiletype eq "cpp") { } else { print "};\n"; }

if($theLang eq "cpp") { printFooter(); }

exit(0);


sub doClass
{
  # closing bracket for previous class maybe?
  #if($theClass eq "UNKNOWN") { }
  #else { print "};\n"; print "\n\n"; }
  if($theFiletype eq "cpp") { } 
  else {
  # name
  print "class ";
  print "$symName";
  # parent, if any
  if($symParent eq "UNKNOWN") { print ";\n"; }
  else { 
    print " : public $symParent";
    #print "  // class";
    print "\n{";
    if($theLang eq "java") {
      print "\n";
    }
    else {
      print "\n";
      print "public:";  # for now since we don't have that info for menthods
    }
  }
  print "\n";
  }
  if($theFiletype eq "cpp") {
    print "\n"; 
    print "#include \"$symName"; print ".h\"\n";
    if($symType eq "EXTERNAL") { }
    else {
      print "\n";
      print "\n";
      print "////////////////////////////////////////////////////////////////////////////////\n";
      print "//  $symName Class\n";
      print "////////////////////////////////////////////////////////////////////////////////\n";
      print "\n";
    }
  }
  $theClass=$symName;
}


# NOTE: need to special case c++ destructors someplace in here...
sub doMethod
{
  $theType=$symType;
  $theName=$symName;
  if($symArgs eq "") { $theArgs="void"; } else { $theArgs=$symArgs; }
  if($theFiletype eq "cpp") { }
  else { print "  "; }
  # all java are public (for now)
  if($theLang eq "java") { print "public "; }
  # virtual
  if($isVirtual eq 1) { print "virtual "; }
  # return type
  if($symType) { print "$theType "; }
  if($theFiletype eq "cpp") { print "$theClass"; print "::"; }
  # name
  print "$theName";
  # args
  print "(";
  if($theArgs) { print "$theArgs"; }
  print ")";
  #print "  // method";
  $doBody=0;
  if($theLang eq "java") { $doBody=1; }
  if($theFiletype eq "cpp") { $doBody=1; }
  # empty code if needed
  if($doBody eq 1) {
    print "\n";
    if($theLang eq "java") { print "  "; }
    print "{\n";
    if($theLang eq "java") { print "  "; }
    print "  // TODO: code goes here\n";
    if($theLang eq "java") { print "  "; }
    print "}\n";
    print "\n";
  }
  else { print ";\n"; }
}


sub doVar
{
  if($inVars eq false) { print "  #\n";  $inVars=1; }
  print "  ";
  # type
  if($isPointer eq 1){
    if($theLang eq "java") {
      chop($symType);  # remove extra space
      chop($symType);  # remove "*"
      $isPointer=0;
      # special case c strings
      if($symType eq "char") {
        $symType="JString";
      }
    }
  }
  print "$symType";
  if($isPointer eq 0) { print " "; }
  # name
  print "$symName";
  if($isConst eq 1) {
    print "=";
    # value
    print "$symArgs";
  }
  print ";";
  #print "  // var";
  print "\n";
}


sub doArray
{
  if($inVars eq false) { print "  #\n";  $inVars=1; }
  print "  ";
  # type
  print "$symType";
  # name
  print " $symName\[";
  print "blah";
  print "\];";
  #print "  // array";
  print "\n";
}


sub printHeader
{
  if($theFiletype eq "h") {
    print "//#ifndef NICKVM_JAVAC_CLASSNAME_H\n";
    print "//#define NICKVM_JAVAC_CLASSNAME_H\n";
    print "\n";
    print "\n";
    #print "// IMPORTANT!  This file is machine read!\n";
    #print "// Please follow formatting and layout EXACTLY!\n";
    #print "\n";
    #print "\n";
    print "#include \"../../njavacpp.h\"\n";
    print "\n";
    print "\n";
  }
  if($theFiletype eq "cpp") {
    print "#define DEBUG_OUT dBug\n";
    print "//#define DEBUG_OUT dBug\n";
    print "//#define DEBUG_OUT dBug\n";
    print "//#define DEBUG_OUT *aNullStream\n";
    print "//#define CONS_OUT std::cerr\n";
    print "#define CONS_OUT *aDefaultOutputStream\n";
    print "#define CONS_IN std::cin\n";
    print "//#define CONS_IN *inStream\n";
    print "#define ERR_OUT std::cerr\n";
    print "\n";
    print "\n";
    print "#ifdef DEBUG_VERBOSE\n";
    print "//#undef DEBUG_VERBOSE\n";
    print "#endif // DEBUG_VERBOSE\n";
    print "\n";
  }
}


sub printFooter
{
  if($theFiletype eq "h") {
    print "\n";
    print "\n";
    print "//#endif // NICKVM_JAVAC_CLASSNAME_H\n";
  }
}
