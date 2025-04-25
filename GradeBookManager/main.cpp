/*
########## TO DO ##########

1.) Add menu input
2.) Learn how to read, write, and remove from files
3.) Implement functions

void addStudent(vector<Student>&)
Prompt for name & score, validate score (0–100), then push_back.

void listStudents(const vector<Student>&)
Print a table of all entries, e.g.

Name           Score
Alice          92.5
Bob            78.0

double average(const vector<Student>&)
Sum all scores ÷ count.

Student findMin(const vector<Student>&)
Traverse to find the lowest.

Student findMax(const vector<Student>&)
Traverse to find the highest.

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>

struct Student {
    std::string name;
    double score;
};

std::string gradeFile = "grades.txt";

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

bool saveAndQuit(std::vector<Student>& roster) {
    std::ifstream in(gradeFile);
    if(!in){
        std::ofstream out(gradeFile);
        out.close();

        in.open(gradeFile);
        if(!in) {
            std::cout << "Still unable to open grades.txt\n";
        }
    }

    std::ofstream out(gradeFile, std::ios::out | std::ios::app);
    for(const auto& students : roster) {
        out << students.name << "," << students.score << std::endl;
    }

    out.close();

    std::cout << "Goodbye.";
    return false;
}


void addStudent(std::vector<Student>& roster) {
    double grade;
    std::string name;

    std::cout << "Enter student name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    std::cout << "Enter student grade: ";
    std::cin >> grade;

    Student newStudent{name, grade};
    roster.push_back(newStudent);
}

int removeStudent() {
    return 0;
}

void listStudents(std::vector<Student>& roster) {
    std::string line;
    std::ifstream in(gradeFile);
    if(!in) {
        std::ofstream out(gradeFile);
        out.close();

        in.open(gradeFile);
        if(!in) {
            std::cout << "Still unable to open grades.txt\n";
        }
    }

    if (isFileEmpty(gradeFile)){
        std::cout << "Student list is currently empty" << std::endl;
    }

    while(std::getline(in, line)){
        
    }

    in.close();
}


void menu() {
    std::cout << "###Choose Action###" << std::endl;
    std::cout << "1) Add student" << std::endl;
    std::cout << "2) Remove student" << std::endl;
    std::cout << "3) List all" << std::endl;
    std::cout << "4) Show average" << std::endl;
    std::cout << "5) Show min/max" << std::endl;
    std::cout << "6) Save & quit" << std::endl;
}


int main() {
    int userChoice;
    bool running = true;

    std::vector<Student> roster;

    while(running) {

        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;
    
        switch(userChoice) {
            case(1):
                addStudent(roster); 
                break;
            case(2):
                return 0;
                break;
            case(3):
                listStudents(roster);
                break;
            case(4):
                return 0;
                break;
            case(5):
                return 0;
                break;
            case(6):
                running = saveAndQuit(roster);
        }

    }


    return 0;
}
