/*microparser per xml */

%{
#pragma warning(disable : 4786 )
#include "xml.h"
  struct Attribute {
    string attr, val;
  };
  typedef map<string, string> Attributes;
  typedef vector<Xml> Elements;

#include "xmlparser.tab.h"
#include <stdio.h>
#ifdef WIN32
int isatty(int) { return 0; }
#endif
int xml_line = 1;

%}
ID    [A-Za-z0-9_]+
TEXT  [^\n\"]+
CONTENT [^\n\<]+

%option yylineno
%x value comment cdata tag 
%%

<*>\n                  { xml_line++; }
[ \t\r\f\v]+           {}


\<                     { BEGIN(tag); return ELEM_START; }
<tag>\?                { return QMARK; }
<tag>\!                { return MARK; }
<tag>{ID}              { yylval.name= new char[yyleng + 1];
                         strcpy(yylval.name,yytext);   
                         return ID; }
<tag>=                 { return EQUAL; }
<tag>\"                { BEGIN(value); return DELIM;}
<value>[^\"]*          { yylval.name= new char[yyleng + 1];
                         strcpy(yylval.name,yytext);   
                         return ELEM_TEXT; }
<value>\"              { BEGIN(tag); return DELIM; }
<tag>\/                { return END; }
<tag>\>                { BEGIN(INITIAL); return ELEM_END; }

{CONTENT}              { yylval.name= new char[yyleng + 1];
                         strcpy(yylval.name,yytext);   
                         return ELEM_TEXT; }

"<!--"                 { BEGIN(comment); }
<comment>[^\-\n]+      {}
<comment>"-"[^\-\n]+   {}
<comment>"--"[^\>\n]+  {}
<comment>"-->"         { BEGIN(INITIAL); }

"<[CDATA["             { BEGIN(cdata); return CDATA_START; }
<cdata>[^\]\n]+        { yylval.name= new char[yyleng + 1];
                         strcpy(yylval.name,yytext);   
                         return CDATA_CONTENT;
                       }
<cdata>"]"[^\]\n]*    {}
<cdata>"]]"[^>\n]*    {}
<cdata>"]]>"           { BEGIN(INITIAL); return CDATA_END;}

%%

