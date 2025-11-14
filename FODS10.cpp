#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class Student{
public:
    int roll;
    string name;
    bool occupied;
    bool deleted;
    Student(){
        roll = -1;
        name = "";
        occupied = false;
        deleted = false;
    }
};



class HashMap{
private:
    Student table[100];  

public:
    void insert(int roll, string name){
        int index = roll % 100;
        int start = index;
       

        while(table[index].occupied || table[index].deleted){
            if(table[index].occupied && table[index].roll == roll) {
                table[index].name = name;
                return;
            }
           

            index = (index + 1) % 100;
            if(index == start){
                cout<<"Hash table full! Cannot insert "<<roll<<endl;
                return;
            }
        }



        table[index].roll = roll;
        table[index].name = name;
        table[index].occupied = true;
        table[index].deleted = false;
       
    }

    void search(int roll){
        int index = roll % 100;
        int start = index;

        while(table[index].occupied || table[index].deleted){
            if (table[index].occupied && table[index].roll == roll){
                cout<<"Roll: "<<roll<<"Name: "<<table[index].name<<endl;
                return;
            }
            index = (index + 1) % 100;
            if (index == start) break;
        }
        cout<<"Roll "<<roll <<" not found.\n";
    }

    void remove(int roll){
        int index = roll % 100;
        int start = index;

        while (table[index].occupied || table[index].deleted){
            if (table[index].occupied && table[index].roll == roll) {
                table[index].occupied = false;
                table[index].deleted = true;
                cout << "Deleted roll " << roll << " from index " << index << endl;
                return;
            }
            index = (index + 1) % 100;
            if (index == start) break;
        }
        cout << "Roll " << roll << " not found for deletion.\n";
    }

    void display(){
        bool empty = true;
        for(int i = 0; i < 100; i++) {
            if(table[i].occupied) {
                cout<<"Roll: "<<table[i].roll<<"Name: "<<table[i].name<<endl;
                empty = false;
            }
        }
        if(empty)
            cout << "Table is empty\n";
    }
};


int nameValid(string& name){
    if(name[0]==' ' || name[name.size()-1]==' ') return 0;
    if(!(name[0]>='A' && name[0]<='Z')) return 0;
    for(int i=1;i<name.size();i++){
        if(!((name[i]>='a' && name[i]<='z') || (name[i]>='A' && name[i]<='Z') || (name[i]==' '))) return 0;
        if(name[i]==' '){
            if(name[i+1]==' ') return 0;
            if(!(name[i+1]>='A' && name[i+1]<='Z')) return 0;
        }
        else{
            if((name[i+1]>='A' && name[i+1]<='Z')) return 0;
        }
    }
    return 1;
}


int valueChecker(){
    int choice;
    string line;
    while (true) {
        cout << "Enter Choice: ";
        getline(cin, line);
        stringstream ss(line);
        if (ss >> choice && ss.eof() && choice >= 1 && choice <= 8) {
            break;
        } 
        else {
            cout << "Invalid choice! Please enter a number between 1 and 8.\n";
        }
    }
    return choice;
}

int valueCheckerBT(){

    int choice;
    string line;
    while (true){
        getline(cin, line);
        stringstream ss(line);
        if (ss >> choice && ss.eof() && choice >= 0 && choice <= 100000000) {
            break;
        } 
        else {
            cout << "Invalid roll number! Please enter a number between 0 and 10000000.\n";
        }
    }
    return choice;
}

int main() {
    HashMap h;
    int roll;
    string name;
    bool flag;

    while (true){
        cout << "1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Exit\n";

        int choice = valueChecker();

        switch (choice) {
            case 1:
                cout << "Enter Roll Number: ";
                roll = valueCheckerBT();
               
                
                flag = true;
                while(flag){
                    cout << "Enter Name: ";
                    getline(cin, name);
                    if(nameValid(name)){
                        flag = false;
                    }
                    else{
                        printf("Name is Entered Wrong, Please try Again.\n");
                    }
                }
                h.insert(roll, name);
                break;

            case 2:
                cout << "Enter Roll Number to Search: ";
                roll = valueCheckerBT();
                
                
                h.search(roll);
                break;

            case 3:
                cout << "Enter Roll Number to Delete: ";
                roll = valueCheckerBT();
                h.remove(roll);
                break;

            case 4:
                h.display();
                break;

            case 5:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
