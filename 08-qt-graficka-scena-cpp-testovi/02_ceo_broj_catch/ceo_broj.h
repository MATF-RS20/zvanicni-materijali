#ifndef CEOBROJ_H_
#define CEOBROJ_H_

#include <iostream>
#include <math.h>
#include <vector>

class ceo_broj {
public:
    ceo_broj();

    ceo_broj(int n, unsigned osnova);

    ceo_broj operator+(const ceo_broj &c) const;

    ceo_broj operator-(const ceo_broj &c) const;

    ceo_broj operator*(const ceo_broj &c) const;

    ceo_broj operator/(const ceo_broj &c) const;

    bool operator==(const ceo_broj &c) const;

    bool operator!=(const ceo_broj &c) const;

    unsigned osnova() const;

    int znak() const;

    friend std::ostream &operator<<(std::ostream &, const ceo_broj &);

private:
    void inicijalizacija_cifara(unsigned n);

    char zapis_cifre(int c) const;

    void abs_sabiranje(const ceo_broj &veci, const ceo_broj &manji,
                       ceo_broj &r) const;

    void abs_oduzimanje(const ceo_broj &veci, const ceo_broj &manji,
                        ceo_broj &r) const;

    // da li je prvi >= drugi
    bool abs_veci(const ceo_broj &x, const ceo_broj &y) const;

    static void abs_mnozenje_cifrom(const ceo_broj &x, unsigned cifra,
                                    ceo_broj &r)
    {
        unsigned prenos = 0;

        for (unsigned j = 0; j < x.m_cifre.size(); j++) {
            unsigned a = x.m_cifre[j] * cifra + prenos;
            r.m_cifre.push_back(a % x.m_osnova);
            prenos = a / x.m_osnova;
        }

        if (prenos > 0)
            r.m_cifre.push_back(prenos);
    }

    unsigned m_osnova;
    int m_znak;
    std::vector<unsigned> m_cifre;
};

#endif /* CEOBROJ_H_ */
