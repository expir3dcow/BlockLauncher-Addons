#include <jni.h>
#include <dlfcn.h>
#include "mcpelauncher.h"

int (*GetSlimeSizeReal)();

int GetSlimeSizeHook(){
  return 70; //change the number to change the slime size
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
  void * handle = dlsym(RTLD_DEFAULT,"_ZNK5Slime12getSlimeSizeEv");
  mcpelauncher_hook(handle, (void*)*GetSlimeSizeHook, (void**)GetSlimeSizeReal);
}
