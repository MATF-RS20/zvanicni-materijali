#include "ceo_broj.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>

ceo_broj::ceo_broj()
{
}

ceo_broj::ceo_broj(int n, unsigned osnova = 10)
    : m_osnova(osnova), m_znak(n >= 0 ? 1 : -1)
{
    if (osnova > 36) {
        throw std::invalid_argument("Suvise velika osnova");
    }
    inicijalizacija_cifara(abs(n));
}

unsigned ceo_broj::osnova() const
{
    return m_osnova;
}

int ceo_broj::znak() const
{
    return m_znak;
}

ceo_broj ceo_broj::operator+(const ceo_broj &c) const
{
    if (osnova() != c.osnova()) {
        throw std::invalid_argument("Nisu iste osnove!");
    }

    ceo_broj r;

    // ako su brojevi istog znaka
    if (znak() == c.znak()) {
        // broju koji ima vecu apsolutnu vrednost dodajemo broj sa manjom aps.
        // vrednoscu
        if (abs_veci(*this, c)) {
            abs_sabiranje(*this, c, r);
        } else {
            abs_sabiranje(c, *this, r);
        }

        r.m_znak = znak();

    } else if (abs_veci(*this, c)) {
        // ako su razlicitog znaka, od broja sa vecom aps. vred. oduzimamo  broj sa
        // manjom aps. vred.
        abs_oduzimanje(*this, c, r);
        r.m_znak = znak();

    } else {
        abs_oduzimanje(c, *this, r);
        r.m_znak = c.znak();
    }

    return r;
}

ceo_broj ceo_broj::operator-(const ceo_broj &c) const
{
    if (osnova() != c.osnova()) {
        throw std::invalid_argument("Nisu iste osnove!");
    }

    ceo_broj r;

    // ako su brojevi razlicitog znaka
    if (znak() != c.znak()) {
        // broju sa vecom aps. vred. dodajemo broj sa manjom aps. vred.
        if (abs_veci(*this, c)) {
            abs_sabiranje(*this, c, r);
        } else {
            abs_sabiranje(c, *this, r);
        }

        r.m_znak = znak();

    } else if (abs_veci(*this, c)) {
        // ako su brojevi istog znaka, od broja sa vecom aps. vred. oduzimamo broj
        // sa  manjom aps. vred.
        abs_oduzimanje(*this, c, r);
        r.m_znak = znak();

    } else {
        abs_oduzimanje(c, *this, r);
        r.m_znak = -znak();
    }

    return r;
}

ceo_broj ceo_broj::operator*(const ceo_broj &c) const
{
    if (osnova() != c.osnova()) {
        throw std::invalid_argument("Nisu iste osnove!");
    }

    ceo_broj r;
    r.m_osnova = m_osnova;
    r.m_znak = 1;

    for (int i = m_cifre.size() - 1; i >= 0; i--) {
        // mnozimo medjurezultat osnovom
        r.m_cifre.insert(r.m_cifre.begin(), 0);

        // izracunavamo jedan medjuproizvod
        ceo_broj korak;
        korak.m_osnova = m_osnova;
        korak.m_znak = 1;
        abs_mnozenje_cifrom(c, m_cifre[i], korak);

        // dodajemo na medjurezultat
        r = r + korak;
    }

    r.m_znak = znak() * c.znak();
    return r;
}

bool ceo_broj::operator==(const ceo_broj &c) const
{
    if ((*this).m_osnova != c.m_osnova) {
        return false;
    }

    if ((*this).m_znak != c.m_znak) {
        return false;
    }

    if ((*this).m_cifre.size() != c.m_cifre.size()) {
        return false;
    }

    for (unsigned i = 0; i < (*this).m_cifre.size(); i++) {
        if ((*this).m_cifre[i] != c.m_cifre[i]) {
            return false;
        }
    }

    return true;
}

bool ceo_broj::operator!=(const ceo_broj &c) const
{
    return !operator==(c);
}

char ceo_broj::zapis_cifre(int c) const
{
    std::string cifre = "0123456789abcdefghijklmnopqrstuwvxyz";
    return cifre[c];
}

