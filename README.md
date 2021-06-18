# fp-sisop-IT09-2021

Nama Anggota | NRP
------------------- | --------------		
Daniel Evan | 05311940000016
Natasya Abygail N | 05111940000020
Muhammad Naufal Imantyasto | 05111940000041

## List of Contents :
- [AUTENTIKASI](####AUTENTIKASI)
	- [1a](#1A)
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
##### 
