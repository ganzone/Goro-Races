%{
  #pragma warning(disable : 4786 )
  #include "xml.h"
  #include <stdio.h>
  #include <stdlib.h>

  struct Attribute {
    string attr, val;
  };
  typedef map<string, string> Attributes;
  typedef vector<Xml> Elements;

  void yyerror (char *s);
  int yylex();
  Xml *xml_element;
  extern FILE *yyin;
  extern int xml_line;
%}

%union {
  char *name;
  string *text;
  Attribute *attr;
  Attributes *attrs;
  Xml *element;
  Elements *elements;
};

%type<element> xml, tag;
%type<attr> attribute;
%type<attrs> attributes;
%type<element> tags;
%type<text> content, contents;
%type<null> header, version, doctype;
%token<name> ID, ELEM_TEXT, ELEM_CONTENT, CDATA_CONTENT
%token CDATA_START, CDATA_END, ELEM_START, END, ELEM_END, DELIM, QMARK, MARK, EQUAL

%expect 1
%%

xml:
header tag { xml_element = $2;}
| tag { $$ = $1; xml_element = $1; }
;

doctype:
ELEM_START MARK ID ID ID DELIM ELEM_TEXT DELIM ELEM_END {}
;
version:
ELEM_START QMARK ID ID EQUAL DELIM ELEM_TEXT DELIM QMARK ELEM_END {}
;

header:
version { }
| version doctype { }
;

tag:
ELEM_START ID attributes END ELEM_END {
  $$ = new Xml;
  $$->id = string($2);
  delete $2;
  $$->attr = *($3);
  delete $3;
}
/*| ELEM_START ID attributes ELEM_END contents ELEM_START END ID ELEM_END {
  $$ = new Xml;
  $$->id = string($2);
  $$->attr = *($3);
  $$->content = *($5);
  delete $2;
  delete $3;
  if(!strcmp($2, $8)) { YYABORT; }
  }*/
| ELEM_START ID attributes ELEM_END tags ELEM_START END ID ELEM_END {
  $$ = new Xml;
  $$->id = string($2);
  $$->attr = *($3);
  $$->children = ($5)->children;
  $$->content = ($5)->content;
  delete $2;
  delete $3;
  delete $5;
  if(!strcmp($2, $8)) { YYABORT; }
}
;

tags:
/*empty*/ { $$ = new Xml;}
| tags  tag { $$->children.push_back(*($2)); delete $2;}
| tags contents { $$->content.append(*($2)); delete $2; }
;

attribute:
ID {
  $$ = new Attribute;
  $$->attr = string($1);
  delete $1;
}
| ID EQUAL DELIM DELIM {
  $$ = new Attribute;
  $$->attr = string($1);
  delete $1;
}
| ID EQUAL DELIM ELEM_TEXT DELIM { 
  $$ = new Attribute;
  $$->attr = string($1);
  delete $1;
  $$->val = string($4);
  delete $4;
}
;

attributes:
/*empty*/ { $$ = new Attributes;}
| attributes attribute {
  /*  if($$->count($2->attr))
      assert("Double attribute");*/
  (*$$)[$2->attr] = $2->val;
  delete $2;
}
;

contents:
content {
  $$ = new string(*($1));
  delete $1;
}
| contents content {
  $$->append(*($1));
  delete $1;
}
;

content:
ELEM_TEXT { 
  $$ = new string;
  $$->append($1);
}
| CDATA_START CDATA_CONTENT CDATA_END {
  $$ = new string;
  $$->append($2);
}
;

%%

void yyerror (char *s)  {/* Called by yyparse on error */
  fprintf (stderr,"%s at line %d\n", s, xml_line);
}

extern "C" {
int yywrap() { return 1; }     
}

//void set_input(FILE *fp);

int XmlDoc::read(const string &file) {
  FILE *fp;
  fp = fopen(file.c_str(), "r");
  if(!fp) return 0;
  yyin = fp;
  if(yyparse() != 0) {
    fclose(fp);
    return 0;
  }
  start = xml_element;
  fclose(fp);
  return 1;
}

/*int main(int argc, char *argv[]) {
  if(argc == 1) {
    printf("uso: xmltest <file.xml>\n");
    return 0;
  }
  XmlDocument doc;
  if(doc.read(argv[1]))
    printf("%s\n", doc.root().xml().c_str());
  else
    printf("Could not read document\n");
  return 1;
}*/
















