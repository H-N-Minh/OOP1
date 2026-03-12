#ifndef DATABASE_HPP
#define DATABASE_HPP


#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Major.hpp"

using std::vector;


class Database
{
  vector<const Major*> majors_;
  const Major& maxStudent(STUDENT_GROUP group, unsigned min_to_count) const;
  const Major& maxRatio(STUDENT_GROUP group, unsigned min_to_count) const ;
  void parseFile(const string& filename);  

  public:
    Database(string filename) { parseFile(filename); }
    Database(const Database& other) = delete;
    virtual ~Database();

    void mostTotalStudent () const;
    void mostFemale () const;
    void minFemaleRatio (unsigned min_to_count) const;
    void maxFemaleRatio (unsigned min_to_count) const;
    void mostInternationals (unsigned min_to_count) const;
    // feel free to add more/different search queries! :)

};


#endif // DATABASE_HPP