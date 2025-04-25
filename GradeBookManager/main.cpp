#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>

struct Student {
    std::string name;
    double score;
};

std::string gradeFile = "grades.txt";

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

void loadData(std::vector<Student>& roster) {
    std::string line;
    std::ifstream in(gradeFile);

    while(std::getline(in, line)){

        int commaPos = line.find(",");

        std::string name = line.substr(0, commaPos);

        std::string score = line.substr(commaPos + 1);
        double nscore = std::stod(score);

        Student newStudent{name, nscore};
        roster.push_back(newStudent);
    }

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

    std::ofstream out(gradeFile, std::ios::out | std::ios::trunc);
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

    for(const auto& students : roster) {
        std::cout << students.name << "," << students.score << std::endl;
    }

    in.close();
}

void averageGrade(std::vector<Student>& roster) {
    int count = 0;
    double nscore = 0;

    for(const auto& students : roster) {
        nscore += students.score;
        count += 1;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average of all grades is: " << nscore / count << std::endl;
}

void minMaxGrades(std::vector<Student>& roster) {
    std::string minName;
    std::string maxName;
    double minScore = roster[0].score;
    double maxScore = roster[0].score;

    for(const auto& students : roster) {
        int current = students.score;
        if(current <= minScore){
            minName = students.name;
            minScore = students.score;
        } else if(current >= maxScore) {
            maxName = students.name;
            maxScore = students.score;
        }
    }
    std::cout << "Student with lowest score: " << minName << ", " << minScore << std::endl;
    std::cout << "Student with highest score: " << maxName << ", " << maxScore << std::endl;
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
    loadData(roster);

    while(running) {

        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        while (userChoice < 1 || userChoice > 6){
            std::cout << "Please only enter a number from 1 to 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userChoice;
        }
    
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
                averageGrade(roster);
                break;
            case(5):
                minMaxGrades(roster);
                break;
            case(6):
                running = saveAndQuit(roster);
        }

    }


    return 0;
}
