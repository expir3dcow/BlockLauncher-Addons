#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include "mcpelauncher.h"


static int(*UseController_Real)(); //this is the real mcpe function

int useControllerHook(){ //this is the function that will override the real one	
	__android_log_print(ANDROID_LOG_INFO, "MyMod", "Swag level is over 9000");
	return 1;
}
	




JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void *handle = dlsym(RTLD_DEFAULT,"_ZN9Minecraft13useControllerEv"); //this is the symbol for using the controller
	mcpelauncher_hook(handle,(void*)&useControllerHook,(void**)&UseController_Real); //we hook the method
	return JNI_VERSION_1_2;
}
