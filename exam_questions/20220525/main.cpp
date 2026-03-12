#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

// class String:

class String {
protected:
    vector<char> string_;
public:
    String(char* str) {
        for (size_t i = 0; str[i]; i++) {
            string_.push_back(str[i]);
        }
    }
    String (const String& other) { string_ = other.string_; }
    virtual ~String() = default;
    
    String operator= (const String& other) = delete;
    
    virtual void print() const {
        for (char c : string_) {
            cout << c;
        }
    }
    
    friend std::ostream& operator<< (std::ostream& out,const String mss);
};

std::ostream& operator<< (std::ostream& out,const String mss) {
    for (char c : mss.string_) {
        out << c;
    }
    return out;
}

// class SecretString:
class SecretString : public String {
protected:
    char symbol_;
public:
    SecretString(char* str, char sym) : String(str), symbol_{sym} {}
    SecretString(const SecretString& other) : String(other) {
        symbol_ = other.symbol_;
    }
    ~SecretString() override = default;
    
    SecretString operator= (const SecretString& other) = delete;
    
    void print() const override {
        for (char c : string_) {
            cout << symbol_;
        }
    }
    
    friend std::ostream& operator<< (std::ostream& out,const SecretString mss);
};

std::ostream& operator<< (std::ostream& out,const SecretString mss) {
    for (char c : mss.string_) {
        out << mss.symbol_;
    }
    return out;
}



int main()
{
  char text[30] = "OOP is awesome!";
  String str(text);
  SecretString secstr(text, '#');
  
  str.print();
  cout << " (print)" << endl;
  
  cout << str << endl;
  
  secstr.print();
  cout << " (print)" << endl;
  
  cout << secstr << endl << endl;
  
  
  cout << "--- Copies ---" << endl;
  String copy{str};
  cout << copy << " (<< copy)" << endl;
  copy.print();
  cout << " (print)" << endl;
  
  SecretString secret_copy{secstr};
  cout << secret_copy << " (<< secret_copy)" << endl;
  secret_copy.print();
  cout << " (print)" << endl << endl;
  
  cout << "--- Polymorphism ---" << endl;
  String &strref{secstr};
  strref.print();
  cout << endl;
  return 0;
}