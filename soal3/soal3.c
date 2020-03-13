#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>


int main() {
  int status;
        
  pid_t child_id;
  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
          char *arg[3] = {"unzip", "/home/denta/modul2/jpg.zip", NULL};
          execv("/usr/bin/unzip", arg);
        
  } else {
    while ((wait(&status)) > 0);
 
    // this is child
    pid_t child_id1;
    child_id1 = fork();

      if (child_id1 < 0) {
      exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

  if (child_id1 == 0) 
  {
        char *argv[] = {"mkdir", "-p", "/home/denta/modul2/indomie", NULL};
        execv("/bin/mkdir", argv);
  }else{
        while ((wait(&status)) > 0);
        sleep(5);
        char *argv[] = {"mkdir", "-p", "/home/denta/modul2/sedaap", NULL};
        execv("/bin/mkdir", argv);
  } 
}
}
