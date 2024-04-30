
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


#include "Component.h"
#include "Graphics.h"


////////////////////////////////////////////////////////////////////////////////
//  Component Class
////////////////////////////////////////////////////////////////////////////////

Component::Component()
{
  init();
}


void Component::repaint()
{
  // NOTE: Should always be overriden...
}


void Component::paint(Graphics *g)
{
  // NOTE: Should always be overriden...
}


void Component::update()
{
  // NOTE: Should always be overriden...
}

