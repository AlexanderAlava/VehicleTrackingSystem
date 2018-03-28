#include <iostream>
#include <vector>
using namespace std;

// Defining the Car class //
class Car
{
  public:

    // Declaring data members //
    string type;
    string make;
    string model;
    string year;
    int count;

    // Declaring the constructor //
    Car(string type, string make, string model, string year);

    // Declaring member functions //
    void addCar();
    void deleteCar();
    void sellCar();
    void searchCar();
    void printInventory();

    // Declaring the destructor //
    ~Car();

};

// Defining the constructor for the Car class //
Car::Car(string type, string make, string model, string year)
{
  type = type;
  make = make;
  model = model;
  year = year;
}

void Car::addCar()
{
  // Declaring temporary string variables //
  string tempType;
  string tempMake;
  string tempModel;
  string tempYear;

  // Prompting for and reading in user input for car details //
  cout << "Please enter the following information regarding the vehicle:\n";
  cout << "Type: ";
  cin >> tempType;
  cout << "Make: ";
  cin >> tempMake;
  cout << "Model: ";
  cin >> tempModel;
  cout << "Year: ";
  cin >> tempYear;

  Car newCar(tempType, tempMake, tempModel, tempYear);
  inventory.push_back(newCar); // TODO(Vector placement/usage has to be sorted out, not currently working) //
}

// Defining the function that will delete car batches from the car vector //
void Car::deleteCar()
{

}

// Defining the function that will delete a sold car from the inventory //
void Car::sellCar()
{

}

// Defining the function that will search for a specific car //
void Car::searchCar()
{

}

// Defining the function that will print the current inventory //
void Car::printInventory()
{

}

// Defining the destructor for the Car class //
Car::~Car()
{
  // Empty body for destructor //
}

int main()
{
  // Declaring an integer variable //
  int option = 0;

  // Declaring a vector of Car pointers //
  vector<Car *> inventory(); // TODO Should this be Car or Car *? //

  cout << "Welcome to this car dealership!\n\n";

  // Establishing an infinite while loop to run the program //
  while(true)
  {
    // Prompting for and reading in input for current selection //
    cout << "(1) Add a car batch to the inventory.\n";
    cout << "(2) Delete a car batch from the inventory.\n";
    cout << "(3) Complete a sale.\n";
    cout << "(4) Search for a specific car in the inventory.\n";
    cout << "(5) Print current availability of all vehicles in the inventory.\n\n";
    cout << "Please enter your selection or enter anything else to exit the program: ";
    cin >> option;

    // Establishing a switch case that determines current action //
    switch (option)
    {
      case 1:
        // Call addCar //
        break;
      case 2:
        // Call deleteCar //
        break;
      case 3:
        // Call sellCar //
        break;
      case 4:
        // Call searchCar //
        break;
      case 5:
        // Call printInventory //
        break;
      default:
        cout << "\n\nThank you for using this program!\nSee you next time!\n";
        return 0;
    }
  }
  return 0;
}
