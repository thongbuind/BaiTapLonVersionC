#include "header.h"
void tinh_nang_them (product p[], manage m[], int* index_manage, int* number_in, int* money_out, int* count, char name_staff_tmp[]) {
    char name_add[100];
    int quantity_add;
    int price;
    int tmp = *count;
    int check = 0;
    int checkcheck = 0;
    printf("   Nhap ten san pham muon them: ");
    fgets(name_add, sizeof(name_add), stdin);
    name_add[strcspn(name_add, "\n")] = '\0';
    // vòng do while để nhập số lượng thêm vào kho
    do {
        printf("   Nhap so luong: ");
        scanf("%d", &quantity_add);
        getchar();
    } while (quantity_add <= 0);
    // vòng do while để nhập số lượng thêm vào kho
    do {
        printf("   Nhap gia tien cua san pham: ");
        scanf("%d", &price);
        getchar();
    } while (price <= 0);
    // check xem sản phẩm đã có trong kho chưa
    // nếu có trong kho rồi thì hỏi có muốn nhập kho không
    for (int i=0; i<*count; i++) {
        if (strcmp(name_add, p[i].name) == 0) {
            char q[100];
            int ynq;
            do {
                printf("   San pham nay da co san trong kho, ban co muon nhap kho khong(yes/no): ");
                fgets(q, sizeof(q), stdin);
                q[strcspn(q, "\n")] = '\0';
                yesno_question(q, &ynq);
                if (ynq==1) {
                    nhap_kho(name_add, quantity_add, *count, p, &check, money_out, m, index_manage, name_staff_tmp, number_in);
                }
                checkcheck=1;
            } while (ynq!=0 && ynq!=1);
            break;
        }
    }
    // nếu chưa có trong kho thì thêm vào
    if (checkcheck==0) {
        them(name_add, quantity_add, price, count, p, &check, money_out, m, index_manage, name_staff_tmp, number_in);
    }
    if (*count > tmp) {
        check=1;
    }
    if (check==1) {
        printf("   ✅Nhap kho thanh cong.\n");
    } else {
        printf("   ❌San pham khong duoc them vao kho, xin thu lai.\n");
    }
}

void tra_cuu_danh_sach(int count, product p[]) {
    printf("      Tong mat hang: %d\n", count);
    printf("  |STT|    TEN MAT HANG    |SO LUONG|GIA TIEN|\n");
    for (int i = 0; i < count; i++) {
        printf("  |%2d |%-20s|%5d   |%8.2d|\n", i + 1, p[i].name, p[i].quantity, p[i].price);
    }
}

void tra_cuu_vi_tri (char name[], int count, product p[], char* y, int* x, int* check) {
    for (int i=0; i<count; i++) {
        if (strcmp(name, p[i].name) == 0) {
            if (p[i].price<100000) {
                strcpy(y, "A");
            } else if (p[i].price<=1000000) {
                strcpy(y, "B");
            } else if (p[i].price<=10000000) {
                strcpy(y, "C");
            } else {
                strcpy(y, "D");
            }
            if (p[i].quantity<30) {
                *x = 1;
            } else if (p[i].quantity<=70) {
                *x = 2;
            } else if (p[i].quantity<=100) {
                *x = 3;
            } else {
                *x = 4;
            }
            *check=1;
        }
    }
}
void them (char name[], int quantity_add, int price, int* count, product p[], int* check, int* money_out, manage m[], int* index_manage, char name_staff_tmp[], int* number_in) {
    //p[count] = {name, quantity_add, price};
    strcpy(p[*count].name, name);
    p[*count].quantity = quantity_add;
    p[*count].price = price;
    *count+=1;
    *money_out += price * quantity_add;
    //m[index_manage] = {name, quantity_add, name_staff_tmp};
    strcpy(m[*index_manage].name_product, name);
    m[*index_manage].quantity = quantity_add;
    strcpy(m[*index_manage].name_staff, name_staff_tmp);
    *index_manage+=1;
    *number_in+=1;
}
void tinh_nang_tra_cuu (product p[], int* count) {
    int q;
    // hiển thị menu cho người dùng chọn
    printf("   Ban muon tra cuu gi?\n");
    printf("       1.Danh sach\n");
    printf("       2.Vi tri hang hoa\n");
    do {
        printf("   Chon thao tac: ");
        scanf("%d", &q);
    } while (q!=1 && q!=2);
    // hàm if else
    if (q==1) {
        tra_cuu_danh_sach(*count, p);
        getchar();
    } else if (q==2) {
        char name_search[100];
        char y;
        int x;
        int check=0;
        printf("   Nhap ten san pham muon tra cuu: ");
        getchar();
        //getline(cin, name_search);
        fgets(name_search, sizeof(name_search), stdin);
        name_search[strcspn(name_search, "\n")] = '\0';
        tra_cuu_vi_tri(name_search, *count, p, &y, &x, &check);
        if (check==1) {
            //cout << "   Vi tri san pham: " << y << x << endl;
            printf("   Vi tri san pham: %c%d\n", y, x);
        } else {
            //cout << "   ❌Khong nhan dien duoc san pham" << endl;
            printf("   ❌Khong nhan dien duoc san pham\n");
        }
    }
}

