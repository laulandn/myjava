
// NOTE: This was translated from Java to C++ by an old version of njavac


#include "njavacpp.h"


#include "java/lang/System.h"
#include "java/lang/Integer.h"

#include "java/awt.h"

#include "java/applet/Applet.h"


class lines : public Applet
    {
     public: void paint(Graphics *g)
      {
      int width=getSize()->width;
      int height=getSize()->height;
      int wfactor=0xffffff/width;
      int hfactor=0xffffff/height;
      for(int t=0;t<width;t++) 
        {
        int tcolor=t*wfactor;
        g->setColor(new Color((tcolor&0xff0000)>>16,(tcolor&0xff00)>>8,tcolor&0xff));
        g->drawLine(t,0,width-t,height);
}
      
      for(int t=0;t<height;t++) 
        {
        int tcolor=t*hfactor;
        g->setColor(new Color((tcolor&0xff0000)>>16,(tcolor&0xff00)>>8,tcolor&0xff));
        g->drawLine(0,t,width,height-t);
}
      
}
    
};




#include "../../cpp/guilib/AApp.h"


int main(int argc,char **argv)
{
  aThisApp->start(argc,argv);
  //System=new _nickvm_jSystemInternal;
  lines *theApp=new lines;
  theApp->run();
  theApp->start();
  return 0;
}

