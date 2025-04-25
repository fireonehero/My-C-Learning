#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>
#include <algorithm>

struct Student {
    std::string name;
    double score;
};

std::string gradeFile = "grades.txt";

std::string trim(const std::string& s){
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if(start == std::string::npos){
        return "";
    }else {
        return s.substr(start, end - start + 1);
    }
}

void loadData(std::vector<Student>& roster) {
    std::ifstream in(gradeFile);
    if (!in.is_open()) {
        std::cerr << "Error: could not open " << gradeFile << "\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        auto commaPos = line.rfind(',');
        if (commaPos == std::string::npos) {
            std::cerr << "Skipping malformed line: " << line << "\n";
            continue;
        }

        auto rawName = line.substr(0, commaPos);
        auto rawScoreStr = line.substr(commaPos + 1);
        auto name = trim(rawName);
        auto scoreStr = trim(rawScoreStr);

        if (!name.empty() && name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.size() - 2);
        }

        name = trim(name);
        scoreStr = trim(scoreStr);

        try {
            double score = std::stod(scoreStr);
            roster.push_back({ name, score });
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid score for " << name << ": " << scoreStr << "\n";
        }
    }
}

bool saveAndQuit(const std::vector<Student>& roster) {
    std::ofstream out(gradeFile);

    if (!out) {
        std::cerr << "Failed to open " << gradeFile << " for writing!\n";
        return false;
      }
      
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

    while (! (std::cin >> grade) || grade < 0.0 || grade > 100.0) {
        std::cout << "Please enter a grade from 0 to 100: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }      

    Student newStudent{name, grade};
    roster.push_back(newStudent);
}

void removeStudent(std::vector<Student>& roster) {
    std::string studentName;

    std::cout << "Enter name of student to remove: ";
    std::cin >> studentName;

    auto studentPos = std::find_if(roster.begin(), roster.end(), [&](const Student& s){ return s.name == studentName; });
    if (studentPos != roster.end()) {
        roster.erase(studentPos);
    } else {
        std::cout << "No student named " << studentName << " found.\n";
    }


}

void listStudents(const std::vector<Student>& roster) {
    if (roster.empty()) {
        std::cout << "No students in the grade book.\n";
        return;
    }      

    for(const auto& students : roster) {
        std::cout << students.name << "," << students.score << std::endl;
    }
}

void averageGrade(const std::vector<Student>& roster) {
    int count = 0;
    double nscore = 0;

    if (roster.empty()) {
        std::cout << "No students in the grade book.\n";
        return;
      }

    for(const auto& students : roster) {
        nscore += students.score;
        count += 1;
    }

    std::cout << "Average of all grades is: " << nscore / count << std::endl;
}

void minMaxGrades(const std::vector<Student>& roster) {
    if (roster.empty()) {
        std::cout << "No students in the grade book.\n";
        return;
    }   

    double minScore = roster[0].score;
    std::string minName  = roster[0].name;
    double maxScore = roster[0].score;
    std::string maxName  = roster[0].name;

    for(const auto& student : roster) {
        double current = student.score;
        if(current < minScore){
            minName = student.name;
            minScore = student.score;
        } 
        if(current > maxScore) {
            maxName = student.name;
            maxScore = student.score;
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
    std::cout << std::fixed << std::setprecision(2);
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
                removeStudent(roster);
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
