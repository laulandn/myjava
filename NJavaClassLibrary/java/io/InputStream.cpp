
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


#include "InputStream.h"

#include "../util/Stream.h"


////////////////////////////////////////////////////////////////////////////////
//  InputStream Class
////////////////////////////////////////////////////////////////////////////////

InputStream::InputStream(Stream *s)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"InputStream::InputStream()\n";
#endif // DEBUG_VERBOSE
  st=s;
  nickvmFile=fopen(s->getName(),"r");
  if(nickvmFile) {
#ifdef DEBUG_VERBOSE
    DEBUG_OUT<<"fopen of \""<<s->getName()<<"\" was good.\n";
#endif // DEBUG_VERBOSE
  }
  else {
    ERR_OUT<<"InputStream: Couldn't fopen \""<<s->getName()<<"\"!\n";
    err.setError();
    exit(EXIT_FAILURE);
  }
}


InputStream::~InputStream()
{
  this->close();
}


void InputStream::close()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"InputStream::close()\n";
#endif // DEBUG_VERBOSE
  if(nickvmFile) fclose(nickvmFile);
  nickvmFile=NULL;
}


int InputStream::read(char *buf,unsigned int count)
{
  if(err.getError()) return -1;
  if(!nickvmFile) return -1;
  return fread(buf,1,count,nickvmFile);
}


int InputStream::getSize()
{
  if(err.getError()) return 0;
  int ret=0;
  if(nickvmFile) {
    int bookmark=ftell(nickvmFile);
    fseek(nickvmFile,0,SEEK_END);
    ret=ftell(nickvmFile);
    fseek(nickvmFile,bookmark,SEEK_SET);
  }
  return ret;
}


