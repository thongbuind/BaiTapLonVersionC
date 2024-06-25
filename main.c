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

void menu_0();
void menu_main();
void menu_6(int);
void tra_cuu_danh_sach(int, product[]);
void tra_cuu_vi_tri(char[], int, product[], char*, int*, int*);
void them(char[], int, int, int*, product[], int*, int*, manage[], int*, char, int*);
void xuat_kho(char[], int, int, product[], int*, int*, manage[], int*, char, int*);
void nhap_kho(char[], int, int, product[], int*, int*, manage[], int*, char, int*);
int tinh_toan(char[][100], int[], int, int, product[]);
void yesno_question(char[], int*);

void tinh_nang_tra_cuu (product[], int*);
void tinh_nang_them (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_xuat_kho (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_nhap_kho (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_tinh_toan (product[], manage[], int*, int*, int*, int*, char[]);
void tinh_nang_quan_ly(product[], int, manage[], int*, int*, int*, int*, int*, int*, char[][100]);

void nidai_assistant (product[], int*, int*, int*, manage[], int*, char[], int*, int*);
void check_regex (char[], char[], char[]);
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
            //m[index_manage] = {name, quantity_in, name_staff_tmp};
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
                // Dùng vòng do-while để nhập giá
                do {
                    printf("   Nhap gia san pham: ");
                    scanf("%d", &price);
                    getchar();
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
