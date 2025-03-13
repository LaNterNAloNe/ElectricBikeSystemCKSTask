#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct {
    int uid;
    char usrn[14];
    char psw[14];
}ADMIN_LOGIN_DATA;

int main(){
    char *usrn,*psw;
    int counts=0;
    FILE *fp = fopen("C:\\EBS\\DATA\\ADMIN.DAT","ab+");
    ADMIN_LOGIN_DATA *DATA=malloc(sizeof(ADMIN_LOGIN_DATA));
    if(fp == NULL) printf("Error to open file."),getch(),exit(1);

    fseek(fp,0,SEEK_END);
    counts = ftell(fp)/sizeof(ADMIN_LOGIN_DATA);

    fseek(fp,0,SEEK_SET);

    printf("Enter Admin Username: ");
    scanf("%s",DATA->usrn);
    printf("Enter Admin Password: ");
    scanf("%s",DATA->psw);
    DATA->uid = counts + 10001;
    fwrite(DATA,sizeof(ADMIN_LOGIN_DATA),1,fp);
    
    printf("The info you've typed:\nUsername: %s\nPassword: %s\nAnd uid: %d\nhave written into ADMIN.DAT. Press Any key to exit.\n\n",DATA->usrn,DATA->psw,DATA->uid);
    getch();

    fclose(fp);
    return 0;
}