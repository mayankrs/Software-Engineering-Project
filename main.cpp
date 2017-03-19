#include<stdio.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>

using namespace std;

class User{
  int userID;
  char name[50];
  char username[25];
  char password[25];
protected:
  char firstname[50];
  char lastname[50];
public:
  User(){

  }

  User(char name[],char username[],char password[]){
    strcpy(this->name,name);
    strcpy(this->username,username);
    strcpy(this->password,password);
  }

  void setName(char name[]){
    strcpy(this->name,name);
  }

  void setUsername(char username[]){
    strcpy(this->username,username);
  }

  void setPassowrd(char password[]){
    strcpy(this->password,password);
  }

  void setUserID(int userID){
    this->userID = userID;
  }

  int getUserID(){
    return userID;
  }

  char* getName(){
    return name;
  }

  char* getUsername(){
    return username;
  }

  char* getPassword(){
    return password;
  }
};

class Bill{
public:
  int custNo;
  int rentAmt;
  int foodAmt;
  int servicesAmt;
  int billID;
public:
  Bill(){

  }
  Bill(int custNo,int rentAmt=0,int servicesAmt=0){
    this->custNo = custNo;
    this->rentAmt = rentAmt;
    this->servicesAmt = servicesAmt;
    this->foodAmt = 0;
    billID = custNo;
  }

  void addRentAmt(int amt){
    rentAmt += amt;
  }

  void addFoodAmt(int amt){
    foodAmt += amt;
  }

  void addServicesAmt(int amt){
    servicesAmt += amt;
  }
};

class Customer:public User{
  int custNo;
  int roomType;
  int age;
  char phoneNo[100];
public:
  Customer(){

  }
  Customer(char name[],char username[],char password[],char firstname[],char lastname[],char phoneNo[],int age,int roomType):User(name,username,password){
    this->age = age;
    strcpy(this->firstname,firstname);
    strcpy(this->lastname,lastname);
    strcpy(this->phoneNo,phoneNo);
    this->roomType = roomType;
  }

  int setCustNo(int custNo){
    this->custNo = custNo;
  }

  int getCustNo(){
    return custNo;
  }

  int getAge(){
    return age;
  }

  char* getPhoneNo(){
    return phoneNo;
  }

  void addFood(int amt){
    Bill B;

    ifstream infile;
    string filename = "bills.txt";
    infile.open(filename.c_str(),ios::in);

    ofstream outfile;
    string filename2 = "bills2.txt";
    outfile.open(filename2.c_str(),ios::out);

    while(infile.read((char*)&B,sizeof(Bill))){
      if(B.custNo == custNo){
        B.addFoodAmt(amt);
        outfile.write((char*)&B,sizeof(Bill));
      }else{
        outfile.write((char*)&B,sizeof(Bill));
      }
    }

    outfile.close();
    infile.close();

    remove(filename.c_str());
    rename("bills2.txt","bills.txt");
  }

  void addServices(int amt){
    Bill B;

    ifstream infile;
    string filename = "bills.txt";
    infile.open(filename.c_str(),ios::in);

    ofstream outfile;
    string filename2 = "bills2.txt";
    outfile.open(filename2.c_str(),ios::out);

    while(infile.read((char*)&B,sizeof(Bill))){
      if(B.custNo == custNo){
        B.addServicesAmt(amt);
        outfile.write((char*)&B,sizeof(Bill));
      }else{
        outfile.write((char*)&B,sizeof(Bill));
      }
    }

    outfile.close();
    infile.close();

    remove(filename.c_str());
    rename("bills2.txt","bills.txt");
  }

  void addRent(int amt,int days){
    int total = amt*roomType*days;

    Bill B;

    ifstream infile;
    string filename = "bills.txt";
    infile.open(filename.c_str(),ios::in);

    ofstream outfile;
    string filename2 = "bills2.txt";
    outfile.open(filename2.c_str(),ios::out);

    while(infile.read((char*)&B,sizeof(Bill))){
      if(B.custNo == custNo){
        B.addRentAmt(total);
        outfile.write((char*)&B,sizeof(Bill));
      }else{
        outfile.write((char*)&B,sizeof(Bill));
      }
    }

    outfile.close();
    infile.close();

    remove(filename.c_str());
    rename("bills2.txt","bills.txt");
  }

