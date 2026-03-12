
#include <iostream>
#include <vector>
#include "Database.hpp"

using std::string;
using std::vector;

using std::cout;
using std::endl;

int main()
{
    Database database("Studierendenstatistik.csv");
    database.mostTotalStudent();
    database.mostFemale();
    database.minFemaleRatio(50);
    database.maxFemaleRatio(50);
    database.mostInternationals(50);
    return 0;
}