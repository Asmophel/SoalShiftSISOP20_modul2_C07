#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int CheckNum(char arr[]){
    for (int i = 0; i < strlen(arr); i++){
        if (arr[i] < '0' || arr[i] > '9'){
            printf ("range waktu harus menggunakan angka\n");
            return 0;
        }else {
            return 1;
        }
    }
}

int main(int argc, char *argv[]){
    int jalan=1,flag,sec,min,hour;
    char adress[50];

    if(argc > 5 || argc < 5){
        printf("input membutuhkan 4 argumen\n");
        return 0;
    }

    if ((strcmp(argv[1], "*"))==0){
        sec = jalan;
    } else if (CheckNum(argv[1])){
        sec = atoi(argv[1]);
        if (sec > 59 || sec < 0){
            printf("range detik salah\n");
            return 0;
        }
    } else {
        return 0;
    }

    if ((strcmp(argv[2], "*"))==0){
        min = jalan;
    } else if (CheckNum(argv[2])){
        min = atoi(argv[2]);
        if (min > 59 || min < 0){
            printf("range menit salah\n");
            return 0;
        }
    } else {
        return 0;
    }
    
    /*else if (atoi(argv[2]) < 0 || atoi(argv[2]) > 59){
            printf ("range waktu harus menggunakan angka\n");
            return 0;
    }*/ 

    if ((strcmp(argv[3], "*"))==0){
        hour = jalan;
    } else if (CheckNum(argv[3])){
        hour = atoi(argv[3]);
        if (hour > 23 || hour < 0){
            printf("range jam salah\n");
            return 0;
        }
    } else {
        return 0;
    }

    printf("argumen sudah benar lur\n");

    pid_t pid, sid;

    pid = fork();

    if (pid < 0){
      exit(EXIT_FAILURE);
    }

    if (pid > 0){ 
      exit(EXIT_SUCCESS);
    }
    umask(0);

    sid = setsid();
    if (sid < 0){
      exit(EXIT_FAILURE);
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) 
    {
      time_t waktu;
      struct tm* tm_skrg;  

      waktu = time(NULL);
      tm_skrg = localtime(&waktu);

      if ((tm_skrg->tm_sec == sec || sec == jalan) && (tm_skrg->tm_min == min || min == jalan) 
        && (tm_skrg->tm_hour == hour || hour == jalan))
      {
        pid_t child_id;
        child_id = fork();

        int status;

        if (child_id == 0)
        {    
          char *argexec[] = {"bash", argv[4], NULL};
          execv("/bin/bash", argexec);
        }
        else 
          while ((wait(&status)) > 0);
      }

      sleep(1);
    }

}