  int checkOut(){
    Customer X;

    ifstream infile;
    infile.open("customers.txt",ios::in);

    ofstream outfile;
    outfile.open("customers2.txt",ios::out);

    while(infile.read((char*)&X,sizeof(Customer))){
      if(X.getCustNo() != custNo){
        outfile.write((char*)&X,sizeof(Customer));
      }
    }

    infile.close();
    outfile.close();

    remove("customers.txt");
    rename("customers2.txt","customers.txt");

    return custNo;
  }

};


class Staff: public User{
  int staffNo;
  int age;
  char designation[50];

public:
  Staff(){

  }
  Staff(char name[],char username[],char password[],char firstname[], char lastname[],int age,char designation[]):User(name,username,password){
    strcpy(this->firstname,firstname);
    strcpy(this->lastname,lastname);
    strcpy(this->designation,designation);
    this->age = age;
  }

  void setStaffNo(int staffNo){
    this->staffNo = staffNo;
  }

  int getStaffNo(){
    return staffNo;
  }

  char* getFirstname(){
    return firstname;
  }

  char *getLastname(){
    return lastname;
  }

  int getAge(){
    return age;
  }

  char* getDesignation(){
    return designation;
  }

  void generateBill(int id){
    Bill B;

    ifstream infile;
    string filename = "bills.txt";
    infile.open(filename.c_str(),ios::in);

    ofstream outfile;
    outfile.open("bill2.txt",ios::in);


    while(infile.read((char*)&B,sizeof(Bill))){
      if(B.billID == id){
        int total = B.foodAmt+B.rentAmt+B.servicesAmt;
        cout<<"----------INVOICE----------\n";
        cout<<"--Rent Amount = "<<B.rentAmt<<"--\n";
        cout<<"--Food Charges = "<<B.foodAmt<<"--\n";
        cout<<"--Service Charges = "<<B.servicesAmt<<"--\n";
        cout<<"-----------------------------\n";
        cout<<"--Subtotal = "<<total<<"--\n";
        cout<<"------------------------------\n";
        cout<<"--Total(Inclusive of 15% Tax) = "<<total*1.15<<"--\n";
      }else{
        outfile.write((char*)&B,sizeof(Bill));
      }
    }

    infile.close();
    outfile.close();

    remove("bills.txt");
    rename("bills2.txt","bills.txt");
  }

  void registerCustomer(){
    char username[50],password[50],firstname[50],lastname[50],phoneNo[10];
    int age,custNo,roomType;

    cout<<"Enter Username: ";
    cin>>username;
    cout<<"Enter Password: ";
    cin>>password;
    cout<<"Enter Firstname: ";
    cin>>firstname;
    cout<<"Enter Lastname: ";
    cin>>lastname;
    cout<<"Enter your Phone Number: ";
    cin>>phoneNo;
    cout<<"Enter your age: ";
    cin>>age;
    cout<<"Enter Room Type: ";
    cin>>roomType;

    char name[100];
    strcat(name,firstname);
    strcat(name," ");
    strcat(name,lastname);
    int id = age+phoneNo[0]-48;
    Customer C(name,username,password,firstname,lastname,phoneNo,age,roomType);
    C.setCustNo(id);

    string filename = "customers.txt";

    ofstream outfile;
    outfile.open(filename.c_str(),ios::out | ios::app);
    outfile.write((char*)(&C),sizeof(Customer));
    outfile.close();

    Bill B(id);
    outfile.open("bills.txt",ios::out|ios::app);
    outfile.write((char*)(&B),sizeof(Bill));
    outfile.close();
  }

  void addStaffMember(){
    char name[100],username[50],password[50], firstname[50],lastname[50],designation[50];
    int age;
    cout<<"Enter Username: ";
    cin>>username;
    cout<<"Enter Password: ";
    cin>>password;
    cout<<"Enter Firstname: ";
    cin>>firstname;
    cout<<"Enter Lastname: ";
    cin>>lastname;
    cout<<"Enter designation: ";
    cin>>designation;
    cout<<"Enter the Age: ";
    cin>>age;

    strcat(name,firstname);
    strcat(name," ");
    strcat(name,lastname);

    Staff S(name,username,password,firstname,lastname,age,designation);

    //int id = lastUserId();
    S.setStaffNo(age+username[0]);

    string filename = "staff.txt";

    ofstream outfile;
    outfile.open(filename.c_str(),ios::out | ios::app);
    outfile.write((char*)&S,sizeof(Staff));
    outfile.close();
  }

};



