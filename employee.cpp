//A C++ program to maintain an elementary database of employees using files.
#include <iostream>	
#include <string.h>
#include <conio.h>	
#include <fstream>	
#include <iomanip>	
#include <windows.h>
using namespace std;	
void gotoxy(short x,short y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

class group	            
{
    struct person	                
    {
        char flag;
        char empcode[5]; 
        char name[40]; 
        int age;
        float salary;
    }p;	                                                 
    fstream file;	                                    

public:
    group();	        //constructor
    void addrec();	    //add record
    void listrec();	    //list record
    void modirec();	    //modify record
    void delrec();	    //delete record
    void recallrec();	//retrieve deleted record
    void packrec();	    //pack record
    void exit();	    //exit
};
 
group::group()
{
    file.open("Emp.txt",ios::binary|ios::out|ios::in);		//open file in binary, read & write mode 
    if(!file)	                                            //check whether file is successfully opened
    {
        cout<<"Enable to open file"; 
        exit();
    }
}

void group::exit()
{
    file.close();	                         //close the file
}

void group::listrec()
{
    file.seekg(0);	                        //set the position of next character to be extracted from file
    int j=1;
    while(file.read((char*)&p,sizeof(p)))	//read from file until EOF
    {   
        if(p.flag!='*')	                    //display only that record for which flag is not ‘*’
        {
            cout<<"Record"<<j++; 
            cout<<setw(10)<<p.empcode<<setw(10)<<p.name<<setw(6)<<p.age<<setw(10)<<p.salary; 
            cout<<"\nPress any key....\n";
            getch();	                    //read a single character, use to hold console screen
        }
    }
    file.clear();
}

void group::delrec()
{
    char code[5]; 
    long long pos;
    unsigned count=0;
    cout<<"Enter employee code:"; 
    cin>>code;
    file.seekg(0);
    while(file.read((char*)&p,sizeof(p)))
    {
        if(strcmp(p.empcode,code)==0)	
        {
            p.flag='*';	                         //assign flag with ‘*’ to mark as deleted 
            pos = count*sizeof(p);
            file.seekp(pos);	                 //set the position of pointer in the output sequence 
            file.write((char*)&p,sizeof(p));	//writing in the new position
            return;
        }
        count++;
    }
    cout<<"No employee in file with code "<<code<<endl;
    cout<<"Press any key....";
    getch();
}

void group::addrec()
{
    char ch;
    file.seekp(0,ios::end);	            //set the position at end of file 
    do
    {
        cout<<"Enter employee code, name, age & salary\n";
        cin>>p.empcode>>p.name>>p.age>>p.salary; 
        p.flag=' ';
        file.write((char*)&p,sizeof(p));	        //writing in the file 
        cout<<"Add another record? (Y/N)";
        cin>>ch;
    }while(ch=='Y'||ch=='y');
}

void group::modirec()
{
    char code[5]; 
    long long pos;
    unsigned count=0;
    cout<<"Enter employee code:"; 
    cin>>code;
    file.seekg(0); 
    while(file.read((char*)&p,sizeof(p)))
    {
        if(p.flag==' ' && strcmp(p.empcode,code)==0)	
        {
            cout<<"Enter new record\n";
            cin>>p.empcode>>p.name>>p.age>>p.salary; 
            pos = count*sizeof(p);
            file.seekp(pos);
            file.write((char*)&p,sizeof(p));	//writing modified record in the file 
            return;
        }
        count++;
    }
    cout<<"No employee in file with code "<<code<<endl; 
	cout<<"Press any key....";
    getch();
}

void group::recallrec()
{
    char code[5];
    long long pos;
    unsigned count=0;
 
    cout<<"Enter employee code:"; 
    cin>>code;
    file.seekg(0);
    while(file.read((char*)&p,sizeof(p)))
    {
        if(strcmp(p.empcode,code)==0)	        //check empcodes are equal
        {
            p.flag=' ';	                        //assign flag with ‘ ’ to retrieve record 
            pos=count*sizeof(p);
            file.seekp(pos);
            file.write((char*)&p,sizeof(p));	//writing in the file
            return;
        }
        count++;
    }
    cout<<"No employee in file with code "<<code<<endl; 
    cout<<"Press any key....";
    getch();
}

void group::packrec()
{
    ofstream outfile;	
    outfile.open("temp.txt");	            //create a temperoray file in write mode
    file.seekg(0);
    while(file.read((char*)&p,sizeof(p)))	//copy that record for which flag is not '*'
    {
        if(p.flag!='*')
            outfile.write((char*)&p,sizeof(p));
    }
    outfile.close();	
    file.close();
    remove("Emp.txt");	
    rename("temp.txt","Emp.txt");	                    //rename file 
    file.open("Emp.txt",ios::binary|ios::in|ios::out);	//open file in binary, read & write mode
}

int main()
{
    char choice;
    group g;	
    do
    {
        system("cls");
        gotoxy(30,10); 
        cout<<"1. Add records"; 
        gotoxy(30,11);
        cout<<"2. List records"; 
        gotoxy(30,12);
        cout<<"3. Modify records";
        gotoxy(30,13);
        cout<<"4. Delete records"; 
        gotoxy(30,14);
        cout<<"5. Recall records";
        gotoxy(30,15);
        cout<<"6. Pack records";
        gotoxy(30,16);
        cout<<"0. Exit"; 
        gotoxy(30,18);

        cout<<"Your choice ?";
        cin>>choice;

        system("cls"); 
        switch(choice)
        {
            case '1': g.addrec(); break;
            case '2': g.listrec(); break;
            case '3': g.modirec(); break;
            case '4': g.delrec(); break;
            case '5': g.recallrec(); break;
            case '6': g.packrec(); break;
            case '0': g.exit();
        }
    }while(choice!='0');

return 0;
}

