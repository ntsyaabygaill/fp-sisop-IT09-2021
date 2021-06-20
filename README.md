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

**SERVER**
```C
else if (strcmp(fin,"2")==0){
                fin = strtok(NULL," ");
                if (strcmp(fin,"sudo")==0){
                    printf("use sudo\n");
                    send(newSocket, "use_bener", strlen("use_bener"), 0);
                    fin = strtok(NULL," ");
                    strcpy(database,fin);
                    printf("database : %s\n",database);
                }
                else {
                    strcpy (use_kred,fin);
                    printf("use not sudo : %s\n",use_kred);
```
**CHECK GRANT**
```C
		    //CHECK grant
                    char * buff3 = 0;
                    char *ret3={0};
                    long length;
                    FILE * f = fopen ("databases/grant.txt", "rb");

                    if (f)
                    {
                        fseek (f, 0, SEEK_END);
                        length = ftell (f);
                        fseek (f, 0, SEEK_SET);
                        buff3 = malloc (length);
                    if (buff3)
                    {
                        fread (buff3, 1, length, f);
                    }
                    fclose (f);
                    }
                    ret3 = strstr(buff3,use_kred);
                    if (ret3){
                        send(newSocket, "use_bener", strlen("use_bener"), 0);
                        printf("use database\n");
                        fin = strtok(NULL," ");
                        strcpy(database,fin);
                        printf("database : %s\n",database);
                    }
                    else {
                        send(newSocket, "use_salah", strlen("use_salah"), 0);
                        printf("grant gaada\n");
                    }
                    //END check grant
```

**CLIENT**

```C
 else if (strcmp(command, "USE")==0){
                scanf("%s",database);
                //sudo
                if (permission==0){
                    potong = strtok(database,";");
                    strcpy(buffer,"2 ");
                    strcat(buffer,"sudo ");
                    strcat(buffer,database);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
                //not sudo
                else{
                    strcpy(buffer,"2 ");
                    potong = strtok(database,";");
                    strcat(buffer,database);
                    strcat(buffer,":");
                    strcat(buffer,kred_uname);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
                bzero(buffer, sizeof(buffer));
                recv(clientSocket, buffer, 1024, 0);
                //printf ("\nbuffer_use : %s\n",buffer);
                if(strcmp(buffer,"use_bener")==0){
                    printf("use database : %s\n",database);
                }
                else if (strcmp(buffer,"use_salah")==0){
                    printf("unauthorized to use this database\n");
                }
                continue;
            }

```

##### - GRANT PERMISSION

**SERVER**
```C
else if (strcmp(fin,"3")==0){
                fp = fopen("databases/grant.txt", "a+");
                fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("%s\n",fin);
                strcpy(buffer,fin);
            }
```

**CLIENT**
```C
 else if (strcmp(command, "GRANT")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                scanf("%s",dump2);
                scanf("%s",user);
                strcpy(buffer,"3 ");
                strcat(buffer,database);
                strcat(buffer,":");
                strcat(buffer,user);
                potong = strtok(buffer,";");
                strcpy(buffer,potong);
                if (permission==0)
                    send(clientSocket, buffer, strlen(buffer), 0);
                else
                    printf("Unauthorized\n");
                    continue;
            }
```
#### DDL [ Data Definition Language ]
##### - CREATE DATABASE 
**SERVER**
```C
else if (strcmp(fin,"4")==0){
                fin = strtok(NULL," ");
                strcpy(makedb,"databases/");
                strcat(makedb,fin);
                mkdir(makedb,0700);
                fin = strtok(NULL," ");
                fp = fopen("databases/grant.txt", "a+");
                //fin = strtok(NULL," ");
                strcat(fin,"\n");
                fputs(fin,fp);
                fclose(fp);
                printf("Create Database %s\n",fin);
            }
```

**CLIENT**
```C
else if (strcmp(tipe,"DATABASE")==0){
                    scanf("%s",database);
                    potong = strtok(database,";");
                    strcpy(buffer,"4 ");
                    strcat(buffer,database);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    if (permission==0){
                        strcat(buffer,":");
                        strcat(buffer,"sudo");
                    }
                    else{
                        strcat(buffer,":");
                        strcat(buffer,kred_uname);
                    }
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
```

