// Project: Touch 'n Go RFID Assistant - LDCW6123
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function to display header
void displayHeader() {
    cout << "====================================================\n";
    cout << "       TOUCH 'N GO RFID TOLL ASSISTANT SYSTEM       \n";
    cout << "====================================================\n";
}

int main() {
    int vehicleClass;
    int entryPlaza, exitPlaza;
    double currentBalance, fare = 0.0;
    char confirmPayment;

    displayHeader();

    // Step 1: Input eWallet Balance
    cout << "Enter current TnG eWallet Balance (RM): ";
    cin >> currentBalance;

    if (currentBalance < 0) {
        cout << "Invalid balance entry. Exiting program.\n";
        return 1;
    }

    // Step 2: Input Vehicle Class
    cout << "\nSelect Vehicle Class:\n";
    cout << "1. Class 1 (Motorcars, Vans, Taxis)\n";
    cout << "2. Class 2 (2-Axle Lorries & Buses)\n";
    cout << "3. Class 3 (3+ Axle Heavy Trucks)\n";
    cout << "Enter choice (1-3): ";
    cin >> vehicleClass;

    // Step 3: Input Entry and Exit Plazas
    cout << "\nSelect Entry Highway Plaza:\n";
    cout << "1. Sungai Besi\n";
    cout << "2. Kajang\n";
    cout << "3. Seremban\n";
    cout << "Enter choice (1-3): ";
    cin >> entryPlaza;

    cout << "\nSelect Exit Highway Plaza:\n";
    cout << "1. Sungai Besi\n";
    cout << "2. Kajang\n";
    cout << "3. Seremban\n";
    cout << "Enter choice (1-3): ";
    cin >> exitPlaza;

    if (entryPlaza == exitPlaza) {
        cout << "\nError: Entry and Exit plazas cannot be the same for RFID passage.\n";
        return 1;
    }

    // Step 4: Logic to calculate fare using switch/if statements
    if ((entryPlaza == 1 && exitPlaza == 2) || (entryPlaza == 2 && exitPlaza == 1)) {
        fare = 2.40; // Sg Besi <-> Kajang
    } else if ((entryPlaza == 2 && exitPlaza == 3) || (entryPlaza == 3 && exitPlaza == 2)) {
        fare = 4.10; // Kajang <-> Seremban
    } else if ((entryPlaza == 1 && exitPlaza == 3) || (entryPlaza == 3 && exitPlaza == 1)) {
        fare = 6.50; // Sg Besi <-> Seremban
    } else {
        cout << "Invalid plaza selection.\n";
        return 1;
    }

    // Adjust fare multiplier by vehicle class
    if (vehicleClass == 2) {
        fare *= 1.5;
    } else if (vehicleClass == 3) {
        fare *= 2.0;
    }

    // Display Summary
    cout << fixed << setprecision(2);
    cout << "\n----------------------------------------------------\n";
    cout << "                  TRIP SUMMARY                      \n";
    cout << "----------------------------------------------------\n";
    cout << "Toll Fare Calculated : RM " << fare << endl;
    cout << "Current eWallet      : RM " << currentBalance << endl;

    // Step 5: Check eWallet sufficiency and auto-reload logic
    if (currentBalance >= fare) {
        double newBalance = currentBalance - fare;
        cout << "\nRFID Scan Status     : SUCCESS (Boom Gate Opening)\n";
        cout << "Deducted Amount      : RM " << fare << endl;
        cout << "Remaining Balance    : RM " << newBalance << endl;

        if (newBalance < 10.00) {
            cout << "\n[WARNING] Low Balance Alert! Consider Auto-Reloading via eWallet App.\n";
        }
    } else {
        double shortage = fare - currentBalance;
        cout << "\nRFID Scan Status     : REJECTED (Insufficient Funds)\n";
        cout << "Shortage Amount      : RM " << shortage << endl;
        cout << "[ACTION REQUIRED] Please reload at least RM " << shortage << " to proceed through RFID lane.\n";
    }

    cout << "====================================================\n";
    return 0;
}
// End of tng_rfid_system.cpp
