
%{
#include <stdio.h>
%}

%option noyywrap

%%

\/\/ { printf("SLASHSLASH\n"); }
\/\* { printf("SLASHSTAR\n"); }
\*\/ { printf("STARSLASH\n"); }

0x[a-zA-Z0-9]+  { printf("HEXINTEGER %s\n",yytext); }
[0-9]+  { printf("INTEGER %s\n",yytext); }
[0-9]*\.[0-9]+  { printf("FLOAT %s\n",yytext); }

\.  { printf("PERIOD\n"); }
\,  { printf("COMMA\n"); }
\+\+  { printf("PLUSPLUS\n"); }
\-\-  { printf("MINUSMINUS\n"); }
\&\&  { printf("ANDAND\n"); }
\|\|  { printf("OROR\n"); }

\=\=  { printf("EQUALSEQUALS\n"); }
\!\=  { printf("NOTSEQUALS\n"); }

\<\<  { printf("LESSLESS\n"); }
\>\>  { printf("GREATERGREATER\n"); }
\<\=  { printf("LESSEQUAL\n"); }
\<  { printf("LESS\n"); }
\>\=  { printf("GREATEREQUAL\n"); }
\>  { printf("GREATER\n"); }

\+\=  { printf("PLUSEQUAL\n"); }
\-\=  { printf("MINUSEQUAL\n"); }
\*\=  { printf("STAREQUAL\n"); }
\&\=  { printf("ANDEQUAL\n"); }
\|\=  { printf("OREQUAL\n"); }

\=  { printf("EQUALS\n"); }

\+  { printf("PLUS\n"); }
\-  { printf("MINUS\n"); }
\*  { printf("STAR\n"); }
\/  { printf("SLASH\n"); }
\&  { printf("AND\n"); }
\%  { printf("PERCENT\n"); }
\|  { printf("OR\n"); }

\~  { printf("TILDAE\n"); }
\?  { printf("QUESTION\n"); }
\!  { printf("EXCLAIM\n"); }
\^  { printf("RAISE\n"); }
\`  { printf("BACKQUOTE\n"); }
\'  { printf("SINGLEQ\n"); }
\"  { printf("DOUBLEQ\n"); }

\;  { printf("SEMICOLON\n"); }
\:  { printf("COLON\n"); }
\{  { printf("OPEN_C\n"); }
\[  { printf("OPEN_S\n"); }
\(  { printf("OPEN_P\n"); }
\)  { printf("CLOSE_P\n"); }
\]  { printf("CLOSE_S\n"); }
\}  { printf("CLOSE_C\n"); }

import { printf("IMPORT\n"); }
class { printf("CLASS\n"); }

public { printf("PUBLIC\n"); }
private { printf("PRIVATE\n"); }

super { printf("SUPER\n"); }
this { printf("THIS\n"); }
new { printf("NEW\n"); }
extends { printf("EXTENDS\n"); }
implements { printf("IMPLEMENTS\n"); }

try { printf("TRY\n"); }
catch { printf("CATCH\n"); }
throws { printf("THROWS\n"); }

void { printf("VOID\n"); }
int { printf("INT\n"); }
float { printf("FLOAT\n"); }
double { printf("DOUBLE\n"); }
boolean { printf("BOOLEAN\n"); }
static { printf("STATIC\n"); }

if { printf("IF\n"); }
else { printf("ELSE\n"); }
for { printf("FOR\n"); }
while { printf("WHILE\n"); }

switch { printf("SWITCH\n"); }
case { printf("CASE\n"); }
break { printf("BREAK\n"); }
default { printf("DEFAULT\n"); }

synchronized { printf("SYNCHRONIZED\n"); }

return { printf("RETURN\n"); }

true { printf("TRUE\n"); }
false { printf("FALSE\n"); }
null { printf("NULL\n"); }

[a-zA-Z0-9_]+ { printf("\"%s\"\n",yytext); }

\ + { printf("SPACE\n"); /* Ignore all other characters. */ }
\t+ { printf("SPACE\n"); /* Ignore all other characters. */ }
\n+ { printf("NEWLINE\n"); /* Ignore all other characters. */ }

. { printf("ERROR \"%s\"?\n",yytext); /* Ignore all other characters. */ }

%%

int main(void)
{
    /* Call the lexer, then quit. */
    yylex();
    return 0;
}
