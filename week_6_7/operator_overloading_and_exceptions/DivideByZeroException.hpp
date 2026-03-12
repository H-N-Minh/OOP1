#ifndef DIVIDE_BY_ZERO_EXCEPTION_HPP
#define DIVIDE_BY_ZERO_EXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;

// TODO
class DivideByZeroException : public std::exception {
    const char* message_;
public:
    DivideByZeroException(const char* mss) : message_{mss} {}
    DivideByZeroException(DivideByZeroException& other) = default;

    const char* what () const noexcept override { return message_; }
};

#endif // DIVIDE_BY_ZERO_EXCEPTION_HPP