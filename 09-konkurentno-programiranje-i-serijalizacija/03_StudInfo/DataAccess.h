#ifndef DATA_ACCESS_H_
#define DATA_ACCESS_H_

#include "ui_formMain.h"

/**
 * Klasa za citanje i pisanje podataka u fajl
 */
class DataAccess {
public:
    DataAccess(Ui::FormMain * form);

    /**
     * Cita podatke iz fajla
     * @param file ime fajla iz kog citamo podatke
     */
    void read(const QString & file);

    /**
     * Pise podatke u fajla
     * @param file ime fajla u kojem cuvamo podatke
     */
    void write(const QString & file);

private:
    void readText(const QString & file);
    void readXML(const QString & file);

    void writeText(const QString & file);
    void writeXML(const QString & file);

    Ui::FormMain * ui;

};

#endif // DATA_ACCESS_H_