void ceo_broj::abs_sabiranje(const ceo_broj &veci, const ceo_broj &manji,
                             ceo_broj &r) const
{
    unsigned osn = r.m_osnova = veci.m_osnova;
    unsigned prenos = 0;
    unsigned br_cifara_manjeg = manji.m_cifre.size();
    unsigned br_cifara_veceg = veci.m_cifre.size();

    for (unsigned i = 0; i < br_cifara_veceg; i++) {
        unsigned c = veci.m_cifre[i]
                     + (br_cifara_manjeg > i ? manji.m_cifre[i] : 0) + prenos;
        if (c >= osn) {
            prenos = 1;
            c -= osn;

        } else {
            prenos = 0;
        }

        r.m_cifre.push_back(c);
    }

    if (prenos > 0) {
        r.m_cifre.push_back(prenos);
    }
}

void ceo_broj::abs_oduzimanje(const ceo_broj &veci, const ceo_broj &manji,
                              ceo_broj &r) const
{
    unsigned osn = r.m_osnova = veci.m_osnova;
    int pozajmica = 0;
    unsigned br_cifara_manjeg = manji.m_cifre.size();
    unsigned br_cifara_veceg = veci.m_cifre.size();

    for (unsigned i = 0; i < br_cifara_veceg; i++) {
        int c = (int)veci.m_cifre[i]
                - (int)(br_cifara_manjeg > i ? manji.m_cifre[i] : 0)
                - (int)pozajmica;
        if (c < 0) {
            pozajmica = 1;
            c += osn;

        } else {
            pozajmica = 0;
        }

        r.m_cifre.push_back(c);
    }

    // brisemo vodece nule
    while (r.m_cifre.size() > 1 && r.m_cifre.back() == 0) {
        r.m_cifre.pop_back();
    }
}

// da li je prvi >= drugi
bool ceo_broj::abs_veci(const ceo_broj &x, const ceo_broj &y) const
{
    if (x.m_cifre.size() > y.m_cifre.size()) {
        return true;
    }

    if (x.m_cifre.size() < y.m_cifre.size()) {
        return false;
    }

    for (int i = x.m_cifre.size(); i >= 0; i--) {
        if (x.m_cifre[i] > y.m_cifre[i]) {
            return true;
        }

        if (x.m_cifre[i] < y.m_cifre[i]) {
            return false;
        }
    }

    // slucaj x==y
    return true;
}

void ceo_broj::inicijalizacija_cifara(unsigned n)
{
    m_cifre.clear();

    while (n > 0) {
        m_cifre.push_back(n % m_osnova);
        n /= m_osnova;
    }

    if (m_cifre.size() == 0) {
        m_cifre.push_back(0);
    }
}

std::ostream &operator<<(std::ostream &ostr, const ceo_broj &c)
{
    if (c.m_znak < 0) {
        ostr << '-';
    }

    for (int i = c.m_cifre.size() - 1; i >= 0; i--) {
        ostr << c.zapis_cifre(c.m_cifre[i]);
    }

    return ostr;
}

std::optional<int> ceo_broj::u_int() const
{
    // Korektna implementacija bi išla preko
    // std::numeric_limits<int>::max
    if (m_cifre.size() > 9) {
        return {};
    }

    int rezultat = std::accumulate(
                    m_cifre.begin(), m_cifre.end(),
                    0,
                    [] (int acc, auto current) {
                        return 10 * acc + current;
                    });

    return m_znak * rezultat;
}

std::optional<ceo_broj> ceo_broj::iz_niske(const std::string &s, unsigned osnova)
{
    ceo_broj rezultat;
    rezultat.m_cifre.resize(s.length());

    std::transform(s.begin(), s.end(),
                   rezultat.m_cifre.begin(),
                   [] (char c) {
                       return c >= '0' && c <= '9' ? c - '0'
                            : c >= 'a' && c <= 'z' ? c - 'a' + 10
                            : c >= 'A' && c <= 'Z' ? c - 'A' + 10
                            : -1;
                   });

    auto nevalidna_cifra =
        std::find_if(rezultat.m_cifre.cbegin(), rezultat.m_cifre.cend(),
                 [osnova] (auto cifra) { return cifra >= osnova; });

    if (nevalidna_cifra != rezultat.m_cifre.cend()) {
        return {};
    }

    return rezultat;
}



