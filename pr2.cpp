#include <iostream>
#include <string>
using namespace std;

// ===================== VEHICLE CLASS =====================
class Vehicle
{
private:
    int vehicleID;
    string manufacturer;
    string model;
    int year;

protected:
    int getID() const
    {
        return vehicleID;
    }

public:
    static int totalVehicles;

    // Default Constructor
    Vehicle()
    {
        vehicleID = 0;
        manufacturer = "";
        model = "";
        year = 0;
        totalVehicles++;
    }

    // Parameterized Constructor
    Vehicle(int id, string manu, string mod, int yr)
    {
        vehicleID = id;
        manufacturer = manu;
        model = mod;
        year = yr;
        totalVehicles++;
    }

    // Destructor
    virtual ~Vehicle()
    {
        totalVehicles--;
    }

    // Setters
    void setVehicleID(int id)
    {
        vehicleID = id;
    }

    void setManufacturer(string manu)
    {
        manufacturer = manu;
    }

    void setModel(string mod)
    {
        model = mod;
    }

    void setYear(int yr)
    {
        year = yr;
    }

    // Getters
    int getVehicleID() const
    {
        return vehicleID;
    }

    string getManufacturer() const
    {
        return manufacturer;
    }

    string getModel() const
    {
        return model;
    }

    int getYear() const
    {
        return year;
    }

    virtual void display()
    {
        cout << "\nVehicle ID : " << vehicleID;
        cout << "\nManufacturer : " << manufacturer;
        cout << "\nModel : " << model;
        cout << "\nYear : " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

// ===================== CAR CLASS (Single Inheritance) =====================
class Car : public Vehicle
{
private:
    string fuelType;

public:
    Car() : Vehicle()
    {
        fuelType = "";
    }

    Car(int id, string manu, string mod, int yr, string fuel)
        : Vehicle(id, manu, mod, yr)
    {
        fuelType = fuel;
    }

    void setFuelType(string fuel)
    {
        fuelType = fuel;
    }

    string getFuelType()
    {
        return fuelType;
    }

    void display() override
    {
        Vehicle::display();
        cout << "Fuel Type : " << fuelType << endl;
    }
};

// ===================== ELECTRIC CAR (Multilevel) =====================
class ElectricCar : public Car
{
private:
    float batteryCapacity;

public:
    ElectricCar() : Car()
    {
        batteryCapacity = 0;
    }

    ElectricCar(int id, string manu, string mod, int yr,
                string fuel, float battery)
        : Car(id, manu, mod, yr, fuel)
    {
        batteryCapacity = battery;
    }

    void display() override
    {
        Car::display();
        cout << "Battery Capacity : " << batteryCapacity << " kWh" << endl;
    }
};

// ===================== SPORTS CAR (Multilevel) =====================
class SportsCar : public ElectricCar
{
private:
    int topSpeed;

public:
    SportsCar() : ElectricCar()
    {
        topSpeed = 0;
    }

    SportsCar(int id, string manu, string mod, int yr,
              string fuel, float battery, int speed)
        : ElectricCar(id, manu, mod, yr, fuel, battery)
    {
        topSpeed = speed;
    }

    void display() override
    {
        ElectricCar::display();
        cout << "Top Speed : " << topSpeed << " km/h" << endl;
    }
};

// ===================== AIRCRAFT CLASS =====================
class Aircraft
{
protected:
    int flightRange;

public:
    Aircraft()
    {
        flightRange = 0;
    }

    Aircraft(int range)
    {
        flightRange = range;
    }

    void displayAircraft()
    {
        cout << "Flight Range : " << flightRange << " km" << endl;
    }
};

// ===================== FLYING CAR (Multiple Inheritance) =====================
class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar()
    {
    }

    FlyingCar(int id, string manu, string mod, int yr,
              string fuel, int range)
        : Car(id, manu, mod, yr, fuel), Aircraft(range)
    {
    }

    void display()
    {
        Car::display();
        displayAircraft();
    }
};

// ===================== SEDAN (Hierarchical Inheritance) =====================
class Sedan : public Car
{
public:
    Sedan()
    {
    }

