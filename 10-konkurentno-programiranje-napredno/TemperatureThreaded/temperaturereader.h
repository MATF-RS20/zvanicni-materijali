#ifndef TEMPERATUREREADER_H
#define TEMPERATUREREADER_H

#include <QWidget>
#include <QVector>
#include <QMutex>
#include <QTimer>

#include "cellthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TemperatureReader; }
QT_END_NAMESPACE

class TemperatureReader : public QWidget
{
    Q_OBJECT

public:
    TemperatureReader(QWidget *parent = nullptr);
    ~TemperatureReader();

    // Deklaracija statickih promenljivih
    static QVector<QVector<double>> matrix_;
    static QMutex mutex_matrix_;
    static int num_of_rows_;

public slots:
    void onPbStartReading();
    void onThreadFinished(int i, int j, double new_value);

private slots:
    void onTimerTimeout();

private:
    Ui::TemperatureReader *ui_;
    QVector<CellThread*> threads_;
    QTimer timer_;
};
#endif // TEMPERATUREREADER_H
