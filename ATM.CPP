#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct users{
 char accHolderName[40],accNumber[30],accPassword[10],accBalance[20];
};
struct user_log_model{
 char accHolderName[40],accNumber[30],accPassword[10];
 unsigned long int accBalance;
}logged_user;
struct users u[100], copyUser;
int homeScreen();
int adminlogin();
int userlogin();
int createNewUser();
int checkAccountNumber(char aN[30]);
int checkPassword(int p, char accountPin[30]);
int userChoices();
void deposit_money();
void withdraw_money();
void fast_cash();
void check_balance();
void change_pin();
void update();
int main(){
 int choice;
 clrscr();
 choice=homeScreen();
 if(choice==0){
  adminlogin();
 }else if(choice==1){
  userlogin();
 }else{
  printf("\nINVALID CHOICE !!! Please enter a valid option.");
 }
 getch();
 return 0;
}
int homeScreen(){
 int c;
 printf("...................Welcome to Automated Banking System...................");
 printf("\nPlease enter the code corresponding to the operation you want to perform.\n1.\tLogin for Users\n\n0.\tAdmin Login\n");
 fflush(stdin);
 scanf("%d",&c);
 return c;
}
int adminlogin(){
 char username[30],password[30];
 int in,ad_ch;
 printf("\nPlease enter your username:\t");
 fflush(stdin);
 scanf("%s",username);
 if(strcmp(username,"admin")==0){
  printf("\nPlease enter your password:\t");
  fflush(stdin);
  char charc;
  while((charc=getch())!=13){
   printf("*");
   password[in]=charc;
   in++;
  }
  password[in]='\0';
  if(strcmp(password,"admin@2023#")==0){
   printf("\nPlease enter the code corresponding to the action you want to perform:\n1.\tCreate New User\n2.\tLogout\n");
   fflush(stdin);
   scanf("%d",&ad_ch);
   if(ad_ch==1){
    createNewUser();
   }else if(ad_ch==2){
    clrscr();
    main();
   }else{
    printf("\nINVALID CHOICE !!! Please enter a valid option.");
   }
  }else{
   printf("\nINVALID PASSWORD... Please enter a valid password.\n");
   return 1;
  }
 }else{
  printf("\nINVALID USERNAME... Please enter a valid username.\n");
  return 1;
 }
 return 0;
}
int createNewUser(){
 char f_name[40],l_name[20],pass[10];
 FILE *fp;
 int n;
 printf("\nEnter the number of users you want to create:\t");
 fflush(stdin);
 scanf("%d",&n);
 fp=fopen("student.dat","ab");
 if(fp==NULL){
  printf("\nAn unexpected error occurred... Please try again.");
  exit(1);
 }
 else{
  for(int i=0;i<n;i++){
   printf("\nFor User[%d]:",i+1);
   printf("\nEnter first name:\t");
   fflush(stdin);
   gets(f_name);
   printf("\nEnter last name:\t");
   fflush(stdin);
   gets(l_name);
   strcat(f_name," ");
   strcat(f_name,l_name);
   strcpy(u[i].accHolderName,f_name);
   randomize();
   int accN=random(1000000),accNcopy=accN,accsize=0,accNu[6];
   char accNum[30],bankcode[30];
   while(accN>0){
    accN%10;
    accsize++;
    accN/=10;
   }
   for(int v=0;v<6-accsize;v++){
    accNu[v]=0;
   }
   for(int j=6-accsize;j<6;j++){
    accNu[j]=accNcopy%10;
    accNcopy/=10;
   }
   int index=0;
   for(int l=0;l<6;l++){
    index+=sprintf(&accNum[index],"%d",accNu[l]);
   }
   strcpy(bankcode,"00100501");
   strcat(bankcode,accNum);
   strcpy(u[i].accNumber,bankcode);
   printf("\nEnter Account Balance:\t");
   fflush(stdin);
   scanf("%s",u[i].accBalance);
   printf("\nEnter a 5-digit pin for this account:\t");
   fflush(stdin);
   char charc1,hideninput[10];
   int in1=0;
   while((charc1=getch())!=13){
    printf("*");
    hideninput[in1]=charc1;
    in1++;
   }
   hideninput[in1]='\0';
   strcpy(u[i].accPassword,hideninput);
   printf("\nUser created successfully...\nName:\t%s\nAccount Number:\t%s\nAccount Balance:\t%s\nPassword:\t%s\n",u[i].accHolderName,u[i].accNumber,u[i].accBalance,u[i].accPassword);
  }
  fwrite(&u,sizeof(struct users),100,fp);
  fclose(fp);
 }
 return 0;
}
int userlogin(){
 char accountNumber[30];
 int accComp;
 printf("\nPlease Enter your account number:\t");
 fflush(stdin);
 scanf("%s",accountNumber);
 accComp=checkAccountNumber(accountNumber);
 if(accComp==0){
  printf("\nSorry you couldn't be logged in...");
 }else if(accComp==1){
  printf("\nYou're successfully logged in!!!");
  userChoices();
 }else{
  main();
  printf("\nAn unexpected error occurred. Please try again...");
 }
 return 0;
}
int checkAccountNumber(char aN[30]){
 FILE *fp1;
 char accountPin[30];
 int log=0,k;
 struct users z[100];
 fp1=fopen("student.dat","r");
 if(fp1==NULL){
  printf("\nAn unexpected error occurred... Please try again.");
  exit(1);
 }
 else{
  for(k=0;k<100;k++){
   do{
    fread(&u,sizeof(struct users),1,fp1);
    if(strcmp(u[k].accNumber,aN)==0){
     printf("\nPlease Enter your account pin:\t");
     fflush(stdin);
     char charc2,hideninput2[10];
     int in2=0;
     while((charc2=getch())!=13){
      printf("*");
      hideninput2[in2]=charc2;
      in2++;
     }
     hideninput2[in2]='\0';
     strcpy(accountPin,hideninput2);
     if(strcmp(u[k].accPassword,accountPin)==0){
      strcpy(logged_user.accHolderName,u[k].accHolderName);
      strcpy(logged_user.accNumber,u[k].accNumber);
      logged_user.accBalance=atoi(u[k].accBalance);
      strcpy(logged_user.accPassword,u[k].accPassword);
      log=1;
     }
     break;
    }
   }while(!feof(fp1));
   break;
  }
 }
 fclose(fp1);
 return log;
}
int userChoices(){
 int user_ch;
 strupr(logged_user.accHolderName);
 printf("\n\n\tHello %s",logged_user.accHolderName);
 printf("\n\tPlease enter the code corresponding to the action you want to perform:\n\t1.\tDeposit Money\n\t2.\tWithdraw Money\n\t3.\tFast Cash\n\t4.\tCheck Balance\n\t5.\tChange Pin\n\t0.\tCancel\n");
 scanf("%d",&user_ch);
 if(user_ch==0){
  main();
 }else if(user_ch==1){
  deposit_money();
  update();
 }else if(user_ch==2){
  withdraw_money();
  update();
 }else if(user_ch==3){
  fast_cash();
  update();
 }else if(user_ch==4){
  check_balance();
 }else if(user_ch==5){
  change_pin();
  update();
 }else{
  main();
 }
 getch();
 return 1;
}
void deposit_money(){
 unsigned long int depo_amt;
 printf("\nPlease enter the amount you want to deposit (in multiples of 500 only)\n");
 fflush(stdin);
 scanf("%lu",&depo_amt);
 if((depo_amt%500)!=0){
  printf("\nPlease enter amount in multiple of 500.");
 }else{
  logged_user.accBalance+=depo_amt;
  printf("\nPlease insert %lu cash.",depo_amt);
 }
}
void withdraw_money(){
 unsigned long int draw_amt;
 printf("\nPlease enter the amount you want to withdraw (in multiples of 500 only)\n");
 fflush(stdin);
 scanf("%lu",&draw_amt);
 if(draw_amt>logged_user.accBalance){
  printf("\nInsufficient Balance!!!");
 }else if(draw_amt>25000){
  printf("\nMaximum Withdraw limit exceeded...");
 }else if((draw_amt%500)!=0){
  printf("\nPlease enter amount in multiple of 500.");
 }else{
  logged_user.accBalance-=draw_amt;
  printf("\nPlease collect your cash and card.");
 }
}
void fast_cash(){
 int fast_ch;
 unsigned long int fast_draw_amt;
 printf("\nPlease enter the code corresponding to the amount you want to withdraw:\n1. 1000\t2. 2000\n3. 4000\t4. 5000\n5. 10000\t6.15000\n7.20000\t8.25000\n");
 fflush(stdin);
 scanf("%d",&fast_ch);
 if(fast_ch==1){
  fast_draw_amt=1000;
 }else if(fast_ch==2){
  fast_draw_amt=2000;
 }else if(fast_ch==3){
  fast_draw_amt=4000;
 }else if(fast_ch==4){
  fast_draw_amt=5000;
 }else if(fast_ch==5){
  fast_draw_amt=10000;
 }else if(fast_ch==6){
  fast_draw_amt=15000;
 }else if(fast_ch==7){
  fast_draw_amt=20000;
 }else if(fast_ch==8){
  fast_draw_amt=25000;
 }else{
  main();
 }
 if(fast_draw_amt>logged_user.accBalance){
  printf("\nInsufficient Balance!!!");
 }else{
  logged_user.accBalance-=fast_draw_amt;
  printf("\nPlease collect your cash and card.");
 }
}
void check_balance(){
 printf("\nYour current balance is: %d",logged_user.accBalance);
}
void change_pin(){
 printf("\nPlease enter a new pin of 5-digit:\t");
 fflush(stdin);
 char charc3,hideninput3[10];
 int in3=0;
 while((charc3=getch())!=13){
  printf("*");
  hideninput3[in3]=charc3;
  in3++;
 }
 hideninput3[in3]='\0';
 strcpy(logged_user.accPassword,hideninput3);
}
void update(){
 unsigned long int ab=logged_user.accBalance,abrev=0;
 while(ab!=0){
  abrev=abrev*10;
  abrev=abrev+ab%10;
  ab=ab/10;
 }
 unsigned long int AccNum=abrev,AccNCopy=abrev,AccNu[8];
 int AccSize=0;
 char AccBal[8];
 while(AccNum>0){
  AccNum%10;
  AccSize++;
  AccNum/=10;
 }
 for(int g=0;g<8-AccSize;g++){
  AccNu[g]=0;
 }
 for(int d=8-AccSize;d<8;d++){
  AccNu[d]=AccNCopy%10;
  AccNCopy/=10;
 }
 int indexLog=0;
 for(int q=0;q<8;q++){
  indexLog+=sprintf(&AccBal[indexLog],"%lu",AccNu[q]);
 }
 strcpy(copyUser.accHolderName,logged_user.accHolderName);
 strcpy(copyUser.accNumber,logged_user.accNumber);
 strcpy(copyUser.accBalance,AccBal);
 strcpy(copyUser.accPassword,logged_user.accPassword);
 //printf("Current User:\nName:\t%s\nAccount Number:\t%s\nBalance:\t%s\nPassword:\t%s",copyUser.accHolderName,copyUser.accNumber,copyUser.accBalance,copyUser.accPassword);
 FILE *fpOrg,*fpCopy;
 fpOrg=fopen("student.dat","rb");
 fpCopy=fopen("stu_copy.dat","ab");
 if(fpOrg==NULL || fpCopy==NULL){
  printf("\nAn unexpected error occurred, please try again...");
  exit(1);
 }else{
  fread(&u,sizeof(struct users),100,fpOrg);
  for(int w=0;w<100;w++){
   if(strcmp(u[w].accNumber,logged_user.accNumber)==0){
    strcpy(u[w].accHolderName,copyUser.accHolderName);
    strcpy(u[w].accNumber,copyUser.accNumber);
    strcpy(u[w].accBalance,copyUser.accBalance);
    strcpy(u[w].accPassword,copyUser.accPassword);
   }
  }
  fwrite(&u,sizeof(struct users),100,fpCopy);
 }
 fclose(fpOrg);
 fclose(fpCopy);
 remove("student.dat");
 rename("stu_copy.dat","student.dat");
}