#include<iostream>
#include<vector>
#include<iterator> 
using namespace std;

enum EntityType{
	ET_Student, ET_Librarian
};

// Input validation (Exception)
void readInt(int *a){
    while(true){
        try{
            cin>>*a;
            if((bool)cin.fail() || *a<0){
                cin.clear();
                cin.ignore(10000, '\n');
                throw("Expected +ve integer. Please enter again.\n");
            }
        break;
        }catch(const char *c){
            cout<<c;
        }

    }
}


//Input validation for float.
void readFloat(float *a){
    while(true)
    {
        try{
            cin>>*a;
            if((bool)cin.fail() || *a<0){
                cin.clear();
                cin.ignore(10000, '\n');
                throw("Expected +ve real number. Please enter again.\n");
            }
            break;
        }catch(const char *c){
            cout<<c;
        }
    }
}

class Entity {  //abstract class
public:
    string name;
    string address;
    int phone;

    virtual void setDetails()=0;
    virtual void getDetails()=0;         //function definition should be done in derived class
	static Entity* create(EntityType type, short i);
};

class Student:public Entity
{
public:
    int usn;
    string branch;
    string password;

    Student(){
        setDetails();
    }

    Student(short i){
        usn = i;
        name = "XYZ";
        branch = "CSE";
        password = "password";
        address = "KLE";
        phone = 123456;

    }

    void setDetails()
    {
        cout<<"Enter Name ";
        cin>>name;
        cout<<"Enter Address: ";
        cin>>address;
        cout<<"Enter Phone no.: ";
        readInt(&phone);
        cout<<"Enter usn of the student:";
        readInt(&usn);
        cout<<"Enter the branch:";
        cin>>branch;
        cout<<"Enter the password:";
        cin>>password;
    }

    bool changePassword(){
        string pass;
        cout<<"Enter current password: ";
        cin>>pass;
        if(pass == this->password){
            cout<<"Enter new password: ";
            cin>>this->password;
            cout<<"Password change successful\n";
        } else {
            cout<<"Wrong password\n";
            return false;
        }
        return true;
    }
    void getDetails() {
        cout<<"==============Student Details==============\n";
        cout<<"USN:"<<usn<<endl;
        cout<<"Name:"<<usn<<endl;
        cout<<"Branch:"<<branch<<endl;
    }
};

class Librarian: public Entity
{
public:
    int id;
    string designation;
    int salary;
    string password;

    Librarian(){
        setDetails();
    }
    Librarian(short i){
        id = i;
        designation = "Admin";
        salary = 200000;
        password = "admin";
        name = "KLE_ADMIN";
        phone = 12345;
        address = "Vidyanagar";
    }

    void setDetails() {
        cout<<"Enter your ID";
        readInt(&id);
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Address ";
        cin>>address;
        cout<<"Enter Phone no.: ";
        readInt(&phone);
        cout<<"Enter your salary :";
        readInt(&salary);
        cout<<"Enter your designation:";
        cin>>designation;
        cout<<"Enter the password:";
        cin>>password;
    }

    void getDetails() {
        cout<<"==============Librarian Details==============\n";
        cout<<"Librarian id:"<<id<<endl;
        cout<<"Name:"<<id<<endl;
        cout<<"Designation:"<<designation<<endl;
        cout<<"Salary:"<<salary<<endl;
    }

    bool changePassword(){
        string pass;
        cout<<"Enter current password: ";
        cin>>pass;
        if(pass == this->password){
            cout<<"Enter new password: ";
            cin>>this->password;
            cout<<"Password change successful\n";
        } else {
            cout<<"Wrong password\n";
            return false;
        }
        return true;
    }

};

class Book
{
public:
    int isbn;
    string title;
    string author;
    int pages;
    float price;

    Book(){
        setDetails();
    }

    Book(int i,string t,string a,int p,float pr){
        isbn = i;
        title =t;
        author =a;
        pages = p;
        price = pr;
    }

    void setDetails() {
        cout<<"Enter ISBN: ";
        readInt(&isbn);
        cout<<"Enter Title: ";
        cin>>title;
        cout<<"Enter Author: ";
        cin>>author;
        cout<<"Enter No of pages: ";
        readInt(&pages);
        cout<<"Enter Price: ";
        readFloat(&price);
    }
    void getDetails() {
        cout<<"=======Book Details=======\n";
        cout<<"ISBN: "<<isbn<<endl;
        cout<<"Enter Title: "<<title<<endl;
        cout<<"Enter Author: "<<author<<endl;
        cout<<"Enter No of pages: "<<pages<<endl;
        cout<<"Enter Price: "<<price<<endl;
    }

};

