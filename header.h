#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>


struct product {
    string name;
    int quantity;
    int price;
};

struct manage {
    string name_product;
    int quantity;
    string name_staff;
};


// Khai báo các hàm của Thông

// Khai báo các hàm của Thành

// Khai báo các hàm của Long
void tra_cuu_danh_sach(int, product[]);
void tra_cuu_vi_tri(char[], int, product[], char*, int*, int*);
void tinh_nang_them (product[], manage[], int*, int*, int*, int*, char[]);
void them(char[], int, int, int*, product[], int*, int*, manage[], int*, char, int*);
void tinh_nang_tra_cuu (product[], int*);

// Khai báo các hàm của Thiên




#endif // HEADER_H
