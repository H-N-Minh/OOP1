#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include<bits/stdc++.h>


using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

const size_t STUDENT_NO {4};
const size_t QUIT {69};


class Error : public std::exception {
    string mss_;
public:
    Error(string mss) : mss_{mss} {}

    const string whatis() const noexcept { return mss_; }
};


class Dynamics {
    string name_;

public:
    Dynamics(string name) : name_{name} {}

    virtual ~Dynamics() = default;

    // special methods
    string getName() const { return name_; }
};


struct Drinks : public Dynamics {
    float liter_;
public:
    Drinks(string name, float liter) : Dynamics(name), liter_{liter} {}

    void sipping() {
        liter_ -= 0.1;
    }
};


class Food : public Dynamics {
    size_t amount_;
public:
    Food(string name) : Dynamics(name), amount_{100} {}

    void eating (size_t n_ppl) {
        // reduce the amount of food depends on number of ppl eating
        amount_ /= std::pow(2, n_ppl);
    }
    size_t getAmount() const {
        return amount_;
    }
};


class Student : public Dynamics {
public:
    shared_ptr<Drinks> drinks_;
    shared_ptr<Food> food_;
    Student(string name) : Dynamics(name), drinks_{nullptr}, food_{nullptr} {}
};


class Table {
    Table() {
        // Fill table with empty nullpter
        for (size_t __ = 0; __ < STUDENT_NO + 1; __++)
        {
            vector<std::shared_ptr<Dynamics>> row;
            for (size_t _ = 0; _ < STUDENT_NO; _++)
            {
                row.push_back(nullptr);
            }
            board_.push_back(row);
        }
    }
public:
    static vector<vector<std::shared_ptr<Dynamics>>> board_;

    // SINGLETON
    Table(const Table& other) = delete;
    Table operator= (const Table& other) = delete;
    static const unique_ptr<Table>& init() {
        static const unique_ptr<Table> instance_ {new Table};
        return instance_;
    }
    // Special methods
    friend std::ostream& operator<< (std::ostream& out, const unique_ptr<Table>& table);

    // methods
    vector<string> getValidMoves() {
    // returns string of all valid moves
        vector<string> moves;
        moves.push_back("quit");
        moves.push_back("show");
        
        bool eatable = false;  // helper var for checking if cmd Drink or Eat is valid
        bool drinkable = false; 

        for (size_t i = 0; i < STUDENT_NO * 2; i++)
        {
            size_t row_student, row_drink, col;
            size_t row_food = 2;
            if (i < STUDENT_NO) { row_student = 0, row_drink = 1, col = i; }
            else { row_student = 4, row_drink = 3, col = STUDENT_NO*2 - i - 1; }

            // sit
            if (board_[row_student][col] == nullptr) {
                moves.push_back("sit " + std::to_string(i));
                continue;
            }
            // leave
            moves.push_back("leave " + std::to_string(i));
            // order & drink & pass
            if (board_[row_drink][col] == nullptr) {
                moves.push_back("order " + std::to_string(i));
            }
            else if (!drinkable)
            {
                moves.push_back("drink");
                moves.push_back("pass");
                drinkable = true;
            }
            // food
            if (board_[row_food][col] == nullptr) {
                moves.push_back("food " + std::to_string(i));
            }
            else if (!eatable) {
                moves.push_back("eat");
                eatable = true;
            }
        }
        return moves;
    }
};


vector<vector<std::shared_ptr<Dynamics>>> Table::board_;

// Functions

std::ostream& operator<< (std::ostream& out, const unique_ptr<Table>& table) {
// print the table with cout
    out << "0 1 2 3" << endl;
    for (auto row : table->board_)
    {
        size_t counter {0};
        for (auto dym : row)
        {
            // letters
            if (dym == nullptr)
            {                
                out << ".";
            }
            else {
                out << dym->getName();
            }
            // space between letters
            if (counter++ < STUDENT_NO - 1)
            {
                out << "-";
            }
        }
        out << endl;
    }
    out << "7 6 5 4" << endl << endl;
    return out;
}

//commands

void sit(size_t i) {
    string name;
    size_t row, col;
    if (i < STUDENT_NO)
    {
        name = "M", row = 0, col = i;
    }
    else
    {
        name = "W", row = 4, col = STUDENT_NO*2 - i - 1;
    }
    shared_ptr<Student> hi (new Student(name));
    Table::board_[row][col] = hi;
    hi->food_ = std::dynamic_pointer_cast<Food> (Table::board_[2][col]);
}

