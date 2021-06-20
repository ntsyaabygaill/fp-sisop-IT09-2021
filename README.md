# fp-sisop-IT09-2021

Nama Anggota | NRP
------------------- | --------------		
Daniel Evan | 05311940000016
Natasya Abygail N | 05111940000020
Muhammad Naufal Imantyasto | 05111940000041

## List of Contents :
- [AUTENTIKASI](####AUTENTIKASI)
- [AUTHORISASI](####AUTHORISASI)
- [DDL](####DDL)
- [DML](####DML)
- [LOGGING](####LOGGING)
- [RELIABILITY](####RELIABILITY)
- [EXTRA](####EXTRA)


## SOAL FP ( Sistem Database Sederhana )

### Bagaimana Program Diakses

- Program server berjalan sebagai daemon

- Untuk bisa akses console database, perlu buka program client (kalau di linux seperti command mysql di bash)

- Program client dan utama berinteraksi lewat socket

- Program client bisa mengakses server dari mana aja


**DIRECTORY STRUCTURE**

*Note : Penamaan dari program bebas*

```txt
# Struktur server (ketika program dijalankan)

[folder_server_database]
-[program_database]
-databases/
--[nama_database]/  → Directory
---[nama_tabel]         → File
```
Contoh struktur untuk server :
```txt
databaseku/
-program_databaseku
-databases/
--database1/
---table11
---table12
--database2/
---table21
---table22
---table23
```

### Bagaimana Database Digunakan
	- AUTENTIKASI
		- SUDO
		- CREATE USER
	- AUTHORISASI
		- USE
		- GRANT PERMISSION
	- DDL [ Data Definition Language ]
		- CREATE DATABASE 
		- CREATE TABLE 
		- DROP [DATABASE | TABLE | COLUMN]
	- DML [ Data Manipulation Language ]
		- INSERT INTO
		- UPDATE
		- DELETE FROM
		- SELECT
		- WHERE 
		- 
	- LOGGING 
	- RELIABILITY
			

## PENYELESAIAN

Dibawah ini adalah library yang digunakan :

**SERVER**
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>

#define PORT 4444
```
**CLIENT**
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
```

Dibawah ini adalah proses Connecting Socket antara Server dan Client :

**SERVER**
```C
int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
    printf("[-]Error in binding.\n");
    exit(1);
    }
    printf("[+]Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0){
    printf("[+]Listening....\n");
    }else{
    printf("[-]Error in binding.\n");
    }
  ```

**CLIENT**
```C
 int clientSocket, ret;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Client Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
    printf("[-]Error in connection.\n");
    exit(1);
    }
    printf("[+]Connected to Server.\n");
```

### Bagaimana Database Digunakan
#### AUTENTIKASI
##### - SUDO



##### - CREATE USER

**CLIENT**
```C
if(strcmp(tipe,"USER")==0){
                        scanf("%s",uname);
                        scanf("%s %s",dump1,dump2);
                        scanf("%s",password);
                        strcpy(buffer,"1 ");
                        strcat(buffer,uname);
                        strcat(buffer,":");
                        strcat(buffer,password);
                        potong = strtok(buffer,";");
                        strcpy(buffer,potong);
                        //check root
                        if (permission==0)
                            send(clientSocket, buffer, strlen(buffer), 0);
                        else
                            printf("Unauthorized\n");
                            continue;
                }
```
**SERVER**
```C
if (strcmp(fin,"1")==0){
                fp = fopen("databases/user.txt", "a+");
                fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("%s\n",fin);
                strcpy(buffer,fin);
            }
```

#### AUTENTIKASI
##### - USE
