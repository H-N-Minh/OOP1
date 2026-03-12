#include "Major.hpp"

        
Major::Major(string id, string name, unsigned fem_dom, unsigned mal_dom, unsigned fem_int, unsigned mal_int, unsigned total)
: ID_{id}, name_{name},
groups_{
    {STUDENT_GROUP::FEM_DOM,             fem_dom},
    {STUDENT_GROUP::MAL_DOM,             mal_dom},
    {STUDENT_GROUP::FEM_INT,             fem_int},
    {STUDENT_GROUP::MAL_INT,             mal_int},
    {STUDENT_GROUP::TOTAL,                 total},
    {STUDENT_GROUP::TOTAL_FEM, fem_dom + fem_int},
    {STUDENT_GROUP::TOTAL_MAL, mal_dom + mal_int},
    {STUDENT_GROUP::TOTAL_DOM, fem_dom + mal_dom},
    {STUDENT_GROUP::TOTAL_INT, fem_int + mal_int},
}
{}

double Major::ratioCal(STUDENT_GROUP group) const { 
    return groups_.at(group) * 1.0 / groups_.at(STUDENT_GROUP::TOTAL);
}