#include <stdio.h>
#include <string.h>
#include <regex.h>

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

void menu_0();
void menu_main();
void menu_6(int);
void tra_cuu_danh_sach(int, product[]);
void tra_cuu_vi_tri(char[], int, product[], char*, int*, int*);
void them(char[], int, int, int*, product[], int*, int*, manage[], int*, char, int*);
void xuat_kho(char[], int, int, product[], int*, int*, manage[], int*, char, int*);
void nhap_kho (char[], int, int, product[], int*, int*, manage[], int*, char[], int*);
int tinh_toan(char[][100], int[], int, int, product[]);
void yesno_question(char[], int*);

void tinh_nang_tra_cuu (product[], int*);
void tinh_nang_them (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_xuat_kho (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_nhap_kho (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_tinh_toan (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_quan_ly(product[], int, manage[], int*, int*, int*, int*, int*, int*, char[][100]);

void nidai_assistant (product[], int*, int*, int*, manage[], int*, char[], int*, int*);
void check_regex (char[], char[]);
int check_oders (char[]);
int check_yes_no (char[]);

int main() {
    product p[100];
    manage m[100];
    p[0] = {"sach giai tich", 19, 3000};
    p[1] = {"sach vat ly", 15, 23000};
    p[2] = {"sach tin hoc", 17, 20000};
    p[3] = {"cap sach", 16, 300000};
    p[4] = {"ao dong phuc", 61, 150000};
    p[5] = {"quan dong phuc", 61, 110000};
    p[6] = {"may chieu", 7, 1100000};
    int count = 7;
    int index_manage = 0;
    int number_in = 0;
    int number_out = 0;
    int total_money = 10000000;
    int money_in = 0;
    int money_out = 0;
    int option_0 = 0;
    int option_main = 0;
    int ynq0;
    char c[100];
    int index_staff = 0;
    char staff[20][100];
    menu_0();
    printf("Nhap thao tac: ");
    do {
        do {
            scanf("%d", &option_0);
            getchar();
            if (option_0 == 1) {
                printf("Nhap ten nhan vien: ");
                fgets(staff[index_staff], sizeof(staff[index_staff]), stdin);
                staff[index_staff][strcspn(staff[index_staff], "\n")] = '\0';
                char name_staff_tmp[50];
                for (int i=0; i<50; i++) {
                    name_staff_tmp[i] = staff[index_staff][i];
                }
                index_staff+=1;
                do {
                    menu_main();
                    do {
                        printf("Nhap thao tac: ");
                        scanf("%d", &option_main);
                        getchar();
                    } while (option_main > 6 && option_main < 1);
                    switch (option_main) {
                        case 1: {
                            tinh_nang_tra_cuu(p, &count);
                            break;
                        }
                        case 2: {
                            tinh_nang_them(p, m, &index_manage, &number_in, &money_out,&count, name_staff_tmp);
                            break;
                        }
                        case 3: {
                            tinh_nang_xuat_kho(p, m, &index_manage, &money_in, &number_out, &count, name_staff_tmp);
                            break;
                        }
                        case 4: {
                            tinh_nang_nhap_kho(p, m,&index_manage, &money_out, &number_in, &count, name_staff_tmp);
                            break;
                        }
                        case 5: {
                            tinh_nang_tinh_toan(p, m, &index_manage, &money_in, &number_out, &count, name_staff_tmp);
                            break;
                        }
                        case 6: {
                            tinh_nang_quan_ly(p, count, m, &total_money, &money_in, &money_out, &number_in, &number_out, &index_staff, staff);
                            break;
                        }
                        default:
                            printf("   ❌Khong xac dinh duoc lenh.\n");
                            break;
                    }
                    do {
                        printf("Ban muon tiep tuc khong(yes/no): ");
                        fgets(c, sizeof(c), stdin);
                        c[strcspn(c, "\n")] = '\0';
                        yesno_question(c, &ynq0);
                        if (ynq0==3) {
                            printf("❌Khong xac dinh duoc lenh.\n");
                        }
                    } while (ynq0==3);
                } while (ynq0==1);
            } else if (option_0 == 2) {
                break;
            }else if (option_0 == 3) {
                printf("Nhap ten nhan vien: ");
                fgets(staff[index_staff], sizeof(staff[index_staff]), stdin);
                staff[index_staff][strcspn(staff[index_staff], "\n")] = '\0';
                char name_staff_tmp[100];
                strcpy(name_staff_tmp, staff[index_staff]);
                index_staff+=1;
                // ///////////////////////////////////////////////////////////////
                nidai_assistant(p, &count, &money_out, &money_in, m, &index_manage, name_staff_tmp, &number_in, &number_out);
                // ///////////////////////////////////////////////////////////////
            } else {
                printf("❌Khong xac dinh duoc lenh, vui long nhap lai.\n");
            }
            menu_0();
            printf("Nhap thao tac: ");
        } while (option_0!=1 && option_0!=2);
    } while (option_0==1);
}

void menu_main() {
    printf("~~~~~~~ HE THONG QUAN LY XUAT NHAP KHO ~~~~~~~\n");
    printf("1. Tra cuu                 4. Nhap kho\n");
    printf("2. Them moi                5. Tinh toan\n");
    printf("3. Xuat kho                6. Quan ly\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void menu_0() {
    printf("~~~~~~~ HE THONG QUAN LY XUAT NHAP KHO ~~~~~~~\n");
    printf("      1. Dang nhap                2. Thoat\n");
    printf("               3. Tro ly ao ニダイ\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void menu_6(int total_money) {
    printf("~~~~~~~~~~~~~~~~~~ QUAN LY ~~~~~~~~~~~~~~~~~~~\n");
    printf("       Tong tien: %d VND\n", total_money);
    printf("1. Tien ra vao               3. Lich su xuat kho\n");
    printf("2. Nhan vien                 4. Lich su nhap kho\n");
    printf("5. Sap xep danh sach\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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

void xuat_kho (char name[], int quantity_out, int count, product p[], int* check, int* money_in, manage m[], int* index_manage, char name_staff_tmp[], int* number_out) {
    for (int i=0; i<count; i++) {
        if (strcmp(name, p[i].name) == 0) {
            if (p[i].quantity >= quantity_out) {
                p[i].quantity = p[i].quantity - quantity_out;
                *money_in += p[i].price * quantity_out;
                *check=1;
                //m[index_manage] = {name, -quantity_out, name_staff_tmp};
                strcpy(m[*index_manage].name_product, name);
                m[*index_manage].quantity = -quantity_out;
                strcpy(m[*index_manage].name_staff, name_staff_tmp);
                *index_manage+=1;
                *number_out+=1;
            } else {
                *check=3;
            }
        }
    }
}

void nhap_kho (char name[], int quantity_in, int count, product p[], int* check, int* money_out, manage m[], int* index_manage, char name_staff_tmp[], int* number_in) {
    for (int i=0; i<count; i++) {
        if (strcmp(name, p[i].name) == 0) {
            p[i].quantity = p[i].quantity + quantity_in;
            *money_out += p[i].price * quantity_in;
            *check=1;
            strcpy(m[*index_manage].name_product, name);
            m[*index_manage].quantity = quantity_in;
            strcpy(m[*index_manage].name_staff, name_staff_tmp);
            *index_manage+=1;
            *number_in+=1;
        }
    }
}

int tinh_toan (char name[][100], int quantity[], int index, int count, product p[]) {
    int sum=0;
    for (int i=0; i<index; i++){
        for (int j=0; j<count; j++) {
            if (strcmp(name[i], p[j].name) == 0) {
                sum += p[j].price * quantity[i];
            }
        }
    }
    return sum;
}

void yesno_question(char q[], int* ynq) {
    if (strcmp(q, "yes") == 0 || strcmp(q, "y") == 0 || strcmp(q, "co") == 0 || strcmp(q, "yesss") == 0 || strcmp(q, "ye") == 0 || strcmp(q, "yess") == 0 || strcmp(q, "1") == 0 || strcmp(q, "coo") == 0 || strcmp(q, "cooo") == 0 || strcmp(q, "coooo") == 0 || strcmp(q, "yessss") == 0) {
        *ynq = 1;
    } else if (strcmp(q, "no") == 0 || strcmp(q, "n") == 0 || strcmp(q, "khong") == 0 || strcmp(q, "noo") == 0 || strcmp(q, "nooo") == 0 || strcmp(q, "khongg") == 0 || strcmp(q, "0") == 0 || strcmp(q, "khonggg") == 0) {
        *ynq = 0;
    } else {
        *ynq = 3;
    }
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

void tinh_nang_xuat_kho(product p[], manage m[], int* index_manage, int* money_in, int* number_out, int* count, char name_staff_tmp[100]) {
    char name_out[100];
    int quantity_out;
    int check = 0;
    printf("   Nhap ten mat hang xuat kho: ");
    fgets(name_out, sizeof(name_out), stdin);
    name_out[strcspn(name_out, "\n")] = '\0';
    // Vòng do-while để nhập số lượng
    do {
        printf("   Nhap so luong: ");
        scanf("%d", &quantity_out);
        getchar();
    } while (quantity_out <= 0);
    // Dùng hàm xuất kho
    xuat_kho(name_out, quantity_out, *count, p, &check, money_in, m, index_manage, name_staff_tmp, number_out);
    if (check == 1) {
        printf("   ✅Xuat kho thanh cong.\n");
    } else if (check == 0) {
        printf("   ❌Khong ton tai hang hoa trong kho.\n");
    } else if (check == 3) {
        printf("   ❌Khong du so luong.\n");
    }
}

void tinh_nang_nhap_kho(product p[], manage m[], int* index_manage, int* money_out, int* number_in, int* count, char name_staff_tmp[]) {
    char name_in[100];
    int quantity_in;
    int check = 0;
    int price;
    printf("   Nhap ten mat hang nhap kho: ");
    fgets(name_in, sizeof(name_in), stdin);
    name_in[strcspn(name_in, "\n")] = '\0';
    // Dùng vòng do-while để nhập số lượng hợp lệ
    do {
        printf("   Nhap so luong: ");
        scanf("%d", &quantity_in);
        getchar();
    } while (quantity_in <= 0);
    nhap_kho(name_in, quantity_in, *count, p, &check, money_out, m, index_manage, name_staff_tmp, number_in);
    // Kiểm tra nhập kho thành công hay không
    if (check == 1) {
        printf("   ✅Nhap kho thanh cong.\n");
    } else {
        // Nếu không thành công thì tức là do sản phẩm chưa có sẵn trong kho, hỏi xem có muốn nhập kho hay không
        char q[10];
        int ynq;
        do {
            printf("   San pham nay chua co san trong kho, ban co muon them khong(yes/no): ");
            scanf("%s", q);
            getchar();
            yesno_question(q, &ynq);
            if (ynq == 1) {
                do {
                    printf("   Nhap gia san pham: ");
                    scanf("%d", &price);
                    getchar();
                    // them if
                } while (price <= 0);
                them(name_in, quantity_in, price, count, p, &check, money_out, m, index_manage, name_staff_tmp, number_in);
                printf("   ✅Them san pham thanh cong.\n");
            } else if (ynq == 2) {
                printf("   ❌San pham khong duoc them vao kho.\n");
            } else {
                printf("   ❌Khong xac dinh duoc lenh.\n");
            }
        } while (ynq != 0 && ynq != 1);
    }
}

void tinh_nang_tinh_toan (product p[], manage m[], int* index_manage, int* money_in, int* number_out, int* count, char name_staff_tmp[100]) {
    int index;
    int checkcheck;
    char q[100];
    // dùng vòng do while để nhập số lượng
    do {
        printf("   Nhap so luong mat hang can tinh: ");
        scanf("%d", &index);
        getchar();
        // them if
    } while (index <= 0);
    // phải khai báo biến ở đây vì index vừa mới nhập
    char name[index][100];
    int quantity[index];
    int check[index];
    int ynq;
    for (int i=0; i<index; i++) {
        check[i] = 0;
        // dùng vòng do while để nhập và check tên sp
        do {
            printf("   Nhap ten mat hang %d: ", i+1);
            fgets(name[i], sizeof(name[i]), stdin);
            name[i][strcspn(name[i], "\n")] = '\0';
            for (int j=0; j<*count; j++) {
                if (strcmp(name[i], p[j].name) == 0) {
                    check[i] = 1;
                }
            }
        } while (check[i] != 1);
        // dùng vòng do while để nhập số lượng
        do {
            check[i] = 1;
            printf("   Nhap so luong cua mat hang %d: ", i+1);
            scanf("%d", &quantity[i]);
            getchar();
            // kiểm tra số lượng có đủ trong kho không
            for (int j=0; j<*count; j++) {
                if (strcmp(name[i], p[j].name) == 0) {
                    if (quantity[i] > p[j].quantity) {
                        check[i] = 0;
                        printf("   ❌ So luong san pham khong du trong kho.\n");
                    }
                }
            }
        } while (quantity[i] <= 0 || check[i] == 0);
    }
    printf("   Thanh tien: %d VND\n", tinh_toan(name, quantity, index, *count, p));
    // hỏi xem muốn xuất kho những sản phẩm trên không
    do {
        printf("   Ban muon xuat hoa don khong? ");
        scanf("%s", q);
        getchar();
        yesno_question(q, &ynq);
        if (ynq==1) {
            for (int i=0; i<index; i++) {
                xuat_kho(name[i], quantity[i], *count, p, &checkcheck, money_in, m, index_manage, name_staff_tmp, number_out);
            }
            printf("   ✅ Xuat kho thanh cong.\n");
        } else if (ynq==3) {
            printf("   ❌ Khong xac dinh duoc lenh.\n");
        }
    } while (ynq==3);
}

void tinh_nang_quan_ly(product p[], int count, manage m[], int *total_money, int *money_in, int *money_out, int *number_in, int *number_out, int *index_staff, char staff[][100]) {
    // check xem nhân viên có được cấp quyền truy cập tính năng không
    if (strcmp(staff[*index_staff - 1], "quanly") == 0) {
        int option_6;
        *total_money = *total_money + *money_in - *money_out;
        menu_6(*total_money);
        
        do {
            printf("   Chon thao tac: ");
            scanf("%d", &option_6);
            getchar();
        } while (option_6 > 5 || option_6 < 1);
        
        switch (option_6) {
            case 1: {
                printf("       Tong tien chi ra: %d\n", *money_out);
                printf("       Tong tien thu vao: %d\n", *money_in);
                break;
            }
            case 2: {
                printf("           Tong so nhan vien lam viec: %d\n", *index_staff);
                printf("       |%2s|%-20s|\n", "STT", "TEN NHAN VIEN");
                for (int i = 0; i<*index_staff; i++) {
                    printf("       |%2d |%-20s|\n", i + 1, staff[i]);
                }
                break;
            }
            case 3: {
                int stt = 1;
                printf("       So lan xuat kho: %d\n", *number_out);
                printf("       |STT|    TEN MAT HANG    |SO LUONG|   TEN NHAN VIEN    |\n");
                for (int i = 0; i < (*number_out + *number_in); i++) {
                    if (m[i].quantity < 0) {
                        printf("       |%2d |%-20s|%-8d|%-20s|\n", stt++, m[i].name_product, -m[i].quantity, m[i].name_staff);
                    }
                }
                break;
            }
            case 4: {
                int stt = 1;
                printf("       So lan nhap kho: %d\n", *number_in);
                printf("       |STT|    TEN MAT HANG    |SO LUONG|   TEN NHAN VIEN    |\n");
                for (int i = 0; i < (*number_out + *number_in); i++) {
                    if (m[i].quantity > 0) {
                        printf("       |%2d |%-20s|%-8d|%-20s|\n", stt++, m[i].name_product, m[i].quantity, m[i].name_staff);
                    }
                }
                break;
            }
            case 5: { // Sắp xếp lại danh sách kho
                int q;
                printf("   Sap xep theo:\n");
                printf("       1. Gia tien tang dan\n");
                printf("       2. Gia tien giam dan\n");
                printf("       3. So luong ton kho tang dan\n");
                printf("       4. So luong ton kho giam dan\n");
                printf("   Chon thao tac: ");
                scanf("%d", &q);
                getchar();
                switch (q) {
                    case 1: {
                        for (int i = 0; i < count; i++) {
                            int min_index = i;
                            for (int j = i; j < count; j++) {
                                if (p[j].price < p[min_index].price) {
                                    min_index = j;
                                }
                            }
                            struct product tmp = p[i];
                            p[i] = p[min_index];
                            p[min_index] = tmp;
                        }
                        printf("   ✅Sap xep thanh cong\n");
                        break;
                    }
                    case 2: {
                        for (int i = 0; i < count; i++) {
                            int max_index = i;
                            for (int j = i; j < count; j++) {
                                if (p[j].price > p[max_index].price) {
                                    max_index = j;
                                }
                            }
                            struct product tmp = p[i];
                            p[i] = p[max_index];
                            p[max_index] = tmp;
                        }
                        printf("   ✅Sap xep thanh cong\n");
                        break;
                    }
                    case 3: {
                        for (int i = 0; i < count; i++) {
                            int min_index = i;
                            for (int j = i; j < count; j++) {
                                if (p[j].quantity < p[min_index].quantity) {
                                    min_index = j;
                                }
                            }
                            struct product tmp = p[i];
                            p[i] = p[min_index];
                            p[min_index] = tmp;
                        }
                        printf("   ✅Sap xep thanh cong\n");
                        break;
                    }
                    case 4: {
                        for (int i = 0; i < count; i++) {
                            int max_index = i;
                            for (int j = i; j < count; j++) {
                                if (p[j].quantity > p[max_index].quantity) {
                                    max_index = j;
                                }
                            }
                            struct product tmp = p[i];
                            p[i] = p[max_index];
                            p[max_index] = tmp;
                        }
                        printf("   ✅Sap xep thanh cong\n");
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                printf("   ❌Khong xac dinh duoc lenh, vui long thu lai.\n");
                // không bao giờ xảy ra vì vòng do while ở trên không cho phép nhập sai
                break;
        }
    } else {
        printf("   ❌Ban khong co quyen truy cap quan ly.\n");
    }
}

void nidai_assistant (product p[], int* count, int* money_out, int* money_in, manage m[], int* index_manage, char name_staff_tmp[], int* number_in, int* number_out) {
    // tương tự trên nhưng giao tiếp 1 cách thoải mái hơn
    char oders[100];
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%50s\n", "🤖ニダイ");
    printf("Xin chao, toi la ニダイ assistant, rat han hanh\n");
    printf("duoc lam quen. Toi co the giup ban trong cong\n");
    printf("viec xuat nhap kho.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    do {
        printf("You: ");
        fgets(oders, sizeof(oders), stdin);
        oders[strcspn(oders, "\n")] = '\0';
        check_oders(oders);
        switch (check_oders(oders)) {
            case 0:
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Toi chua hieu y ban cho lam");
                printf("%46s\n", "Ban co the noi ro hon khong?");
                break;
            case 1: {
                // tra cứu
                char q[100];
                char q_regex[100];
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Toi co the giup ban:");
                printf("%46s\n", "Tra cuu danh sach");
                printf("%46s\n", "Tra cuu vi tri");
                do {
                    printf("You: ");
                    fgets(q, sizeof(q), stdin);
                    q[strcspn(q, "\n")] = '\0';
                    check_regex(q, q_regex);
                    if (strcmp(q_regex, "danh sach") == 0) {
                        tra_cuu_danh_sach(*count, p);
                        strcpy(q, "ok, cam on");
                        // nếu rảnh sẽ nâng cấp
                    } else if (strcmp(q_regex, "vi tri")) {
                        char name[100];
                        char name_regex[100];
                        char y;
                        int x;
                        int check = 0;
                        printf("%50s\n", "🤖ニダイ");
                        printf("%46s\n", "Ban muon tra cuu vi tri");
                        printf("%46s\n", "cua san pham nao?");
                        printf("You: ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = '\0';
                        check_regex(name, name_regex);
                        tra_cuu_vi_tri(name_regex, *count, p, &y, &x, &check);
                        if (check==1) {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%44s%d%d\n", "San pham o vi tri: ", y, x);
                            strcpy(q, "ok, cam on");
                            // nếu rảnh sẽ nâng cấp
                        } else {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "San pham nay khong ton tai");
                            printf("%46s\n", "trong kho, ban hay kiem");
                            printf("%46s\n", "tra lai danh sach kho");
                            printf("%46s\n", "hoac loi chinh ta nhe");
                            strcpy(q, "ok, cam on");
                            // nếu rảnh sẽ nâng cấp
                        }
                    } else {
                        printf("%50s\n", "🤖ニダイ");
                        printf("%46s\n", "Toi chua hieu y ban.");
                    }
                } while (strcmp(q, "ok, cam on") != 0);
                break;
            }
            case 2: {
                // thêm mới
                char name[100];
                int quantity;
                int price;
                int check_name = 0;
                int check_them_kho = 1;
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Ten san pham ban muon");
                printf("%46s\n", "them moi vao kho la gi?");
                do {
                    printf("You: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    check_name = 1;
                    for (int i=0; i<*count; i++) {
                        if (strcmp(name, p[i].name) == 0) {
                            check_name = 0;
                            char q[100];
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "San pham nay da co trong kho,");
                            printf("%46s\n", "ban co muon nhap kho khong?");
                            do {
                                printf("You: ");
                                fgets(q, sizeof(q), stdin);
                                q[strcspn(q, "\n")] = '\0';
                                if (check_yes_no(q) == 1) {
                                    check_them_kho = 1;
                                    check_name = 1;
                                } else if (check_yes_no(q) == 0) {
                                    check_them_kho = 0;
                                    check_name = 1;
                                } else {
                                    printf("%50s\n", "🤖ニダイ");
                                    printf("%46s\n", "Toi chua hieu y ban");
                                }
                            } while (check_them_kho != 1 && check_them_kho != 0);
                        }
                    }
                } while (check_name == 0);
                if (check_them_kho == 1) {
                    printf("%50s\n", "🤖ニダイ");
                    printf("%46s\n", "So luong la bao nhieu?");
                    do {
                        printf("You: ");
                        scanf("%d", &quantity);
                        getchar();
                        if (quantity <= 0) {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "So luong san pham phai lon");
                            printf("%46s\n", "hon 0, vui long nhap lai");
                        }
                    } while (quantity <= 0);
                    printf("%50s\n", "🤖ニダイ");
                    printf("%46s\n", "San pham nay co");
                    printf("%46s\n", "gia bao nhieu?");
                    do {
                        printf("You: ");
                        scanf("%d", &price);
                        if (price <= 0) {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "Gia tien san pham phai lon");
                            printf("%46s\n", "hon 0, vui long nhap lai");
                        }
                    } while (price <= 0);
                    getchar();
                    them(name, quantity, price, count, p, &check_them_kho, money_out, m, index_manage, name_staff_tmp, number_in);
                    printf("%50s\n", "🤖ニダイ");
                    printf("%46s\n", "San pham da duoc them vao kho");
                }
                break;
            }
            case 3: {
                // chào
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Chao mot ngay moi tot lanh");
                printf("%46s\n", "Toi co the giup gi cho ban");
                break;
            }
            case 4: {
                // xuất kho
                char name[100];
                char name_regex[100];
                int quantity;
                int check_name = 0;
                int check_quantity = 0;
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Ban muon xuat kho");
                printf("%46s\n", "san pham nao?");
                do {
                    printf("You: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    check_regex(name, name_regex);
                    for (int i=0; i<*count; i++) {
                        if (strcmp(name_regex, p[i].name) == 0) {
                            check_name = 1;
                            break;
                        }
                    }
                    if (check_name == 0) {
                        printf("%50s\n", "🤖ニダイ");
                        printf("%46s\n", "San pham nay khong ton tai");
                        printf("%46s\n", "trong kho, ban hay kiem");
                        printf("%46s\n", "tra lai danh sach kho");
                        printf("%46s\n", "hoac loi chinh ta nhe");
                    }
                } while (check_name == 0);
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "So luong xuat kho");
                printf("%46s\n", "la bao nhieu?");
                do {
                    do {
                        printf("You: ");
                        scanf("%d", &quantity);
                        getchar();
                        if (quantity <= 0) {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "So luong san pham phai lon");
                            printf("%46s\n", "hon 0, vui long nhap lai");
                        }
                    } while (quantity <= 0);
                    for (int i=0; i<*count; i++) {
                        if (strcmp(name_regex, p[i].name) == 0) {
                            if (quantity > p[i].quantity) {
                                printf("%50s\n", "🤖ニダイ");
                                printf("%46s\n", "So luong ban yeu cau lon hon");
                                printf("%46s\n", "so san pham dang co trong");
                                printf("%46s\n", "kho, vui long nhap lai");
                            } else {
                                check_quantity = 1;
                            }
                        }
                    }
                } while (check_quantity == 0);
                xuat_kho(name_regex, quantity, *count, p, &check_name, money_in, m, index_manage, name_staff_tmp, number_out);
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Xuat kho thanh cong");
                getchar();
                break;
            }
            case 5: {
                // nhập kho
                char name[100];
                char name_regex[100];
                int quantity = 0;
                int check_name = 0;
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Ban muon nhap kho");
                printf("%46s\n", "san pham nao?");
                printf("You: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                check_regex(name, name_regex);
                for (int i=0; i<*count; i++) {
                    if (strcmp(name_regex, p[i].name) == 0) {
                        check_name = 1;
                        printf("%50s\n", "🤖ニダイ");
                        printf("%46s\n", "So luong la bao nhieu?");
                        do {
                            printf("You: ");
                            scanf("%d", &quantity);
                            getchar();
                            if (quantity <= 0) {
                                printf("%50s\n", "🤖ニダイ");
                                printf("%46s\n", "So luong san pham phai lon");
                                printf("%46s\n", "hon 0, vui long nhap lai");
                            }
                        } while (quantity <= 0);
                        getchar();
                        nhap_kho(name, quantity, *count, p, &check_name, money_out, m, index_manage, name_staff_tmp, number_in);
                        printf("%50s\n", "🤖Nidai");
                        printf("%46s\n", "Nhap kho thanh cong");
                    }
                }
                if (check_name == 0) {
                    char q[100];
                    int quantity = 0;
                    int price;
                    printf("%50s\n", "🤖ニダイ");
                    printf("%46s\n", "San pham nay chua co trong");
                    printf("%46s\n", "kho, ban co muon them moi");
                    printf("%46s\n", "san pham vao kho khong?");
                    do {
                        printf("You: ");
                        fgets(q, sizeof(q), stdin);
                        q[strcspn(q, "\n")] = '\0';
                        if (check_yes_no(q) == 1) {
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "San pham nay gia bao nhieu");
                            do {
                                printf("You: ");
                                scanf("%d", &price);
                                getchar();
                                if (price <= 0) {
                                    printf("%50s\n", "🤖ニダイ");
                                    printf("%46s\n", "Gia tien san pham phai lon");
                                    printf("%46s\n", "hon 0, vui long nhap lai");
                                }
                            } while (price <= 0);
                            getchar();
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "So luong la bao nhieu?");
                            do {
                                printf("You: ");
                                scanf("%d", &quantity);
                                getchar();
                                if (quantity <= 0) {
                                    printf("%50s\n", "🤖ニダイ");
                                    printf("%46s\n", "So luong san pham phai lon");
                                    printf("%46s\n", "hon 0, vui long nhap lai");
                                }
                            } while (quantity <= 0);
                            getchar();
                            them(name_regex, quantity, price, count, p, &check_name, money_out, m, index_manage, name_staff_tmp, number_in);
                            printf("%50s\n", "🤖ニダイ");
                            printf("%46s\n", "Them moi thanh cong");
                        } else if (check_yes_no(q) == 0) {
                            break;
                        }
                    } while (check_yes_no(q) != 1 && check_yes_no(q) != 2);
                }
                break;
            }
            case 6: {
                // tinh toan
                char q[100];
                int input;
                printf("%50s\n", "🤖ニダイ");
                printf("%46s\n", "Ban can tinh tien bao");
                printf("%46s\n", "nhieu loai san pham?");
                do {
                    printf("You: ");
                    scanf("%d", &input);
                    if (scanf("%d", &input) != 1 || input <= 0) {
                        printf("%50s\n", "🤖ニダイ");
                        printf("%46s\n", "So san pham phai lon hon 0");
                        while (getchar() != '\n');
                    }
                } while (scanf("%d", &input) != 1 || input <= 0);
                char name[input][100];
                char name_regex[input][100];
                int quantity[input];
                int check[input];
                for (int i=0; i<input; i++) {
                    do {
                        printf("%50s\n", "🤖Nidai");
                        printf("%45s Nhap ten san pham %d\n", "", i + 1);
                        printf("You: ");
                        fgets(name[i], sizeof(name[i]), stdin);
                        name[i][strcspn(name[i], "\n")] = '\0';
                        check_regex(name[i], name_regex[i]);
                        for (int j=0; j<*count; j++) {
                            if (strcmp(name_regex[i], p[j].name) == 0) {
                                check[i]=1;
                            }
                        }
                        do {
                            printf("%50s\n", "🤖Nidai");
                            printf("%45s Nhap so luong cua mat hang %d\n", "", i + 1);
                            printf("You: ");
                            scanf("%d", &quantity[i]);
                            getchar();
                            if (scanf("%d", &quantity[i]) != 1) {
                                while (getchar() != '\n');
                            }
                        } while (quantity[i] <= 0 || scanf("%d", &quantity[i]) != 1);
                        if (check[i] != 1) {
                            printf("%50s\n", "🤖Nidai");
                            printf("%46s\n", "San pham nay khong ton");
                            printf("%46s\n", "tai trong kho, vui long");
                            printf("%46s\n", "kiem tra lai.");
                        }
                    } while (check[i] != 1);
                }
                printf("%50s\n", "🤖Nidai");
                int total = tinh_toan(name_regex, quantity, input, *count, p);
                printf("%36s Thanh tien: %.2d VND\n", "", total);
                break;
            }
            case 7: {
                // quan ly
                printf("%50s\n", "🤖Nidai");
                printf("%46s Toi khong co quyen truy cap\n", "");
                printf("%46s vao tinh nang quan ly\n", "");
                break;
            }
            case 8: {
                char q[100];
                char q_regex[100];
                printf("%50s\n", "🤖Nidai");
                printf("%50s\n", "Toi ten la Nidai assistant, toi");
                printf("%46s\n", "duoc tao ra de giup ban trong");
                printf("%46s\n", "viec xuat nhap kho, ban muon");
                printf("%46s\n", "biet them thong tin ve toi hay");
                printf("%46s\n", "nhung viec ma toi co the lam?");
                printf("You: ");
                fgets(q, sizeof(q), stdin);
                q[strcspn(q, "\n")] = 0;
                check_regex(q, q_regex);
                if (strcmp(q_regex, "thong tin") == 0) {
                    printf("%50s\n", "🤖Nidai");
                    printf("%46s\n", "Dm tao gioi thieu het roi");
                } else if (strcmp(q_regex, "lam") == 0 || strcmp(q_regex, "giup") == 0) {
                    printf("%50s\n", "🤖Nidai");
                    printf("%46s\n", "Duoi day la danh sach nhung");
                    printf("%46s\n", "viec toi co the lam:");
                    printf("%46s\n", "Tra cuu danh sach hang hoa");
                    printf("%46s\n", "Tra cuu vi tri hang hoa");
                    printf("%46s\n", "Them san pham moi vao kho");
                    printf("%46s\n", "Tinh toan gia tri don hang");
                    printf("%46s\n", "Xuat kho");
                    printf("%46s\n", "Nhap kho");
                }
                printf("%50s\n", "🤖Nidai");
                printf("%46s\n", "Ban muon toi giup gi nao");
                break;
            }
            case 10:
                printf("%50s\n", "🤖Nidai");
                printf("%46s\n", "Hen gap lai");
                break;
                
            default:
                printf("Khong xac dinh duoc lenh.\n");
                break;
        }
        if (check_oders(oders) != 3 && check_oders(oders) != 10 && check_oders(oders) != 0 && check_oders(oders) != 8) {
            printf("%50s\n", "🤖Nidai");
            printf("%46s\n", "Ban co muon toi giup");
            printf("%46s\n", "them gi nua khong?");
        }
    } while (check_oders(oders) != 10);
}

int check_oders(char oders[]) {
    regex_t tra_cuu, kiem_tra, danh_sach, danh_muc, xem, them, xuat_kho, nhap_kho, tinh_toan, quan_ly, gioi_thieu, chao_hello;
    regcomp(&tra_cuu, "tra cuu", REG_EXTENDED);
    regcomp(&kiem_tra, "kiem tra", REG_EXTENDED);
    regcomp(&danh_sach, "danh sach", REG_EXTENDED);
    regcomp(&danh_muc, "danh muc", REG_EXTENDED);
    regcomp(&xem, "xem", REG_EXTENDED);
    regcomp(&them, "them", REG_EXTENDED);
    regcomp(&xuat_kho, "xuat kho", REG_EXTENDED);
    regcomp(&nhap_kho, "nhap kho", REG_EXTENDED);
    regcomp(&tinh_toan, "tinh toan", REG_EXTENDED);
    regcomp(&quan_ly, "quan ly", REG_EXTENDED);
    regcomp(&gioi_thieu, "gioi thieu", REG_EXTENDED);
    regcomp(&chao_hello, "chao|hello|hey", REG_EXTENDED | REG_ICASE);
    if (regexec(&tra_cuu, oders, 0, NULL, 0) == 0 || regexec(&kiem_tra, oders, 0, NULL, 0) == 0 || regexec(&danh_sach, oders, 0, NULL, 0) == 0 || regexec(&danh_muc, oders, 0, NULL, 0) == 0 || regexec(&xem, oders, 0, NULL, 0) == 0) {
        return 1;
    } else if (regexec(&them, oders, 0, NULL, 0) == 0) {
        return 2;
    } else if (regexec(&chao_hello, oders, 0, NULL, 0) == 0) {
        return 3;
    } else if (regexec(&xuat_kho, oders, 0, NULL, 0) == 0) {
        return 4;
    } else if (regexec(&nhap_kho, oders, 0, NULL, 0) == 0) {
        return 5;
    } else if (regexec(&tinh_toan, oders, 0, NULL, 0) == 0) {
        return 6;
    } else if (regexec(&quan_ly, oders, 0, NULL, 0) == 0) {
        return 7;
    } else if (regexec(&gioi_thieu, oders, 0, NULL, 0) == 0) {
        return 8;
    } else if (strcmp(oders, "k") == 0 || strcmp(oders, "ko") == 0 || strcmp(oders, "khong") == 0 || strcmp(oders, "no") == 0 || strcmp(oders, "noo") == 0 || strcmp(oders, "nooo") == 0 || strcmp(oders, "bye") == 0 || strcmp(oders, "bye bye") == 0 || strcmp(oders, "bai") == 0 || strcmp(oders, "bai bai") == 0 || strcmp(oders, "tam biet") == 0 || strcmp(oders, "oke, bye") == 0 || strcmp(oders, "oke bye") == 0 || strcmp(oders, "oke, chao") == 0 || strcmp(oders, "oke chao") == 0 || strcmp(oders, "oke, tam biet") == 0 || strcmp(oders, "oke tam biet") == 0 || strcmp(oders, "ok, bye") == 0 || strcmp(oders, "ok bye") == 0 || strcmp(oders, "ok, chao") == 0 || strcmp(oders, "ok chao") == 0 || strcmp(oders, "ok, tam biet") == 0 || strcmp(oders, "ok tam biet") == 0 || strcmp(oders, "k can dau, cam on") == 0 || strcmp(oders, "k can nua dau, cam on") == 0 || strcmp(oders, "ko can dau, cam on") == 0 || strcmp(oders, "ko can nua dau, cam on") == 0 || strcmp(oders, "khong can dau, cam on") == 0 || strcmp(oders, "khong can nua dau, cam on") == 0 || strcmp(oders, "toi het cau hoi roi, bye") == 0 || strcmp(oders, "thoi khong con gi nua dau") == 0 || strcmp(oders, "deo") == 0) {
        return 10;
    }
    regfree(&tra_cuu);
    regfree(&kiem_tra);
    regfree(&danh_sach);
    regfree(&danh_muc);
    regfree(&xem);
    regfree(&them);
    regfree(&xuat_kho);
    regfree(&nhap_kho);
    regfree(&tinh_toan);
    regfree(&quan_ly);
    regfree(&gioi_thieu);
    regfree(&chao_hello);
    return 0;
}

int check_yes_no(char q[]) {
    if (strcmp(q, "dong y") == 0 || strcmp(q, "co") == 0 || strcmp(q, "yes") == 0 ||
        strcmp(q, "yess") == 0 || strcmp(q, "yesss") == 0 || strcmp(q, "ok") == 0 ||
        strcmp(q, "oke") == 0 || strcmp(q, "okee") == 0 || strcmp(q, "okeee") == 0 ||
        strcmp(q, "duoc") == 0 || strcmp(q, "duoc thoi") == 0 || strcmp(q, "uh") == 0 || strcmp(q, "uhm") == 0 || strcmp(q, "uhmm") == 0 || strcmp(q, "uk") == 0 || strcmp(q, "ukm") == 0 || strcmp(q, "ukmm") == 0 || strcmp(q, "uhm duoc") == 0 || strcmp(q, "uhm ok") == 0 || strcmp(q, "uhm oke") == 0 || strcmp(q, "ukm ok") == 0 || strcmp(q, "ukm oke") == 0) {
        return 1;
    }
    else if (strcmp(q, "no") == 0 || strcmp(q, "noo") == 0 || strcmp(q, "nooo") == 0 || strcmp(q, "thoi") == 0 || strcmp(q, "thoii") == 0 || strcmp(q, "thoiii") == 0 || strcmp(q, "k") == 0 || strcmp(q, "ko") == 0 || strcmp(q, "khong") == 0 || strcmp(q, "khongg") == 0 || strcmp(q, "khonggg") == 0 || strcmp(q, "tu choi") == 0 || strcmp(q, "thoi khoi") == 0 || strcmp(q, "khong can dau") == 0 || strcmp(q, "ko can dau") == 0 || strcmp(q, "k can dau") == 0 || strcmp(q, "khong can") == 0 || strcmp(q, "ko can") == 0 || strcmp(q, "k can") == 0 || strcmp(q, "deo") == 0) {
        return 0;
    }
    return 3;
}

// Hàm để lọc từ khóa từ input
void check_regex(char *input, char *output) {
    regex_t sach_giai_tich, sach_vat_ly, sach_tin_hoc, cap_sach, ao_dong_phuc, quan_dong_phuc, may_chieu;
    regex_t danh_sach, vi_tri, lam, giup, thong_tin;
    regcomp(&sach_giai_tich, "sach giai tich", REG_EXTENDED);
    regcomp(&sach_vat_ly, "sach vat ly", REG_EXTENDED);
    regcomp(&sach_tin_hoc, "sach tin hoc", REG_EXTENDED);
    regcomp(&cap_sach, "cap sach", REG_EXTENDED);
    regcomp(&ao_dong_phuc, "ao dong phuc", REG_EXTENDED);
    regcomp(&quan_dong_phuc, "quan dong phuc", REG_EXTENDED);
    regcomp(&may_chieu, "may chieu", REG_EXTENDED);
    regcomp(&danh_sach, "danh sach", REG_EXTENDED);
    regcomp(&vi_tri, "vi tri", REG_EXTENDED);
    regcomp(&lam, "lam", REG_EXTENDED);
    regcomp(&giup, "giup", REG_EXTENDED);
    regcomp(&thong_tin, "thong tin", REG_EXTENDED);
        if (regexec(&sach_giai_tich, input, 0, NULL, 0) == 0) {
            strcpy(output, "sach giai tich");
        } else if (regexec(&sach_vat_ly, input, 0, NULL, 0) == 0) {
            strcpy(output, "sach vat ly");
        } else if (regexec(&sach_tin_hoc, input, 0, NULL, 0) == 0) {
            strcpy(output, "sach tin hoc");
        } else if (regexec(&cap_sach, input, 0, NULL, 0) == 0) {
            strcpy(output, "cap sach");
        } else if (regexec(&ao_dong_phuc, input, 0, NULL, 0) == 0) {
            strcpy(output, "ao dong phuc");
        } else if (regexec(&quan_dong_phuc, input, 0, NULL, 0) == 0) {
            strcpy(output, "quan dong phuc");
        } else if (regexec(&may_chieu, input, 0, NULL, 0) == 0) {
            strcpy(output, "may chieu");
        } else {
            strcpy(output, input);
        }
        if (regexec(&lam, input, 0, NULL, 0) == 0) {
            strcpy(output, "lam");
        } else if (regexec(&giup, input, 0, NULL, 0) == 0) {
            strcpy(output, "giup");
        } else if (regexec(&thong_tin, input, 0, NULL, 0) == 0) {
            strcpy(output, "thong tin");
        } else {
            strcpy(output, input);
        }
        if (regexec(&danh_sach, input, 0, NULL, 0) == 0) {
            strcpy(output, "danh sach");
        } else if (regexec(&vi_tri, input, 0, NULL, 0) == 0) {
            strcpy(output, "vi tri");
        } else {
            strcpy(output, input);
        }
    regfree(&sach_giai_tich);
    regfree(&sach_vat_ly);
    regfree(&sach_tin_hoc);
    regfree(&cap_sach);
    regfree(&ao_dong_phuc);
    regfree(&quan_dong_phuc);
    regfree(&may_chieu);
    regfree(&danh_sach);
    regfree(&vi_tri);
    regfree(&lam);
    regfree(&giup);
    regfree(&thong_tin);
}

