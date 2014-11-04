
#include <string>
#include <jni.h>
#include <string.h>
#include <android/log.h>
#include <dlfcn.h>
#include "mcpelauncher.h"

using namespace std; //so we don't need to say std::string

static string(*Name_Real)(void* p); //this is the real mcpe function, p is a string , void* can point to any data type

string versionNameHook(void* p){ //this is the function that will override the real one	
	return "***  Yolow swag, MLG pro, 21, about a week ago, follow me on twitter @expir3dcow ***"; //change the string to whatever you wish
}
	
	


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void *handle = dlsym(RTLD_DEFAULT,"_ZN6Common20getGameVersionStringEv"); //this is the symbol for version name
	mcpelauncher_hook(handle,(void*)&versionNameHook,(void**)&Name_Real); //we hook the method
	return JNI_VERSION_1_2;
}
