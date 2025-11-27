#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    bool occupied;
    bool deleted;

    Student() {
        roll = -1;
        name = "";
        occupied = false;
        deleted = false;
    }
};

int nameValid(string &name) {
    if (name.empty()) return 0;
    if (name[0] == ' ' || name.back() == ' ') return 0;
    if (!(name[0] >= 'A' && name[0] <= 'Z')) return 0;

    for (int i = 1; i < name.size(); i++) {
        char c = name[i];

        if (!(isalpha(c) || c == ' ')) return 0;

        if (c == ' ') {
            if (i + 1 >= name.size()) return 0;
            if (name[i + 1] == ' ') return 0;
            if (!(name[i + 1] >= 'A' && name[i + 1] <= 'Z')) return 0;
        }
        else {
            if (i + 1 < name.size() && (name[i + 1] >= 'A' && name[i + 1] <= 'Z'))
                return 0;
        }
    }
    return 1;
}

class HashMap {
private:
    Student table[100];

public:

    void insert(int roll, string name) {
        int index = roll % 100;
        int start = index;
        int firstDeleted = -1;

        while (table[index].occupied || table[index].deleted) {
            if (table[index].occupied && table[index].roll == roll) {
                cout << "Roll number already exists! Insert failed.\n";
                return;
            }

            if (table[index].deleted && firstDeleted == -1)
                firstDeleted = index;

            index = (index + 1) % 100;
            if (index == start) break;
        }

        if (firstDeleted != -1)
            index = firstDeleted;

        table[index].roll = roll;
        table[index].name = name;
        table[index].occupied = true;
        table[index].deleted = false;
    }

    void search(int roll) {
        int index = roll % 100;
        int start = index;

        while (table[index].occupied || table[index].deleted) {

            if (table[index].occupied && table[index].roll == roll) {
                cout << "Roll: " << roll << "   Name: " << table[index].name << endl;
                return;
            }

            index = (index + 1) % 100;
            if (index == start) break;
        }

        cout << "Roll " << roll << " not found.\n";
    }

    void update(int roll) {
        int index = roll % 100;
        int start = index;

        do {
            if (table[index].occupied && table[index].roll == roll) {
                string newName;

                while (true) {
                    cout << "Enter new name: ";
                    getline(cin, newName);
                    if (nameValid(newName)) break;
                    cout << "Invalid Name! Try again.\n";
                }

                table[index].name = newName;
                cout << "Updated roll " << roll << " with new name: " << newName << endl;
                return;
            }

            index = (index + 1) % 100;

        } while (index != start && (table[index].occupied || table[index].deleted));

        cout << "Roll " << roll << " not found.\n";
    }

    void remove(int roll) {
        int index = roll % 100;
        int start = index;

        while (table[index].occupied || table[index].deleted) {

            if (table[index].occupied && table[index].roll == roll) {
                table[index].occupied = false;
                table[index].deleted = true;
                cout << "Deleted roll " << roll << " from index " << index << endl;
                return;
            }

            index = (index + 1) % 100;
            if (index == start) break;
        }

        cout << "Roll " << roll << " not found.\n";
    }

    void display() {
        bool empty = true;
        for (int i = 0; i < 100; i++) {
            if (table[i].occupied) {
                cout << "[" << i << "] "
                     << "Roll: " << table[i].roll
                     << "   Name: " << table[i].name << endl;
                empty = false;
            }
        }
        if (empty)
            cout << "Table is empty\n";
    }
};

int getValidNumber(string message, int minVal, int maxVal) {
    string s;
    while (true) {
        cout << message;
        getline(cin, s);

        bool ok = true;

        if (s.empty()) ok = false;

        for (char c : s) {
            if (!isdigit(c)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            long long num = stoll(s);
            if (num >= minVal && num <= maxVal)
                return num;
        }

        cout << "Invalid input! Enter digits only between "
             << minVal << " and " << maxVal << ".\n";
    }
}

int main() {
    HashMap h;
    int roll;
    string name;

    while (true) {
        cout << "\n1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Update Student\n";
        cout << "5. Display Hash Table\n";
        cout << "6. Exit\n";

        int choice = getValidNumber("Enter Choice: ", 1, 6);

        switch (choice) {
            case 1:
                roll = getValidNumber("Enter Roll Number: ", 0, 100000000);
                while (true) {
                    cout << "Enter Name: ";
                    getline(cin, name);
                    if (nameValid(name)) break;
                    else cout << "Invalid Name! Try again.\n";
                }
                h.insert(roll, name);
                break;

            case 2:
                roll = getValidNumber("Enter Roll Number to Search: ", 0, 100000000);
                h.search(roll);
                break;

            case 3:
                roll = getValidNumber("Enter Roll Number to Delete: ", 0, 100000000);
                h.remove(roll);
                break;

            case 4:
                roll = getValidNumber("Enter Roll Number to Update: ", 0, 100000000);
                h.update(roll);
                break;

            case 5:
                h.display();
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;
        }
    }
}
