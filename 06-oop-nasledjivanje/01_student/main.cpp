#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

enum class studies
{
    Matematika,
    Informatika,
    AstronomijaIAstrofizika
};

class student 
{
public:
    student(const std::string & name, const studies studies)
        : m_name(name)
        , m_studies(studies)
    {}

    // Destruktori baznih klasa UVEK moraju da budu deklarisani kao virtualni,
    // da bi se pozivali ispravni destruktori tokom unistavanja.
    virtual ~student()
    {
        std::cout << "~student" << std::endl;
    }

    double average() const
    {
        return std::accumulate(m_grades.cbegin(), m_grades.cend(), 0) / static_cast<double>(m_grades.size());
    }

    void add_grade(const int grade)
    {
        m_grades.push_back(grade);
    }

    // Da bi se neko ponasanje definisalo kao polimorfno,
    // potrebno je u baznoj klasi za dati metod
    // navesti kljucnu rec `virtual`...
    virtual std::string name() const
    {
        return m_name + "(" + program() + ")";
    }

protected:
    std::string program() const
    {
        switch (m_studies)
        {
        case studies::Matematika:
            return "Matematika";
        case studies::Informatika:
            return "Informatika";
        case studies::AstronomijaIAstrofizika:
            return "Astronomija i Astrofizika";
        default:
            throw "Nepoznat smer";
        }
    }

private:
    std::string m_name;
    studies m_studies;
    std::vector<int> m_grades;
};

class master_student : public student 
{
public:
    master_student(const std::string & name, const studies studies, const std::string & thesis, const std::string & mentor)
        // Pozivanje konstruktora bazne klase
        : student(name, studies)
        // Inicijalizacija ostalih atributa
        , m_thesis(thesis)
        , m_mentor(mentor)
    {}

    ~master_student()
    {
        std::cout << "~master_student" << std::endl;
    }

    // ... a u izvedenoj klasi za dati metod
    // navesti kljucnu rec `override`.
    std::string name() const override
    {
        return student::name() + " MSC";
    }

    const std::string & thesis() const
    {
        return m_thesis;
    }

private:
    std::string m_thesis;
    std::string m_mentor;
};

int main()
{
    std::cout << "Testiranje kreiranja objekata..." << std::endl;
    student s1("Petar Petrovic", studies::Matematika);

    s1.add_grade(8);
    s1.add_grade(9);
    s1.add_grade(8);
    s1.add_grade(9);

    std::cout << "s1: " << s1.name() << " " << s1.average() << std::endl;

    master_student s2("Janka Jankovic", studies::Informatika, "Plan 9 FS", "Mirko Mirkovic");

    s2.add_grade(9);
    s2.add_grade(10);
    s2.add_grade(9);

    std::cout << "s2: " << s2.name() << " " << s2.average() << std::endl;

    // Kako mozemo sacuvati podatak potklase kao podatak natklase?
    std::cout << "\nTestiranje kastovanja uz hijerarhiju..." << std::endl;
    
    // Jedan pokusaj bi bio cuvanjem objekta:
    const student s2_object = s2;
    std::cout << "s2_object: " << s2_object.name() << " " << s2_object.average() << std::endl;

    // Kao sto vidimo iz ispisa,
    // cak i ako je metod `name` deklarisan kao virtualan,
    // objekat `s2_sliced` nema informaciju o tome da je to zapravo `master_student`.
    // Ova pojava se naziva odsecanje (engl. slicing).

    // Drugi pokusaj je cuvanjem reference:
    const student & s2_ref = s2;
    std::cout << "s2_ref: " << s2_ref.name() << " " << s2_ref.average() << std::endl;

    // Kao sto vidimo iz ispisa,
    // bice pozvan odgovarajuci metod,
    // zato sto pri "kastovanju" referenci ne dolazi do odsecanja.
    
    // Slicno vazi i za pokazivace:
    const student * s2_pointer = &s2;
    std::cout << "s2_pointer: " << s2_pointer->name() << " " << s2_pointer->average() << std::endl;

    std::cout << "\nTestiranje kastovanja niz hijerarhiju..." << std::endl;

    // Primetimo da je tip `s2_pointer` pokazivac na `student`.
    // Zbog toga, bez obzira sto on zapravo sadrzi adresu objekta tipa `master_student`,
    // ne mozemo preko njega da pristupimo clanicama 
    // koje su definisane u `master_student`, a nisu u `student`.
    // Naredna linija ne prolazi kompilaciju:
    
    // s2_pointer->thesis();

    // Da bismo kastovali pokazivac niz hijerarhiju klasa (engl. downcast),
    // moramo da pozovemo operator dynamic_cast,
    // koji vrsti kastovanje u toku izvrsavanja programa.
    // Ako ovaj operator vrati `nullptr`, to znaci da 
    // pokazivac zapravo ne sadrzi adresu ciljane klase.
    const auto s2_master = dynamic_cast<const master_student*>(s2_pointer);
    if (s2_master)
    {
        std::cout << "s2_master: " << s2_master->name() << " " 
            << s2_master->average() << " " << s2_master->thesis() << std::endl;
    }
    else
    {
        std::cout << "Konverzija nije uspesna" << std::endl;
    }

    // Slicno vazi i za reference,
    // sa razlikom da se u slucaju neuspeha ispaljuje std::bad_cast
    try
    {
        const auto s2_master_ref = dynamic_cast<const master_student&>(s2_ref);
        std::cout << "s2_master_ref: " << s2_master_ref.name() << " "
            << s2_master_ref.average() << " " << s2_master_ref.thesis() << std::endl;
    } 
    catch (const std::bad_cast & err)
    {
        std::cout << "Konverzija nije uspesna: " << err.what() << std::endl;
    }

    // Domaci: istraziti rad sa hijerarhijom klasa
    // u slucaju sa pametnim pokazivacima.

    return 0;
}
