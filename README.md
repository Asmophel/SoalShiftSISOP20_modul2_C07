# SoalShift_Modul 1 Kelompok C07
##### Fandi Wahyu R - 05111840000108, Brananda Denta WP - 05111840000143

### Outline
+ [Soal 1](#soal-1)
+ [Soal 2](#soal-2)
    * [2a](#2a)
    * [2b](#2b)
    * [2c](#2c)
    * [2d](#2d)
    * [2e](#2e)
+ [Soal 3](#soal-3)
    * [3a](#3a)
    * [3b](#3b)
    * [3c](#3c)
    * [3d](#3d)

## Soal 1
### Soal
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh

Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

## Source Code

```
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
```

### Penjelasan
```
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
```
berfungsi untuk mengecek apakah argumen merupakan angka, dengan cara mengecek tiap index di array

```
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
```
if pertama untuk mengecek, apabila argumen berupa ```*```, sec = jalan = 1, jika bukan ```*``` maka panggil fungsi ```CheckNum```, jika fungsi mereturn 0, berarti argumen adalah angka, lalu masukkan argumen ke variabel sec dengan menggunakan atoi, selanjutnya cek apakah argumen sudah memenuhi range dari detik yaitu 0 - 59, jika salah print kata" tersebut, jika semua salah, return o. Syntax diatas dapat digunakan juga untuk argumen ke-2 dan ke-3.

```
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
```
merupakan daemon

```
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
```
untuk mendapatkan fungsi waktu, gunakan directory time.h, lalu masukkan dalam variabel sec, min, dan hour. cek apakah sec, min, dan hour sudah benar. jika sudah benar, child akan menjalankan bash ke directory yang sudah dimasukkan di argumen ke 4.

## Soal 2
### Soal
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk
menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

### penyelesaian
### 2a

membuat folder menggunakan mkdir pada terminal bernama folder khusus
```
mkdir folderkhusus
```

membuat program c yang ada dalam folderkhusus

isi dari program c nya adalah membuat daemon lalu loop yang ada dalam daemon tersebut diisi dengan fork.
isi dari fork tersebut adalah sebagai berikut

membuat variabel waktufile yang akan menampung waktu pada saat itu, lalu menggunakan fungsi strftime untuk mengambil waktu pada saat itu

```
       time_t waktufile;
    struct tm *lt;
    time(&waktufile);
    lt = localtime(&waktufile);
    char date[26], namafile[100];
    strftime(namafile, 100, "%Y-%m-%d_%H:%M:%S", lt);
```


lalu child yang ada di fork tersebut membuat folder dengan ketentuan seperti pada soal
```
        if(child_id2 == 0){
        char *argv[] = {"mkdir", namafile, NULL};
        execv("/bin/mkdir", argv);
```

### 2b
membuat loop sebanyak 20. isi dari loop tersebut adalah mendownload gambar dengan ketentuan pada soal. diberi sleep(5) karena jeda antar mendownload gambar adalah 5 detik
```
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
```
### 2c
lalu membuat fork lagi dan child dari fork tersebut bekerja untuk menzip folder yang sudah selesai mendownload total 20 gambar
```
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
```

dan untuk menghapus folder yang sudah selesai di zip digunakan command rm
```
        int status5;
        while(wait(&status5) > 0);
        char *argv[] = {"rm", "-rf", curFolder, NULL};
        execv("/bin/rm", argv);
```

lalu menambahkan sleep agar program tersebut di jeda selama 30 detik
```
    sleep(30);
```

### 2d
membuat killer
```
  temp = fopen("killer.sh", "w");
```
meremove
```
  fputs("rm $0\n", temp);
```

### 2e

mendeteksi input argumen dengan menggunakan strcmp
```
  if(strcmp(argb[1], "-a") == 0){
    ModeA();
  }
  if(strcmp(argb[1], "-b") == 0){
    ModeB();
  }
```

untuk supaya jika argumen -a akan memberhentikan program langung menggunakan
```
 fputs("killOrder=$(echo $(pidof soal2coba))\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  ```

untuk supaya jika argumen -b maka akan membiarkan proses download sampai selesai dan di zip lalu remove folder lalu di stop
```
  fputs("killOrder=$(echo $(pidof soal2coba))\n", temp);
  fputs("killOrder=${killOrder##* }\n", temp);c
  fputs("kill -9 $killOrder\n", temp);
```


## Soal 3
### soal
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).

a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.

c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.

d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk
### penyelesaian
### 3a

membuat program c

membuat fork di dalam program c lalu di dalam child dari fork tersebut diisi dengan perintah execv yang berguna untuk membuat folder indomie
```
	if (child_1 == 0) {
	// child 1
		char *argv[] = {"mkdir", "-p", "/home/denta/modul2/indomie", NULL};
		execv("/bin/mkdir", argv);
  }
```

membuat fork baru dan child diisi dengan membuat folder sedap
```
		if (child_1 == 0) {
		// child 2
			sleep(5);
			char *argv[] = {"mkdir", "-p", "/home/denta/modul2/sedaap", NULL};
			execv("/bin/mkdir", argv);
		}
```

### 3b
membuat fork baru lalu di dalam child yang ada di fork baru ini diisi dengan perintah execv yang berguna untuk meng-unzip folder zip yang sudah di download pada drive modul 2
```
			if (child_1 == 0) {
			// child 3
				//while (wait(&status) > 0);
				chdir("/home/denta/modul2");
				char *zip[] = {"unzip", "/home/denta/modul2/jpg.zip", NULL};
				execv("/usr/bin/unzip", zip);
			}
```
### 3c
memindahkan semua file dan semua directory menggunakan S_IFDIR
```
if (stat(path, &filetype) == 0) {
							if (filetype.st_mode & S_IFDIR) {
								if (child_1 = fork() == 0) {
									char *move1[] = {"mv", path, "/home/denta/modul2/indomie/", NULL};
									execv("/bin/mv", move1);
								}
							} else {
								if (child_1 = fork() == 0) {
									char *move2[] = {"mv", path, "/home/denta/modul2/sedaap/", NULL};
									execv("/bin/mv", move2);
								} 
```

### 3d
membuat file coba1.txt di setiap folder yang ada dalam indomie dan 3 detik kemudian membuat file coba2.txt
```
						strcpy(location, "/home/denta/modul2/indomie/");
						strcat(location, makefile->d_name);
			
						if (child_1 = fork() > 0) {
							chdir(location);
							char *mktxt1[] = {"touch", "coba1.txt", NULL};
							execv("/bin/touch", mktxt1);
						} sleep(3);
						if (child_1 = fork() > 0) {
                            // sleep(3);
							chdir(location);
							char *mktxt2[] = {"touch", "coba2.txt", NULL};
							execv("/bin/touch", mktxt2);
						}

```
