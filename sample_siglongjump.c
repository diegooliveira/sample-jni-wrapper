#include <setjmp.h>
#include <stdio.h>

static sigjmp_buf env;

int foo(int p) {
  if (p)
	siglongjmp(env,p); /* return to sigstejmp returning p */
  return 0;
}


int main() {
  int a,r;
  if (!(r=sigsetjmp(env, 1))) {
    for (a=0; a<10; a++) {
      fprintf(stdout,"%d\n",foo(a));
      fflush(stdout);
    }
  } else {
    fprintf(stdout,"exceptionally returned %d",r);
    fflush(stdout);
  }
}
