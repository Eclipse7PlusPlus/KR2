#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cstdint>

using namespace std;

struct Student {
    char name[30];
    int group;
    double grade;
};

void GenerateTestFiles();
void FindNumberF1F2();
void DataEntry(Student& person);
void PrintPerson(const Student& person);
void SaveToFile(const Student& person, const string& filename);
void LoadFromFile(Student& person, const string& filename);

int main() {
    GenerateTestFiles();
    FindNumberF1F2();

    Student person;
    DataEntry(person);
    PrintPerson(person);
    SaveToFile(person, "file.txt");

    Student loadedPerson;
    LoadFromFile(loadedPerson, "file.txt");
    cout << "\nLoaded from file:\n";
    PrintPerson(loadedPerson);

    return 0;
}

void GenerateTestFiles() {
    ofstream fout("fin.txt");
    ifstream fin("fout.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Ошибка создания файлов!" << endl;
    }
    fin.close();
    fout.close();
}
Student* InputStudents(std::string& filename, int32_t numberstudents){
Student* students = new Student[numberstudents];
std::fstream file(filename);
    std::string line;
    int32_t index{1};

    while(std::getline(file,line)&& index<numberstudents){
    size_t firstpos = line.find(";");
    size_t secondpos = line.find(";", firstpos);

    std::string name = line.substr(0,firstpos);
    std::string groupstr = line.substr(firstpos-secondpos+1);
    std::string gradestr = line.substr(secondpos+1);
    int32_t group = stoi(groupstr);
    double grade = stoi(gradestr);
}
}

void PrintPerson(const Student& person) {
    cout << "\nДанные человека:\n";

    cout << "Имя: " << person.name << " " 
         <<   " "<< person.group << person.grade;

}

void SaveToFile(const Student& person, const string& filename) {
    fstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    file << person.name << ";"
        << person.group << ";"
        << person.grade << ";"<<endl;
    file.close();
    cout << "Данные сохранены в файл " << filename << endl;
}

void LoadFromFile(Student& person, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    file >> person.name
       >>person.group
       >>person.grade;

    file.close();
}
void SearchBySNP(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    Student searchSNP;
    cout << "Введите имя для поиска: ";
    std::cin >> searchSNP.name;
    
    Student person;
    bool found = false;

    while (file >> person.name
                >> person.grade
                >> person.group) {
        
        if (person.name == searchSNP.name&&
            person.group == searchSNP.group) {
            
            cout << "\nНайдена запись:\n";
            cout << "ФИО: " << person.name << " " 
                 << person.group << " " 
                 << person.grade << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "Запись не найдена." << endl;
    }

    file.close();
}
void SortByNameGroup(Student& person,const string& filename,int32_t numstudents){
    sort(person,person + numstudents, [](const Student& a, const Student& b) {
    if(a.group!=b.group){
        return a.group > b.group;
    
    }
    else{
        return a.name >b.name;
    }
});
}
void SortByName (Student& person,const string& filename,int32_t numstudents){
   sort(person,person + numstudents, [](const Student& a, const Student& b) {
    return a.name< b.name;});
}

void ShowInfoGrades(Student& person, const string& filename, int32_t numstudents){
    Student* temp = new Student[numstudents];
    copy(person, person + numstudents,temp);
    SortByNameGroup(person,filename,numstudents);
    for(int32_t i{};i<numstudents;++i){
    }
}
