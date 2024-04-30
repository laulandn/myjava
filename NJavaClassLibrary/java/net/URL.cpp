
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


#include "URL.h"

#include "../util/Stream.h"

#include "../io/InputStream.h"


////////////////////////////////////////////////////////////////////////////////
//  URL Class
////////////////////////////////////////////////////////////////////////////////

URL::URL(NJString tbase, NJString tname)
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"URL::URL(\""<<tbase<<"\",\""<<tname<<"\")\n";
#endif // DEBUG_VERBOSE
  base=tbase; name=tname;
}


InputStream *URL::openStream()
{
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"URL::openStream()\n";
#endif // DEBUG_VERBOSE
/*
  char fn[256];
  strcpy(fn,base);
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"strdup'd...\n";
  DEBUG_OUT<<"fn is now \""<<fn<<"\"\n";
#endif // DEBUG_VERBOSE
  strcat(fn,"/");
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"/ strcat'd...\n";
  DEBUG_OUT<<"fn is now \""<<fn<<"\"\n";
#endif // DEBUG_VERBOSE
  strcat(fn,name);
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"name strcat'd...\n";
  DEBUG_OUT<<"fn is now \""<<fn<<"\"\n";
#endif // DEBUG_VERBOSE
  char *n=strdup(fn);
#ifdef DEBUG_VERBOSE
  DEBUG_OUT<<"n is now \""<<n<<"\"\n";
  DEBUG_OUT<<"going to use path \""<<n<<"\"\n";
#endif // DEBUG_VERBOSE
*/
  Stream *st=new Stream(name);
  return new InputStream(st);
}


