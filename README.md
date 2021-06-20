# fp-sisop-IT09-2021

Nama Anggota | NRP
------------------- | --------------		
Daniel Evan | 05311940000016
Natasya Abygail N | 05111940000020
Muhammad Naufal Imantyasto | 05111940000041

## List of Contents :
- [AUTENTIKASI](####AUTENTIKASI)
	- [CREATE USER](#####CREATE USER)
	- [1b](#1B)
	- [1c](#1C)
	- [1d](#1D)
	- [1e](#1E)
	- [1f](#1F)
	- [1g](#1G)
	- [1h](#1H)
- [No 2](#Cara-Pengerjaan)
	- [2a](#2A)
	- [2b](#2B)
	- [2c](#2C)
- [No 3](#Cara-Pengerjaan)
	- [3a](#3A)
	- [3b](#3B)
	- [3c](#3C)
	- [3d](#3D)
	- [3e](#3E)

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
#### AUTENTIKASI
##### CREATE USER

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
