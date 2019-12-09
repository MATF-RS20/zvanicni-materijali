#ifndef CELLTHREAD_H
#define CELLTHREAD_H

#include <QThread>

class CellThread : public QThread
{
    Q_OBJECT

public:
    CellThread(const int i, const int j);

protected:
    void run() override;

signals:
    void threadFinished(int i, int j, double new_value);

private:
    int i_;
    int j_;
};

#endif // CELLTHREAD_H
