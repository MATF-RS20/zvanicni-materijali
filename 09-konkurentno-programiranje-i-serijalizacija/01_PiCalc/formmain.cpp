#include "formmain.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QTime>

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

double FormMain::calculatePiValue() const
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

    return 4 * hits / count;
}

void FormMain::onButtonStart()
{
    labelValue->setText("Calculating...");
    labelValue->setText(QString::number(calculatePiValue()));
}
