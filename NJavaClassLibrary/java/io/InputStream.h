#ifndef NICKVM_JAVAC_INPUTSTREAM_H
#define NICKVM_JAVAC_INPUTSTREAM_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Stream;


class InputStream : public __njobjectInternal {
public:
  InputStream(Stream *s);
  virtual ~InputStream();
  //
  void close();
  int read(char *buf,unsigned int count);
  int getSize();
  //
protected:
  Stream *st;
  FILE *nickvmFile;
};



#endif

