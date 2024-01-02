#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define some constants for the cost and time of hiring a boat
const double HOUR_COST = 20.0;      // Cost of hiring a boat for one hour in dollars
const double HALF_HOUR_COST = 12.0; // Cost of hiring a boat for half an hour in dollars
const int START_TIME = 10;           // Start time of hiring a boat in hours
const int END_TIME = 17;             // End time of hiring a boat in hours

// Define a class for a Boat
class Boat {
public:
    int number;        // The number of the boat
    double money;      // The money taken by the boat in a day in dollars
    double hours;      // The total hours hired by the boat in a day
    int return_time;   // The time when the boat must be returned in hours

    // Constructor to initialize a boat
    Boat(int boatNumber) : number(boatNumber), money(0.0), hours(0.0), return_time(0) {}

    // Function to calculate the money taken in a day for one boat
    void calculateMoneyForOneBoat() {
        cout << "\nBoat " << number << ":\n";
        double duration;
        double cost;
        int hireTime;

        cout << "Enter the duration of hiring (0.5 or 1) hour(s): ";
        cin >> duration;

        if (duration == 0.5 || duration == 1) {
            if (duration == 0.5) {
                cost = HALF_HOUR_COST;
            } else {
                cost = HOUR_COST;
            }

            cout << "Enter the time when the boat is hired (between 10 and 16): ";
            cin >> hireTime;

            if (hireTime >= START_TIME && hireTime < END_TIME) {
                money += cost;
                hours += duration;
                return_time = hireTime + duration;

                if (return_time <= END_TIME) {
                    cout << "Hired for " << duration << " hours starting at " << hireTime << ":00.\n";
                    cout << "Must be returned at " << return_time << ":00.\n";
                    cout << "Total cost: $" << cost << ".\n";
                } else {
                    cout << "Cannot be hired. Must be returned before 17:00.\n";
                }
            } else {
                cout << "Cannot be hired before 10:00 or after 16:00.\n";
            }
        } else {
            cout << "Invalid duration. Please enter 0.5 or 1.\n";
        }
    }

    // Function to display boat information
    void displayBoatInfo() {
        cout << "Boat " << number << ": $" << money << " (Total hours: " << hours << ")\n";
    }
};

// Define a function to find the next boat available
int findNextBoatAvailable(const vector<Boat>& boats, int currentTime) {
    int index = -1;
    int available = 0;
    int earliest = END_TIME + 1;

    for (int i = 0; i < boats.size(); i++) {
        if (boats[i].return_time <= currentTime) {
            available++;

            if (index == -1) {
                index = i;
            }
        } else {
            if (boats[i].return_time < earliest) {
                earliest = boats[i].return_time;
            }
        }
    }

    cout << "Total available boats: " << available << "\n";

    if (available == 0) {
        cout << "The earliest time a boat will be available is " << earliest << ":00.\n";
    }

    return index;
}

// Define a function to calculate the money taken for all the boats at the end of the day
void calculateMoneyForAllBoats(const vector<Boat>& boats) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int unusedBoats = 0;
    int mostUsedBoat = 0;

    for (int i = 0; i < boats.size(); i++) {
        totalMoney += boats[i].money;
        totalHours += boats[i].hours;

        if (boats[i].hours == 0) {
            unusedBoats++;
        }

        if (boats[i].hours > boats[mostUsedBoat].hours) {
            mostUsedBoat = i;
        }
    }

    cout << "\nReport for the owner:\n";
    cout << "Total money taken: $" << totalMoney << "\n";
    cout << "Total hours hired: " << totalHours << "\n";
    cout << "Unused boats: " << unusedBoats << "\n";
    cout << "Most used boat: Boat " << boats[mostUsedBoat].number << " with " << boats[mostUsedBoat].hours << " hours.\n";
}

int main() {
    vector<Boat> boats; // Initialize a vector to store boats

    cout << "Welcome to the Boat Hiring System!\n";

    // Create and add 10 boats to the vector
    for (int i = 0; i < 10; i++) {
        boats.push_back(Boat(i + 1));
    }

    int userChoice;
    int currentTime;

    do {
        // Display menu
        cout << "\nMenu:\n";
        cout << "1. Hire a Boat\n";
        cout << "2. Check End-of-Day Report\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                // Display available boats
                cout << "\nAvailable Boats:\n";
                for (int i = 0; i < boats.size(); i++) {
                    if (boats[i].return_time <= currentTime || boats[i].return_time == 0) {
                        cout << "Boat " << boats[i].number << "\n";
                    }
                }

                // Prompt user for boat choice
                cout << "Enter the number of the boat you want to hire (or enter -1 to go back to the menu): ";
                cin >> userChoice;

                if (userChoice >= 1 && userChoice <= boats.size()) {
                    // Prompt user for current time
                    cout << "Enter the current time (between 10 and 16): ";
                    cin >> currentTime;

                    // Calculate money for the chosen boat
                    boats[userChoice - 1].calculateMoneyForOneBoat();

                    // Display updated boat information
                    boats[userChoice - 1].displayBoatInfo();
                } else if (userChoice != -1) {
                    cout << "Invalid boat choice. Please choose a valid boat number.\n";
                }
                break;

            case 2:
                // Check end-of-day report
                cout << "\nTask 3: Calculate the money taken for all the boats at the end of the day\n";
                calculateMoneyForAllBoats(boats);
                break;

            case 3:
                // Exit
                cout << "\nThank you for using the Boat Hiring System!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

    } while (userChoice != 3);

    return 0;
}