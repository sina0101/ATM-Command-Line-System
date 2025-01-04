#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
#define DATA_FILE "users.txt"

//  کاربران
typedef struct {
    char cardNumber[20];
    char pin[10];
    double balance;}
     User ;

User users[MAX_USERS];
int userCount=0;

// توابع کمکی
void loadUsers();
void saveUsers();
int login(int *userIndex);
void checkBalance(int userIndex) ;
void withdrawMoney(int userIndex) ;
void depositMoney(int userIndex) ;
void changePin(int userIndex) ;

int main() {
    loadUsers() ;
    int userIndex=-1 ;
    int choice ;

    printf( "سیستم ATM\n");
    if (login (&userIndex) ) {
        do{
            printf("\nمنوی اصلی:\n");
            printf("1. بررسی موجودی\n");
            printf("2. برداشت پول\n");
            printf("3. واریز پول\n");
            printf("4. تغییر رمز عبور\n");
            printf("5. خروج\n");
            printf("انتخاب کنید: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    checkBalance(userIndex);
                    break;
                case 2:
                    withdrawMoney(userIndex);
                    break;
                case 3:
                    depositMoney(userIndex);
                    break;
                case 4:
                    changePin(userIndex);
                    break;
                case 5:
                    printf("خروج از سیستم.\n");
                    saveUsers();
                    break;
                default:
                    printf("انتخاب نامعتبر است!\n");
            }
        } while (choice != 5);}
             else {
        printf("ورود ناموفق!\n");
    }

    return 0;
}

void loadUsers() 
{
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {

        printf("خطا در باز کردن فایل دیتابیس.\n");
        
        return;}

    while (fscanf(file,"%s %s %lf",users[userCount].cardNumber,users[userCount].pin, &users[userCount].balance) != EOF) {
        userCount++ ;
    }

    fclose(file);
    }

void saveUsers() 
{
    FILE *file = fopen(DATA_FILE,"w");
    if (file==NULL){
        printf("خطا در ذخیره فایل دیتابیس.\n");
        return;
    }

    for (int i =0;i< userCount; i++) {
        fprintf(file, "%s %s %.2lf\n", users[i].cardNumber, users[i].pin, users[i].balance);
    }

    fclose(file);}

int login(int *userIndex) {
    char cardNumber[20], pin[10];

    printf("شماره کارت: ");
    scanf("%s", cardNumber);
    printf("رمز عبور: ");
    scanf("%s", pin);
    for (int i = 0; i < userCount; i++) {
        
        if (strcmp(users[i].cardNumber, cardNumber) == 0 && strcmp(users[i].pin, pin) == 0) {
            *userIndex = i;
            return 1;
        }}
    return 0 ;
}

void checkBalance(int userIndex)
 {

    printf("موجودی فعلی شما: %.2lf تومان\n", users[userIndex].balance);
}

void withdrawMoney(int userIndex)
{
    double amount  ;
    printf("مبلغ برداشت: ");
    scanf("%lf",&amount);

    if (amount>users[userIndex].balance) {
        printf("موجودی کافی نیست!\n");}
         else {
        users[userIndex].balance -= amount;
        printf("برداشت موفقیت‌آمیز بود. موجودی جدید: %.2lf تومان\n", users[userIndex].balance);}}
void depositMoney(int userIndex) 
{
    
    double amount;

    printf("مبلغ واریز: ");
    scanf("%lf", &amount);
    users[userIndex].balance += amount;
    printf("واریز موفقیت‌آمیز بود. موجودی جدید: %.2lf تومان\n", users[userIndex].balance);
    }
void changePin(int userIndex)
 {
    char newPin[10];
    printf("رمز عبور جدید: ");
    scanf("%s", newPin);
    strcpy(users[userIndex].pin, newPin);
    printf("رمز عبور با موفقیت تغییر یافت.\n");}