class BookIssue
{
public:
    Book* book;
    Student* stud;
    string issue_date;
    string due_date;
    int daysLate;

    BookIssue(Book* b,Student* s, string i,string d){
        book = b;
        stud = s;
        issue_date = i;
        due_date = d;
        daysLate = 0;
    }

    void getDetails(){
        cout<<"=======Book Issue Details=======\n";
        cout<<"Issue Date : "<<issue_date<<endl;
        cout<<"Due Date : "<<issue_date<<endl;
        cout<<"Days late : "<<daysLate<<endl;
        cout<<"Fine : "<<calculateFine()<<endl;
        cout<<"Book ISBN: "<<book->isbn<<"     Issued to USN: "<<stud->usn<<endl;
    }

    float calculateFine() {
        return daysLate * 20.0;
    }
};

Entity* Entity::create(EntityType type,short i){
        if(type == ET_Student)
            return i==0?(new Student()):(new Student(i));
        else if(type == ET_Librarian)
            return i==0?(new Librarian()):(new Librarian(i));
        else return NULL;
}

class Client{
	public:
	Entity* createEntity(EntityType type,short i){
		return Entity::create(type,i);
	}
};

class Library {
public:
    int lcode;
    Client cl;
    vector<Book> bookList;
    vector<BookIssue> bIssues;
    vector<Librarian> librList;

    Library(int c,
            vector<Book> bookL,
            vector<BookIssue> bIssL,
            vector<Librarian> librL){
                lcode = c;
                bookList = bookL;
                bIssues = bIssL;
                librList = librL;
    }

    void init(){
        int ch;
        int ID;
        string pass;
        do {
            cout<<"==========Welcome==========\n";
            cout<<"Enter: \n";
            cout<<"1.Login as Librarian\n2.Login as Student\n3.Register new Librarian\n4.View all books\n5.Exit\n\n";
            readInt(&ch);
            switch(ch){
                case 1:
                    cout<<"Enter ID & password\n";
                    readInt(&ID);
                    cin>>pass;
                    loginLibr(ID,pass);
                    break;

                case 2:
                    cout<<"Enter USN & password\n";
                    readInt(&ID);
                    cin>>pass;
                    loginStud(ID,pass);
                    break;
                case 3: 
                    cout<<"New Librarian Registration\n";
                    librList.push_back(*dynamic_cast<Librarian*>(cl.createEntity(ET_Librarian,0)));
                    break;
                case 4:
                    cout<<"Books Available\n";
                    viewAllBooks();
                case 5: break;

                default:
                    cout<<"Wrong Input\n\n\n\n";
            }
        }while(ch!=5);
        
    }

    void viewAllBooks(){
        if(!bookList.empty()) {
            vector<Book>::iterator it;
            for(it = bookList.begin(); it < bookList.end(); it++)
                cout<<"Book ISBN: "<<it->isbn<<"    Book Title: "<<it->title<<"    Book Author: "<<it->author<<endl;
        } else {
            cout<<"===== Oops! No books in the library. Please add books =====\n";
        }
    }

    void loginLibr(int ID,string pass) {
        vector<Librarian>::iterator it;
        int c;
        bool flag = false;
        for(it = librList.begin(); it < librList.end(); it++){
            if(it->id == ID && it->password==pass){
                flag = true;
                break;
            }
        }

        // login success/failure
        if(!flag) {
            cout<<"\nWrong ID or Password!\n\n\n";
        } else {
            do {
                cout<<"===== Logged in as Librarian =====\n";
                cout<<"Enter: \n";
                cout<<"1.Issue Book\n2.Change password\n3.Change Student details\n4.View all Issues\n5.Add New Book\n6.Remove Book\n7.Logout\n\n";
                readInt(&c);
                switch(c){
                    case 1:
                        cout<<"Book Issue\n";
                        issueBook();
                        break;

                    case 2:
                        while(!it->changePassword()){
                            cout<<"Try Again!\n";
                        }
                        c = 7;
                        break;
                    case 3: 
                        cout<<"Change Student Details\n";
                        changeStudDetails();
                        break;
                    case 4: viewAllIssues();
                        break;
                    case 5: 
                        bookList.push_back(*(new Book()));
                        break;
                    case 6:
                        removeBook();
                        break;
                    case 7: break;
                    default:
                        cout<<"Wrong Input\n\n\n\n";
                }

            }while(c!=7);
        }
    }

