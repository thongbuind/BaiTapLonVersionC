#include <stdio.h>
#include <string.h>
#include "header.h"

int main() {
    struct product p[100] = {
        {"sach giai tich", 19, 3000},
        {"sach vat ly", 15, 23000},
        {"sach tin hoc", 17, 20000},
        {"cap sach", 16, 300000},
        {"ao dong phuc", 61, 150000},
        {"quan dong phuc", 61, 110000},
        {"may chieu", 7, 1100000}
    };
    struct manage m[100];
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
                            //tinh_nang_xuat_kho(p, m, &index_manage, &money_in, &number_out, &count, name_staff_tmp);
                            break;
                        }
                        case 4: {
                            //tinh_nang_nhap_kho(p, m,&index_manage, &money_out, &number_in, &count, name_staff_tmp);
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
