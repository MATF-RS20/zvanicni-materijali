#include "formmain.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QTime>

#include "picalcthreaded.h"

FormMain::FormMain(QWidget *parent)
    : QWidget(parent)
{
    buttonStart = new QPushButton("Izracunaj Pi", this);
    labelValue = new QLabel("...", this);

    auto layout = new QVBoxLayout();

    QWidget::setLayout(layout);
    QWidget::resize(300, 100);

    layout->addWidget(buttonStart);
    layout->addWidget(labelValue);

    layout->addWidget(new QLineEdit(this));

    QObject::connect(buttonStart, &QPushButton::clicked,
                     this, &FormMain::onButtonStart);
}

FormMain::~FormMain()
{
}

void FormMain::onButtonStart()
{
    labelValue->setText("Calculating...");

    // Kreiramo novu nit sa dinamickim zivotnim vekom
    // Moze li biti lokalna promenljiva?
    auto thread = new PiCalcThreaded();

    // Postavljamo osluskivace nad signalom za kraj izracunavanja.
    // Oba slot-metoda ce biti dodata u red
    // umesto da im se signal prosledi odmah (5. argument `Qt::QueuedConnection`).

    // 1. osluskivac ce pozvati slot-metod `void FormMain::onPiCalcThreadFinished(double value)`
    // kome ce biti prosledjena vrednost iz signala (tj. izracunat broj pi).
    QObject::connect(thread, &PiCalcThreaded::calculatedPiValue,
                     this, &FormMain::onPiCalcThreadFinished,
                     Qt::QueuedConnection);
    // 2. osluskivac ce pozvati slot-metod nad samom niti
    // kojim kazemo da se planira unistavanje niti
    QObject::connect(thread, &PiCalcThreaded::calculatedPiValue,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    // Pokrecemo nit
    thread->start();
}

void FormMain::onPiCalcThreadFinished(double value)
{
    labelValue->setText(QString::number(value));
}
