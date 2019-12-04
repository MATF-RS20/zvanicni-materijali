#ifndef PICALCTHREADED_H
#define PICALCTHREADED_H

#include <QThread>

// Klasa `QThread` predstavlja baznu klasu
// koja implementira razne funkcionalnosti za rad sa nitima.
// Da bismo je koristili, potrebno je da je nasa klasa nasledi,
// i da prevazidje metod `void run()`,
// u kome se navodi kod koji nit treba da izracuna.
// Nakon instanciranja nase klase,
// potrebno je pozvati metod `void start()`
// kojim se zapocinje kreiranje niti i izracunavanje.
class PiCalcThreaded : public QThread
{
    // Klasa QThread nasledjuje klasu QObject,
    // sto znaci da i niti moraju da ukljuce makro Q_OBJECT.
    Q_OBJECT

public:
    PiCalcThreaded();
    ~PiCalcThreaded();

    // Kako da znamo da je nit zavrsila?
    // Potrebno je da definisemo metod koji predstavlja signal
    // koji ce biti emitovan u metodu `void run()`.
    // Ovaj signal mozemo osluskivati u glavnoj niti.
Q_SIGNALS:
    void calculatedPiValue(double value);

protected:
    void run() override;
};

#endif // PICALCTHREADED_H
