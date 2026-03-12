
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "../Major.hpp"

using std::string;
using std::ifstream;
using std::istringstream;
using std::vector;
using std::cout;
using std::endl;


void parseFile(const string& fname, vector<Major*>& majors_) {
    ifstream file{fname};
    if (!file.is_open()) { cout << "No such file found" << endl; }
    
    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream isline{line};
        string token;
        int i {0};
        vector<string> str;
        vector<unsigned> ul;
        while(getline(isline, token, ',')) {
            if (i < 2) {
                str.push_back(token);
            } else {
                unsigned t = std::stoul(token, nullptr, 0);
                ul.push_back(t);
            }
            i++;
        }
        majors_.push_back(new Major(str.at(0), str.at(1), ul.at(0), ul.at(1), ul.at(2), ul.at(3), ul.at(4)));
    }
    file.close();
}

int main() {
    vector<Major*> majors_;
    parseFile("../Studierendenstatistik.csv", majors_);
    for (Major* major : majors_) {
        cout << major->getName() << endl;
    }
}