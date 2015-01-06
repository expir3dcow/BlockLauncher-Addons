#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include "mcpelauncher.h"

/*This method is written by MrARM, all credit to him*/
void reconstructVTable(void** vtable) {
	int i = -1;
	while(true) {
		i++;
		void* method = vtable[i];
		if(method == NULL) {
			if(i >= 3) {
				break;
			}
			__android_log_print(ANDROID_LOG_INFO, "mod", "vtable: %i %i null\n", i, method);
			continue;
		}
		
		Dl_info info;
		int ret = dladdr(method, &info);
		if(ret != 0) {
			void* addrcheck = dlsym(RTLD_DEFAULT, info.dli_sname);
			__android_log_print(ANDROID_LOG_INFO, "mod", "vtable %i %i %s %i\n", i, method, info.dli_sname, addrcheck);
		}else{
			__android_log_print(ANDROID_LOG_INFO, "mod", "vtable: %i %i not found\n", i, method);
		}
	}
}

int getMaxHealth(){
  return 1;//change to whatver you wish. 1 = 0.5 hearts
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void * reserved){
  void** chicken_vtable = (void**)dlsym(RTLD_DEFAULT,"_ZTV7Chicken");
  //reconstructVTable(chicken_vtable); //prints all the offsets to log, including max health which was 104
  chicken_vtable[104] = getMaxHealth();
  return JNI_VERSION_1_2;
}
