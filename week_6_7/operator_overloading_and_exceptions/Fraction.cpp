#include "Fraction.hpp"
#include "DivideByZeroException.hpp"

void Fraction::reduce() {
    int z = zahler_;
    int n = nenner_;
    int r = zahler_ % nenner_;
    while (true) {
        if (r == 0) {
            zahler_ /= n;
            nenner_ /= n;
            break;
        }
        z = n;
        n = r;
        r = z % n;
    }
    // negative
    if (nenner_ < 0) {
        zahler_ *= -1;
        nenner_ *= -1;
    }
}

Fraction::Fraction(int z = 0, int n = 1)
: zahler_{z}
{
    if (n == 0) {
        DivideByZeroException err {"0 in the denominator invalid!\n"};
        throw err;
    } else {
        nenner_ = n;
    }
    reduce();
}

Fraction::Fraction(Fraction& other) {
    zahler_ = other.getNominator();
    nenner_ = other.getDenominator();
}

Fraction Fraction::operator= (const Fraction& other) {
    zahler_ = other.getNominator();
    nenner_ = other.getDenominator();
    return *this;
}

Fraction Fraction::operator+ (const Fraction& second) {
    int z = zahler_ * second.getDenominator() + second.getNominator() * nenner_;
    int n = nenner_ * second.getDenominator();
    Fraction hi (z, n);
    return hi;
}

Fraction Fraction::operator+= (const Fraction& second) {
    *this = *this + second;
    return *this;
}

Fraction Fraction::operator+ (const int a) {
    Fraction y {a};
    Fraction z;
    z = (*this) + y;
    return z;
}

Fraction Fraction::operator++ (int) {
    Fraction res {(*this)};
    (*this) = (*this) + 1;
    return res;
}

Fraction Fraction::operator++ () {
    (*this) = (*this) + 1;
    return (*this);
}

Fraction Fraction::operator- () {
    Fraction res {zahler_ * (-1), nenner_};
    return res;
}

Fraction Fraction::operator~ () {
    Fraction res {nenner_, zahler_};
    return res;
}

Fraction Fraction::operator/= (const Fraction& other) {
    if (other.getNominator() == 0) {
        DivideByZeroException err {"Dividing by 0 not valid!\n"};
        throw err;
    }
    Fraction res {zahler_ * other.getDenominator(), nenner_ * other.getNominator()};
    *this = res;
    return *this;
}

bool Fraction::operator! () {
    if (this->value() == 0)
    {
        return true;
    }
    return false;
}

Fraction::operator bool () {
    if (this->value() == 0)
    {
        return false;
    }
    return true;
}

bool Fraction::operator== (const Fraction& other) {
    double x = this->value();
    double y = other.value();
    return (x == y);
}

bool Fraction::operator!= (const Fraction& other) {
    double x = this->value();
    double y = other.value();
    return (x != y);
}

bool Fraction::operator< (const Fraction& other) {
    double x = this->value();
    double y = other.value();
    return x < y;
}    

bool Fraction::operator<= (const Fraction& other) {
    double x = this->value();
    double y = other.value();
    return (x <= y);
}    

Fraction operator+ (const int a, Fraction& other) {
    Fraction y {a};
    Fraction z;
    z = other + y;
    return z;
}

std::ostream& operator<< (std::ostream& out, const Fraction f) {
    return out << f.getNominator() << " / " << f.getDenominator() << endl;
}


#include <cassert>
#include <sstream>

int main()
{

Fraction a(5769, 243);
  Fraction b(1283, 54); // b > a
  Fraction c(6410, 270); // a == c
  Fraction d(-641, 27);

  std::cout << a << b << c << d;

  if (a == b || a == d || b == a || b == c || b == d || c == b || c == d || 
      d == a || d == b || d == c)
    assert(false && "Inequival fractions are assumed as equal in ==!\n");
  if (!(a == a && a == c && b == b && c == a && c == c && d == d))
    assert(false && "Equal fractions are assumed as inequival in ==!\n");

  if (!(a != b && a != d && b != a && b != c && b != d && c != b && c != d &&
      d != a && d != b && d != c))
    assert(false && "Inequival fractions are assumed as equal in !=!\n");
  if (a != a || a != c || b != b || c != a || c != c || d != d)
    assert(false && "Equal fractions are assumed as inequival in !=!\n");

  if (!(a < b && c < b && d < a && d < b && d < c))
    assert(false && "<-operator not working correctly!\n");
  if (a < a || a < c || a < d || b < a || b < b || b < c || b < d || c < a || 
      c < c || c < d || d < d)
    assert(false && "<-operator not working correctly!\n");

  if (!(a <= a && a <= b && a <= c && b <= b && c <= a && c <= b && c <= c && d <= a && 
      d <= b && d <= c && d <= d))
    assert(false && "<=-operator not working correctly!\n");
  if (a <= d || b <= a || b <= c || b <= d || c <= d)
    assert(false && "<=-operator not working correctly!\n"); 

  std::cout << "\nTestcase passed!\n\n";
  std::cout << "-----------------------------------------------\n" << std::endl;

  return 1;
}