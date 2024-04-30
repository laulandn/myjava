#! /usr/bin/perl

$last="";

while(<>) {
  $good=0;
  #
  if(/^HEXINTEGER (.*)$/) { print $1; $good=1; }
  if(/^INTEGER (.*)$/) { print $1; $good=1; }
  if(/^FLOAT (.*)$/) { print $1; $good=1; }
  #
  if(/^SPACE$/) { print " "; $good=1; }
  if(/^NEWLINE$/) { print "\n"; $good=1; }
  #
  if(/^SLASHSLASH$/) { print "//"; $good=1; }
  if(/^SLASHSTAR$/) { print "/*"; $good=1; }
  if(/^STARSLASH$/) { print "*/"; $good=1; }
  #
  if(/^OPEN_C$/) { print "{\n"; $good=1; }
  if(/^CLOSE_C$/) { print "}\n"; $good=1; }
  if(/^OPEN_P$/) { print "("; $good=1; }
  if(/^CLOSE_P$/) { print ")"; $good=1; }
  if(/^OPEN_S$/) { print "["; $good=1; }
  if(/^CLOSE_S$/) { print "]"; $good=1; }
  #
  if(/^PERIOD$/) { print "."; $good=1; }
  if(/^COMMA$/) { print ","; $good=1; }
  if(/^PLUSPLUS$/) { print "++"; $good=1; }
  if(/^MINUSMINUS$/) { print "--"; $good=1; }
  if(/^ANDAND$/) { print "&&"; $good=1; }
  if(/^OROR$/) { print "||"; $good=1; }
  #
  if(/^EQUALSEQUALS$/) { print "=="; $good=1; }
  if(/^NOTEQUALS$/) { print "!="; $good=1; }
  #
  if(/^LESSLESS$/) { print "<<"; $good=1; }
  if(/^GREATERGREATER$/) { print ">>"; $good=1; }
  if(/^LESSEQUAL$/) { print "<="; $good=1; }
  if(/^LESS$/) { print ">"; $good=1; }
  if(/^GREATEREQUAL$/) { print ">="; $good=1; }
  if(/^GREATER$/) { print ">="; $good=1; }
  #
  if(/^PLUSEQUAL$/) { print "+="; $good=1; }
  if(/^MINUSEQUAL$/) { print "-="; $good=1; }
  if(/^STAREQUAL$/) { print "*="; $good=1; }
  if(/^ANDEQUAL$/) { print "&="; $good=1; }
  if(/^OREQUAL$/) { print "|="; $good=1; }
  #
  if(/^EQUALS$/) { print "="; $good=1; }
  #
  if(/^PLUS$/) { print "+"; $good=1; }
  if(/^MINUS$/) { print "-"; $good=1; }
  if(/^STAR$/) { print "*"; $good=1; }
  if(/^SLASH$/) { print "/"; $good=1; }
  if(/^AND$/) { print "&"; $good=1; }
  if(/^PERCENT$/) { print "%"; $good=1; }
  if(/^OR$/) {  if($good eq 0) { print "|"; $good=1; } }
  #
  if(/^TILDAE$/) { print "~"; $good=1; }
  if(/^QUESTION$/) { print "?"; $good=1; }
  if(/^EXCLAIM$/) { print "!"; $good=1; }
  if(/^RAISE$/) { print "^"; $good=1; }
  if(/^BACKQUOTE$/) { print "`"; $good=1; }
  if(/^SINGLEQ$/) { print "'"; $good=1; }
  if(/^DOUBLEQ$/) { print "\""; $good=1; }
  #
  if(/^SEMICOLON$/) { print ";"; $good=1; }
  if(/^COLON$/) {  if($good eq 0) { print ":"; $good=1; } }
  #
  if(/^IMPORT$/) { print "#include"; $good=1; }
  if(/^CLASS$/) { print "class"; $good=1; }
  #
  if(/^PUBLIC$/) { print "public"; $good=1; }
  if(/^PRIVATE$/) { print "private"; $good=1; }
  #
  if(/^SUPER$/) { print "/*super*/"; $good=1; }
  if(/^THIS$/) { print "this"; $good=1; }
  if(/^NEW$/) { print "new"; $good=1; }
  if(/^EXTENDS$/) { print "/*extends*/"; $good=1; }
  if(/^IMPLEMENTS$/) { print "/*implements*/"; $good=1; }
  #
  if(/^TRY$/) { print "try"; $good=1; }
  if(/^CATCH$/) { print "catch"; $good=1; }
  if(/^THROWS$/) { print "throws"; $good=1; }
  #
  if(/^VOID$/) { print "void"; $good=1; }
  if(/^INT$/) {  if($good eq 0) { print "int"; $good=1; } }
  if(/^FLOAT$/) { print "float"; $good=1; }
  if(/^DOUBLE$/) { if($good eq 0) { print "double"; $good=1; } }
  if(/^BOOLEAN$/) { print "bool"; $good=1; }
  if(/^STATIC$/) { print "static"; $good=1; }
  #
  if(/^IF$/) { print "if"; $good=1; }
  if(/^ELSE$/) { print "else"; $good=1; }
  if(/^FOR$/) { print "for"; $good=1; }
  if(/^WHILE$/) { print "while"; $good=1; }
  #
  if(/^SWITCH$/) { print "switch"; $good=1; }
  if(/^CASE$/) { print "case"; $good=1; }
  if(/^BREAK$/) { print "break"; $good=1; }
  if(/^DEFAULT$/) { print "default"; $good=1; }
  #
  if(/^RETURN$/) { print "return"; $good=1; }
  #
  if(/^SYNCHRONIZED$/) { print "/*synchronized*/"; $good=1; }
  #
  if(/^TRUE$/) { print "true"; $good=1; }
  if(/^FALSE$/) { print "false"; $good=1; }
  if(/^NULL$/) { print "null"; $good=1; }
  #
  if(/^\"(.*)\"$/) { if($good eq 0) { print $1; $good=1; } }
  #
  if($good eq 0) { print "\nNot recognised: $_\n"; }
  #
  $last=$_;
}
