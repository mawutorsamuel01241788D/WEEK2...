// Digital Attendance System
// EEE227 Mid-Semester Capstone Project

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ================= STUDENT CLASS =================
class Student {
private:
    string name;
    string indexNumber;

public:
    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }

    string getIndex() {
        return indexNumber;
    }

    string getName() {
        return name;
    }

    void saveToFile() {
        ifstream check("students.txt");
        string line;

        while (getline(check, line)) {
            if (line.find(indexNumber) != string::npos) {
                cout << "Student already exists!\n";
                check.close();
                return;
            }
        }
        check.close();

        ofstream file("students.txt", ios::app);
        file << name << "," << indexNumber << endl;
        file.close();

        cout << "Student registered successfully!\n";
    }

    static void viewStudents() {
        ifstream file("students.txt");
        string line;

        cout << "\n===== REGISTERED STUDENTS =====\n";

        if (!file) {
            cout << "No students found.\n";
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    static bool studentExists(string index) {
        ifstream file("students.txt");
        string line;

        while (getline(file, line)) {
            if (line.find(index) != string::npos) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
};

// ================= ATTENDANCE SESSION CLASS =================
class AttendanceSession {
private:
    string courseCode;
    string date;
    string startTime;
    string duration;

public:
    AttendanceSession(string c, string d, string s, string dur) {
        courseCode = c;
        date = d;
        startTime = s;
        duration = dur;
    }

    string getFileName() {
        return "session_" + courseCode + "_" + date + ".txt";
    }

    void createSession() {
        ofstream file(getFileName());
        file << "Course: " << courseCode << endl;
        file << "Date: " << date << endl;
        file << "Start Time: " << startTime << endl;
        file << "Duration: " << duration << endl;
        file << "-----------------------------\n";
        file.close();

        cout << "Session created successfully!\n";
    }

    void markAttendance(string index, string status) {
        if (!Student::studentExists(index)) {
            cout << "Student not registered!\n";
            return;
        }

        ofstream file(getFileName(), ios::app);
        file << index << "," << status << endl;
        file.close();

        cout << "Attendance marked.\n";
    }

    void displayReport() {
        ifstream file(getFileName());
        string line;

        int present = 0, absent = 0, late = 0;

        cout << "\n===== ATTENDANCE REPORT =====\n";

        if (!file) {
            cout << "Session file not found.\n";
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;

            if (line.find("Present") != string::npos)
                present++;
            else if (line.find("Absent") != string::npos)
                absent++;
            else if (line.find("Late") != string::npos)
                late++;
        }

        file.close();

        cout << "\n===== SUMMARY =====\n";
        cout << "Present: " << present << endl;
        cout << "Absent : " << absent << endl;
        cout << "Late   : " << late << endl;
    }
};

// ================= MAIN MENU =================
int main() {
    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Session\n";
        cout << "4. Mark Attendance\n";
        cout << "5. View Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, index;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Index Number: ";
            getline(cin, index);

            Student s(name, index);
            s.saveToFile();
        }

        else if (choice == 2) {
            Student::viewStudents();
        }

        else if (choice == 3) {
            string code, date, time, duration;
            cout << "Course Code: ";
            cin >> code;
            cout << "Date (YYYY_MM_DD): ";
            cin >> date;
            cout << "Start Time: ";
            cin >> time;
            cout << "Duration: ";
            cin >> duration;

            AttendanceSession session(code, date, time, duration);
            session.createSession();
        }

        else if (choice == 4) {
            string code, date, index, status;
            cout << "Course Code: ";
            cin >> code;
            cout << "Date (YYYY_MM_DD): ";
            cin >> date;

            AttendanceSession session(code, date, "", "");

            cout << "Student Index: ";
            cin >> index;

            do {
                cout << "Status (Present/Absent/Late): ";
                cin >> status;
            } while (status != "Present" && status != "Absent" && status != "Late");

            session.markAttendance(index, status);
        }

        else if (choice == 5) {
            string code, date;
            cout << "Course Code: ";
            cin >> code;
            cout << "Date (YYYY_MM_DD): ";
            cin >> date;

            AttendanceSession session(code, date, "", "");
            session.displayReport();
        }

    } while (choice != 0);

    cout << "Program exited.\n";
    return 0;
}