void order(size_t i, float liter) {
    shared_ptr<Drinks> drinks {new Drinks("o", liter)};
    if (i < STUDENT_NO)
    {
        Table::board_[1][i] = drinks;   // for table 
        shared_ptr<Student> student = std::dynamic_pointer_cast<Student>(Table::board_[0][i]) ;
        student->drinks_ = drinks;   // for student
    }
    else
    {
        Table::board_[3][STUDENT_NO*2 - i - 1] = drinks;   // for table  
        shared_ptr<Student> student = std::dynamic_pointer_cast<Student>(Table::board_[4][STUDENT_NO*2 - i - 1]);
        student->drinks_ = drinks;   // for student
    }
}

void leave(size_t i) {
    size_t row_student, row_drink, col;
    size_t row_food = 2;
    if (i < STUDENT_NO)
    {   
        row_student = 0, row_drink = 1, col = i;
    }
    else {
        row_student = 4, row_drink = 3, col = STUDENT_NO*2 - i - 1;
    }
    shared_ptr<Student> student = std::dynamic_pointer_cast<Student>(Table::board_[row_student][col]) ;
    student->drinks_ = nullptr;   // remove drink from student
    Table::board_[row_drink][col] = nullptr;    // remove drink from table
    Table::board_[row_student][col] = nullptr;      // remove student from table
    if ((student->food_ != nullptr) && (student->food_.use_count() == 2)) { // remove food from table if no one eats
        student->food_ = nullptr;
        Table::board_[row_food][col] = nullptr;
    }
}

void food(size_t i) {
    shared_ptr<Food> food { new Food("0") };
    if (i >= STUDENT_NO) { i = STUDENT_NO*2 - i - 1; }
    Table::board_[2][i] = food;     // set food on table

    // assign food to students
    if (Table::board_[0][i] != nullptr) {
        shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[0][i]);
        student->food_ = food;
    }
    if (Table::board_[4][i] != nullptr) {
        shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[4][i]);
        student->food_ = food;
    }
}

void report() {
    // show ptr of food and drink of each student
    for (size_t counter = 0; counter < 8; counter++)
    {
        size_t i = counter < STUDENT_NO ? counter : STUDENT_NO*2 - counter - 1;
        cout << "Student " << counter << ": " << Table::board_[counter < STUDENT_NO ? 0 : 4][i] << endl;
        if (Table::board_[counter < STUDENT_NO ? 0 : 4][i] != nullptr)
        {
            shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[counter < STUDENT_NO ? 0 : 4][i]);
            cout << "    drink: " << student->drinks_ << "      food: " << student->food_ << endl;
        }
    }
    cout << endl;

    /*/ show ptr of each square of table
    for (size_t row = 0; row < 5; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            cout << row << "_" << col << " : " << Table::board_[row][col] << endl;
        }
    }  */

    //show amount of food on table
    for (size_t col = 0; col < STUDENT_NO; col++)
    {
        if (Table::board_[2][col] != nullptr)
        {
            shared_ptr<Food> food = std::dynamic_pointer_cast<Food> (Table::board_[2][col]);
            cout << food->getAmount() << " of food left on col " << col << endl;
        }
    }    
}

void pass() {
    shared_ptr<Drinks> temp_old = nullptr, temp_new = nullptr;

    // prepare for marking the first student of the loop
    shared_ptr<Student> first_student;
    size_t first_row, first_col;
    bool found_first = false;

    // goes through every seat clockwise
    for (size_t count = 0; count < STUDENT_NO * 2 ; count++)
    {
        size_t row_student = count < STUDENT_NO ? 0 : 4, col = count < STUDENT_NO ? count : STUDENT_NO*2 - count - 1;
        size_t row_drink = row_student == 0 ? 1 : 3;

        // skip if seat has no student
        if (Table::board_[row_student][col] == nullptr) { continue; }
        
        // set new drinks
        shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[row_student][col]);
        temp_new = student->drinks_;
        student->drinks_ = temp_old;
        Table::board_[row_drink][col] = temp_old;
        temp_old = temp_new;

        // marking the first student of the loop
        if (!found_first) {
            first_student = student, first_col = col, first_row = row_drink, found_first = true;
        }
    }

    // giving the first student his actual drink
    first_student->drinks_ = temp_old;
    Table::board_[first_row][first_col] = temp_old;
}

void sip() {
    for (size_t i = 0; i < STUDENT_NO * 2; i++)
    {
        size_t row_drink = i < STUDENT_NO ? 1 : 3, col = i < STUDENT_NO ? i : STUDENT_NO*2 - i - 1;
        size_t row_student = (row_drink == 1 ? 0 : 4);

        if (Table::board_[row_drink][col] != nullptr)
        {
            shared_ptr<Drinks> drink = std::dynamic_pointer_cast<Drinks> (Table::board_[row_drink][col]);
            drink->sipping();

            if (drink->liter_ < 0.0)
            {
                Table::board_[row_drink][col] = nullptr;
                shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[row_student][col]);
                student->drinks_ = nullptr;
            }
        }
    }
}

