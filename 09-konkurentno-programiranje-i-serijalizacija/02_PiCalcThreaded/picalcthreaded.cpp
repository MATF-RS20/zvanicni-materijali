#include "picalcthreaded.h"

#include <QTime>
#include <QDebug>

PiCalcThreaded::PiCalcThreaded()
{
    qDebug() << "Nit je kreirana\n";
}

PiCalcThreaded::~PiCalcThreaded()
{
    qDebug() << "Nit je unistena\n";
}

void PiCalcThreaded::run()
{
    // Racunamo pribliznu vrednost broja Pi tako sto
    // uzimamo nasumicne tacke iz kvadrata [0,1] x [0,1]
    // i proveravamo da li su udaljeni od (0,0) manje od 1

    qsrand(static_cast<unsigned>(QTime(0, 0, 0).secsTo(QTime::currentTime())));

    auto hits = 0.0, count = 0.0;

    while (hits < 100000000)
    {
        const double x = (qrand() % 512) / 512.0;
        const double y = (qrand() % 512) / 512.0;

        ++count;
        if (x * x + y * y <= 1)
        {
            ++hits;
        }
    }

    // Kada zavrsimo za izracunavanjem,
    // emitujemo signal i prosledjujemo mu vrednost
    // koja ce biti prosledjena svim slot-metodima
    // koji su osluskivali ovaj signal.
    emit calculatedPiValue(4 * hits / count);
}
