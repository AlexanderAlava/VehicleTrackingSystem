#include <iostream>     // console i/o
#include <algorithm>    // needed to use 'for_each'
#include <vector>       // supports vector of cars
#include <string>       // car descriptions
#include <sstream>      // converting count of cars from string of user intput to int
#include <fstream>      // file i/o

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
    void deleteCar(vector<Car> &inventory);
    void sellCar(vector<Car> &inventory);
    void searchCar(vector<Car> inventory); //searches for car based on parameters. all fields not needed
    void printInventory(vector<Car> inventory);
    void promptCar(string &tempType, string &tempMake, string &tempModel, string &tempYear);
    int getCarIndex(vector<Car> inventory); //gets index of car in inventory that matches search. ALL FIELDS NEEDED
    bool carExists(vector<Car> inventory, int &carIndex);
    void carDescToLower(string &lowerType, string &lowerMake, string &lowerModel, string &lowerYear);
    friend ostream& operator<<(ostream& os, Car& car);
    friend bool operator==(const Car& compare1, const Car& compare2);
    // Declaring the destructor //
    ~Car();

};

class InventoryFile
{
    // Declaring data members //
public:
    bool fileExists = false;
    const string fName = "inventory.csv";
    // Declaring constructor //
    InventoryFile();
    // Declaring member functions
    vector<Car> readFileToInventory(); //reads inventory in CSV file and writes to vector
    void saveInventoryToFile(vector<Car> inventory);    //saves inventory to file in CSV format
    // Declaring the destructor //
    ~InventoryFile();
};


// Defining the constructor for the Car class //
Car::Car(string type2, string make2, string model2, string year2, int count2) : type(type2), make(make2), model(model2),
year(year2), count(count2)
{
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
    std::cout << "Count: ";
    getline(std::cin, sTempCount);
    stringstream convert(sTempCount);   //converting string to int
    convert >> iTempCount;
    //cout << iTempCount << " iTempCount" << endl;

    //If user leaves Count empty or puts down a dumb negative number, assume at least 1 car and not 0 or nega-cars
    if (iTempCount <= 0)
        iTempCount = 1;


    Car newCar(tempType, tempMake, tempModel, tempYear, iTempCount); // Make newCar object with desired Type, Make, Model, and Year
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
    
    
    /*-------------------------------------------------------------------------------------
    Original logic that checked if car was in the inventory already 
    -------------------------------------------------------------------------------------*/

    //int newCarIndex = newCar.getCarIndex(inventory);     // Get index to see if it exists in the vector already
    //if(newCarIndex == -1)
    //{
    //    inventory.push_back(newCar);    // TODO(Vector placement/usage has to be sorted out, not currently working) //
    //}
    //else
    //{
    //    inventory[newCarIndex].count += newCar.count; //Add count of the car with the same attributes
    //}
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
    if (searchedCar.carExists(inventory,carIndex))
    {
        //Decrement car count
        inventory[carIndex].count--;
        //If car has 0 or less, then delete car and remove the index from the vector
        if (inventory[carIndex].count <= 0)
        {
            inventory[carIndex].~Car();
            inventory.erase(inventory.begin() + carIndex);
        }
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

    vector<Car> tempList;
    for (int pos = 0; pos < inventory.size(); pos++)
    {
        //Get description of car in vector
        vCarType = inventory[pos].type;
        vCarMake = inventory[pos].make;
        vCarModel = inventory[pos].model;
        vCarYear = inventory[pos].year;
        //Make them lowercase
        car.carDescToLower(vCarType, vCarMake, vCarModel, vCarYear);
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
    std::cout << endl  << endl << "Number of cars in inventory: " << numCars << endl; //print total number of cars
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

// Defining the constructor for the InventoryFile class //
InventoryFile::InventoryFile()
{
    ifstream fIn(fName);
    if (fIn)
    {
        fileExists = true;
        std::cout << std::endl << std::endl << "Inventory file found" << std::endl;
    }
    else
    {
        fileExists = false;
        std::cout << std::endl << std::endl << "Inventory NOT file found. Creating file..." << std::endl;
        ofstream fOut(fName);
        fOut.close();
    }
}

// Defining the readFileToInventory function //
vector<Car> InventoryFile::readFileToInventory()
{
    vector<Car> invFileContents;    //store cars in this vector
    vector<string> lineVector;      //split line into vector
    string line = "";               //string for storing line
    int tempNum;
    //if file exists then parse the csv
    if (this->fileExists)
    {
        //open file
        ifstream fIn(fName);
        //while there are lines, read them
        while (std::getline(fIn, line))
        {
            //for parsing and converting to int
            stringstream parse(line);

            //iterate through the stringstream to parse csv
            while (parse)
            {
                //store data between commas
                string data;
                std::getline(parse, data, ',');
                lineVector.push_back(data);
            }
            //convert last value to int
            stringstream convert(lineVector[4]);
            convert >> tempNum;
            //create car and store in vector
            Car car(lineVector[0], lineVector[1], lineVector[2], lineVector[3], tempNum);
            invFileContents.push_back(car);
            lineVector.clear();
        }
    }

    return invFileContents;
}

// Defining the saveInventoryToFile function //
void InventoryFile::saveInventoryToFile(vector<Car> inventory)
{
    ofstream fOut(fName);
    //Make sure it is open for writing
    if (fOut.is_open())
    {
        for (int pos = 0; pos < inventory.size(); pos++)
        {
            stringstream convert;
            convert << inventory[pos].count;
            fOut << inventory[pos].type << "," << inventory[pos].make << "," << inventory[pos].model << "," << inventory[pos].year << "," << convert.str() << endl;
        }
    }
    fOut.close();
}

InventoryFile::~InventoryFile()
{

}

int main()
{
    // Declaring an integer variable //
    int option = 0;

    // Declaring placeholder car for calling non-static methods //
    Car car("0", "0", "0", "0", 0);
    // Declaring InventoryFile object to handle reading and writing inventory to disk //
    InventoryFile invFile;
    // Declaring a vector of Car pointers //
    vector<Car> inventory(invFile.readFileToInventory()); // Attempt to read inventory to disk //
    std::cout << "Welcome to this car dealership!\n\n";

    // Establishing an infinite while loop to run the program //
    while (true)
    {
        // Prompting for and reading in input for current selection //
        std::cout << "(1) Add a car batch to the inventory.\n";
        std::cout << "(2) Delete a car batch from the inventory.\n";
        std::cout << "(3) Complete a sale.\n";
        std::cout << "(4) Search for a specific car in the inventory.\n";
        std::cout << "(5) Print current availability of all vehicles in the inventory.\n";
        std::cout << "(6) Save current inventory of all vehicles to file.\n\n";

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
        case 6:
            // Call saveInventoryToFile //
            invFile.saveInventoryToFile(inventory);
            break;
        default:
            std::cout << "\n\nThank you for using this program!\nSee you next time!\n";
            invFile.saveInventoryToFile(inventory);
            return 0;
        }
    }
    return 0;
}
