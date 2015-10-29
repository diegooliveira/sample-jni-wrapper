#include <string.h> /* memset */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "SampleLib.h"
#include <dlfcn.h>
#include <signal.h>


JNIEXPORT jint JNICALL Java_SampleLib_soma
(JNIEnv *env, jobject obj, jint a, jint b) {

	if (a == 2){        
		char *s = "hello world";
		*s = 'H';
	}

	return a + b;
}
