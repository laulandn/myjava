#ifndef EMU_NJAVA_H
#define EMU_NJAVA_H


#include "../../cpp/alib/abaseclass.h"
#include "../../cpp/alib/abasics.h"


#include "../../nemu/elib/eio.h"


// Standard "tiny" files
#define NJAVA_STDIN   0
#define NJAVA_STDOUT  1
#define NJAVA_STDERR  2


// Path for root of the emulated filesystem...
#define NJAVA_FS_PATH "/tmp/nemu"


class EJavaVM : public EEmu {
public:
  // Public Member Functions
  EJavaVM();
  virtual ~EJavaVM();
  //
  static bool recognizeName(const char *name);
  void setKind(const char *name);
  virtual const char *getName();
  virtual const char *guessCpu(const char *name);
  //
  bool systemCall(UINT num=0);
  virtual void resetEmu();
  virtual void setMap(EMapAbstract *m);
  virtual bool interp(const char *cmd,const char *a1,const char *a2,const char *a3);
  //
private:
  // Private Member Functions
  virtual void init();
  void initIO(uint8_t type);
  // these read the classfile (actually parse it into objects)
  void loadInitialClass();
};


#endif // EMU_NJAVA_H
