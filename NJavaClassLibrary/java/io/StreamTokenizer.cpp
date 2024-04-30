
#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT dBug
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cerr
#define CONS_OUT *aDefaultOutputStream
#define CONS_IN std::cin
//#define CONS_IN *inStream
#define ERR_OUT std::cerr


#ifdef DEBUG_VERBOSE
//#undef DEBUG_VERBOSE
#endif // DEBUG_VERBOSE


#include "StreamTokenizer.h"
#include "InputStream.h"

#include "../util/Stream.h"


////////////////////////////////////////////////////////////////////////////////
//  StreamTokenizer Class
////////////////////////////////////////////////////////////////////////////////

StreamTokenizer::StreamTokenizer(InputStream *is)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"StreamTokenizer::StreamTokenizer()\n";
#endif // DEBUG_VERBOSE
  ist=is;
  eolSig=false;
  comment='#';
  sval=NULL;
  nval=0;
  ttype=TT_EOF;
  ptr=0;
  size=is->getSize();
  data=(char *)malloc(size);
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"is size="<<size<<"\n";
#endif // DEBUG_VERBOSE
  if(data) {
    is->read(data,size);
  }
}


StreamTokenizer::~StreamTokenizer()
{
  if(data) free(data);
  data=NULL;
}


void StreamTokenizer::eolIsSignificant(bool t)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"StreamTokenizer::eolIsSignificant("<<t<<")\n";
#endif // DEBUG_VERBOSE
  eolSig=t;
}


void StreamTokenizer::commentChar(char c)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"StreamTokenizer::commentChar('"<<c<<"')\n";
#endif // DEBUG_VERBOSE
  comment=c;
}


unsigned int StreamTokenizer::nextToken()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"StreamTokenizer::nextToken()\n";
#endif // DEBUG_VERBOSE
  if(ptr==size) {
#ifdef DEBUG_VERBOSE
    //DEBUG_OUT<<"At EOF.\n";
#endif // DEBUG_VERBOSE
    ttype=TT_EOF;
    return TT_EOF;
  }
  unsigned int ret=TT_WORD;
  char buf[256];
  char c=' ';
  unsigned int t=0;
  bool reading=true;
  while(reading) {
    if(ptr>size) {
      ERR_OUT<<"nextToken ran past end of data!\n";
      reading=false;
      return TT_EOF;
    }
    c=data[ptr];
    buf[t]=c;
#ifdef DEBUG_VERBOSE
    //DEBUG_OUT<<"\""<<c<<"\"";
#endif // DEBUG_VERBOSE
    if((c==' ')||(c=='\t')) {
      if(t) reading=false;
    }
    if(c=='\n') reading=false;
    if(reading) {
      if((c!=' ')&&(c!='\t')) t++;
      ptr++;
    }
  }
  buf[t]=0;
#ifdef DEBUG_VERBOSE
  //DEBUG_OUT<<"Got \""<<buf<<"\"\n";
#endif // DEBUG_VERBOSE
  if(!t) {
#ifdef DEBUG_VERBOSE
    //DEBUG_OUT<<"t was zero!\n";
#endif // DEBUG_VERBOSE
    ptr++;
    if(c=='\n') ret=TT_EOL;
  }
  switch(buf[0]) {
    case '0':
    case '.':
    case '-':
      sscanf(buf,"%f",&nval);
      ret=TT_NUMBER;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      sscanf(buf,"%f",&nval);
      if(nval!=0.0) ret=TT_NUMBER;
      break;
    default:
      break;
  }
  if(ret==TT_WORD) sval=strdup(buf);
#ifdef DEBUG_VERBOSE
  //DEBUG_OUT<<"Going to return "<<ret<<"\n";
#endif // DEBUG_VERBOSE
  ttype=ret;
  return ret;
}


NJString StreamTokenizer::toString()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"StreamTokenizer::toString()\n";
#endif // DEBUG_VERBOSE
  NJString ret=(NJString)"";
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"Going to return \""<<ret<<"\"\n";
#endif // DEBUG_VERBOSE
  return ret;
}
