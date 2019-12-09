#include "temperaturereader.h"
#include "ui_temperaturereader.h"

#include <QMessageBox>

// Inicijalizacija statickih promenljivih
QVector<QVector<double>> TemperatureReader::matrix_;
QMutex TemperatureReader::mutex_matrix_;
int TemperatureReader::num_of_rows_ = 0;

TemperatureReader::TemperatureReader(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::TemperatureReader)
    , timer_(this)
{
    ui_->setupUi(this);

    // Povezivanje signala i slot-metoda u okviru formulara
    QObject::connect(ui_->pb_start_reading, &QPushButton::clicked,
                     this, &TemperatureReader::onPbStartReading);
}

TemperatureReader::~TemperatureReader()
{
    // Zatvaramo veb pregledac
    ui_->browser->close();

    // Brisemo auto-generisanu klasu koja implementira formular
    delete ui_;

    // Brisemo niti
    for (auto thread : threads_)
    {
        if (!thread->isFinished())
        {
            thread->quit();
        }
        delete thread;
    }
}

void TemperatureReader::onPbStartReading()
{
    // Dohvatamo broj iz QLineEdit polja
    // i pokusavamo da ga parsiramo u celi broj
    const auto number_str = ui_->le_num_of_rc->text();
    bool parsed;
    const auto number = number_str.toInt(&parsed);

    // Ako je korisnik uneo nesto sto nije broj
    // ili je uneo nepozitivan broj,
    // onda mu treba prikazati poruku da ispravi unos
    if (!parsed || number <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Morate uneti ispravan pozitivan broj");
        msgBox.exec();
        return;
    }

    // Iskljucujemo sve kontrole za unos podataka
    ui_->groupBox->setDisabled(true);

    // Popunjavamo kvadratnu matricu nasumicnim vrednostima iz [15, 30).
    // S obzirom da je matrica podatak koji se koristi u drugim nitima,
    // potrebno je da ga zakljucamo koriscenjem muteksa.
    TemperatureReader::mutex_matrix_.lock();

    TemperatureReader::num_of_rows_ = number;

    for (auto i = 0; i < num_of_rows_; ++i)
    {
        QVector<double> row;
        for (auto j = 0; j < num_of_rows_; ++j)
        {
            row.push_back((qrand() % 15 + 15));
        }
        matrix_.push_back(row);
    }

    // Pravimo niti na osnovu procitane vrednosti.
    // Svaka nit ce izracunati vrednost jednog polja u matrici
    // na osnovu susednih polja.
    for (auto i = 0; i < num_of_rows_; ++i)
    {
        for (auto j = 0; j < num_of_rows_; ++j)
        {
            auto thread = new CellThread(i, j);
            QObject::connect(thread, &CellThread::threadFinished,
                             this, &TemperatureReader::onThreadFinished,
                             Qt::QueuedConnection);

            threads_.push_back(thread);
        }
    }

    // Postavljamo tajmer koji ce pokrenuti niti
    // na svaku 1.5 sekundu
    QObject::connect(&timer_, &QTimer::timeout,
                     this, &TemperatureReader::onTimerTimeout);
    timer_.start(1500);

    // Ne zaboravimo da otkljucamo zakljucani muteks!
    TemperatureReader::mutex_matrix_.unlock();
}

void TemperatureReader::onTimerTimeout()
{
    // Zapocinjemo sve niti
    for (auto thread_iter = threads_.begin(); thread_iter != threads_.end(); ++thread_iter)
    {
        // Ako ima neka nit koja jos uvek radi, prvo cemo je ugasiti...
        if (!(*thread_iter)->isFinished())
        {
            (*thread_iter)->quit();
        }
        // ...pa cemo je onda pokrenuti ponovo
        (*thread_iter)->start();
    }
}

void TemperatureReader::onThreadFinished(int i, int j, double new_value)
{
    TemperatureReader::mutex_matrix_.lock();
    // Azuriramo vrednost u matrici
    matrix_[i][j] = new_value;

    // Azuriramo prikaz matrice u prikazu
    QString matrix_html("<table style=\"border-collapse: collapse;\">");
    for (const auto & row : matrix_)
    {
        matrix_html += "<tr>";
        for (const auto & cell : row)
        {
            matrix_html +=
                    "<td style=\"border: 1px solid black; padding: 10px;\">"
                        + QString::number(cell) +
                    "</td>";
        }
        matrix_html += "</tr>";
    }
    matrix_html += "</table>";
    ui_->browser->setHtml(matrix_html);
    TemperatureReader::mutex_matrix_.unlock();

    // Prekidamo nit na ciji signal reagujemo
    const auto thread_id = i * TemperatureReader::num_of_rows_ + j;
    threads_[thread_id]->quit();
}
