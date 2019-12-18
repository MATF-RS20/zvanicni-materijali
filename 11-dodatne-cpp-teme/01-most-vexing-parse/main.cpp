// Primer koji ilustruje koncept Most_vexing_parse
// https://en.wikipedia.org/wiki/Most_vexing_parse

#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

class Timer {
public:
    Timer()
        : now_(chrono::system_clock::now())
    {}

private:
    friend ostream& operator<<(ostream& os, const Timer& t);

    chrono::time_point<chrono::system_clock> now_;
};

ostream& operator<<(ostream& os, const Timer& t)
{
    const auto tt (chrono::system_clock::to_time_t(t.now_));
    const auto loct (std::localtime(&tt));
    return os << put_time(loct, "%c");
}

class TimeKeeper {
public:
    explicit TimeKeeper(const Timer& t)
        : t_(t)
    {}

    const Timer & get_time()
    {
        return t_;
    }

private:
    const Timer & t_;
};

int main()
{
    // -----------------------------------------------------------------------
    // Iako deluje ocigledno sta smu uradili, kompilator prijavljuje ne tako
    // ociglednu gresku.
    // -----------------------------------------------------------------------
    // g++
    // -----------------------------------------------------------------------
    // g++ -g -std=c++17 -Wall   -c -o main.o main.cpp
    // main.cpp: In function ‘int main()’:
    // main.cpp:30:24: error: request for member ‘get_time’ in ‘time_keeper’, which is of non-class type ‘TimeKeeper(Timer (*)())’
    //    30 |     return time_keeper.get_time();
    //       |                        ^~~~~~~~
    //
    // -----------------------------------------------------------------------
    // clang++
    // -----------------------------------------------------------------------
    // clang++ -g -std=c++17 -Wall   -c -o main.o main.cpp
    // main.cpp:25:28: warning: parentheses were disambiguated as a function declaration [-Wvexing-parse]
    //      TimeKeeper time_keeper(Timer());
    //                            ^~~~~~~~~
    // main.cpp:25:29: note: add a pair of parentheses to declare a variable
    //      TimeKeeper time_keeper(Timer());
    //                             ^
    //                             (      )
    // main.cpp:37:23: error: member reference base type 'TimeKeeper (Timer (*)())' is not a structure or union
    //     return time_keeper.get_time();
    //            ~~~~~~~~~~~^~~~~~~~~
    // 1 warning and 1 error generated.
    //
    //
    // Naredna naredba se moze interpretrirati kao:
    // 1. Definicija promenljive `time_keeper` klase `TimeKeeper` koja se inicijalizuje instancom klase `Timer`.
    // 2. Deklaracijom funkcije `time_keeper` koja vraac objekat tipa `TimeKeeper` i ima jedan neimenovani argument koji
    //      predstavlja pokazivac na funkciju koja ne prihvata argumente i vraca objekat tipa `Timer`
    // C++ standard preferira (2), iako vecina programera ocekuje (1).
    // -----------------------------------------------------------------------
    //TimeKeeper time_keeper(Timer());
    // -----------------------------------------------------------------------

    // Problem sa parsiranjem se od C++11 resava koriscenjem
    // 'uniformne inicijalizacije' (eng. uniform initialization).

    // -----------------------------------------------------------------------
    // (1)
    // -----------------------------------------------------------------------
    //TimeKeeper time_keeper{Timer()};
    // -----------------------------------------------------------------------
    // (2)
    // -----------------------------------------------------------------------
    //TimeKeeper time_keeper(Timer{});
    // -----------------------------------------------------------------------
    // (3)
    // -----------------------------------------------------------------------
    TimeKeeper time_keeper{Timer{}};
    // -----------------------------------------------------------------------

    cout << time_keeper.get_time();

    return 0;
}