##### - CREATE TABLE 
**SERVER**
```C
 else if (strcmp(fin,"5")==0){
                fin = strtok(NULL," ");
                char table_name[100];
                strcpy(table_name,fin);
                printf("Create TABLE (nama) : %s\n",fin);
                fin = strtok(NULL," ");
                fin = strtok(NULL,"(");

                char string[2000];
                strcpy(string,fin);
                const char s[2] = " ";
                char token;
                char final[1000]={0};
                int i=0;

                / get the first token /
                token = strtok(string, s);

                / walk through other tokens */
                while( token != NULL ) {
                    if (strcmp(token,")")==0)
                        break;
                    if (i%2==0){
                        strcat(final,token);
                        strcat(final,", ");
                    }

                    token = strtok(NULL, s);
                    i++;
                }
                printf("final column : %s\n",final);
                FILE *fpt;
                char fpath[1000]={0};
                strcpy(fpath,"databases/");
                strcat(fpath,database);
                strcat(fpath,"/");
                strcat(fpath,table_name);
                strcat(fpath,".csv");
                fpt = fopen(fpath, "a+");
                strcat(final,"\n");
                fprintf(fpt,final);
                fclose(fpt);
            }
```

**CLIENT**
```C
 else if (strcmp(tipe,"TABLE")==0){
                    scanf("%s",database);
                    gets(table_cnt);
                    potong = strtok(table_cnt,";");
                    strcpy(buffer,"5 ");
                    strcat(buffer,database);
                    strcat(buffer," ");
                    strcat(buffer, table_cnt);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
```
##### - DROP [DATABASE | TABLE | COLUMN]

Untuk Fungsi DROP pada sisi client diawali dengan syntax
            ```C
	    else if (strcmp(command, "DROP")==0){
                scanf("%s",tipe
	    ```
**DROP DATABASE**
**SERVER**
```C
  else if (strcmp(fin,"6")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                fin = strtok(NULL, " ");
                strcpy(drop_db,"databases/");
                strcat(drop_db,fin);
                printf("database drop : %s\n",drop_db);
                strcpy(cmd,"rm -r ");
                strcat(cmd,drop_db);
                system(cmd);
                // char *argv[] = {"rm", "-r",drop_db,NULL};
                // execv("/bin/rm", argv);
            }
```
**CLIENT**
```C
  if (strcmp(tipe,"DATABASE")==0){
                    scanf("%s",database);
                    strcpy(buffer,"6 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
```
**DROP TABLE**
**SERVER**
```C
 else if (strcmp(fin,"7")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                fin = strtok(NULL, " ");
                strcpy(drop_db,"databases/");
                strcat(drop_db,database);
                strcat(drop_db,"/");
                strcat(drop_db,fin);
                strcat(drop_db,".csv");
                printf("table drop ini : %s\n",drop_db);
                strcpy(cmd,"rm ");
                strcat(cmd,drop_db);
                system(cmd);
            }
```

**CLIENT**
```C
else if (strcmp(tipe,"TABLE")==0){
                    scanf("%s",database);
                    strcpy(buffer,"7 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
```
**DROP COLUMN**
**SERVER**
```C
else if (strcmp(fin,"8")==0){
                char drop_db[1000]={0};
                char cmd[1000]={0};
                char col[1000]={0};
                char tab[1000]={0};
                char snum[5]={0};
                char oldname[100];
                char newname[100];
                char jalur[100];
                fin = strtok(NULL, " ");
                strcpy(col,fin);
                fin = strtok(NULL, " ");
                strcpy(tab,"databases/");
                strcat(tab,database);
                strcat(tab,"/");
                strcat(tab,fin);
                strcat(tab,".csv");
                printf("Drop table (database): %s\n",database);
                printf("Drop table (table): %s\n",tab);
                printf("Drop table (column): %s\n",col);

                FILE* stream = fopen(tab, "r");

                char line[1024];
                fgets(line, 1024, stream);
                puts(line);
                const char s[3] = ", ";
                char token;
                char pembanding[100];
                strcpy(pembanding,col);
                int i =1;

                / get the first token /
                token = strtok(line, s);

                / walk through other tokens */
                while( token != NULL ) {
                    //printf( " %s\n", token );
                    if(strcmp(pembanding,token)==0){
                        printf("field ke : %d\n",i);
                        break;
                    }

                    token = strtok(NULL, s);
                    i++;
                }
                //cut -d, -f4 --complement MyFile.csv > Out.csv
                sprintf(snum, "%d", i);
                strcpy (cmd,"cut -d, -f");
                strcat (cmd,snum);
                strcat (cmd," --complement ");
                strcat (cmd,tab);
                strcat (cmd," > databases/");
                strcat (cmd,database);
                strcat (cmd,"/out.csv");
                system(cmd);
                strcpy(cmd,"rm ");
                strcpy(cmd,tab);
                system(cmd);
                strcpy(jalur,"databases/");
                strcat(jalur,database);
                strcat(jalur,"/");
                strcpy(oldname,jalur);
                strcat(oldname,"out.csv");
                strcpy(newname,tab);
                rename(oldname, newname);
            }
```

**CLIENT**
```C
else if (strcmp(tipe,"COLUMN")==0){
                    char collumn[100];
                    scanf("%s",collumn);
                    scanf("%s",dump1);
                    scanf("%s",database);
                    strcpy(buffer,"8 ");
                    strcat(buffer,collumn);
                    strcat(buffer," ");
                    strcat(buffer,database);
                    //printf("%s\n",buffer);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    //printf("%s\n", collumn);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    continue;
                }
```
#### DML [ Data Manipulation Language ]
##### - INSERT INTO

