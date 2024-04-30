#ifndef NICKVM_JAVAC_STREAMTOKENIZER_H
#define NICKVM_JAVAC_STREAMTOKENIZER_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class InputStream;


class StreamTokenizer : public __njobjectInternal {
public:
  StreamTokenizer(InputStream *is);
  StreamTokenizer(InputStream& is);
  virtual ~StreamTokenizer();
  //
  void eolIsSignificant(bool t);
  void commentChar(char c);
  unsigned int nextToken();
  NJString toString();
  //
  unsigned int ttype;
  float nval;
  char *sval;
  //

static const unsigned int TT_EOL=1;
static const unsigned int TT_EOF=2;
static const unsigned int TT_WORD=10;
static const unsigned int TT_NUMBER=20;

//
protected:
  bool eolSig;
  char comment;
  InputStream *ist;
  char *data;
  unsigned int size;
  unsigned int ptr;
};


#endif // NICKVM_JAVAC_STREAMTOKENIZER_H

