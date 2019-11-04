#include <vector>
#include <iostream>
#include <string>

class Vehicle
{
public:
    virtual ~Vehicle() = default;

    // Tip vozila je nepoznat za baznu klasu,
    // pa zato ovaj metod mora biti apstraktan (notacija `= 0` ispod).
    // Apstraktne klase se ne mogu instancirati, vec vazi pravilo:
    // - U stablu hijerarhije na svakom putu od korena (bazne klase)
    //   do svih listova (najspecificnijih izvedenih klasa)
    //   mora postojati makar jedna implementacija apstraktnog metoda.
    // Na primer, na putu `Vehicle` -> `VehicleWithWindow` -> `Car`,
    // apstraktni metod `Type()` je implementiran u klasi `Car`.
    virtual std::string Type() const = 0;

    // Zasto kreiramo metod koji vraca pokazivac na kopiju objekta?
    // Zato sto konstruktor kopije ne moze biti virtualan!
    // Umesto toga, metod `Copy()` ce u konkretnim klasama biti prevazidjen
    // tako da vraca dinamicki objekat odgovarajuceg tipa.
    // Na primer, u klasi `Car` kreira dinamicki objekat tipa `Car` i vraca `Car *`.
    // Konverzija iz `Car *` u `Vehicle *` je trivijalna jer je uz istu hijerarhiju.
    virtual Vehicle * Copy() const = 0;
    
    unsigned NumOfWheels() const
    {
        return m_numOfWheels;
    }

    unsigned NumOfSeats() const
    {
        return m_numOfSeats;
    }

protected:
    Vehicle(const unsigned wheels, const unsigned seats)
        : m_numOfWheels(wheels)
        , m_numOfSeats(seats)
    {}

    unsigned m_numOfWheels;
    unsigned m_numOfSeats;
};

std::ostream & operator<<(std::ostream& out, const Vehicle& v)
{
    return out << v.Type() << " " << v.NumOfSeats() << " " << v.NumOfWheels();
}

class Bicycle : public Vehicle
{
public:
    Bicycle(const unsigned wheels = 2u, const unsigned seats = 1u)
        : Vehicle(wheels, seats)
    {}

    Vehicle * Copy() const override
    {
        return new Bicycle(*this);
    }

    std::string Type() const override
    {
        return "Bicycle";
    }
};

std::ostream & operator<<(std::ostream & out, const Bicycle & b)
{
    return out << b.Type() << " " << b.NumOfSeats() << " " << b.NumOfWheels();
}

class VehicleWithWindows : public Vehicle
{
public:
    unsigned NumOfWindows() const
    {
        return m_numOfWindows;
    }

protected:
    VehicleWithWindows(const unsigned windows, const unsigned seats, const unsigned wheels)
        : Vehicle(wheels, seats)
        , m_numOfWindows(windows)
    {}

    unsigned m_numOfWindows;
};

std::ostream & operator<<(std::ostream & out, const VehicleWithWindows & vsp)
{
    return out << vsp.Type() << " " << vsp.NumOfSeats() << " " << vsp.NumOfWheels() << " " << vsp.NumOfWindows();
}

class Car : public VehicleWithWindows
{
public:
    Car(const unsigned windows = 6u, const unsigned seats = 5u, const unsigned wheels = 4u)
        : VehicleWithWindows(windows, seats, wheels)
    {}

    Vehicle * Copy() const override
    {
        return new Car(*this);
    }

    std::string Type() const override
    {
        return "Car";
    }
};

std::ostream & operator<<(std::ostream & out, const Car & a)
{
    return out << a.Type() << " " << a.NumOfSeats() << " " << a.NumOfWheels() << " " << a.NumOfWindows();
}

class Truck : public VehicleWithWindows
{
public:
    Truck(const unsigned windows = 3u, const unsigned seats = 3u, const unsigned wheels = 6u)
        : VehicleWithWindows(windows, seats, wheels)
    {}

    Vehicle * Copy() const override
    {
        return new Truck(*this);
    }

    std::string Type() const override
    {
        return "Truck";
    }
};

std::ostream & operator<<(std::ostream & out, const Truck & k)
{
    return out << k.Type() << " " << k.NumOfSeats() << " " << k.NumOfWheels() << " " << k.NumOfWindows();
}

class VehiclePark
{
public:
    VehiclePark() = default;
    ~VehiclePark()
    {
        for (auto v : m_vehicles)
        {
            delete v;
        }
        m_vehicles.clear();
    }

    VehiclePark(const VehiclePark & other)
    {
        for (const auto v : other.m_vehicles)
        {
            m_vehicles.push_back(v->Copy());
        }
    }

    // Implementiramo netrivijalni destruktor i konstruktor kopije.
    // Prema "pravilu 5", treba implementirati i: 
    // - operator dodeljivanja sa semantikom kopiranja
    // - konstruktor pomeranja
    // - operator dodeljivanja sa semantikom pomeranja
    // Uraditi za domaci!

    void Add(Vehicle * vehicle)
    {
        m_vehicles.push_back(vehicle);
    }
private:
    friend std::ostream & operator<<(std::ostream & out, const VehiclePark & vp);

    std::vector<Vehicle*> m_vehicles;
};

std::ostream & operator<<(std::ostream & out, const VehiclePark & vp)
{
    for (const auto v : vp.m_vehicles)
    {
        out << *v << ", ";
    }
    return out;
}

int main()
{
    const Car a;
    const Truck k;
    const Bicycle b;

    const VehicleWithWindows* v = new Truck();

    std::cout << a << std::endl;
    std::cout << k << std::endl;
    std::cout << b << std::endl;
    std::cout << *v << std::endl;

    VehiclePark vp;

    vp.Add(new Car(a));
    vp.Add(new Truck(k));
    vp.Add(new Car());
    vp.Add(new Bicycle(4, 2));

    std::cout << vp << std::endl;

    auto vp2 = vp;

    vp2.Add(new Truck());

    std::cout << vp2 << std::endl;
    std::cout << vp << std::endl;

    delete v;

    return 0;
}
