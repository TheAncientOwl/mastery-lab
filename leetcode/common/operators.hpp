#include <iostream>
#include <iterator>
#include <type_traits>

#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}
