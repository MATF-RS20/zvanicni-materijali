#include "FormMain.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>

FormMain::FormMain()
    : dataAccess(&ui)
{
    ui.setupUi(this);

    connect(ui.buttonOpen, SIGNAL(clicked()), this, SLOT(buttonOpenClicked()));
    connect(ui.buttonSave, SIGNAL(clicked()), this, SLOT(buttonSaveClicked()));
    connect(ui.buttonAddExam, SIGNAL(clicked()), this, SLOT(buttonAddExamClicked()));
    connect(ui.buttonRemoveExam, SIGNAL(clicked()), this, SLOT(buttonRemoveExamClicked()));
    connect(ui.buttonClearExams, SIGNAL(clicked()), this, SLOT(buttonClearExamsClicked()));
}

void FormMain::buttonOpenClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Izaberite fajl");

    if (!file.isEmpty())
    {
        dataAccess.read(file);
    }
}

void FormMain::buttonSaveClicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Izaberite fajl");

    if (!file.isEmpty())
    {
        dataAccess.write(file);
    }
}

void FormMain::buttonAddExamClicked()
{
    QString value = QInputDialog::getText(this, "Prijava ispita", "ID ispita");

    if (!value.isEmpty())
    {
        ui.listExams->addItem(value);
    }
}

void FormMain::buttonRemoveExamClicked()
{
    // https://doc.qt.io/qt-5/containers.html#the-foreach-keyword
    foreach (QListWidgetItem * item, ui.listExams->selectedItems())
    {
        delete item;
    }
}

void FormMain::buttonClearExamsClicked()
{
    ui.listExams->clear();
}
