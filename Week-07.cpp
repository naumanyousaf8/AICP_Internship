#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Charity {
    string name;
    double total;
};

void displayCharities(const vector<Charity>& charities) {
    cout << setw(25) << "Charity Number" << setw(25) << "Charity Name\n";
    for (size_t i = 0; i < charities.size(); ++i) {
        cout << setw(25) << i + 1 << setw(25) << charities[i].name << "\n";
    }
}

void displayTotals(const vector<Charity>& charities) {
    cout << "\nCharity Totals (Descending Order):\n";
    cout << setw(25) << "Charity Name" << setw(25) << "Total Donated\n";
    vector<Charity> sortedCharities = charities;
    sort(sortedCharities.begin(), sortedCharities.end(),
              [](const Charity& a, const Charity& b) { return a.total > b.total; });

    for (const auto& charity : sortedCharities) {
        cout << setw(25) << charity.name << setw(25) << "$" << charity.total << "\n";
    }
}

int main() {
    vector<Charity> charities = {{"Charity 1", 0.0}, {"Charity 2", 0.0}, {"Charity 3", 0.0}};
    double shoppingBill, donation;
    int choice;
    double grandTotal = 0.0;

    cout << "Welcome to the Charity Donation System!\n\n";

    for (auto& charity : charities) {
        cout << "Enter the name of " << charity.name << ": ";
        getline(cin, charity.name);
    }

    while (true) {
        cout << "\n";
        displayCharities(charities);

        cout << "\nEnter your choice (1, 2, 3) or -1 to show totals: ";
        cin >> choice;

        if (choice == -1) {
            cout << "\n";
            displayTotals(charities);

            grandTotal = charities[0].total + charities[1].total + charities[2].total;
            double donationFromTotal = 0.01 * grandTotal;

            cout << "\nGRAND TOTAL DONATED TO CHARITIES: $" << grandTotal << "\n";
            cout << "Your donation also contributes to the grand total. From the total amount, $"
                      << donationFromTotal << " will be donated to all charities collectively.\n";

            break;
        }

        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please choose 1, 2, 3, or -1 to show totals.\n";
            continue;
        }

        cout << "Enter your shopping bill amount: $";
        cin >> shoppingBill;

        donation = 0.01 * shoppingBill;

        charities[choice - 1].total += donation;

        cout << "\nThank you for your donation of $" << donation << " to " << charities[choice - 1].name << ".\n";
    }

    return 0;
}
