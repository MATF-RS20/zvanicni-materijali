#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class FormMain : public QWidget
{
    Q_OBJECT

public:
    FormMain(QWidget *parent = nullptr);
    ~FormMain();

public Q_SLOTS:
    void onButtonStart();

private:
    double calculatePiValue() const;

    QPushButton * buttonStart;
    QLabel * labelValue;
};
#endif // FORMMAIN_H
