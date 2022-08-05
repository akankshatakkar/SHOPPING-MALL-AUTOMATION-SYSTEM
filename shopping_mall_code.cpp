#include<iostream>
#include<conio.h>
#include<fstream>
#include<process.h>
#include<stdio.h>
#include<windows.h>
#include<iomanip>
using namespace std;


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Product
{
public:
int pno;
char name[50];
float price,qty,tax,dis;
void create_product()
{
cout<<"\nPlease Enter The Product No. of the Product:"<<endl;
cin>>pno;
cin.ignore();
cout<<"\n\nPlease Enter The Name of the Product:"<<endl;
gets(name);
cout<<"\nPlease Enter The Price of the Product:"<<endl;
cin>>price;
cout<<"\nPlease Enter The Discount(%):"<<endl;
cin>>dis;
}
void show_product()
{
cout<<"\nThe Product Number of the Product:"<<pno;
cout<<"\nThe Name of the Product:";
puts(name);
cout<<"\nThe Price of the Product:"<<price;
cout<<"\nDiscount:"<<dis;
}
int retpno()
{
return pno;}
float retprice()
{
return price;
}
char *retname()
{
return name;
}
int retdis()
{
return dis;
}
};                               //class ends here
//global declaration for stream object , object
fstream fp;
Product pr,pr1;
void write_product()
{
fp.open("Shop.txt",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(Product));
fp.close();
cout<<"\n\nThe Product Has Been Created";
getch();
}
//function to read all records from file
void display_all()
{
system("cls");
cout<<"\n\n\n\t\tDISPLAY ALL RECORD!!!\n\n";
fp.open("Shop.txt",ios::in);
while(fp.read((char*)&pr,sizeof(Product)))
{
pr.show_product();
cout<<"\n\n======================================================\n";
getch();
}
fp.close();
getch();
}
//function to read specific record from file
void display_sp(int n)
{
int flag=0;
fp.open("Shop.txt",ios::in);
while(fp.read((char*)&pr,sizeof(Product)))
{
if(pr.retpno()==n)
{
system("cls");
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nRecord Not Exists";
getch();
}
//function to modify record of file
void modify_product()
{
int no,found=0;
system("cls");
cout<<"\n\n\tModify";
cout<<"\n\n\tPlease Entner The Product No. of the Product";
cin>>no;
fp.open("Shop.txt",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(Product))&&found==0)
{
if(pr.pno==no)
{
pr.show_product();
cout<<"\nPlease Enter The New Details of Product:"<<endl;
//flush();
pr.create_product();
int pos=-1*sizeof(pr);
fp.seekp(pos,ios::cur);
fp.write((char*)&pr,sizeof(Product));
cout<<"\n\n\tRecord Updated";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\nRecord Not Found";
getch();
}
//function to delete record of file
void delete_product()
{
system("cls");
ifstream fp1("Shop.txt",ios::in);
ofstream fp2("Temp.txt",ios::out);
int no;
char found='f',confirm='n';
cout<<"Enter Product number of the product to be deleted\n";
cin>>no;
while(!fp1.eof())
{
fp1.read((char*)&pr,sizeof(pr));
if(pr.retpno()==no)
{
pr.show_product();
found='t';
cout<<"Are You Sure You Want To Delete This Record?(y/n)...";
cin>>confirm;
if(confirm=='n')
fp2.write((char*)&pr,sizeof(pr));
}
else
fp2.write((char*)&pr,sizeof(pr));
}
if(found=='f')
cout<<"Record Not Found!!!\n";
fp1.close();
fp2.close();
remove("Shop.txt");
rename("Temp.txt","Shop.txt");
fp1.open("Shop.txt",ios::in);
cout<<"Now The File Contains\n";
while(!fp.eof())
{
fp1.read((char*)&pr1,sizeof(pr1));
if(fp1.eof())
break;
pr1.show_product();
}
fp1.close();
getch();
}
//function to display all the products of list
void menu()
{
system("cls");
fp.open("Shop.txt",ios::in);
if(!fp)
{
cout<<"ERROR!!!FILE COULD NOT BE OPEN\n\n\nGo To Admin Menu to CReate File";
cout<<"\n\n\nProgram is Closing....";
getch();
exit(0);
}
cout<<"\n\n\t\tPRODUCT MENU\n\n";
cout<<"=============================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"==============================================================\n";
while(fp.read((char*)&pr,sizeof(Product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}
//function to place order and generating bill for products
void place_order()
{
int order_arr[50],quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu();
cout<<"\n\n\n\n\n==================================================";
cout<<"\n                  -->>PLACE YOUR ORDER<<--";
cout<<"\n========================================================\n";
do{
cout<<"\n\nEnter The Product No. Of The Product:";
cin>>order_arr[c];
cout<<"\nQuantity In Number:";
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order Another Product?(y/n)";
cin>>ch;
}
while(ch=='y'||ch=='Y');
cout<<"\n\nThank You For Placing The Order";
getch();
system("cls");
cout<<"\n*************************INVOICE***********************************\n";
cout<<"\nPr No. \tPr Name \tQuantity \tPrice \tAmount \tAmount after Discount\n";
for(int x=0;x<=c;x++)
{
fp.open("Shop.txt",ios::in);
fp.read((char*)&pr,sizeof(Product));
while(!fp.eof())
{
if(pr.retpno()==order_arr[x])
{
amt=pr.retprice()*quan[x];
damt=amt-(amt*pr.retdis()/100);
cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
total+=damt;
}
fp.read((char*)&pr,sizeof(Product));
}
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL="<<total;
getch();
}
//introductioon function
void intro()
{
system("cls");
gotoxy(25,3);
cout<<"---->>SUPER MARKET<<----";
gotoxy(25,7);
cout<<"--->>BILLING<<---";
gotoxy(25,11);
cout<<"-->>PROJECT<<--";
cout<<"\n\n\n\n\n\n\nMADE BY : Akanksha Takkar";
cout<<"\n\nSCHOOL : Gyan Bharati School";
getch();
}
//administrator menu function
void admin_menu()
{
system("cls");
char ch2;
cout<<"\n\n\n\tADMINISTRATION MENU \n";
cout<<"\t___________________________";
cout<<"\n\n\t1:CREATE PRODUCT";
cout<<"\n\n\t2:DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3:QUERY";
cout<<"\n\n\t4:MODIFY PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6:VIEW PRODUCT MENU";
cout<<"\n\n\t7:BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice(1-7)";
cin>>ch2;
switch(ch2)
{
case '1':system("cls");
write_product();
break;
case '2':display_all();
break;
case '3': int num;
system("cls");
cout<<"\n\n\tPlease Enter The Product No.";
cin>>num;
display_sp(num);
break;
case '4':modify_product();
break;
case '5':delete_product();
case '6':menu();
getch();
case'7':break;
default: cout<<"\a";
admin_menu();
}
}
//the main function
int main()
{
char ch;
intro();
do
{
system("cls");
cout<<"\n-->>Welcome To Super Market Billing System Application<<--\n";
cout<<"\t**********************************************\n\n";
cout<<"\n\n\n\tMAIN MENU\n";
cout<<"\t____________________________________";
cout<<"\n\n\t01:CUSTOMER";
cout<<"\n\n\t02:ADMINISTRATOR";
cout<<"\n\n\t03:EXIT";
cout<<"\n\n\tPlease Select Your Option";
cin>>ch;
switch(ch)
{
case '1':system("cls");
place_order();
getch();
break;
case '2':admin_menu();
break;
case '3':exit(0);
default: cout<<"\a";
}
}
while(ch!='3');
return 0;
}
