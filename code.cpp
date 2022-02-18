#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

const int MAX_CARS = 999;

struct cars{
    char carName[100] = {' '};
    double MPG;
    int cylinders;
    double displacememnt;
    double horsePower;
    double weight;
    double acceleration;
    int model;
    bool validEntry;
    char origin[100] = {' '};
    cars();
};

cars::cars(){
    MPG = 0;
    cylinders = 0;
    displacememnt = 0;
    horsePower = 0;
    weight = 0;
    acceleration = 0;
    model = 0;
    validEntry = false;
};

void readCarData(ifstream &carFile, int start, int end, cars carz[MAX_CARS]);
void printCars(cars Cars[], int start, int end);
void printOrigin(char origin[], int orSize, int start, int end, cars Cars[MAX_CARS]);
void removeCar(cars Cars[]);
void addCar(cars Cars[]);
int readInt(const char prompt[]);
double readDouble(const char prompt[]);
void displayMenu(cars Cars[]);

int main(){
    //makes all importand variables used throughout the code
    ifstream carFile("cars.txt");
    cars Cars[MAX_CARS];
    readCarData(carFile, 0, 100, Cars);
    //starting menu
    displayMenu(Cars);
    
    return 0;
}

void addCar(cars Cars[]){

    int firstInvalid = -1;
    //Finding invalid Entry
    for(int index = 0; index < MAX_CARS; index++){
        if(Cars[index].validEntry == false){
            firstInvalid = index;
            break;
        }
    }
    if(firstInvalid != -1){
        //Entering New car

        cout << "Empty Slot found (" << firstInvalid << ")" << endl;
        cout << "Enter the cars name: ";
        cin.ignore(100, '\n');
        cin.getline(Cars[firstInvalid].carName, 50);
        //cin >> Cars[firstInvalid].carName;
        Cars[firstInvalid].MPG = readDouble("Enter MPG:");
        Cars[firstInvalid].cylinders = readInt("Enter cylinders:");
        Cars[firstInvalid].displacememnt = readDouble("Enter displacement: ");
        Cars[firstInvalid].horsePower = readDouble("Enter HorsePower: ");
        Cars[firstInvalid].weight = readDouble("Enter Weight:");
        Cars[firstInvalid].acceleration = readDouble("Enter Acceleration: ");
        Cars[firstInvalid].model = readInt("Enter Model#: ");
        cout << "Enter Origin: ";
        cin >> Cars[firstInvalid].origin;
        Cars[firstInvalid].validEntry = true;
        cout << "car entered";

    }else{
        //full message
        cout << "database full!";
    }

}

void removeCar(cars Cars[]){
    //getting one to remove

    int removalIndex = readInt("Enter a car to be removed: ");
    
    //turning index off
    if(removalIndex >= 0 || removalIndex <= MAX_CARS){
        Cars[removalIndex].validEntry = false;
    }
    //comfirmation message (idk why)
    cout << "item removed" << endl;

};

void printOrigin(char origin[], int orSize, int start, int end, cars Cars[999]){

    bool same = true;
    //variable to keep track of if it has the right origin

    //comparing your origin to the origin of the index car
    for(int index = start; index < end; index++){
        if(Cars[index].validEntry == false){
            continue;
        }
        for(int index1 = 0; index1 < orSize; index1++){

            if(origin[index1] != Cars[index].origin[index1]){
                same = false;
                continue;
            }
        }

        //skipping over the print code if the origins do not match
        if(same == false){
            same = true;
            continue;
        }

        //print code
        cout << Cars[index].carName << ";";
        cout << Cars[index].MPG << ";";
        cout << Cars[index].cylinders << ";";
        cout << Cars[index].displacememnt << ";";
        cout << Cars[index].horsePower << ";";
        cout << Cars[index].weight << ";";
        cout << Cars[index].acceleration << ";";
        cout << Cars[index].model << ";";
        cout << Cars[index].origin << endl;
        
        same = true;
    }

};

void readCarData(ifstream &carFile, int start, int end, cars carz[MAX_CARS]){


    //just reads and puts each variable into the right spot
    for(int index = start; index < end; index++){

        carFile.get(carz[index].carName, 100, ';');
        carFile.ignore(100, ';');
        carFile >> carz[index].MPG;
        carFile.ignore(100, ';');
        carFile >> carz[index].cylinders;
        carFile.ignore(100, ';');
        carFile >> carz[index].displacememnt;
        carFile.ignore(100, ';');
        carFile >> carz[index].horsePower;
        carFile.ignore(100, ';');
        carFile >> carz[index].weight;
        carFile.ignore(100, ';');
        carFile >> carz[index].acceleration;
        carFile.ignore(100, ';');
        carFile >> carz[index].model;
        carFile.ignore(100, ';');
        carFile.get(carz[index].origin, 100, '\n');
        carFile.ignore(100, '\n');
        carz[index].validEntry = !carFile.eof();

    }

}

void printCars(cars Cars[MAX_CARS], int start, int end){


    //confirming that the index is valid and then printing it out
    for(int index = start; index < end; index++){
        if(Cars[index].validEntry == false){
            continue;
        }

        cout << Cars[index].carName << ";";
        cout << Cars[index].MPG << ";";
        cout << Cars[index].cylinders << ";";
        cout << Cars[index].displacememnt << ";";
        cout << Cars[index].horsePower << ";";
        cout << Cars[index].weight << ";";
        cout << Cars[index].acceleration << ";";
        cout << Cars[index].model << ";";
        cout << Cars[index].origin << endl;
        
    }
}


//your code
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
double readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}


void displayMenu(cars Cars[]){

    int option = -1;
    int low;
    int high;
    int originLength;
    char origin[100];

    //while loop so you can do multiple functions
    while(1){

        //displaying and finding what function they want to use
        cout << "Functions:" << endl;
        cout << "Display Car list (Enter 1)" << endl;
        cout << "Remove a Car from list (Enter 2)" << endl;
        cout << "Add a Car to the list (Enter 3)" << endl;
        cout << "Display Cars by Origin (Enter 4)" << endl;
        cout << "Quit (Enter 5)" << endl << endl;

        while(option < 1 || option > 5){
            option = readInt("");
        }

        //all of the different functions with some text and cin cout if needed
        if(option == 1){
            cout << "Enter the range of cars to be displayed:" << endl;
            low = readInt("low: ");
            high = readInt("high: ");
            printCars(Cars, low, high);
        }
        if(option == 2){

            removeCar(Cars);

        }
        if(option == 3){

            addCar(Cars);

        }
        if(option == 4){

            cout << "Enter the Origin: ";
            cin >> origin;
            originLength = readInt("How many characters are in the origin: ");
            cout << "Enter the range of cars to be displayed: " << endl;
            low = readInt("low: ");
            high = readInt("high: ");
            printOrigin(origin, originLength, low, high, Cars);

        }
        //quit
        if(option == 5){
            break;
        }
        //reseting variable
        option = -1;

    }
    
    
}