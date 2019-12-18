#include <iostream>

using namespace std;

class fibonacci_iterator
{
    unsigned i_ {0};
    unsigned second_prev_ {0};
    unsigned first_prev_ {1};

public:
    fibonacci_iterator() = default;
    explicit fibonacci_iterator(unsigned i)
        : i_{i}
    {}

    unsigned operator*() const
    {
        return first_prev_;
    }

    fibonacci_iterator& operator++()
    {
        const auto old_b = first_prev_;
        first_prev_ += second_prev_;
        second_prev_ = old_b;
        ++i_;
        return *this;
    }

    bool operator!=(const fibonacci_iterator &o) const
    {
        return i_ != o.i_;
    }
};

class fib_range
{
    unsigned end_n_;
public:
    explicit fib_range(unsigned end_n)
        : end_n_{end_n}
    {}

    [[nodiscard]] fibonacci_iterator begin() const
    {
        return fibonacci_iterator{};
    }

    [[nodiscard]] fibonacci_iterator end() const
    {
        return fibonacci_iterator{end_n_};
    }
};

int main()
{
    for (auto i : fib_range(10))
    {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}