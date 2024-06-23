#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>

struct product {
    char name[50];
    int quantity;
    int price;
};

struct manage {
    char name_product[50];
    int quantity;
    char name_staff[100];
};

// Khai báo các hàm của Thông
void menu_0();
void menu_main();
void menu_6(int);
void yesno_question(char[], int*);
// Khai báo các hàm của Thành

// Khai báo các hàm của Long
void tra_cuu_danh_sach(int, struct product[]);
void tra_cuu_vi_tri(char[], int, struct product[], char*, int*, int*);
void tinh_nang_them (struct product[], struct manage[], int*, int*, int*, int*, char[]);
void them(char[], int, int, int*, struct product[], int*, int*, struct manage[], int*, char, int*);
void tinh_nang_tra_cuu (struct product[], int*);

// Khai báo các hàm của Thiên
int tinh_toan(char[][100], int[], int, int, struct product[]);
void tinh_nang_tinh_toan (struct product[], struct manage[], int*, int*, int*, int*, char[]);
void tinh_nang_quan_ly(struct product[], int, struct manage[], int*, int*, int*, int*, int*, int*, char[][100]);


#endif // HEADER_H