    void removeBook(){
        int isbn;
        bool found = false;
        cout<<"Enter the book ISBN \n";
        readInt(&isbn);
        vector<Book>::iterator i;
        for(i = bookList.begin(); i < bookList.end(); i++) {
            if(i->isbn == isbn){
                found = true;
                break;
            }
        }
        if(found) {
            bool issued = false;
            vector<BookIssue>::iterator it;
            // Looking for the desired book
            for(it = bIssues.begin(); it< bIssues.end();it++){
                if(it->book->isbn == isbn){
                    issued = true;
                    break;
                }
            }
            if(issued) {
                cout<<"Cannot remove as the book has been issued.\n\n";
            } else {
                bookList.erase(i);
                cout<<"Book Removed!\n\n";
            }
        } else {
            cout<<"Book not found!\n\n";
        }

    }

    void viewAllIssues(){
        vector<BookIssue>::iterator it;
        for(it = bIssues.begin(); it < bIssues.end(); it++)
            it->getDetails();
    }

    void issueBook() {
        string i,d;
        int isbn;
        bool found = false;
        cout<<"Enter the book ISBN \n";
        cin>>isbn;
        vector<Book>::iterator it;
        // Looking for the desired book
        for(it = bookList.begin(); it< bookList.end();it++){
            if(it->isbn == isbn){
                found = true;
                break;
            }
        }

        if(found) {
            Book b = *it;
            cout<<"Book title: "<<b.title<<endl;
            cout<<"Enter Issue Date: ";
            cin>>i;
            cout<<"Enter Due Date: ";
            cin>>d;
            cout<<"Enter Student details\n";
            Student* s = dynamic_cast<Student*> (cl.createEntity(ET_Student,0)); // creating and casting student object
            bIssues.push_back(*(new BookIssue(&b,s,i,d)));
            cout<<"Book issued successfully!\n\n";
        } else {
            cout<<"Book not found\n\n";
        }
    }

    void changeStudDetails(){
        int usn;
        bool found =false;
        vector<BookIssue>::iterator it;
        cout<<"Enter your USN: ";
        cin>>usn;
        for(it = bIssues.begin(); it < bIssues.end();it++){
            if(it->stud->usn == usn){
                found =true;
                break;
            }
        }

        if(found){
            it->stud->setDetails();
            cout<<"Student detais have been changed\n\n";
        } else {
            cout<<"Not Found\n\n";
        }
    }

    // Student Login
    void loginStud(int usn, string pass){

        vector<BookIssue>::iterator it;
        int c;
        bool flag = false;
        for(it = bIssues.begin(); it < bIssues.end(); it++){
            if(it->stud->usn == usn && it->stud->password==pass){
                flag = true;
                break;
            }
        }

        // login success/failure
        if(!flag) {
            cout<<"\nWrong ID or Password!\n\n\n";
        } else {
            do {
                cout<<"=====Logged in as Student=====\n";
                cout<<"Enter: \n";
                cout<<"1.View Book Issued\n2.Change password\n3.Return your Book\n4.Logout\n\n";
                readInt(&c);
                switch(c){
                    case 1:
                        cout<<"Book Issue\n";
                        it->book->getDetails();
                        break;

                    case 2:
                        while(!it->stud->changePassword()){
                            cout<<"Try Again!\n";
                        }
                        c = 4;
                        break;
                    case 3: 
                        returnBook(it);
                        cout<<"You are returning your book.\n";
                        c = 4;
                        break;
                    case 4: break;
                    default:
                        cout<<"Wrong Input\n\n\n\n";
                }

            }while(c!=4);
        }

    }

    void returnBook(vector<BookIssue>::iterator it) {
        cout<<"Enter days late\n";
        readInt(&(it->daysLate));
        if(it->calculateFine()!=0){
            cout<<"Please pay your fine: "<<it->calculateFine()<<endl;
        }
        bIssues.erase(it);
    }
};

int main(){
    Client cl;
    vector<Book> bookList;
    vector<BookIssue> bIssue;
    vector<Librarian> librList;
    int i = 0;

    bookList.push_back(*(new Book(++i,"Hello world","ABC",200,25.5)));
    bookList.push_back(*(new Book(++i,"Hello Java","ABC",1000,25.5)));
    bookList.push_back(*(new Book(++i,"Hello Python","ABC",700,25.5)));
    bookList.push_back(*(new Book(++i,"Hello C++","ABC",1200,25.5)));
    bookList.push_back(*(new Book(++i,"Hello Kotlin","ABC",1100,25.5)));

    for(i = 0;i<5;i++)
        bIssue.push_back(*(new BookIssue(&bookList[i],dynamic_cast<Student*>(cl.createEntity(ET_Student,i+1)),"12-04-19","14-04-19")));

    librList.push_back(*dynamic_cast<Librarian*>(cl.createEntity(ET_Librarian,1)));      //Creating the Library Admin object

    Library lib(1,bookList,bIssue,librList);

    lib.init();
    
    return 0;
}
