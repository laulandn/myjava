#! /usr/bin/perl


# Usage: perl pp_javafile.pl <ThreeD.java >ThreeD.java.pp.java
# Would create file named ThreeD.java.pp.java


my $lineNum=0;

my $foundSomething=0;

my $numCurlies=0;
my $numSquares=0;
my $numParens=0;

my $numSingQuotes=0;
my $numDoubQuotes=0;

my $ppprefix="///";

my $theParam3="";
my $theParam1="";
my $theParam2="";


while(<>) {
  $foundSomething=0;
  print "$ppprefix line $lineNum\n";
  #
  lookForModifiers();
  #
  lookForTypes();
  #
  lookForOtherKeywords();
  #
  lookForSingleCharacters();
  #
  lookForDoubleCharacters();
  #
  doSomeQuickChecking();
  #
  if($foundSomething eq 0) {
    #print "$ppprefix (didn't find anything interesting)\n";
  }
  #
  print "$_";
  #
  $lineNum++;
}


exit(EXIT_SUCCESS);


sub handleClass()
{
  #print "$ppprefix handleClass() not implemented...\n";
}


sub handlePackage()
{
  #print "$ppprefix handlePackage() not implemented...\n";
}


sub handleClassOrMember()
{
  #print "$ppprefix handleClassOrMember() not implemented...\n";
}


sub handleDeclOrParams()
{
  #print "$ppprefix handleDeclOrParams() not implemented...\n";
}


sub handleMaybeObject()
{
  #print "$ppprefix handleMaybeObject() not implemented...\n";
}


sub handleMathOrCall()
{
  #print "$ppprefix handleMathOrCall() not implemented...\n";
}


sub handleArray()
{
  #print "$ppprefix handleArray() not implemented...\n";
}


sub handleProbableStaticInit()
{
  #print "$ppprefix handleProbableStaticInit() not implemented...\n";
}


sub handleNoStringScrewUp()
{
  #print "$ppprefix handleNoStringScrewUp() not implemented...\n";
}


sub lookForModifiers()
{
#
  if(/public/) {
    print "$ppprefix modifier public\n";
    $theName="unknown";
    handleClassOrMember();
    $foundSomething=1;
  }
  if(/private/) {
    print "$ppprefix modifier private\n";
    $theName="unknown";
    handleClassOrMember();
    $foundSomething=1;
  }
  if(/protected/) {
    print "$ppprefix modifier protected\n";
    $theName="unknown";
    handleClassOrMember();
    $foundSomething=1;
  }
#
  if(/static/) {
    print "$ppprefix modifier static\n";
    $theName="unknown";
    handleClassOrMember();
    $foundSomething=1;
  }
  #
  if(/extends (\w+)/) {
    fixParam1($1);
    print "$ppprefix has extends $theParam1\n";
    $theName="unknown";
    handleClass();
    $foundSomething=1;
  }
  if(/implements +(\w+)/) {
    fixParam1($1);
    print "$ppprefix has implements $theParam1\n";
    $theName="unknown";
    handleClass();
    $foundSomething=1;
  }
}


