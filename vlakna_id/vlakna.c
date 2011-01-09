#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>

void* th_main(void* a)
{
  printf("T2 getpid: %u\n", getpid());
  printf("T2 gettid: %u\n", (pid_t) syscall(SYS_gettid));
  printf("T2 pthread_self: %u\n", pthread_self());
  sleep(60);
  return NULL;
}

int main()
{
  pthread_t t;

  printf("T1 getpid: %u\n", getpid());
  printf("T1 gettid: %u\n", (pid_t) syscall(SYS_gettid));
  printf("T1 pthread_self: %u\n", pthread_self());
  pthread_create(&t, NULL, th_main, NULL);
  pthread_join(t, NULL);

  //printf("T1 ends\n");
  return 0;
}
