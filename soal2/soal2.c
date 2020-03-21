#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

// void getTimestamp(char *path);
void ModeA();
void ModeB();

int main(int argc, char **argb){
  if(strcmp(argb[1], "-a") == 0){
    ModeA();
  }
  if(strcmp(argb[1], "-b") == 0){
    ModeB();
  }

  char buf[100];
  char *workingDir = getcwd(buf, 100);

  pid_t pid, sid;

  pid = fork();
  
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/denta/modul2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
    chdir(workingDir);
    pid_t child_id1;
    int status1;
    
    child_id1 = fork();

    time_t waktufile;
    struct tm *lt;
    time(&waktufile);
    lt = localtime(&waktufile);
    char date[26], namafile[100];
    strftime(namafile, 100, "%Y-%m-%d_%H:%M:%S", lt);
    
    if(child_id1 == 0){
      pid_t child_id2;
      int status2;
      
      child_id2 = fork();

      if(child_id2 == 0){
        char *argv[] = {"mkdir", namafile, NULL};
        execv("/bin/mkdir", argv);
      } else {
        while((wait(&status2)) > 0);
        pid_t child_id3;
        int status3, i;
        char curFolder[1000]; strcpy(curFolder, namafile);
        char link[100];
        char namagambar[100];
        chdir(namafile);

        for(i=0; i<20; i++){
          strcpy(namafile, curFolder); strcat(namafile, "/");
          time_t waktugambar;
          time(&waktugambar);
          struct tm* lt2 = localtime(&waktugambar);
          strftime(namagambar, 100, "%Y-%m-%d_%H:%M:%S", lt2);
          long int sec = time(NULL)%1000 + 100;
          snprintf(link, 1000, "https://picsum.photos/%ld", sec);
          child_id3 = fork();
          if(child_id3 == 0){
            char *argv[] = {"wget", "-O", namagambar, link, NULL};
            execv("/usr/bin/wget", argv);
          }
          sleep(5);
        }

        pid_t child_id4;
        int status4;
        child_id4 = fork();
        while(wait(&status4) > 0);
        chdir("..");
        char outputZip[1000];
        snprintf(outputZip, 1000, "%s.zip", curFolder);

        pid_t child_id5= fork();
        if(child_id5 == 0){
          char *argv[] = {"zip", "-r", outputZip, curFolder, NULL};
          execv("/usr/bin/zip", argv);
        }
        int status5;
        while(wait(&status5) > 0);
        char *argv[] = {"rm", "-rf", curFolder, NULL};
        execv("/bin/rm", argv);
      }
    }
    sleep(30);
  }
  return 0;
}

void ModeA()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2coba))\n", temp); //ngambil variabel nama killfolder isinya pid nama2coba
  fputs("kill -9 $killOrder\n", temp); //gawe mateni
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempChild_id;
  int tempStatus;
  tempChild_id = fork();

  if(tempChild_id == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  }
}

void ModeB()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2coba))\n", temp);
  fputs("killOrder=${killOrder##* }\n", temp);c
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempChild_id;
  int tempStatus;
  tempChild_id = fork();

  if(tempChild_id == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  }
}