sub lookForTypes()
{
#
  if(/void +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type void $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/boolean +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type boolean $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/byte +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type byte $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/short +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type short $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/int +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type int $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/long +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type int $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  # because this is a basic type in java...we convert to a char
  if(/byte +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type byte $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/float +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type float $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/double +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type double $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
  if(/char +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type char $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
#
  # I know, not actually primative, we're cheating...
  if(/String +(\w+)/) {
    fixParam1($1);
    print "$ppprefix type String $theParam1\n";
    $theName="unknown";
    handleDeclOrParams();
    $foundSomething=1;
  }
#
}


sub lookForOtherKeywords()
{
  if(/^import (.*)\;/) {
    fixParam1($1);
    print "$ppprefix is import $theParam1\n";
    $theName="unknown";
    handleClass();
    $foundSomething=1;
  }
  if(/^package (.*)/) {
    fixParam1($1);
    print "$ppprefix is package $theParam1\n";
    $theName="unknown";
    handlePackage();
    $foundSomething=1;
  }
  if(/class (\w+)/) {
    fixParam1($1);
    print "$ppprefix is class $theParam1\n";
    $theName="unknown";
    handleClass();
    $foundSomething=1;
  }
  if(/for.*\((.*)\;(.*)\;(.*)\)/) {
    fixParam1($1);
    fixParam2($2);
    fixParam3($3);
    print "$ppprefix is for $theParam1 $theParam2 $theParam3\n";
    $foundSomething=1;
  }
  if(/while.*\(.*\)/) {
    fixParam1($1);
    print "$ppprefix is while $theParam1\n";
    $foundSomething=1;
  }
  if(/break(.*)\;/) {
    fixParam1($1);
    print "$ppprefix is break $theParam1\n";
    $foundSomething=1;
  }
  if(/return(.*)\;/) {
    fixParam1($1);
    print "$ppprefix is return $theParam1\n";
    $foundSomething=1;
  }
  #
  if(/super/) {
    print "$ppprefix is super\n";
    $foundSomething=1;
  }
  if(/throw/) {
    print "$ppprefix is throw(s)\n";
    $foundSomething=1;
  }
  if(/catch/) {
    print "$ppprefix is catch\n";
    $foundSomething=1;
  }
  if(/try/) {
    print "$ppprefix is try\n";
    $foundSomething=1;
  }
}


sub lookForSingleCharacters()
{
  if(/\;$/) {
    print "$ppprefix has semicolon\n";
    $foundSomething=1;
  }
  if(/(.*)\.(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has dot lhand=$theParam1 rhand=$theParam2\n";
    $name="unknown";
    handleMaybeObject();
    $foundSomething=1;
  }
  if(/(.*)\*(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has star lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(.*)\-(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has minus lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(.*)\/(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has div lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(.*)\+(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has plus lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(.*)\,(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has comma lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(.*)\=(.*)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has equals lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/\(/) {
    $numParens++;
    print "$ppprefix has openparen $numParens\n";
    $foundSomething=1;
  }
  if(/\)/) {
    $numParens--;
    print "$ppprefix has closeparen $numParens\n";
    $foundSomething=1;
  }
  if(/\{/) {
    $numCurlies++;
    print "$ppprefix has opencurly $numCurlies\n";
    $foundSomething=1;
  }
  if(/\}/) {
    $numCurlies--;
    print "$ppprefix has closecurly $numCurlies\n";
    $foundSomething=1;
  }
  if(/\[/) {
    $numSquares++;
    print "$ppprefix has opensquare $numSquares\n";
    $foundSomething=1;
  }
  if(/\]/) {
    $numSquares--;
    print "$ppprefix has closesquare $numSquares\n";
    $foundSomething=1;
  }
  if(/\'/) {
    $numSingQuotes++;
    print "$ppprefix has singquote $numSingQuotes\n";
    $foundSomething=1;
  }
  if(/\"/) {
    $numDoubQuotes++;
    print "$ppprefix has doubquote $numDoubQuotes\n";
    $foundSomething=1;
  }
}


sub lookForDoubleCharacters()
{
  if(/\((.*)\)/) {
    fixParam1($1);
    print "$ppprefix has bothParens $theParam1\n";
    handleMathOrCall();
    $foundSomething=1;
  }
  if(/\{(.*)\}/) {
    fixParam1($1);
    print "$ppprefix has bothCurlies $theParam1\n";
    $foundSomething=1;
  }
  if(/\[(.*)\]/) {
    fixParam1($1);
    print "$ppprefix has bothSquares $theParam1\n";
    handleArray();
    $foundSomething=1;
  }
  if(/\'(.*)\'/) {
    fixParam1($1);
    print "$ppprefix has bothSingQuotes $theParam1\n";
    handleNoStringScrewUp();
    $foundSomething=1;
  }
  if(/\"(.*)\"/) {
    fixParam1($1);
    print "$ppprefix has bothDoubQuotes $theParam1\n";
    # hack...
    #if($numDoubQuotes eq 1) { $numDoubQuotes=0; }
    handleNoStringScrewUp();
    $foundSomething=1;
  }
  #
  if(/(.*)\,(.*)\,(.*)/) {
    fixParam1($1);
    fixParam2($2);
    fixParam3($3);
    print "$ppprefix has moreThanOneComma $theParam1 $theParam2 $theParam3\n";
    $foundSomething=1;
  }
  if(/(.*)\;(.*)\;(.*)/) {
    fixParam1($1);
    fixParam2($2);
    fixParam3($3);
    print "$ppprefix has moreThanOneSemicolon $theParam1 $theParam2 $theParam3\n";
    $foundSomething=1;
  }
  #
  if(/(\w+) *\+\+/) {
    print "$ppprefix has plusplus $theParam1\n";
    $foundSomething=1;
  }
  if(/(\w+) *\-\-/) {
    print "$ppprefix has minusminus $theParam1\n";
    $foundSomething=1;
  }
  if(/(\w+) *\+\= *(\w+)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has plusequals lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(\w+) *\-\= *(\w+)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has minusequals lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
  if(/(\w+) *\*\= *(\w+)/) {
    fixParam1($1);
    fixParam2($2);
    print "$ppprefix has starequals lhand=$theParam1 rhand=$theParam2\n";
    $foundSomething=1;
  }
}


sub doSomeQuickChecking()
{
  if(/\[.*\]/) {
    if(/\{.*\}/) {
      if(/\=/) {
        print "$ppprefix watch_out looks like static list initializer!\n";
        $theName="unknown";
        handleProbableStaticInit();
      }
    }
  }
  if($numDoubQuotes eq 0) {
    # fine nothing to do
  }
  else {
    # check for numDoubQuotes problem
    print "$ppprefix has numDoubQuotes $numDoubQuotes\n";
  }
  if($numSingQuotes eq 0) {
    # fine nothing to do
  }
  else {
    # check for numSingQuotes problem
    print "$ppprefix has numSingQuotes $numSingQuotes\n";
  }
  if($numParens eq 0) {
    # fine nothing to do
  }
  else {
    # check for numParens problem
    print "$ppprefix has numParens $numParens\n";
  }
  if($numCurlies eq 0) {
    # fine nothing to do
  }
  else {
    # where are we according to curly brackets?
    $theParam1="\"unknown\"";
    if($numCurlies eq 1) {
      $theParam1="\"root_of_class\"";
    }
    if($numCurlies eq 2) {
      $theParam1="\"inside_method\"";
    }
    if($numCurlies eq 3) {
      $theParam1="\"inside_block\"";
    }
    if(/\{(.*)\}/) {
      $theParam1="\"probably_def_of_something\"";  # NOTE: DOES THIS WORK?
    }
    print "$ppprefix state $theParam1\n";
  }
  if($numSquares eq 0) {
    # fine nothing to do
  }
  else {
    # check for numSquares problem
    print "$ppprefix has numSquares $numSquares\n";
  }
}


sub resetFlagsAndCounts()
{
  $numSingQuotes=0;
  $numDoubQuotes=0;
}


sub fixParam1()
{
  my $temp=shift;
  $temp =~ s/^\s+(\w)/$1/;
  $temp =~ s/(\w)\s+$/$1/;
  $temp =~ s/(\w)\;$/$1/;
  $theParam1="\"$temp\"";
}


sub fixParam2()
{
  my $temp=shift;
  $temp =~ s/^\s+(\w)/$1/;
  $temp =~ s/(\w)\s+$/$1/;
  $temp =~ s/(\w)\;$/$1/;
  $theParam2="\"$temp\"";
}


sub fixParam3()
{
  my $temp=shift;
  $temp =~ s/^\s+(\w)/$1/;
  $temp =~ s/(\w)s+$/$1/;
  $temp =~ s/(\w)\;$/$1/;
  $theParam3="\"$temp\"";
}