**SERVER**
```C
else if (strcmp(fin,"9")==0){
                //printf("Insert Into : %s\n",buffer);
                fin = strtok(NULL," ");
                char table_name[100];
                strcpy(table_name,fin);
                printf("INSERT nih : %s\n",fin);
                fin = strtok(NULL," ");
                fin = strtok(NULL,"(");

                char string[2000];
                strcpy(string,fin);
                const char s[2] = " ";
                char token;
                char final[1000]={0};
                int i=0;

                / get the first token /
                token = strtok(string, s);

                / walk through other tokens */
                while( token != NULL ) {
                    if (strcmp(token,")")==0)
                        break;

                    strcat(final,token);
                    //strcat(final,", ");

                    token = strtok(NULL, s);
                    i++;
                }
                printf("final column : %s\n",final);
                FILE *fpt;
                char fpath[1000]={0};
                strcpy(fpath,"databases/");
                strcat(fpath,database);
                strcat(fpath,"/");
                strcat(fpath,table_name);
                strcat(fpath,".csv");
                fpt = fopen(fpath, "a+");
                strcat(final,"\n");
                fprintf(fpt,final);
                fclose(fpt);

            }
```

**CLIENT**
```C
  else if (strcmp(command, "INSERT")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                gets(table_cnt);
                potong = strtok(table_cnt,";");
                strcpy(buffer,"9 ");
                strcat(buffer,database);
                strcat(buffer," ");
                strcat(buffer, table_cnt);
                send(clientSocket, buffer, strlen(buffer), 0);
                continue;
            }
```
##### - UPDATE

**SERVER**
```C

```

**CLIENT**
```C

```
##### - DELETE FROM

**SERVER**
```C
 else if (strcmp(fin,"10")==0){
                char tbl[100]={0};
                fin = strtok(NULL," ");
                strcpy(tbl,"databases/");
                strcat(tbl,database);
                strcat(tbl,"/");
                strcat(tbl,fin);
                strcat(tbl,".csv");
                printf ("Delete ini : %s\n",tbl);
                FILE* stream = fopen(tbl, "r");

                char line[1024];
                fgets(line, 1024, stream);
                puts(line);
                fclose(stream);

                FILE *fpt2;
                // strcat(line,"\n");
                fpt2 = fopen(tbl, "w+");
                fprintf(fpt2,line);
                fclose(fpt2);
            }

```

**CLIENT**
```C
 else if (strcmp(command, "DELETE")==0){
                scanf("%s",dump1);
                scanf("%s",database);
                strcpy(buffer,"10 ");
                strcat(buffer,database);
                potong = strtok(buffer,";");
                strcpy(buffer,potong);
                send(clientSocket, buffer, strlen(buffer), 0);
                continue;
            }
```
##### - SELECT

**SERVER**
```C
else if (strcmp(fin,"11")==0){
                char tbl[100]={0};
                char isicsv[100]={0};
                fin = strtok(NULL," ");
                strcpy(tbl,"databases/");
                strcat(tbl,database);
                strcat(tbl,"/");
                strcat(tbl,fin);
                strcat(tbl,".csv");
                printf ("Select ini : %s\n",tbl);
                FILE* stream = fopen(tbl, "r");

                char line[1024];
                while (fgets(line, 1024, stream))
                {
                    // char* tmp = strdup(line);
                    // printf("ISI : %s\n",tmp);
                    // // NOTE strtok clobbers tmp
                    // free(tmp);
                    strcat(isicsv,line);
                }
                fclose(stream);
                printf("Isi : %s\n",isicsv);
                send(newSocket, isicsv, strlen(isicsv), 0);
            }

```

**CLIENT**
```C
//SELECT
            else if (strcmp(command, "SELECT")==0){
                char isicsv[100]={0};
                scanf("%s",tipe);
                //SELECT *
                if (strcmp(tipe,"*")==0){
                    scanf("%s",dump1);
                    scanf("%s",database);
                    strcpy(buffer,"11 ");
                    strcat(buffer,database);
                    potong = strtok(buffer,";");
                    strcpy(buffer,potong);
                    send(clientSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                    recv(clientSocket, buffer, 1024, 0);
                    strcpy(isicsv,buffer);
                    printf("isi database :\n%s\n",isicsv);
                    continue;
                }
                //END SELECT *
            }
            //END SELECT
```
##### - WHERE 

**SERVER**
```C

```

**CLIENT**
```C

```
#### LOGGING 

**SERVER**
```C

```

**CLIENT**
```C

```
#### RELIABILITY

**SERVER**
```C

```

**CLIENT**
```C

```
