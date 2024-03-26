//TASK_3
#include <iostream>
#include <string>
using namespace std;

struct Date {
    unsigned short day;
    unsigned short month;
    int year;
};

struct Address {
    string street;
    string city;
    string country;
};

struct Student {
    string sureName;
    string name;
    string middleName;
    Date birthDate;
    Address homeAddress;
    string phoneNumber;
    int* gradeExams;
    int* gradeCourseworks;
    int* gradeTests;
    int countExams;
    int countCourseworks;
    int countTests;
};

void fillStudentData(Student& student) {
    cout << "Enter surename: ";
    getline(cin, student.sureName);

    cout << "Enter name: ";
    getline(cin, student.name);

    cout << "Enter middle name: ";
    getline(cin, student.middleName);

    cout << "Enter your birth date (DD MM YYYY): ";
    cin >> student.birthDate.day >> student.birthDate.month >> student.birthDate.year;

    cin.ignore();

    cout << "Enter street: ";
    getline(cin, student.homeAddress.street);

    cout << "Enter city: ";
    getline(cin, student.homeAddress.city);

    cout << "Enter country: ";
    getline(cin, student.homeAddress.country);

    cout << "Enter phone number: ";
    getline(cin, student.phoneNumber);

    cout << "Enter the number of exams: ";
    cin >> student.countExams;
    student.gradeExams = new int[student.countExams];

    for (int i = 0; i < student.countExams; i++) {
        cout << "Enter grade for exam " << i + 1 << ": ";
        cin >> student.gradeExams[i];
    }

    cout << "Enter the number of courseworks: ";
    cin >> student.countCourseworks;
    student.gradeCourseworks = new int[student.countCourseworks];

    for (int i = 0; i < student.countCourseworks; i++) {
        cout << "Enter grade for coursework " << i + 1 << ": ";
        cin >> student.gradeCourseworks[i];
    }

    cout << "Enter the number of tests: ";
    cin >> student.countTests;
    student.gradeTests = new int[student.countTests];

    for (int i = 0; i < student.countTests; i++) {
        cout << "Enter grade for test " << i + 1 << ": ";
        cin >> student.gradeTests[i];
    }
}

void printStudentInfo(const Student& student) {
    cout << "Last Name: " << student.sureName << "\n";
    cout << "First Name: " << student.name << "\n";
    cout << "Middle Name: " << student.middleName << "\n";
    cout << "Birth Date: " << student.birthDate.day << "." << student.birthDate.month << "." << student.birthDate.year << "\n";
    cout << "Home Address: " << student.homeAddress.street << ", " << student.homeAddress.city << ", " << student.homeAddress.country << "\n";
    cout << "Phone Number: " << student.phoneNumber << "\n";

    cout << "Grades for Exams: ";
    for (int i = 0; i < student.countExams; i++) {
        cout << student.gradeExams[i] << " ";
    }
    cout << "\n";

    cout << "Grades for Courseworks: ";
    for (int i = 0; i < student.countCourseworks; i++) {
        cout << student.gradeCourseworks[i] << " ";
    }
    cout << "\n";

    cout << "Grades for Tests: ";
    for (int i = 0; i < student.countTests; i++) {
        cout << student.gradeTests[i] << " ";
    }
    cout << "\n";
}

int main() {
    Student student;

    fillStudentData(student);
    cout << "\n";

    cout << "Student Information:" << "\n\n";

    printStudentInfo(student);

    delete[] student.gradeExams;
    delete[] student.gradeCourseworks;
    delete[] student.gradeTests;

    return 0;
}

//TASK_6
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Device {
    string type;
    string name;
    string model;
    string brand;
    int warrantyPeriod; 
    double price;
    time_t saleDate; 
};

bool checkWarranty(const Device& device, time_t currentDate) {
    time_t expirationDate = device.saleDate + device.warrantyPeriod * 30 * 24 * 60 * 60;
    return expirationDate > currentDate;
}

int countSalesByName(const Device sales[], int salesCount, const string& deviceName, time_t startDate, time_t endDate) {
    int count = 0;
    for (int i = 0; i < salesCount; i++) {
        if (sales[i].name == deviceName && sales[i].saleDate >= startDate && sales[i].saleDate <= endDate) {
            count++;
        }
    }
    return count;
}

void printAllTypes(const Device sales[], int salesCount) {
    const int maxTypes = 100; 
    string deviceTypes[maxTypes];

    int typesCount = 0;
    for (int i = 0; i < salesCount; i++) {
        bool isNewType = true;
        for (int j = 0; j < typesCount; j++) {
            if (deviceTypes[j] == sales[i].type) {
                isNewType = false;
                break;
            }
        }
        if (isNewType) {
            deviceTypes[typesCount] = sales[i].type;
            typesCount++;
        }
    }

    cout << "Types of devices sold:\n";
    for (int i = 0; i < typesCount; i++) {
        cout << deviceTypes[i] << "\n";
    }
}

double calculateTotalSales(const Device sales[], int salesCount, time_t startDate, time_t endDate) {
    double totalSales = 0.0;
    for (int i = 0; i < salesCount; ++i) {
        if (sales[i].saleDate >= startDate && sales[i].saleDate <= endDate) {
            totalSales += sales[i].price;
        }
    }
    return totalSales;
}

void printWarrantyPeriod(const Device& device) {
    cout << "Warranty period for " << device.name << ": " << device.warrantyPeriod << " months\n";
}

int main() {
    const int maxSales = 100; 
    Device sales[maxSales] = {
        {"CPU", "Intel Core i7", "i7-10700K", "Intel", 6, 350.0, time(nullptr)},
        {"GPU", "NVIDIA GeForce RTX 3080", "RTX 3080", "NVIDIA", 12, 699.0, time(nullptr)},
        {"RAM", "Corsair Vengeance LPX", "CMK16GX4M2B3200C16", "Corsair", 24, 99.0, time(nullptr)}
    };

    int salesCount = 3; 

    time_t currentDate = time(nullptr);
    time_t startDate = currentDate - 365 * 24 * 60 * 60; // текущая дата минус 1 год в секундах
    time_t endDate = currentDate;

    cout << "Number of sales for CPU in the last year: " << countSalesByName(sales, salesCount, "Intel Core i7", startDate, endDate) << "\n";
    cout << "Number of sales for GPU in the last year: " << countSalesByName(sales, salesCount, "NVIDIA GeForce RTX 3080", startDate, endDate) << "\n";
    cout << "Number of sales for RAM in the last year: " << countSalesByName(sales, salesCount, "Corsair Vengeance LPX", startDate, endDate) << "\n";

    printAllTypes(sales, salesCount);

    cout << "Total sales amount for the last year: $" << calculateTotalSales(sales, salesCount, startDate, endDate) << "\n";

    cout << "\nWarranty Periods:\n";
    for (int i = 0; i < salesCount; ++i) {
        printWarrantyPeriod(sales[i]);
    }

    return 0;
}