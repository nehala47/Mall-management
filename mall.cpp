//header files
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<iostream>
#include<windows.h>
#include<string>
#include<unistd.h>
#include<cstdlib>
using namespace std;
//global variable
COORD coord={0,0};
//setting initially to 0,0 as x and y co-ordinate respectively
fstream fp1;

//setting the co-ordinate to display output in exact position
void setcoord(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//class shops in which the shop details are being declared
class shops
{
    int shopNo;
    char shopName[30];
    char Stype[30];
    int floorno;
    long int number;
    int duration;
    int rentP;
public:

    //this takes the input of the new shop details
    int createShop(int no)
    {
        shopNo=no;
        cout<<"\n\t\t\t enter the name of shop: ";
        cin>>shopName;
        cout<<"\n\t\t\t enter the type of shop: ";
        cin>>Stype;
        cout<<"\n\t\t\t enter the floor number in gallaria in which shop is situated: ";
        cin>>floorno;
        cout<<"\n\t\t\t enter the contact number of shop: ";
        cin>>number;
        cout<<"\n\t\t\t enter the duration of the shop to which advance rent is paid or to be paid(in years): ";
        cin>>duration;
        cout<<"\n\t\t\t enter the rent of the shop (in rupees): ";
        cin>>rentP;
        return 0;
    }

    //this displays the each shop details whenever it is called

    void showShop()
    {
        cout<<"\n\t\t\t shop number: "<<shopNo;
        cout<<"\n\t\t\t name of shop: "<<shopName;
        cout<<"\n\t\t\t type of shop: "<<Stype;
        cout<<"\n\t\t\t floor number: "<<floorno;
        cout<<"\n\t\t\t contact number: "<< number;
        cout<<"\n\t\t\t duration of advance rent(in years): "<<duration;
        cout<<"\n\t\t\t rent of the shop (in rupees): "<<rentP;
    }
    void showCS()
    {
        cout<<"\n\t\t\t shop number: "<<shopNo;
        cout<<"\n\t\t\t name of shop: "<<shopName;
        cout<<"\n\t\t\t type of shop: "<<Stype;
        cout<<"\n\t\t\t floor number: "<<floorno;
        cout<<"\n\t\t\t contact number: "<< number;
    }

    //this returns the shop number of each when ever it is being called
    int retsno()
    {
        return shopNo;
    }
};
//global declaration
shops sh;

//this function checks if the shop number is already existing or not

int checkS(int no)
    {
        fstream fp3;
        fp3.open("shop.dat",ios::in);
        while(fp3.read((char*)&sh,sizeof(shops)))
	   {
	    if((sh.retsno())==no)
		   {
		       cout<<" It already has same shop number in database";
		       fp3.close();
		       return -1;
		   }
	   }
	   fp3.close();
	   return 0;
    }

//this function adds the shop details in the database
void addshop()
{
    int n,shopNo;
    fp1.open("shop.dat",ios::app|ios::out);
    cout<<"\n\t\t\t enter the shop number: ";
    cin>>shopNo;
    n=checkS(shopNo);
    if(n==-1){
        fp1.close();
        return;
    }
    n=sh.createShop(shopNo);
    fp1.write((char*)&sh,sizeof(shops));
    fp1.close();
    cout<<"\n The shop is being added in the database.... ";
    getch();
}

//this function displays the shop details for the administrator

void displayshopA()
{
     cout<<"\n\n\t\t\t\t SHOPS DETAILS \n";
    cout<<"\n\t\t\t------------------------------------------------\n\n";
    fp1.open("shop.dat",ios::in);
    while(fp1.read((char*)&sh,sizeof(shops)))
	{
	 sh.showShop();
	 cout<<"\n\n\t\t\t==================================================\n";
	 getch();
	 }
    fp1.close();
    getch();
}

// this function modifies the data of the shop which is already in the database

void modifyShop()
{
    int no,found=0;
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Shop No. of The Shop: ";
    cin>>no;
    fp1.open("shop.dat",ios::in|ios::out);
    while(fp1.read((char*)&sh,sizeof(shops)) && found==0)
	   {
	    if(sh.retsno()==no)
		   {
		    sh.showShop();
		    cout<<"\nPlease Enter The New Details of shop: "<<endl;
		    sh.createShop(no);
		    int pos=-1*sizeof(sh);
		    fp1.seekp(pos,ios::cur);
		    fp1.write((char*)&sh,sizeof(shops));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp1.close();
    if(found==0)
        cout<<"\n\n XX Record Not Found XX ";
    getch();
}

//this function displays the shop details for the users/customers

void displayshopC()
{
     cout<<"\n\n\t\t\t\t SHOPS PRESENT IN OUR GALLERIA :\n";
    cout<<"\n\t\t\t------------------------------------------------\n\n";
    fp1.open("shop.dat",ios::in);
    while(fp1.read((char*)&sh,sizeof(shops)))
	{
	 sh.showCS();
	 cout<<"\n\n\t\t\t====================================\n";
	 getch();
	 }
    fp1.close();
    getch();
}

int checkD(int no){
    fstream fp3;
        fp3.open("shop.dat",ios::in);
        while(fp3.read((char*)&sh,sizeof(shops)))
	   {
	    if((sh.retsno())==no)
		   {
		       return 0;
		   }
	   }
	   fp3.close();
	   return -1;
}


//this function deletes the shop details

void deleteShop()
   {
    int no;
    int found;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The shop no. of The shop You Want To Delete: ";
    cin>>no;
    fp1.open("shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp1.seekg(0,ios::beg);
    found=checkD(no);
    if(found==-1){
        cout<<" XX RECORD NOT FOUND XX\n"<<endl;
        return;
    }
    while(fp1.read((char*)&sh,sizeof(shops)))
	{
	 if(sh.retsno()!=no)
		{
		 fp2.write((char*)&sh,sizeof(shops));
		 }
	 }
    fp2.close();
    fp1.close();
    remove("shop.dat");
    rename("temp.dat","shop.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

//this function displays the options for the shop details

void shopD()
{
     int ch;
    fp1.open("shop.dat",ios::in);
     if(!fp1)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN";
       getch();
       exit(0);
     }
    for(;;)
    {
    cout<<"\n\t\t OPTIONS: ";
    cout<<"\n\t 1. add new shops details";
    cout<<"\n\t 2. modify shops details: ";
    cout<<"\n\t 3. delete shops details: ";
    cout<<"\n\t 4. display shops details: ";
    cout<<"\n\t 5. exit";
    cout<<"\n\tenter the choice: ";
    cin>>ch;
    switch(ch)
    {
        case 1: addshop();
                    break;
        case 2: modifyShop();
                    break;
        case 3: deleteShop();
                    break;
        case 4: displayshopA();
                    break;
        case 5: return;
        default:cout<<"\n\t XX INVALID CHOICE XX";
    }
    }
}

//this is class of rent where the details of the rent requests is being declared

class rent
{
    char rname[30];
    char remail[30];
    char rtype[30];
    long int phone;
public:
    //this function creates or takes the input for rent request details
    void createR()
    {
        cout<<"\n\t\t\t enter your name:";
        cin>>rname;
        cout<<"\n\t\t\t enter your email: ";
        cin>>remail;
        cout<<"\n\t\t\t enter the type of shop you want to set up for eg:food,gaming etc: ";
        cin>>rtype;
        cout<<"\n\t\t\t enter your phone number o contact: ";
        cin>>phone;
    }

    //this function displays each rent request whenever it is being called

    void showR()
    {
        cout<<"\n\t\t\t Name: "<<rname;
        cout<<"\n\t\t\t Email: "<<remail;
        cout<<"\n\t\t\t Type of shop they want to set up: "<<rtype;
        cout<<"\n\t\t\t Phone number: "<<phone;
    }

};
//global declaration
rent r;

//this function adds the request for the rent in the database

void addR()
{
    fp1.open("rent.dat",ios::app|ios::out);
    r.createR();
    fp1.write((char*)&r,sizeof(rent));
    fp1.close();
    cout<<"\nYour request is being sent.....Thanks for your valuable time.... admin is going to soon contact you about this...:) ";
    getch();
}

//this function displays the rent requests arrived for the administrator

void displayR()
{
    cout<<"\n\n\t\t\t\t RENT REQUEST DETAILS\n";
    cout<<"\n\t\t\t------------------------------\n\n";
    fp1.open("rent.dat",ios::in);
    while(fp1.read((char*)&r,sizeof(rent)))
	{
	 r.showR();
	 cout<<"\n\n\t\t\t====================================\n";
	 getch();
	 }
    fp1.close();
    getch();
}

//class feedback contains all the details of the feedback declared

class feedback
{
    char fname[30];
    char email[30];
    char feed[30];
public:
    //this function takes the input of feedback details

    void createF()
    {
        cout<<"\n\t\t\t enter your name: ";
        cin>>fname;
        cout<<"\n\t\t\t enter your email id: ";
        cin>>email;
        cout<<"\n\t\t\t enter your feedback: ";
        cin>>feed;
    }

    //this function displays each feedback to the administrator
    void showF()
    {
        cout<<"\n\t\t\t Name:"<<fname;
        cout<<"\n\t\t\t Email id:"<<email;
        cout<<"\n\t\t\t Feedback: "<<feed;
    }
};

//global declaration
feedback f;

//this function adds the feedback by the customers into the database
void addF()
{
    fp1.open("feed.dat",ios::app|ios::out);
    f.createF();
    fp1.write((char*)&f,sizeof(feedback));
    fp1.close();
    cout<<"\nFeedback is being sent.....Thanks for your valuable time :) ";
    getch();
}

//this function displays the details of all the feedbacks to the administrator
void displayF()
{
    cout<<"\n\n\t\t\t\t FEEDBACK DETAILS\n";
    cout<<"\n\t\t\t------------------------------\n\n";
    fp1.open("feed.dat",ios::in);
    while(fp1.read((char*)&f,sizeof(feedback)))
	{
	 f.showF();
	 cout<<"\n\n\t\t\t====================================\n";
	 getch();
	 }
    fp1.close();
    getch();
}

//class staff has all the staff details being declared
class staff
{
    int sno;
    char name[30];
    char type[30];
    char address[30];
    int age;
    long int phn;
public:
    //this takes the input of staff details given by the administrator
    void createS(int no)
    {
        sno=no;
        cout<<"\n\t\t\t enter the staff name: ";
        cin>>name;
        cout<<"\n\t\t\t enter the type of job: ";
        cin>>type;
        cout<<"\n\t\t\t enter the age of the staff: ";
        cin>>age;
        cout<<"\n\t\t\t enter the address of staff: ";
        cin>>address;
        cout<<"\n\t\t\t enter the phone number of staff: ";
        cin>>phn;
    }

    //this displays each staff details to the administrator
    void showS()
    {
        cout<<"\n\t\t\t\t Staff number:  "<<sno;
        cout<<"\n\t\t\t\t Staff name: "<<name;
        cout<<"\n\t\t\t\t Type of job: "<<type;
        cout<<"\n\t\t\t\t Age of staff: "<<age;
        cout<<"\n\t\t\t\t Address of staff: "<<address;
        cout<<"\n\t\t\t\t Phone number: "<<phn;
    }

    //this returns the staff number of the record being called
    int retsno()
    {
        return sno;
    }
};

// global declaration
staff s;
fstream fp;

//this function checks if already the staff number is existing in the database

int check(int no)
    {
        fstream fp3;
        fp3.open("staff.dat",ios::in);
        while(fp3.read((char*)&s,sizeof(staff)))
	   {
	    if((s.retsno())==no)
		   {
		       cout<<"\n\t\tit already has same staff number in database";
		       fp3.close();
		       return -1;
		   }
	   }
	   fp3.close();
	   return 0;
    }

//this function adds the staff record into the database

void addstaff()
{
    int n,sno;
    fp.open("staff.dat",ios::app|ios::out);
    cout<<"\n\t\t\t enter the staff number of the staff: ";
    cin>>sno;
    n=check(sno);
    if(n==-1){
        fp.close();
        return;
    }
    s.createS(sno);
    fp.write((char*)&s,sizeof(staff));
    fp.close();
    cout<<"\nstaff details are being inserted";
    getch();
}

// this function displays the staff details to the administrator

void display()
{
    cout<<"\n\n\t\t\t\t STAFF DETAILS\n";
    cout<<"\n\t\t\t------------------------------\n\n";
    fp.open("staff.dat",ios::in);
    while(fp.read((char*)&s,sizeof(staff)))
	{
	 s.showS();
	 cout<<"\n\n\t\t\t=================================\n";
	 getch();
	 }
    fp.close();
    getch();
}

//this modifies the existing staff details

void modifyS()
{
    int no,found=0;
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Staff No. of The Staff: ";
    cin>>no;
    fp.open("staff.dat",ios::in|ios::out);
    while(fp.read((char*)&s,sizeof(staff)) && found==0)
	   {
	    if(s.retsno()==no)
		   {
		    s.showS();
		    cout<<"\nPlease Enter The New Details of staff: "<<endl;
		    s.createS(no);
		    int pos=-1*sizeof(s);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&s,sizeof(staff));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n XX Record Not Found XX ";
    getch();
}

//this deletes the staff detail

int checkDS(int no){
    fstream fp3;
        fp3.open("staff.dat",ios::in);
        while(fp3.read((char*)&s,sizeof(staff)))
	   {
	    if((s.retsno())==no)
		   {
		       return 0;
		   }
	   }
	   fp3.close();
	   return -1;
}



void deleteS()
   {
   int no;
    int found;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The shop no. of The shop You Want To Delete: ";
    cin>>no;
    fp1.open("staff.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp1.seekg(0,ios::beg);
    found=checkDS(no);
    if(found==-1){
        cout<<"\t\t XX RECORD NOT FOUND XX\n"<<endl;
        return;
    }
    while(fp1.read((char*)&s,sizeof(staff)))
	{
	 if(s.retsno()!=no)
		{
		 fp2.write((char*)&s,sizeof(staff));
		 }
	 }
    fp2.close();
    fp1.close();
    remove("staff.dat");
    rename("temp.dat","staff.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

//sets the co ordinates of the title

void title()
{
    setcoord(30,6);
    cout<<"------------------------------------------------------------";
    setcoord(40,8);
    cout<<"WELCOME TO THE TIME'S SQUARE MALL";
    setcoord(30,10);
    cout<<"------------------------------------------------------------";
}

//this function gives the option for staff details

void staffD()
{
    int ch;
    fp.open("staff.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN";
       getch();
       exit(0);
     }
    for(;;)
    {
    cout<<"\n\t\t OPTIONS: ";
    cout<<"\n\t 1. add new staff details: ";
    cout<<"\n\t 2. modify staff details: ";
    cout<<"\n\t 3. delete staff details: ";
    cout<<"\n\t 4. display staff details: ";
    cout<<"\n\t 5. exit";
    cout<<"\n\t enter the choice: ";
    cin>>ch;
    switch(ch)
    {
        case 1: addstaff();
                    break;
        case 2: modifyS();
                    break;
        case 3: deleteS();
                    break;
        case 4: display();
                    break;
        case 5: return;
        default:cout<<"\n\t XX INVALID CHOICE XX";
    }
    }
}

//this function authenticates the administrator and gives options for managing
void adminLogin()
{
    fstream f;
    string password;
    string username;
    cout<<"\n\t\tUSERNAME: ";
    cin>>username;
    cout<<"\n\t\tPASSWORD: ";
    cin>>password;
    if((username.compare("admin"))!=0 || (password.compare("1234"))!=0)
    {
        cout<<"\n\t\tWRONG USERNAME OR PASSWORD!!!!!!!!";
        return;
    }
    int ch;
    for(;;)
    {
        cout<<"\n\n\n\t\tOPTIONS FOR ADMIN: ";
        cout<<"\n\t\t------------------";
        cout<<"\n\n\t\t\t 1. STAFF DETAILS";
        cout<<"\n\n\t\t\t 2. SHOPS DETAILS";
        cout<<"\n\n\t\t\t 3. REQUESTS RECIEVED FOR RENTING A SHOP IN GALLERIA";
        cout<<"\n\n\t\t\t 4. FEEDBACKS VIEW";
        cout<<"\n\n\t\t\t 5. EXIT";
        cout<<"\n\n\t\t ENTER YOUR CHOICE:";
        cin>>ch;
        switch(ch)
        {
            case 1: staffD();
                        break;
            case 2: shopD();
                        break;
            case 3: displayR();
                        break;
            case 4: displayF();
                        break;
            case 5: return;
            default:cout<<"\n\n\t\t XX INVALID CHOICE XX";
        }
    }
    return;
}

//this function gives the options to the user/customers
void customers()
{
   int ch;
   for(;;)
   {
       cout<<"\n\n\n\t\tOPTIONS FOR  CUSTOMERS: ";
        cout<<"\n\t\t--------------------------";
        cout<<"\n\n\t\t\t 1. SHOPS DETAILS";
        cout<<"\n\n\t\t\t 2. REQUEST FOR RENTING A SHOP IN GALLERIA";
        cout<<"\n\n\t\t\t 3. TO GIVE FEEDBACK ";
        cout<<"\n\n\t\t\t 4. EXIT";
        cout<<"\n\n\t\t Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1:  displayshopC();
                        break;
            case 2: addR();
                        break;
            case 3: addF();
                        break;
            case 4: return;
            default: cout<<"\n\t XX INVALID CHOICE XX";
        }
   }
}

//MAIN FUNCTION
int main()
{
   int ch;
   title();
    for(;;)
    {
        cout<<"\n\n\n\t\tOPTIONS: ";
        cout<<"\n\n\t\t\t 1. LOGIN AS ADMINISTRATOR";
        cout<<"\n\n\t\t\t 2. VIEW AS VISITOR";
        cout<<"\n\n\t\t\t 3. EXIT";
        cout<<"\n\n\t\t ENTER YOUR CHOICE:";
        cin>>ch;
        switch(ch)
        {
            case 1: adminLogin();
                        break;
            case 2: customers();
                        break;
            case 3: exit(0);
            default: cout<<"\n\t\t XX  INVALID CHOICE PLEASE CHECK THE OPTIONS AGAIN   XX";
        }
    }
    cout<<"\n\t\t\t Thank you for visiting :)";
    return 0;
}
