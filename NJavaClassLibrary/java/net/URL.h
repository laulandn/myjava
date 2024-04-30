#ifndef NICKVM_JAVAC_URL_H
#define NICKVM_JAVAC_URL_H


// IMPORTANT!  This file is machine read!
// Please follow formatting and layout EXACTLY!


#include "../../njavacpp.h"


class Stream;
class InputStream;


class URL : public __njobjectInternal {
public:
  URL(NJString base, NJString name);
  //
  InputStream *openStream();
  //
protected:
  NJString base;
  NJString name;
};


#endif // NICKVM_JAVAC_URL_H

