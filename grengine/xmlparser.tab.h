#ifndef XMLPARSER_TAB_H
# define XMLPARSER_TAB_H

typedef union {
  char *name;
  string *text;
  Attribute *attr;
  Attributes *attrs;
  Xml *element;
  Elements *elements;
} YYSTYPE;
# define	ID	257
# define	ELEM_TEXT	258
# define	ELEM_CONTENT	259
# define	CDATA_CONTENT	260
# define	CDATA_START	261
# define	CDATA_END	262
# define	ELEM_START	263
# define	END	264
# define	ELEM_END	265
# define	DELIM	266
# define	QMARK	267
# define	MARK	268
# define	EQUAL	269


extern YYSTYPE yylval;

#endif /* not XMLPARSER_TAB_H */
