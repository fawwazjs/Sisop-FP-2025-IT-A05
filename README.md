# Final Project Sistem Operasi IT

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok 5

Nama | NRP
--- | ---
Ahmad Wildan Fawwaz | 5027241001
Revalina Erica Permatasari | 5027241007
Theodorus Aaron Ugraha | 5027241056
Az Zahra Tasya Adelia | 5027241087

## Deskripsi Soal

> 13. PTHREAD A^B, B^A
    
    a. Program menerima 2 input dari user untuk variable A dan B

    b. Program menggunakan Threading untuk melakukan perhitungan, 1 Thread untuk A^B, 1 thread lagi untuk B^A.

    c.Tampilkan kedua hasil tersebut

### Catatan

> Tidak boleh menghitung A^B dan B^A secara sekuensial (satu per satu) dalam fungsi main utama. Sebaliknya, membuat dua thread terpisah. Thread Pertama: Akan bertanggung jawab penuh untuk menghitung nilai A^B. Thread Kedua: Akan bertanggung jawab penuh untuk menghitung nilai B^A.

Struktur repository:
```
├── src/                   # Source code C
   ├── pthread.c           # Program
```

## Pengerjaan

> a. Program menerima 2 input dari user untuk variable A dan B

**Teori**   

Tahap input merupakan tahap awal dari proses pengolahan yang terjadi pada sistem komputer, tahap ini berupa memasukan data ke dalam sistem komputer melalui proses input (Nur Alifah et al., 2023).

**Solusi**   
Dalam kode C, tulis script:
```c
    printf("Masukkan angka A: ");
    scanf("%d", &A);
    printf("Masukkan angka B: ");
    scanf("%d", &B);
```


> b. Program menggunakan Threading untuk melakukan perhitungan, 1 Thread untuk A^B, 1 thread lagi untuk B^A.

**Teori**

Threading adalah teknik pemrograman yang memungkinkan sebuah program menjalankan beberapa bagian kode secara bersamaan (paralel) dalam satu proses. Pada bahasa C, threading dapat diimplementasikan menggunakan pustaka POSIX Threads (pthread). Dengan threading, program dapat melakukan beberapa tugas secara simultan, sehingga meningkatkan efisiensi dan responsivitas, terutama pada sistem multiprosesor.

Pada kasus perhitungan A^B dan B^A, threading digunakan agar kedua operasi dapat berjalan secara paralel, bukan secara sekuensial. Setiap thread akan menjalankan fungsi yang berbeda secara independen, sehingga hasil perhitungan bisa diperoleh lebih cepat dan efisien.

**Solusi**

- Program menerima dua input integer dari user, yaitu A dan B.
- Dua buah thread dibuat menggunakan pustaka pthread:
    - Thread pertama bertugas menghitung A^B.
    - Thread kedua bertugas menghitung B^A.
- Setiap thread menjalankan fungsi yang menerima argumen berupa struct berisi base, exponent, dan tempat hasil.
- Setelah kedua thread selesai, hasil perhitungan ditampilkan di main thread.
- Program juga menangani kasus error seperti input tidak valid, hasil tidak terdefinisi (misal 0^0, 0^negatif, atau eksponen negatif), dan overflow hasil perhitungan.

Contoh kode pembuatan thread:
```c
pthread_t tid[2];
ThreadArgs args_ab = {A, B, 0, 1};
ThreadArgs args_ba = {B, A, 0, 2};
pthread_create(&tid[0], NULL, thread_ab_func, (void *)&args_ab);
pthread_create(&tid[1], NULL, thread_ba_func, (void *)&args_ba);
```
Setelah kedua thread selesai, hasil diambil dari struct dan ditampilkan ke layar.

> c. Tampilkan kedua hasil tersebut

**Teori**

Setelah proses perhitungan selesai dilakukan oleh masing-masing thread, hasil dari perhitungan A^B dan B^A perlu ditampilkan kepada pengguna. Penampilan hasil ini penting agar pengguna dapat melihat output dari operasi yang telah dilakukan.

**Solusi**

Hasil perhitungan yang telah disimpan dalam variabel atau struktur data tertentu oleh masing-masing thread, perlu digabungkan dan ditampilkan. Penggabungan hasil ini dilakukan di thread utama setelah kedua thread perhitungan selesai dieksekusi.

Contoh kode untuk menampilkan hasil:
```c
printf("Hasil %d^%d = %d\n", A, B, hasil_ab);
printf("Hasil %d^%d = %d\n", B, A, hasil_ba);
```

**Video Menjalankan Program**

https://github.com/user-attachments/assets/1c409ae0-3ad5-44a1-848f-df9ceb5baca8

## Daftar Pustaka

1. Nur Alifah, Deanda, G.V., Juniwan dan Aribowo, D., 2023. Peran teknologi input dan output dalam pengembangan perangkat keras dan perangkat lunak komputer. _Jurnal Kendali Teknik dan Sains_, 1(4):123–136. [https://doi.org/10.59581/jkts-widyakarya.v1i4]
2. Buttlar, D., Farrell, J.P., & Nichols, B. (1996). _Pthreads Programming: A POSIX Standard for Better Multiprocessing_. O'Reilly Media. [https://books.google.co.in/books?id=oMtCFSnvwmoC&printsec=frontcover#v=onepage&q&f=false]
3. Saha, S., & Mukherjee, N. (2017). Multithreading and Parallel Computing in C/C++. _International Journal of Computer Applications_, 162(7), 1-6. [https://www.researchgate.net/publication/385700631_Parallelism_and_Multithreading_in_High-Performance_Computing]
4. Drepper, U. (2007). What Every Programmer Should Know About Memory. _ACM Queue_, 6(9), 30-53. [https://www.researchgate.net/publication/51992176_What_Every_Programmer_Should_Know_About_Memory]