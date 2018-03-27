#include <iostream>
using namespace std;

class Car
{
  public:

    // Data members //
    string type;
    string make;
    string model;
    string year;
    int count;

    // Member functions //
    Car(string type, string make, string model, string year);
    void addCar();
    void deleteCar();
    void sellCar();
    void searchCar();
    void printInventory();
    ~Car();

};

Car::Car(string type, string make, string model, string year)
{
  type = type;
  make = make;
  model = model;
  year = year;
}

void Car::addCar()
{
  string tempType;
  string tempMake;
  string tempModel;
  string tempYear;

  cout << "Please enter the following information regarding the vehicle:\n";
  cout << "Type: ";
  cin >> tempType;
  cout << "Make: ";
  cin >> tempMake;
  cout << "Model: ";
  cin >> tempModel;
  cout << "Year: ";
  cin >> tempYear;

  Car car1(tempType, tempMake, tempModel, tempYear);
}

Car::~Car()
{

}

int main()
{
  int option = 0;

  cout << "Welcome to this car dealership!\n\n";

  cout << "(1) Add a car batch to the inventory.\n";
  cout << "(2) Delete a car batch from the inventory.\n";
  cout << "(3) Complete a sale.\n";
  cout << "(4) Search for a specific car in the inventory.\n";
  cout << "(5) Print current availability of all vehicles in the inventory.\n\n";
  cout << "Please enter your selection or enter anything else to exit the program: ";
  cin >> option;

  return 0;
}