void eat() {
    for (size_t col = 0; col < STUDENT_NO; col++)
    {
        size_t row = 2;

        if (Table::board_[row][col] != nullptr)
        {
            shared_ptr<Food> food = std::dynamic_pointer_cast<Food> (Table::board_[row][col]);
            food->eating(food.use_count() -2);   // 1 for the board and 1 for this var itself, so -2

            //remove food if dish empty
            if (food->getAmount() < 10)
            {
                Table::board_[row][col] = nullptr;
                if (Table::board_[0][col] != nullptr) {
                    shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[0][col]);
                    student->food_ = nullptr;
                }
                if (Table::board_[4][col] != nullptr) {
                    shared_ptr<Student> student = std::dynamic_pointer_cast<Student> (Table::board_[4][col]);
                    student->food_ = nullptr;
                }
            }
        }
    }
}

bool isFloat( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail(); 
}

vector<string> getCommand() {
    // get input to lowercase
    cout << "Enter your move: ('show' to show all moves)\n";
    string sentence, word;
    std::getline(std::cin, sentence);
    std::istringstream istream {sentence};
    vector<string> input;
    while (istream >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        input.push_back(word);
    }
    return input;
}

vector<string> getValidMove(const unique_ptr<Table>& table) {
    while (true)
    {
        try
        {
            cout << table;
            vector<string> input = getCommand();
            // unknown first cmd
            vector<string> valid_first_cmd { "sit", "order", "leave", "food", "pass", "show", "drink", "eat", "quit" };
            if (std::find(valid_first_cmd.begin(), valid_first_cmd.end(), input[0]) == valid_first_cmd.end())
            {
                throw Error("Unknown command!");
            }
            // wrong number of argument
            vector<string> valid_single_cmd { "pass", "drink", "eat", "show", "quit" };
            vector<string> valid_two_cmd { "sit", "leave", "food" };
            if (std::find(valid_single_cmd.begin(), valid_single_cmd.end(), input[0]) != valid_single_cmd.end() 
                && input.size() != 1)
            {
                throw Error("Wrong number of arguments!");
            }
            else if (std::find(valid_two_cmd.begin(), valid_two_cmd.end(), input[0]) != valid_two_cmd.end() 
                && input.size() != 2)
            {
                throw Error("Wrong number of arguments!");
            }
            else if (input[0] == "order" && input.size() != 3) {
                throw Error("Wrong number of arguments!");
            }
            
            // invalid argument
            vector<string> valid_moves = table->getValidMoves();
            string move = input.size() == 1 ? input[0] : input[0] + " " + input[1];
            if (std::find(valid_moves.begin(), valid_moves.end(), move) == valid_moves.end())
            {
                throw Error("Invalid move!");
            }
            if (input[0] == "order") {
                if ((!isFloat(input[2])) || (std::stof(input[2]) <= 0))
                {
                    throw Error("Invalid liter!");
                }
            }

            // if no error are thrown then input is correct
            return input;
        }
        catch(const Error& e)
        {
            cout << e.whatis() << '\n';
        }
    }
}

size_t executeCMD (vector<string> cmd, const unique_ptr<Table>& table) {
    if (cmd[0] == "show")
    {
        cout << "Valid commands are: \n";
        for (string x : table->getValidMoves())
        {
            cout << x << " | ";
        }
        cout << endl;
    }
    else if (cmd[0] == "quit") { cout << "Thanks for playing"; return QUIT; }
    else if (cmd[0] == "sit") { sit(std::stoi(cmd[1])); }
    else if (cmd[0] == "order") { order( std::stoi(cmd[1]), std::stof(cmd[2]) ); }
    else if (cmd[0] == "leave") { leave(std::stoi(cmd[1])); }
    else if (cmd[0] == "food") { food(std::stoi(cmd[1])); }
    else if (cmd[0] == "pass") { pass(); }
    else if (cmd[0] == "drink") { sip(); }
    else if (cmd[0] == "eat") { eat(); }
    
    return 0;
}

//###################################################################################################

//#########################################################
int main() {
    const unique_ptr<Table>& table { Table::init() };
      
    cout << "welcome \n";
    while (true)
    {
        vector<string> cmd = getValidMove(table);
        if (executeCMD(cmd, table) == QUIT) {
            return 0;
        }
    }
}
