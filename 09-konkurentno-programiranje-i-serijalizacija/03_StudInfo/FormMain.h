#ifndef FORM_MAIN_H_
#define FORM_MAIN_H_

#include <QFrame>
#include "ui_formMain.h"
#include "DataAccess.h"

/**
 * Glavna forma projekta
 */
class FormMain: public QFrame
{
    Q_OBJECT

public:
    FormMain();

private Q_SLOTS:
    void buttonOpenClicked();
    void buttonSaveClicked();
    void buttonAddExamClicked();
    void buttonRemoveExamClicked();
    void buttonClearExamsClicked();

private:
    Ui::FormMain ui;
    DataAccess dataAccess;
};

#endif // FORM_MAIN_H_
