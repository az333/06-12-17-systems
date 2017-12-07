#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>

#define KEY 4012

int main(int argc, char *argv[]){
  int sid;
  char * flag = argv[1];
  char * n = argv[2];
  if(argc < 2) printf("    missing flag!\n");
  else if(strcmp(flag, "-c") == 0){
    if(argc < 3) printf("    missing value!\n");
    else{
      sid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      if(sid != -1){
        int val;
        sscanf(n, "%d", &val);
        semctl(sid, 0, SETVAL, val);
	      printf("    semaphore created: %d\n    value set: %d\n", sid, val);
      }
      else{
        printf("    semaphore already exists!\n");
      }
    }
  }

  else if(strcmp(flag, "-v") == 0){
    sid = semget(KEY, 1, IPC_CREAT | 0644);
    if(sid != -1){
      int val = semctl(sid, 0, GETVAL);
      printf("    semaphore value: %d\n",val);
    } else printf("%s\n", strerror(errno));
  }

  else if(strcmp(flag, "-r")== 0){
    sid = semget(KEY, 1, IPC_CREAT | 0644);
    if(sid != -1){
      semctl(sid, 0, IPC_RMID);
      printf("    semaphore removed: %d\n", sid);
    } else printf("%s\n", strerror(errno));
  }

  else printf("    invalid arguments\n");

  return 0;
}
