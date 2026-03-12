#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

using std::cout;
using std::endl;

class Fraction {
    int zahler_;
    int nenner_;
    void reduce();
public:
    Fraction(int z, int n);
    Fraction(Fraction& other);

    // Special Methode
    int getNominator() const { return zahler_; }
    int getDenominator() const { return nenner_; }

    // Arithmetics
    Fraction operator= (const Fraction& other);
    Fraction operator+ (const Fraction& second);
    Fraction operator+= (const Fraction& second);
    Fraction operator+ (const int a);
    Fraction operator++ (int);
    Fraction operator++ ();
    Fraction operator- ();
    Fraction operator~ ();
    Fraction operator/= (const Fraction& other);
    bool operator! ();
    explicit operator bool ();
    bool operator== (const Fraction& other);
    bool operator!= (const Fraction& other);
    bool operator< (const Fraction& other);
    bool operator<= (const Fraction& other);

    // Methoden
    double value() const { return (double) zahler_/nenner_; }
};

Fraction operator+ (const int a, Fraction& other);
std::ostream& operator<< (std::ostream& out, const Fraction f);


#endif // FRACTION_HPPFRACTION_HPP