#include "admission.h"

bool CustomSort(const Applicant*, const Applicant*);

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable table;
    table.reserve(universities.size());
    std::unordered_map<std::string, size_t> university_capacity;
    for (auto& university : universities) {
        university_capacity[university.name] = university.max_students;
    }
    for (const University& university : universities) {
        std::vector<const Student*> students;
        students.reserve(applicants.size());
        table.insert({university.name, students});
    }
    std::vector<const Applicant*> sorted_applicants(applicants.size());
    for (size_t i = 0; i < applicants.size(); ++i) {
        sorted_applicants[i] = &(applicants[i]);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), CustomSort);
    for (auto application : sorted_applicants) {
        for (auto& university : application->wish_list) {
            if (!table.contains(university) || table[university].size() < university_capacity[university]) {
                table[university].emplace_back(&(application->student));
                break;
            }
        }
    }
    return table;
}

bool CustomSort(const Applicant* p1, const Applicant* p2) {
    const Applicant& a1 = *p1;
    const Applicant& a2 = *p2;
    if (a1.points != a2.points) {
        return a1.points > a2.points;
    }
    if (a1.student.birth_date.year != a2.student.birth_date.year) {
        return a1.student.birth_date.year > a2.student.birth_date.year;
    }
    if (a1.student.birth_date.month != a2.student.birth_date.month) {
        return a1.student.birth_date.month > a2.student.birth_date.month;
    }
    if (a1.student.birth_date.day != a2.student.birth_date.day) {
        return a1.student.birth_date.day > a2.student.birth_date.day;
    }
    size_t i1 = a1.student.name.find(' ');
    size_t i2 = a2.student.name.find(' ');
    std::string surname1 = a1.student.name.substr(i1 + 1);
    std::string surname2 = a2.student.name.substr(i2 + 1);
    if (surname1 != surname2) {
        return surname1 > surname2;
    }
    std::string name1 = a1.student.name.substr(0, i1);
    std::string name2 = a2.student.name.substr(0, i2);
    return name1 > name2;
}