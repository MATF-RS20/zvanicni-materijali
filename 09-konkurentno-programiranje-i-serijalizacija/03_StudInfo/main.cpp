
#include <QApplication>

#include "FormMain.h"

int main(int argc, char ** argv)
{
    QApplication application(argc, argv);

    FormMain form;

    form.show();

    return application.exec();
}
