#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *threadfunc(void *parm)
{
  int   i = 0;
  printf("Entered secondary thread\n");
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  while (1) {
    printf("Secondary thread is looping\n");
    pthread_testcancel();
    printf("After cancellation point!!!\n");
    sleep(1);

    if (++i == 5) {
      /* Since default cancel type is deferred, changing the state   */
      /* will allow the next cancellation point to cancel the thread */
      printf("Cancel state set to ENABLE\n");
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }
  } /* infinite */
  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t   thread;
  int   rc=0;

  printf("Entering testcase\n");

  /* Create a thread using default attributes */
  printf("Create thread using the NULL attributes\n");
  rc = pthread_create(&thread, NULL, threadfunc, NULL);
  if (rc != 0) {
      perror("Thread creation failed");
      exit(EXIT_FAILURE);
    }

 
  /* sleep() is not a very robust way to wait for the thread */
  sleep(3);

  printf("Cancel the thread\n");
  rc = pthread_cancel(thread);

  /* sleep() is not a very robust way to wait for the thread */
  sleep(3);
  printf("Main completed\n");
  return 0;
}