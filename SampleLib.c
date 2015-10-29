#include <string.h> /* memset */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "SampleLib.h"
#include <dlfcn.h>
#include <signal.h>


typedef jint (*Java_SampleLib_soma_WRAPPED)(JNIEnv *env, jobject obj, jint a, jint b);


jint throwNoClassDefError( JNIEnv *env, const char *message )
{
    jclass exClass;
    const char *className = "java/lang/RuntimeException";

    exClass = env->FindClass(className);

    return env->ThrowNew(exClass, message );
}

JNIEXPORT jint JNICALL Java_SampleLib_soma
(JNIEnv *env, jobject obj, jint a, jint b) {

    	if( a == 0)
    		return throwNoClassDefError(env, "Erro");

        if (a == 1) {
            void *myso = dlopen("boa.so", RTLD_NOW);
            Java_SampleLib_soma_WRAPPED func = (Java_SampleLib_soma_WRAPPED) dlsym(myso, "Java_SampleLib_soma");
            return func(env, obj, a, b);
        }

        char *s = "hello world";
        *s = 'H';

    return a + b;
}