Staff staffLogin(char username[],char password[],int &status){
  //THIS Function returns the staff ID incase login is successful else returns -1
  string filename = "staff.txt";

  ifstream infile;
  infile.open(filename.c_str(),ios::in);

  Staff S;
  while(infile.read((char *)&S,sizeof(Staff))){
    if(!(strcmp(username,S.getUsername())) && !(strcmp(password,S.getPassword()))){
      status = 1;
      break;
    }
  }
  infile.close();

  return S;
}

Customer customerLogin(char username[],char password[],int &success){
  //THIS Function returns the Customer ID incase login is successful else returns -1
  string filename = "customers.txt";

  ifstream infile;
  infile.open(filename.c_str(),ios::in);

  Customer C;
  int flag = 0;
  while(infile.read((char *)&C,sizeof(Customer))){
    if(!(strcmp(username,C.getUsername())) && !(strcmp(password,C.getPassword()))){
      success = 1;
      break;
    }
  }

  infile.close();

  return C;
}


//FUNCTION Prototypes
void logged_in_as_staff(Staff);
void logged_in_as_customer(Customer);

int main(){
  bool logged_in = false;
  int logged_in_as = -1; //if STAFF = 0, ELSE IF CUSTOMER + 2;
  do{
    if(logged_in == false){
      int ch;
      char username[50], password[50];
      cout<<"1.Log in as Staff\n2.Log in as Customer\n3.Exit\nEnter your choice: ";
      cin>>ch;
      switch(ch){
        case 1:
        {
          cout<<"Username: ";
          cin>>username;
          cout<<"Password: ";
          cin>>password;
          int status = 0;
          Staff S = staffLogin(username,password,status);
          if(status == 1){
              logged_in = true;
              logged_in_as_staff(S);
              logged_in = false;
          }else{
            cout<<"Wrong Login Credentials\n";
          }
        }
        break;
        case 2:
        {
          cout<<"Username: ";
          cin>>username;
          cout<<"Password: ";
          cin>>password;
          int status = 0;
          Customer C = customerLogin(username,password,status);
          if(status == 1){
            logged_in = true;
            logged_in_as_customer(C);
            logged_in = false;
          }else{
            cout<<"Wrong Login Credentials\n";
          }
        }
        break;
        case 3:
        {
          exit(0);
        }
        break;
        default:
          cout<<"Enter a valid option\n";
      }
    }
  }while(logged_in == false);
}


void logged_in_as_staff(Staff S){
  //MAKE CHANGES HERE FOR STAFF ACTIONS
  cout<<"Logged in as Staff\n";
  do{
    int ch;
    cout<<"1. Check-In Customer\n2. Add Staff\n3. Generate Bill\n4.Logout\nEnter your choice: \n";
    cin>>ch;
    switch(ch){
      case 1:
      {
        S.registerCustomer();
      }
      break;
      case 2:
      {
        S.addStaffMember();
      }
      break;
      case 3:
      {
        int id;
        cout<<"Enter Bill ID: ";
        cin>>id;
        S.generateBill(id);
      }
      break;
      case 4:
      {
        return;
      }
      break;
      default:
      cout<<"Enter Valid Option\n";
    }
  }while(1);

}

void logged_in_as_customer(Customer C){
  //MAKE CHANGES HERE FOR USER ACTIONS
  cout<<"Logged in as Customer\n"<<endl;

  do{
    int ch;
    cout<<"1. Order food\n2. Room Service\n3. Check out\n4.Logout\nEnter your choice: \n";
    cin>>ch;
    switch(ch){
      case 1:
      {
        C.addFood(150);
      }
      break;
      case 2:
      {
        C.addServices(300);
      }
      break;
      case 3:
      {
        int days;
        cout<<"Number of Days: ";
        cin>>days;
        C.addRent(1500,days);
        int id = C.checkOut();
        cout<<"Your Bill ID is "<<id<<". Please produce this to the receptionist.\n";
        return;
      }
      break;
      case 4:
      {
        return;
      }
      break;
      default:
      cout<<"Enter Valid Option\n";
    }
  }while(1);
}
