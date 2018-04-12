#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
    Car(string type, string make, string model, string year, int count);

    // Declaring member functions //
    void addCar(vector<Car> &inventory);
    void deleteCar();
    void sellCar(vector<Car> inventory);
    void searchCar(vector<Car> inventory);
    void printInventory(vector<Car> inventory);
    void promptCar(string &tempType, string &tempMake, string &tempModel, string &tempYear);
    int getCarIndex(vector<Car> inventory);
    friend ostream& operator<<(ostream& os, Car& car);
    friend bool operator==(const Car& compare1, const Car& compare2);
    // Declaring the destructor //
    ~Car();

};

// Defining the constructor for the Car class //
Car::Car(string type2, string make2, string model2, string year2, int count2) : type(type2), make(make2), model(model2),
year(year2), count(count2)
{

}

void Car::addCar(vector<Car> &inventory)
{
    // Declaring temporary string variables //
    string tempType;
    string tempMake;
    string tempModel;
    string tempYear;
    string sTempCount;
    int iTempCount = 0;

    // Prompting for and reading in user input for car details //
    promptCar(tempType, tempMake, tempModel, tempYear);
    cout << "Count: ";
    getline(std::cin, sTempCount);
    stringstream convert(sTempCount);   //converting string to int
    convert >> iTempCount;
    //cout << iTempCount << " iTempCount" << endl;

    //If user leaves Count empty, assume at least 1 car and not 0
    if (iTempCount == 0)
        iTempCount = 1;


    Car newCar(tempType, tempMake, tempModel, tempYear, iTempCount); // Make newCar object with desired Type, Make, Model, and Year
    int newCarIndex = newCar.getCarIndex(inventory);     // Get index to see if it exists in the vector already
    if(newCarIndex == -1)
    {
        inventory.push_back(newCar);    // TODO(Vector placement/usage has to be sorted out, not currently working) //
    }
    else
    {
        inventory[newCarIndex].count += newCar.count; //Add count of the car with the same attributes
    }
}

// Defining the function that will delete car batches from the car vector //
void Car::deleteCar()
{

}

// Defining the function that will delete a sold car from the inventory //
void Car::sellCar(vector<Car> inventory)
{

}

// Defining the function that will search for a specific car //
void Car::searchCar(vector<Car> inventory)
{
    string tempType;
    string tempMake;
    string tempModel;
    string tempYear;

    promptCar(tempType, tempMake, tempModel, tempYear);

    vector<Car> tempList;
    for (int pos = 0; pos < inventory.size(); pos++)
    {
        if (inventory[pos].type == tempType || tempType.length() == 0) //if type matches or no input
        {
            if (inventory[pos].make == tempMake || tempMake.length() == 0) //if make matches or no input
            {
                if (inventory[pos].model == tempModel || tempModel.length() == 0) //if model matches or no input
                {
                    if (inventory[pos].year == tempYear || tempYear.length() == 0) //if year matches or no input
                        tempList.push_back(inventory[pos]); //push car from inv on to tempList if it meets criteria
                }
            }
        }
    }
    cout << endl << endl << "Cars matching search: " << endl;
    printInventory(tempList);


}

// Defining the function that will print the current inventory //
void Car::printInventory(vector<Car> inventory)
{
    int numCars = 0;    //for getting total number of cars
    for (int position = 0; position < (int)inventory.size(); position++)
    {
        numCars += inventory[position].count;
        cout << inventory[position] << endl;
    }
    cout << endl  << endl << "Number of cars in inventory: " << numCars << endl; //print total number of cars
}

// Defining the prompt function that will ask for the car details //
void Car::promptCar(string &tempType, string &tempMake, string &tempModel, string &tempYear)
{
    cout << "Please enter the following information regarding the vehicle:" << endl;
    cout << "Type: ";
    getline(std::cin.ignore(), tempType); //need to use cin.ignore() to ignore that newline
    cout << "Make: ";
    getline(std::cin, tempMake);
    cout << "Model: ";
    getline(std::cin, tempModel);
    cout << "Year: ";
    getline(std::cin, tempYear);
    return;
}

// Defining the function that will return the index of an equivalent car //
int Car::getCarIndex(vector<Car> inventory)
{
    for (int pos = 0; pos < inventory.size(); pos++)
    {
        if (inventory[pos] == *this)
            return pos;
    }
    return -1;
}

// Overloading << operator to print cars //
ostream& operator<<(ostream& os, Car& car)
{
    os << "Type:\t" << car.type << endl
        << "Make:\t" << car.make << endl
        << "Model:\t" << car.model << endl
        << "Year:\t" << car.year << endl
        << "Count:\t" << car.count << endl;
    return os;

}

// Overloading == operator for comparing cars //
bool operator==(const Car& compare1, const Car& compare2)
{
    if (compare1.type == compare2.type &&
        compare1.make == compare2.make &&
        compare1.model == compare2.model &&
        compare1.year == compare2.year)
        return true;
    else
        return false;
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

    // Declaring placeholder car for calling non-static methods //
    Car car("0", "0", "0", "0", 0);

    // Declaring a vector of Car pointers //
    vector<Car> inventory; // TODO Should this be Car or Car *? //

    cout << "Welcome to this car dealership!\n\n";

    // Establishing an infinite while loop to run the program //
    while (true)
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
            car.addCar(inventory);
            break;
        case 2:
            // Call deleteCar //
            break;
        case 3:
            // Call sellCar //
            break;
        case 4:
            // Call searchCar //
            car.searchCar(inventory);
            break;
        case 5:
            // Call printInventory //
            car.printInventory(inventory);
            break;
        default:
            cout << "\n\nThank you for using this program!\nSee you next time!\n";
            return 0;
        }
    }
    return 0;
}
