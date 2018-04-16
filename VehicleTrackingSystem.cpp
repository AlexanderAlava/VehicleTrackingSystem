#include <iostream>     // console i/o
#include <algorithm>    // for 'for_each'
#include <vector>       // supports vector of cars
#include <string>       // car descriptions
#include <sstream>      // converting count of cars from string of user intput to int

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
    void addCar(vector<Car> &inventory); //Adds car by prompting the user for information
    void deleteCar(vector<Car> &inventory); //Deletes specific car that matches user supplied information
    void sellCar(vector<Car> &inventory); //Sells specific car that matches user supplied information
    void searchCar(vector<Car> inventory); //searches for car based on parameters. all fields not needed
    void printInventory(vector<Car> inventory); //Prints all cars in the inventory
    void promptCar(string &tempType, string &tempMake, string &tempModel, string &tempYear); //Function to prompt user for information
    int getCarIndex(vector<Car> inventory); //gets index of car in inventory that matches search. ALL FIELDS NEEDED
    bool carExists(vector<Car> inventory, int &carIndex); //checks if car exists and gets the index
    void carDescToLower(string &lowerType, string &lowerMake, string &lowerModel, string &lowerYear); //converts descriptor strings to lowercase for comparing 2 cars
    friend ostream& operator<<(ostream& os, Car& car);
    friend bool operator==(const Car& compare1, const Car& compare2);
    // Declaring the destructor //
    ~Car();

};

// Defining the constructor for the Car class //
Car::Car(string type2, string make2, string model2, string year2, int count2) : type(type2), make(make2), model(model2),
year(year2), count(count2)
{
    //If something goes wrong or the user  puts in a bogus number then set the count of cars to 1
    if (count2 < 1)
        count = 1;
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
    //Get num of cars to add
    std::cout << "Count: ";
    getline(std::cin, sTempCount);
    stringstream convert(sTempCount);   //converting string to int
    convert >> iTempCount;

    //If user leaves Count empty or puts down a dumb negative number, assume at least 1 car and not 0 or nega-cars
    if (iTempCount <= 0)
        iTempCount = 1;

    Car newCar(tempType, tempMake, tempModel, tempYear, iTempCount); // Make newCar object with desired Type, Make, Model, and Year

                                                                     //Check if the car is in the inventory already
    if (newCar.carExists(inventory, iTempCount)) //reusing iTempCount as carIndex
    {
        //if the car already exists in the inventory, add to the count
        inventory[iTempCount].count += newCar.count;
    }
    else
    {
        //if the car doesn't exist in the inventory, add it to the inventory
        inventory.push_back(newCar);
    }

}

// Defining the function that will delete car batches from the car vector //
void Car::deleteCar(vector<Car> &inventory)
{
    //Prompt user for car details
    string tempType;
    string tempMake;
    string tempModel;
    string tempYear;
    int carIndex;
    promptCar(tempType, tempMake, tempModel, tempYear);

    //See if car exists within the inventory
    Car searchedCar(tempType, tempMake, tempModel, tempYear, 0);

    //If car exists, remove it from the inventory
    if (searchedCar.carExists(inventory, carIndex))
    {
        inventory[carIndex].~Car();
        inventory.erase(inventory.begin() + carIndex);
    }
    else
    {
        //otherwise tell user that they can't delete a car that never existed
        std::cout << endl << endl << "Can't delete a car that doesn't exist!" << endl;
    }

}

// Defining the function that will delete a sold car from the inventory //
void Car::sellCar(vector<Car> &inventory)
{
    //Prompt user for car details
    string tempType;
    string tempMake;
    string tempModel;
    string tempYear;
    int carIndex;
    promptCar(tempType, tempMake, tempModel, tempYear);

    //See if car exists within the inventory
    Car searchedCar(tempType, tempMake, tempModel, tempYear, 0);

    //if car exists, decrement the count
    if (searchedCar.carExists(inventory, carIndex))
    {
        //Decrement car count
        inventory[carIndex].count--;
        //If car has 0 or less, then delete car and remove the index from the vector
        if (inventory[carIndex].count <= 0)
        {
            inventory[carIndex].~Car();
            inventory.erase(inventory.begin() + carIndex);
        }
        std::cout << std::endl << "SOLD!" << std::endl;
        return;
    }
    else //otherwise tell user that the car they are trying to sell doesn't exist
    {
        std::cout << endl << endl << "Car does not exist!" << endl;
        return;
    }

}

// Defining the function that will search for a specific car //
void Car::searchCar(vector<Car> inventory)
{
    Car car("0", "0", "0", "0", 0);
    //Declare vars for storing search parameters
    string tempType;
    string tempMake;
    string tempModel;
    string tempYear;

    //Get search parameters and make them lowercase
    promptCar(tempType, tempMake, tempModel, tempYear);
    car.carDescToLower(tempType, tempMake, tempModel, tempYear);

    //Declare vars for cars in vector to make them lowercase
    string vCarType;
    string vCarMake;
    string vCarModel;
    string vCarYear;

    vector<Car> tempList; //vector for storing search results
    for (int pos = 0; pos < inventory.size(); pos++)
    {
        //Get description of car in vector
        vCarType = inventory[pos].type;
        vCarMake = inventory[pos].make;
        vCarModel = inventory[pos].model;
        vCarYear = inventory[pos].year;

        //Make them lowercase
        car.carDescToLower(vCarType, vCarMake, vCarModel, vCarYear);

        //compare lowercase descriptions from inventory to user supplied lowercase descriptions
        //No input for a search field is an implied don't care/wildcard
        if (vCarType == tempType || tempType.length() == 0) //if type matches or no input
        {
            if (vCarMake == tempMake || tempMake.length() == 0) //if make matches or no input
            {
                if (vCarModel == tempModel || tempModel.length() == 0) //if model matches or no input
                {
                    if (vCarYear == tempYear || tempYear.length() == 0) //if year matches or no input
                        tempList.push_back(inventory[pos]); //push car from inv on to tempList if it meets criteria
                }
            }
        }
    }
    //Print list of cars that match the search results
    std::cout << endl << endl << "Cars matching search: " << endl;
    printInventory(tempList);


}

