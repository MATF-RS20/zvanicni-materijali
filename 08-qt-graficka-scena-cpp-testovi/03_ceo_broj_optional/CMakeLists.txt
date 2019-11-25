# Specifikacija najmanje verzije CMake sistema.
# Mora biti prva linija u projektu.
cmake_minimum_required(VERSION 3.10)

# Naziv projekta: izvršne datoteke, biblioteke, ...
project(ceo_broj_optional_test)

# Putanja direktorijuma u kojoj se nalaze zaglavlja za uključivanje
include_directories(catch/single_include)

# Kreiramo promenljivu koja sadrži listu zaglavlja iz našeg koda
set(HEADERS
        ceo_broj.h)

# Kreiramo promenljivu koja sadrži listu implementacija iz našeg koda
set(SOURCES
        ceo_broj.cpp
        ceo_broj_test.cpp)

# Kažemo CMake sistemu da želimo da cilj ovog projekta predstavlja izvršnu datoteku
# čiji naziv odgovara samom nazivu projekta,
# a treba da bude napravljena na osnovu lista zaglavlja i implementacija.
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Dodajemo verziju C++ standarda za kompiliranje cilja koji nosi ime projekta
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)