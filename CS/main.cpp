// Payroll Management System
//Abia Awais Khan 
//Las Positas College 
//Computer Science 1
//Professor Asaad Alsaad 
//April 18, 2025

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  
using namespace std;

// declare Employee
class Employee {
public:
    int id;
    string name;
    double baseSalary;
    double bonus;
    double deduction;
    // initialize employee data
    Employee(int empId, string empName,double base, double bon, double ded) {
        id = empId;
        name= empName;
        baseSalary =base;
        bonus = bon;
        deduction = ded;
    }
    // calculate thesalary
    double calculateNetSalary() {
        return baseSalary+ bonus - deduction;
    }
    // display employee 
    void display() {
        cout << "----------------------------\n";
        cout << "ID: " << id <<"\n";
        cout << "Name: "<< name<<"\n";
        cout << "Base Salary: $"<< baseSalary << "\n";
        cout << "Bonus: $"<< bonus<< "\n";
        cout <<"Deduction: $" << deduction << "\n";
        cout << "Net Salary: $" << calculateNetSalary()<<"\n";
    }
    // Save employee data 
    void saveToFile(ofstream &file) {
        file << id<< ", " << name << ", "<< baseSalary<< ", " << bonus << ", " << deduction << "\n";
    }
    // Load employee data 
    static Employee loadFromLine(string line) {
        int empId;
        string empName;
        double base, bon,ded;
        
        size_t pos;
      //-----------
        pos =line.find(",");
        empId = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
      //----------
        pos = line.find(",");
        empName= line.substr(0, pos);
        line.erase(0,  pos + 1);
      //--------
        pos =line.find(",");
        base = stod(line.substr(0, pos));
        line.erase(0, pos + 1);
      //----------
        pos = line.find(",");
        bon = stod(line.substr(0, pos));
        line.erase(0, pos + 1);
      //-----------
        ded = stod(line);
        return Employee(empId, empName, base, bon, ded);
    }
};
double inputNumber(string prompt) {
    string input;
    cout <<prompt;
    cin >> input;
    input.erase(remove(input.begin(), input.end(), ','), input.end());
    return stod(input);
}

//  ouput 
int main() {
    vector<Employee> employees; 
    int choice;
    do {
        cout << "\n--- Payroll System Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Save to File\n";
        cout << "4. Load from File\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        // Add 
        if (choice == 1) {
            int id;
            string name;
            cout << "Enter Employee ID: ";
            cin >>id;
            cin.ignore(); 
            cout << "Enter Employee Name: " ; 
            getline(cin, name); 
            double base =inputNumber("Enter Base Salary: ");
            double bonus =  inputNumber("Enter Bonus: ");
            double deduction =inputNumber("Enter Deduction: ");
            Employee emp(id, name, base, bonus, deduction);
            employees.push_back(emp);
            cout << "Employee added successfully.\n";
        } else if (choice == 2) {
            if (employees.empty()) {
                cout << "No employees to display.\n";
            } else {
                for (int i = 0; i < employees.size(); i++) {
                    employees[i].display();
                }

              
            }

        } else if (choice == 3) {
            ofstream file("employees.txt");
            for (int i = 0; i < employees.size(); i++) {
                employees[i].saveToFile(file);
            }
            file.close();
            cout <<"Data saved to employees.txt\n";
        } else if (choice == 4) {
            ifstream file("employees.txt");
            string line;
            employees.clear(); 
            while (getline(file, line)) {
                Employee emp = Employee::loadFromLine(line);
                employees.push_back(emp);
            }
            file.close();
            cout << "Data loaded from employees.txt\n";
        } else if (choice == 5) {
            cout << "Exiting Payroll System. Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
  
    return 0;
}
