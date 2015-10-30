#include <string.h> /* memset */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "SampleLib.h"
#include <dlfcn.h>
#include <signal.h>
#include <setjmp.h>

typedef jint (*Java_SampleLib_soma_WRAPPED)(JNIEnv *env, jobject obj, jint a, jint b);


jint throwNoClassDefError( JNIEnv *env, const char *message )
{
    jclass exClass;
    const char *className = "java/lang/RuntimeException";

    exClass = env->FindClass(className);

    return env->ThrowNew(exClass, message );
}

static sigjmp_buf sig_mark;

// Comming back to return the error
void  sig_handler_func(int sig){
  siglongjmp(sig_mark, -1);
}

JNIEXPORT jint JNICALL Java_SampleLib_soma
(JNIEnv *env, jobject obj, jint a, jint b) {

  struct sigaction handler, old_handler;

  // Getting the old handler.
  sigaction(SIGSEGV, NULL, &old_handler);

  // Jump point if something wrong happens
  if (sigsetjmp(sig_mark, 0) == -1) {
    // Restoring the old handler
    sigaction(SIGSEGV, &old_handler, NULL);
    return throwNoClassDefError(env, "Erro");
  }

  // installing the new handler
  handler.sa_handler = sig_handler_func;
  sigemptyset(&handler.sa_mask);
  handler.sa_flags = 0;
  sigaction(SIGSEGV, &handler, NULL);

  // Caling the problematic lib
  void *myso = dlopen("libOriginal.so", RTLD_NOW);
  Java_SampleLib_soma_WRAPPED func = (Java_SampleLib_soma_WRAPPED) dlsym(myso, "Java_SampleLib_soma");
  jint ret = func(env, obj, a, b);
  dlclose(myso);

  // Restoring the old handler
  sigaction(SIGSEGV, &old_handler, NULL);

  return ret;
}