    Sedan(int id, string manu, string mod, int yr, string fuel)
        : Car(id, manu, mod, yr, fuel)
    {
    }
};

// ===================== SUV (Hierarchical Inheritance) =====================
class SUV : public Car
{
public:
    SUV()
    {
    }

    SUV(int id, string manu, string mod, int yr, string fuel)
        : Car(id, manu, mod, yr, fuel)
    {
    }
};

// ===================== VEHICLE REGISTRY =====================
class VehicleRegistry
{
private:
    Vehicle vehicles[100]; // Array of Objects
    int count;

public:
    VehicleRegistry()
    {
        count = 0;
    }

    void addVehicle()
    {
        if (count >= 100)
        {
            cout << "Registry Full!\n";
            return;
        }

        int id, year;
        string manufacturer, model;

        cout << "\nEnter Vehicle ID : ";
        cin >> id;

        cin.ignore();

        cout << "Enter Manufacturer : ";
        getline(cin, manufacturer);

        cout << "Enter Model : ";
        getline(cin, model);

        cout << "Enter Year : ";
        cin >> year;

        vehicles[count].setVehicleID(id);
        vehicles[count].setManufacturer(manufacturer);
        vehicles[count].setModel(model);
        vehicles[count].setYear(year);

        count++;

        cout << "\nVehicle Added Successfully!\n";
    }

    void displayVehicles()
    {
        if (count == 0)
        {
            cout << "\nNo Vehicles Found!\n";
            return;
        }

        cout << "\n===== VEHICLE LIST =====\n";

        for (int i = 0; i < count; i++)
        {
            cout << "\nVehicle " << i + 1 << endl;
            vehicles[i].display();
        }

        cout << "\nTotal Vehicles : " << count << endl;
    }

    void searchVehicle(int id)
    {
        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (vehicles[i].getVehicleID() == id)
            {
                cout << "\nVehicle Found!\n";
                vehicles[i].display();
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\nVehicle Not Found!\n";
        }
    }
};

// ===================== MAIN FUNCTION =====================
int main()
{
    VehicleRegistry registry;

    int choice, id;

    do
    {
        cout << "\n================================";
        cout << "\n   VEHICLE REGISTRY SYSTEM";
        cout << "\n================================";
        cout << "\n1. Add Vehicle";
        cout << "\n2. View All Vehicles";
        cout << "\n3. Search Vehicle By ID";
        cout << "\n4. Demonstrate Inheritance";
        cout << "\n5. Exit";
        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registry.addVehicle();
            break;

        case 2:
            registry.displayVehicles();
            break;

        case 3:
            cout << "\nEnter Vehicle ID : ";
            cin >> id;
            registry.searchVehicle(id);
            break;

        case 4:
        {
            cout << "\n----- Single Inheritance -----\n";
            Car car(101, "Toyota", "Innova", 2024, "Petrol");
            car.display();

            cout << "\n----- Multilevel Inheritance -----\n";
            ElectricCar ecar(102, "Tesla", "Model 3", 2025,
                             "Electric", 75);
            ecar.display();

            cout << "\n----- Sports Car -----\n";
            SportsCar sport(103, "Tesla", "Roadster", 2025,
                            "Electric", 100, 400);
            sport.display();

            cout << "\n----- Multiple Inheritance -----\n";
            FlyingCar fly(104, "Jetson", "Aero", 2026,
                          "Hybrid", 1200);
            fly.display();

            cout << "\n----- Hierarchical Inheritance -----\n";
            Sedan sedan(105, "Honda", "City", 2024, "Petrol");
            SUV suv(106, "Mahindra", "XUV700", 2025, "Diesel");

            cout << "\nSedan Details:\n";
            sedan.display();

            cout << "\nSUV Details:\n";
            suv.display();

            break;
        }

        case 5:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}