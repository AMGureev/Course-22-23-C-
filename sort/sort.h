#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (Iterator i = begin; i != end; ++i) {
        for (Iterator j = begin; j != end; ++j) {
            Iterator next_j = std::next(j);
            if (next_j == end) {
                break;
            }
            if (comparator(*next_j, *j)) {
                std::swap(*j, *next_j);
            }
        }
    }
}