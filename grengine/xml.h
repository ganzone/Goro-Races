/*#***************************************************************************
 * VCGLib                                                            o o     *
 *																																 o     o   *
 * Visual Computing Group                                          _  O  _   *
 * ISTI Institute, CNR Pisa                                         \/)\/    *
 *                                                                 /\/|      *
 * Copyright(C) 1999-2003 by Federico Ponchio                         |      *
 * All rights reserved.                                               \      *
 *																																					 *
 * Permission  to use, copy, modify, distribute  and sell this  software and *
 * its documentation for any purpose is hereby granted without fee, provided *
 * that  the above copyright notice appear  in all copies and that both that *
 * copyright   notice  and  this  permission  notice  appear  in  supporting *
 * documentation. the author makes  no representations about the suitability *
 * of this software for any purpose. It is provided  "as is" without express *
 * or implied warranty.                                                      *
 *					                                                                 *
 *****************************************************************************/
/*#**************************************************************************
  History
 2002 Dec 08 Release for the CI course,
 ... omissis...
****************************************************************************/

#ifndef XML_VCG_H
#define XML_VCG_H

#include <string>
#include <map>
#include <vector>
using namespace std;
namespace vcg {

class Xml {
 public:
  string id;
  string content;
  map<string, string> attr;
  vector<Xml> children;
 public:
  typedef vector<Xml>::iterator iterator;
  iterator begin() { return children.begin(); }
  iterator end() { return children.end(); }
  int count(const string &elem) { return attr.count(elem); }
  string &operator[](const string &elem) { return attr[elem]; }
  string xml() { 
    string ret = "<" + id;
    map<string, string>::iterator a;
    for(a = attr.begin(); a != attr.end(); a++)
      ret.append(" " + (*a).first + "=\"" + (*a).second + "\"");
    if(children.size() || content.size()) {
      ret.append(">\n");
      iterator c;
      for(c = begin(); c != end(); c++)
				ret .append(c->xml());
			ret.append(content);
      ret.append("</" + id + ">\n");
    } else 
      ret.append("/>\n");
    return ret;
  }
};

class XmlDoc {
 public:
  Xml *start;
  int read(const string &file);
  
  Xml &root() { return *start; }
  XmlDoc(): start(NULL) {}
  ~XmlDoc() {
    if(start)
      delete start;
  }
};
}
#endif


