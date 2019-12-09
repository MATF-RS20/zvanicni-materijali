#include "cellthread.h"
#include "temperaturereader.h"

CellThread::CellThread(const int i, const int j)
    : i_(i)
    , j_(j)
{
}

void CellThread::run()
{
    TemperatureReader::mutex_matrix_.lock();
    auto old_value = TemperatureReader::matrix_[i_][j_];
    auto addition = 0.0;
    auto n = TemperatureReader::matrix_.size();
    const auto coefficient = 0.1;

    // Dodajemo temperaturu od celije iznad
    if (i_ > 0)
    {
        addition += coefficient * (TemperatureReader::matrix_[i_-1][j_] - old_value);
    }
    // Dodajemo temperaturu od celije levo
    if (j_ > 0)
    {
        addition += coefficient * (TemperatureReader::matrix_[i_][j_-1] - old_value);
    }
    // Dodajemo temperaturu od celije ispod
    if (i_ < n-1)
    {
        addition += coefficient * (TemperatureReader::matrix_[i_+1][j_] - old_value);
    }
    // Dodajemo temperaturu od celije desno
    if (j_ < n-1)
    {
        addition += coefficient * (TemperatureReader::matrix_[i_][j_+1] - old_value);
    }
    TemperatureReader::mutex_matrix_.unlock();

    emit threadFinished(i_, j_, old_value + addition);
}
