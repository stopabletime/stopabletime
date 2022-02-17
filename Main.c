/* This is a C project for Grocery list management and also generate the bill for all the product using structute and file handling and with basic of C programming language. For the 1 semester
Done by - Naveen and Paras
Date : 07/02/2022 */
//Declaring the header files
#include<stdio.h> 
#include<string.h>
#include<conio.h> 
#include<stdlib.h>
// Declaring structure
struct product{
    int id;
    char name[20];
    int price;
    int qty;
};
struct bill{
    int pid;
    char pname[20];
    int pprice;
};
//Declaring/Prototyping functions
int getID(); 

int billfileno();
void managelist();
void purchaseproduct();
void generatebill();
void addproduct();
void displayAllproduct();
struct product findproduct(int id);
void updateProduct(int id,int qty);
char fproduct[]={"product.dat"}; //Produt data is being handled in this file
char fbill[]={"bill.dat"}; //All the bill data is being handled in this file
int total=0;
int main(){
    FILE *fp;
    int ch;
    while(1){
        system("cls"); //clrscr
        printf("============================================");
        printf("\n\t WELCOME TO GROCERY LIST MANAGEMENT SYSTEM\n\n");
        printf("============================================\n\n");
        printf("1. Manage list \n\n");
        printf("2. Purchase product \n\n");
        printf("3. Generate bill \n\n");
        printf("0. Exit \n\n");
        printf("============================================");
        printf("\n Please enter your Choice :");
        scanf("%d",&ch);
        switch (ch){
            case 1: managelist();
            break;
            case 2: purchaseproduct();
            break;
            case 3: generatebill();
            break;
            case 0: exit(0); 
        }   
    }
    return 0;
}
int getID(){ //This function is to simple automatically generate the product ID for the list
    FILE *fp;
    int value=0;
    fp=fopen("prodid.txt","r"); //File opened in read mode
    if(fp==NULL){
        fp=fopen("prodid.txt","w"); //Just in case if the file isn't created already this is to create new file.
        fprintf(fp,"%d",0);
        fclose(fp);
//Now I am writing this code and only GOD and I know what this code is doing.
        fp=fopen("prodid.txt","w");
        fprintf(fp,"%d",value+1);
        fclose(fp);
        return value+1;
    }
}
// Creating the various functions for my main code.
void managelist(){
    int ch;
    int back=0;
    while(1){
        printf("============================================\n");
        printf("\n\t WELCOME TO GROCERY LIST MANAGEMENT SYSTEM\n\n");
        printf("============================================\n");
        printf("\n1. Add new product ");
        printf("\n2. Display all product ");
        printf("\n3. Back\n\n ");
        printf("============================================\n");
        printf("\n\t Please enter your choice :");
        scanf("%d",&ch);
        switch(ch){
            case 1 : addproduct();
            break;
            case 2 : displayAllproduct();
            break;
            case 0: back=1;
            break;
        }
        if(back=1){
            break;
        }
        else{
            mygetch();
        }
    }
}
void addproduct(){
    FILE *fp;
    struct product t1;
    fp=fopen(fproduct,"ab");
    t1.id=getID();
    printf("\nEnter product name : ");
    scanf("%s",&t1.name);
    printf("\nEnter product price : ");
    scanf("%d",&t1.price);
    printf("\nEnter product quantity : ");
    scanf("%d",&t1.qty);
    fwrite(&t1,sizeof(t1),1,fp);
    fclose(fp);
}
void displayAllproduct(){
    FILE *fp;
    struct product t;
    int id,found=0;
    fp=fopen(fproduct,"rb");
    printf("============================================\n");
        printf("\n\t PRODUCT DETAILS \n\n");
        printf("============================================\n");
        printf("ID\tName\tQuantity\tPrice\n\n");
        while(1){
            fread(&t,sizeof(t),1,fp);
            if(feof(fp)){
                break;
            }
            printf("%d\t",t.id);
            printf("%s\t",t.name);
            printf("%d\t",t.qty);
            printf("%d\t\t\n",t.price);
        }
        printf("============================================\n");
        fclose(fp);
}
void purchaseproduct(){
    char ch1,ch2;
    int id;
    printf("============================================\n");
        printf("\n\t WELCOME TO GROCERY LIST MANAGEMENT SYSTEM\n\n");
        printf("============================================\n");
        while(1){
            displayAllproduct();
            printf("\n\n\n Do you want to purchase [Y/N]: ");
            scanf("%c",&ch1);
            if(ch1=='Y' || 'y'){
                FILE *fp;
                struct bill t1;
                struct product t2;
                fp=fopen(fbill,"ab");
                printf("\n\nEnter the product ID to purchase : ");
                scanf("%d",&id);
                t2=findproduct(id);
                t1.pid=t2.id;
                strcpy(t1.pname,t2.name);
                t1.pprice=t2.price;
                fwrite(&t1,sizeof(t1),1,fp);
                fclose(fp);
            }
            printf("\n\nDo you want to continue [Y/N : ");
            scanf("%c",&ch2);
            if (ch2=='N' || 'n'){
                break;
            }
            mygetch();
        }
}
struct product findproduct(int id){
    FILE *fp;
    struct product t;
    fp=fopen(fproduct,"rb");
    while(1){
        fread(&t,sizeof(t),1,fp);
        if (feof(fp)){
            break;
        }
        if(t.id==id){
            updateProduct(id,t.qty-1);
            break;
        }
    }
    fclose(fp);
    return t;
}
void updateProduct(int id, int qty){
    FILE *fp,*fp1;
    struct product t,t1;
    int found=0;
    fp=fopen(fproduct,"rb");
    fp1=fopen("temp.dat","wb");
    while (1){
        fread(&t,sizeof(t),1,fp);
        if(feof(fp)){
            break;
        }
        if(t.id==id){
            found=1;
            t.qty=qty;
            fwrite(&t,sizeof(t),1,fp1);
        }
        else{
            fwrite(&t,sizeof(t),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0){
        printf("Sorry no record found\n\n");
    }
    else{
        fp=fopen(fproduct,"wb");
        fp1=fopen("temp.dat","rb");
        while(1){
            fread(&t,sizeof(t),1,fp1);
            if (feof(fp1)){
                break;
            }
            fwrite(&t,sizeof(t),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}
void generatebill(){
    FILE *fp,*fp1;
    struct bill t;
    int id,found=0;
    char ch1;
    int brel=0;
    char billname[20];

    fp=fopen(fbill,"rb");
    printf("============================================\n");
        printf("\n\t Bill Details \n\n");
        printf("============================================\n");
        printf("Product-ID\tProduct-Name\tProduct-price\n\n");

        while(1){
            fread(&t,sizeof(t),1,fp);
            if(feof(fp)){
                break;
            }
            printf("%d\t",t.pid);
            printf("%s\t",t.pname);
            printf("%d\t\t\n",t.pprice);
            total=total+t.pprice;
        }
        printf("\n\n ========>>Total Bill Amount [Rs.  : %d ] \n\n",total);
        fclose(fp);
        if(total!=0){
            printf("\n\n\n Do you want to generate Final bill [Y/N] :");
            scanf("%c",&ch1);
            if(ch1=='Y'){
                brel=billfileno();
                sprintf(billname,"%s%d","",brel);
                strcat(billname,".dat");
                fp=fopen(fbill,"rb");
                fp1=fopen(billname,"wb");
                while (1){
                    fread(&t,sizeof(t),1,fp);
                    if(feof(fp)){
                        break;
                    }
                    fwrite(&t,sizeof(t),1,fp1);
                }
                fclose(fp);
                fclose(fp1);
                fp=fopen(fbill,"wb");
                fclose(fp);
                total=0;               
            }
        }
        else{
            printf("\n\n Sorry no record found \n\n");
        }
}
int billfileno(){
    FILE *fp;
    int value=0;
    fp=fopen("billno.txt","r");
    if(fp==NULL){
        fp=fopen("billno.txt","w");
        fprintf(fp,"%d",0);
        fclose(fp);
        fp=fopen("billno.txt","r");
    }
    fscanf(fp,"%d",&value);
    fclose(fp);
    fp=fopen("billno.txt","w");
    fprintf(fp,"%d",value+1);
    fclose(fp);

    return value+1;
}
// Here is the end of program
//Now only god knows what this code is doing, I am left with no clue.