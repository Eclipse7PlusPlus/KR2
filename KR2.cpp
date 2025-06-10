#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>

struct Student {
    char name[30];
    int group;
    double grade;
};

void GenerateTestFile();
int CountStudentsInFile(const std::string& filename);
Student* LoadStudentsFromFile(const std::string& filename, int count);
void SaveStudentsToFile(const std::string& filename, Student* students, int count);
void PrintStudent(const Student& student);
void PrintAllStudents(Student* students, int count);
void SearchByName(Student* students, int count);
void SortByName(Student* students, int count);
void SortByGroupAndName(Student* students, int count);
void ShowAverageGrades(Student* students, int count);

int main() {
    const std::string filename = "students.txt";
    GenerateTestFile();
    
    int studentCount = CountStudentsInFile(filename);
    Student* students = LoadStudentsFromFile(filename, studentCount);
    
    int choice;
    do {
        std::cout << "\n=== Student Database Menu ===\n";
        std::cout << "1. Show all students\n";
        std::cout << "2. Search student by name\n";
        std::cout << "3. Sort students by name\n";
        std::cout << "4. Sort students by group and name\n";
        std::cout << "5. Show average grades\n";
        std::cout << "0. Exit and save changes\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                PrintAllStudents(students, studentCount);
                break;
            case 2:
                SearchByName(students, studentCount);
                break;
            case 3:
                SortByName(students, studentCount);
                std::cout << "Students sorted by name.\n";
                break;
            case 4:
                SortByGroupAndName(students, studentCount);
                std::cout << "Students sorted by group and name.\n";
                break;
            case 5:
                ShowAverageGrades(students, studentCount);
                break;
            case 0:
                SaveStudentsToFile(filename, students, studentCount);
                std::cout << "Changes saved to file. Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 0);

    delete[] students;
    return 0;
}

void GenerateTestFile() {
    std::ofstream file("students.txt");
    if (file.is_open()) {
        file << "Ivanov;101;4.5\n";
        file << "Petrov;102;3.8\n";
        file << "Sidorov;101;4.2\n";
        file << "Smirnov;103;5.0\n";
        file.close();
    }
}

int CountStudentsInFile(const std::string& filename) {
    std::ifstream file(filename);
    int count = 0;
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }
    
    file.close();
    return count;
}

Student* LoadStudentsFromFile(const std::string& filename, int count) {
    Student* students = new Student[count];
    std::ifstream file(filename);
    
    for (int i = 0; i < count; i++) {
        std::string line;
        std::getline(file, line);
        
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        
        strncpy(students[i].name, line.substr(0, pos1).c_str(), 29);
        students[i].name[29] = '\0';
        students[i].group = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        students[i].grade = std::stod(line.substr(pos2 + 1));
    }
    
    file.close();
    return students;
}

void SaveStudentsToFile(const std::string& filename, Student* students, int count) {
    std::ofstream file(filename);
    
    for (int i = 0; i < count; i++) {
        file << students[i].name << ";" 
             << students[i].group << ";" 
             << students[i].grade << "\n";
    }
    
    file.close();
}

void PrintStudent(const Student& student) {
    std::cout << "Name: " << student.name 
              << ", Group: " << student.group 
              << ", Average grade: " << student.grade << "\n";
}

void PrintAllStudents(Student* students, int count) {
    std::cout << "\n=== All Students ===\n";
    for (int i = 0; i < count; i++) {
        PrintStudent(students[i]);
    }
}

void SearchByName(Student* students, int count) {
    char searchName[30];
    std::cout << "Enter student name to search: ";
    std::cin.getline(searchName, 30);
    
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, searchName) == 0) {
            std::cout << "Student found:\n";
            PrintStudent(students[i]);
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "Student not found.\n";
    }
}

void SortByName(Student* students, int count) {
    std::sort(students, students + count, [](const Student& a, const Student& b) {
        return strcmp(a.name, b.name) < 0;
    });
}

void SortByGroupAndName(Student* students, int count) {
    std::sort(students, students + count, [](const Student& a, const Student& b) {
        if (a.group != b.group) {
            return a.group < b.group;
        }
        return strcmp(a.name, b.name) < 0;
    });
}

void ShowAverageGrades(Student* students, int count) {
    std::cout << "\n=== Average Grades ===\n";
    for (int i = 0; i < count; i++) {
        std::cout << students[i].name << ": " << students[i].grade << "\n";
    }
}
