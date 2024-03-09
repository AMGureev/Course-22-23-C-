#include "sort_students.h"

#include <tuple>

bool CompareDate(const Date& d1, const Date& d2) {
    return std::tie(d1.year, d1.month, d1.day) < std::tie(d2.year, d2.month, d2.day);
}

bool AreDatesEqual(const Date& d1, const Date& d2) {
    return std::tie(d1.year, d1.month, d1.day) == std::tie(d2.year, d2.month, d2.day);
}

bool CompareStudentsName(const Student& s1, const Student& s2) {
    if (std::tie(s1.last_name, s1.name) < std::tie(s2.last_name, s2.name)) {
        return true;
    } else if (std::tie(s1.last_name, s1.name) == std::tie(s2.last_name, s2.name)) {
        return AreDatesEqual(s1.birth_date, s2.birth_date);
    }
    return false;
}

bool CompareStudentsDate(const Student& s1, const Student& s2) {
    if (CompareDate(s1.birth_date, s2.birth_date)) {
        return true;
    } else if (AreDatesEqual(s1.birth_date, s2.birth_date)) {
        return std::tie(s1.last_name, s1.name) < std::tie(s2.last_name, s2.name);
    }
    return false;
}

void SortStudents(std::vector<Student>& students, SortKind sortkind) {
    if (sortkind == SortKind::Name) {
        std::sort(students.begin(), students.end(), CompareStudentsName);
    } else {
        std::sort(students.begin(), students.end(), CompareStudentsDate);
    }
}