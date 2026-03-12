
#ifndef MAJOR_HPP
#define MaJOR_HPP

#include <string>
#include <map>

using std::string;
using std::map;

enum class STUDENT_GROUP
{
    FEM_DOM,
    MAL_DOM,
    FEM_INT,
    MAL_INT,
    TOTAL,
    TOTAL_FEM,
    TOTAL_MAL,
    TOTAL_DOM,
    TOTAL_INT
};

class Major
{
    string const ID_;
    string const name_;
    map<STUDENT_GROUP, unsigned> const groups_;

    public:
        Major(string id, string name, unsigned fem_dom, unsigned mal_dom, unsigned fem_int, unsigned mal_int, unsigned total);
        Major(const Major& other) = delete;
        virtual ~Major() = default;

        string getName() const { return name_; }
        unsigned getGroupNumber(STUDENT_GROUP group) const { return groups_.at(group); }

        double ratioCal(STUDENT_GROUP group) const;
};

#endif