#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Define constants for weight limits
const double MIN_GRAVEL_SAND_WEIGHT = 49.9;
const double MAX_GRAVEL_SAND_WEIGHT = 50.1;
const double MIN_CEMENT_WEIGHT = 24.9;
const double MAX_CEMENT_WEIGHT = 25.1;

// Define constants for sack prices
const double CEMENT_PRICE = 3.0;
const double GRAVEL_PRICE = 2.0;
const double SAND_PRICE = 2.0;
const double DISCOUNT_PRICE = 10.0;

// Define a structure to represent a sack
struct Sack {
    char content;
    double weight;
};

// Function to check a single sack
bool checkSingleSack(const Sack& sack) {
    if ((sack.content == 'C' && sack.weight >= MIN_CEMENT_WEIGHT && sack.weight <= MAX_CEMENT_WEIGHT) ||
        ((sack.content == 'G' || sack.content == 'S') && sack.weight >= MIN_GRAVEL_SAND_WEIGHT && sack.weight <= MAX_GRAVEL_SAND_WEIGHT)) {
        return true;
    }
    return false;
}

// Function to check a customer's order
void checkCustomerOrder(const vector<Sack>& order) {
    double totalWeight = 0.0;
    int rejectedSacks = 0;

    cout << "\nChecking customer's order for delivery:\n";

    for (const Sack& sack : order) {
        cout << "Sack Content: " << sack.content << ", Weight: " << sack.weight << " kg - ";

        if (checkSingleSack(sack)) {
            cout << "Accepted\n";
            totalWeight += sack.weight;
        } else {
            cout << "Rejected - Incorrect content or weight\n";
            rejectedSacks++;
        }
    }

    cout << "\nTotal weight of the order: " << totalWeight << " kg\n";
    cout << "Number of rejected sacks: " << rejectedSacks << "\n";
}

// Function to calculate the price for a customer's order
void calculateOrderPrice(const vector<Sack>& order) {
    double regularPrice = 0.0;
    int specialPackCount = 0;

    for (const Sack& sack : order) {
        if (sack.content == 'C') {
            regularPrice += CEMENT_PRICE;
        } else if (sack.content == 'G') {
            regularPrice += GRAVEL_PRICE;
        } else if (sack.content == 'S') {
            regularPrice += SAND_PRICE;
        }
    }

    // Check how many special packs are in the order
    for (size_t i = 0; i < order.size(); ++i) {
        if (i + 4 <= order.size()) {
            if (order[i].content == 'C' && order[i + 1].content == 'S' && order[i + 2].content == 'S' &&
                order[i + 3].content == 'G' && order[i + 4].content == 'G') {
                specialPackCount++;
            }
        }
    }

    cout << "\nCalculating the price for the customer's order:\n";
    cout << "Regular Price: $" << fixed << setprecision(2) << regularPrice << "\n";

    if (specialPackCount > 0) {
        double discountAmount = specialPackCount * DISCOUNT_PRICE;
        double discountedPrice = regularPrice - discountAmount;

        cout << "Special Pack Discount Applied: -$" << fixed << setprecision(2) << discountAmount << "\n";
        cout << "New Price after Discount: $" << fixed << setprecision(2) << discountedPrice << "\n";
    } else {
        cout << "No special pack discount applied.\n";
    }
}

int main() {
    // Task 1: Check the contents and weight of a single sack
      cout << "*************************************************\n";
    Sack singleSack;

    cout << "Check the contents and weight of a single sack\n";
    cout << "Enter the content of the sack (C, G, or S): ";
    cin >> singleSack.content;
    cout << "Enter the weight of the sack in kilograms: ";
    cin >> singleSack.weight;
  cout << "*************************************************\n";
    if (checkSingleSack(singleSack)) {
        cout << "Sack Accepted - Content: " << singleSack.content << ", Weight: " << singleSack.weight << " kg\n";
    } else {
        cout << "Sack Rejected - Incorrect content or weight\n";
    }
  cout << "*************************************************\n";
    // Task 2: Check a customer’s order for delivery
    vector<Sack> customerOrder;
    int numSacks;
    cout << "\nCheck a customer’s order for delivery\n";
    cout << "Enter the number of sacks in the customer's order: ";
    cin >> numSacks;

    for (int i = 0; i < numSacks; ++i) {

        Sack orderSack;

        cout << "\nEnter details for Sack " << i + 1 << ":\n";
        cout << "Enter the content of the sack (C, G, or S): ";
        cin >> orderSack.content;
        cout << "Enter the weight of the sack in kilograms: ";
        cout << "\n*************************************************\n";
        cin >> orderSack.weight;

        customerOrder.push_back(orderSack);
    }
      cout << "*************************************************\n";
    checkCustomerOrder(customerOrder);

    // Task 3: Calculate the price for a customer’s order
    cout << "\nPrice for a customer’s order\n";
    calculateOrderPrice(customerOrder);
      cout << "*************************************************\n";
    return 0;
}