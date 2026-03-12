#include "Database.hpp"
#include <limits>
#include <iomanip>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;
using std::stringstream;
using std::stoul;


Database::~Database()
{
  for (const Major* major : majors_)
  {
    delete major;
  }
};

void Database::parseFile(const string& filename) {
  ifstream file{filename};
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


const Major& Database::maxStudent(STUDENT_GROUP group, unsigned min_to_count=0) const {
  const Major* max{nullptr};
  for (const Major* m : majors_) {
      if (m->getGroupNumber(STUDENT_GROUP::TOTAL) < min_to_count) {
          continue;
      }
      if (!max || (m->getGroupNumber(group) > max->getGroupNumber(group))) {
          max = m;
      }
  }
  return *max;            
}


const Major& Database::maxRatio(STUDENT_GROUP group, unsigned min_to_count=0) const {
  const Major* max{nullptr};
  for (const Major* m : majors_) {
      if (m->getGroupNumber(STUDENT_GROUP::TOTAL) < min_to_count) {
          continue;
      }
      if (!max || (m->ratioCal(group) > max->ratioCal(group))) {
          max = m;
      }
  }
  return *max;            
}


void Database::mostTotalStudent () const {
  const Major& most = maxStudent(STUDENT_GROUP::TOTAL);
  cout << "Das Studium mit den meisten Studierenden an der TU Graz ist " << most.getName()
  << " mit " << most.getGroupNumber(STUDENT_GROUP::TOTAL) << " Studierenden." << endl;
}


void Database::mostFemale () const {
  const Major& most = maxStudent(STUDENT_GROUP::TOTAL_FEM);
  cout << "Das Studium mit den meisten Studentinnen an der TU Graz ist " << most.getName()
  << " mit " << most.getGroupNumber(STUDENT_GROUP::TOTAL_FEM) << " Studentinnen." << endl;
}


void Database::minFemaleRatio (unsigned min_to_count) const {
  const Major& min = maxRatio(STUDENT_GROUP::TOTAL_MAL, min_to_count);
  cout << "Unter allen Studien an der TU Graz, die von mindestens " << min_to_count
      << " Studierenden studiert werden, ist " << min.getName() << " jenes mit dem geringsten Frauenanteil ("
      << std::fixed << std::setprecision(1) << min.ratioCal(STUDENT_GROUP::TOTAL_FEM) * 100
      << " %)." << endl;
}


void Database::maxFemaleRatio (unsigned min_to_count) const {
  const Major& max = maxRatio(STUDENT_GROUP::TOTAL_FEM, min_to_count);
  cout << "Unter allen Studien an der TU Graz, die von mindestens " << min_to_count
      << " Studierenden studiert werden, ist " << max.getName() << " jenes mit dem hoechsten Frauenanteil ("
      << std::fixed << std::setprecision(1) << max.ratioCal(STUDENT_GROUP::TOTAL_FEM) * 100
      << " %)." << endl;
}


void Database::mostInternationals (unsigned min_to_count) const {
  const Major& max = maxRatio(STUDENT_GROUP::TOTAL_INT, min_to_count);
  cout << "Unter allen Studien an der TU Graz, die von mindestens " << min_to_count
      << " Studierenden studiert werden, ist " << max.getName()
      << " jenes mit dem hoechsten Anteil an internationalen Studierenden ("
      << std::fixed << std::setprecision(1) << max.ratioCal(STUDENT_GROUP::TOTAL_INT) * 100
      << " %)." << endl;
}   
