#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> stack;
    for (const auto& action : student_actions) {
        if (action.side == Side::Top) {
            stack.push_front(action.name);
        } else {
            stack.push_back(action.name);
        }
    }
    std::vector<std::string> authors;
    authors.reserve(queries.size());
    for (const auto& query : queries) {
        if (query <= stack.size()) {
            authors.push_back(stack[query - 1]);
        } else {
            authors.push_back("Invalid query");
        }
    }
    authors.erase(std::remove(authors.begin(), authors.end(), ""), authors.end());
    return authors;
}