// Defining the function that will print the current inventory //
void Car::printInventory(vector<Car> inventory)
{
    int numCars = 0;    //for getting total number of cars
    for (int position = 0; position < (int)inventory.size(); position++)
    {
        numCars += inventory[position].count;
        std::cout << inventory[position] << endl;
    }
    std::cout << endl << endl << "Number of cars in inventory: " << numCars << endl; //print total number of cars
}

// Defining the prompt function that will ask for the car details //
void Car::promptCar(string &tempType, string &tempMake, string &tempModel, string &tempYear)
{
    std::cout << "Please enter the following information regarding the vehicle:" << endl;
    std::cout << "Type: ";
    getline(std::cin.ignore(), tempType); //need to use cin.ignore() to ignore that newline
    std::cout << "Make: ";
    getline(std::cin, tempMake);
    std::cout << "Model: ";
    getline(std::cin, tempModel);
    std::cout << "Year: ";
    getline(std::cin, tempYear);
    return;
}

// Defining the function that will return the index of an equivalent car //
int Car::getCarIndex(vector<Car> inventory)
{
    //Iterate through the inventory. Return index if match. Return -1 if no match.
    for (int pos = 0; pos < inventory.size(); pos++)
    {
        if (inventory[pos] == *this)
            return pos;
    }
    return -1;
}

// Defining the function that will return if the car exists in the inventory or not and the index//
bool Car::carExists(vector<Car> inventory, int &carIndex)
{
    //get the index
    carIndex = this->getCarIndex(inventory);
    //return bool based on index
    if (carIndex > -1)
        return true;
    else
    {
        return false;
    }
}


// Defining the function that will transform strings to lower
void Car::carDescToLower(string &lowerType, string &lowerMake, string &lowerModel, string &lowerYear)
{
    //C++ for each turn string into lowercase car Type
    std::for_each(lowerType.begin(), lowerType.end(), [](char & c)
    {
        c = ::tolower(c);
    }
    );
    //C++ for each turn string into lowercase car Make
    std::for_each(lowerMake.begin(), lowerMake.end(), [](char & c)
    {
        c = ::tolower(c);
    }
    );
    //C++ for each turn string into lowercase car Model
    std::for_each(lowerModel.begin(), lowerModel.end(), [](char & c)
    {
        c = ::tolower(c);
    }
    );
    //C++ for each turn string into lowercase car Year
    std::for_each(lowerYear.begin(), lowerYear.end(), [](char & c)
    {
        c = ::tolower(c);
    }
    );
    return;
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
    //Make blank car for calling the function
    Car car("0", "0", "0", "0", 0);
    //Get car description and convert to lower
    string c1LowerType = compare1.type;
    string c1LowerMake = compare1.make;
    string c1LowerModel = compare1.model;
    string c1LowerYear = compare1.year;
    car.carDescToLower(c1LowerType, c1LowerMake, c1LowerModel, c1LowerYear);

    //Get car description and convert to lower
    string c2LowerType = compare2.type;
    string c2LowerMake = compare2.make;
    string c2LowerModel = compare2.model;
    string c2LowerYear = compare2.year;
    car.carDescToLower(c2LowerType, c2LowerMake, c2LowerModel, c2LowerYear);


    if (c1LowerType == c2LowerType &&
        c1LowerMake == c2LowerMake &&
        c1LowerModel == c2LowerModel &&
        c1LowerYear == c2LowerYear)
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
    vector<Car> inventory;
    std::cout << std::endl << "Welcome to this car dealership!\n\n";

    // Establishing an infinite while loop to run the program //
    while (true)
    {
        // Prompting for and reading in input for current selection //
        std::cout << "(1) Add a car batch to the inventory.\n";
        std::cout << "(2) Delete a car batch from the inventory.\n";
        std::cout << "(3) Complete a sale.\n";
        std::cout << "(4) Search for a specific car in the inventory.\n";
        std::cout << "(5) Print current availability of all vehicles in the inventory.\n\n";

        std::cout << "Please enter your selection or enter anything else to exit the program: ";
        std::cin >> option;

        // Establishing a switch case that determines current action //
        switch (option)
        {
        case 1:
            // Call addCar //
            car.addCar(inventory);
            break;
        case 2:
            // Call deleteCar //
            car.deleteCar(inventory);
            break;
        case 3:
            // Call sellCar //
            car.sellCar(inventory);
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
            std::cout << "\n\nThank you for using this program!\nSee you next time!\n";
            return 0;
        }
    }
    return 0;
}
