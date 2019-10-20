#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace matf {

template <typename T1, typename T2>
class pair {
public:
    pair(T1 t1, T2 t2)
        : first(t1), second(t2)
    {
        std::cout << "ctor invoked" << std::endl;
    }

    pair() = default;

    void swap(pair<T1, T2>& other)
    {
        std::swap(first, other.first);
        std::swap(second, other.second);
    }

    T1 first;
    T2 second;
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 t1, T2 t2)
{
    return pair<T1, T2>(t1, t2);
}

} // namespace matf

#endif /* ifndef PAIR_HPP */
