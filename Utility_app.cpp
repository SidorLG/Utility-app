// vending_machine.cpp
// Simplified Vending Machine in C++

// Include input/output library for console interaction
#include <iostream>
// Include iomanip for output formatting (e.g., setw, setfill)
#include <iomanip>
// Include vector for storing list of items
#include <vector>
// Include string for handling text
#include <string>
using namespace std; // Avoids writing std:: repeatedly

// Define a structure to represent an item in the vending machine
struct Item {
    string code, name; // Unique code and item name
    int price;         // Item price in cents
    int stock;         // Number of items available
};

// VendingMachine class definition
class VendingMachine {
    vector<Item> items; // Vector to hold all vending machine items

    // Convert price in cents into a money string (e.g., £1.25)
    string toMoney(int cents) {
        ostringstream ss; // String stream for formatting
        ss << "£" << cents/100               // Convert cents to pounds
           << "." << setw(2) << setfill('0') // Always show 2 decimal places
           << (cents%100);                   // Remainder as pence
        return ss.str(); // Return formatted string
    }

public:
    // Constructor: initializes vending machine with default items
    VendingMachine() {
        items = {
            {"A1", "Coca-Cola", 125, 5},       // Code A1, £1.25, stock 5
            {"A2", "Water", 100, 5},           // Code A2, £1.00, stock 5
            {"B1", "Coffee", 150, 3},          // Code B1, £1.50, stock 3
            {"B2", "Hot Chocolate", 170, 2},   // Code B2, £1.70, stock 2
            {"C1", "Chocolate Bar", 85, 4},    // Code C1, £0.85, stock 4
            {"C2", "Crisps", 95, 4}            // Code C2, £0.95, stock 4
        };
    }

    // Display the vending machine menu
    void showMenu() {
        cout << "\n--- Vending Machine Menu ---\n";
        for (auto &it : items) // Loop through all items
            cout << it.code << " | " << setw(15) << left << it.name // Code and name
                 << " | " << toMoney(it.price)                      // Price formatted
                 << " | Stock: " << it.stock << "\n";               // Stock left
    }

    // Find an item by its code, return pointer if found, else nullptr
    Item* findItem(string code) {
        for (auto &it : items) // Loop through items
            if (it.code == code) return &it; // Match found
        return nullptr; // No match found
    }

    // Handle buying an item
    void buyItem(Item &it) {
        if (it.stock <= 0) { // Check if item is out of stock
            cout << "Sorry, " << it.name << " is out of stock.\n";
            return; // Exit function
        }
        int inserted = 0; // Track money inserted (in cents)
        cout << "Price of " << it.name << ": " << toMoney(it.price) << "\n";
        
        // Keep asking for money until enough is inserted
        while (inserted < it.price) {
            cout << "Insert money (e.g., 1.00) or type 0 to cancel: ";
            double val; cin >> val; // Read money inserted
            if (val == 0) { // Cancel transaction
                cout << "Transaction cancelled. Returning " << toMoney(inserted) << "\n";
                return;
            }
            inserted += int(val*100 + 0.5); // Convert pounds to cents, rounding
            cout << "Total inserted: " << toMoney(inserted) << "\n";
        }
        
        // Item purchased successfully
        it.stock--; // Reduce stock by 1
        cout << "Dispensing " << it.name << " ... Enjoy!\n";
        cout << "Change returned: " << toMoney(inserted - it.price) << "\n"; // Return change
    }

    // Main loop for running the vending machine
    void run() {
        while (true) { // Infinite loop until quit
            showMenu(); // Show available items
            cout << "\nEnter item code (or Q to quit): ";
            string code; cin >> code; // Get user input
            if (code == "Q" || code == "q") break; // Quit program if user enters Q
            Item* choice = findItem(code); // Try to find item by code
            if (!choice) cout << "Invalid code.\n"; // If not found
            else buyItem(*choice); // Otherwise, process purchase
        }
        cout << "Thank you. Goodbye!\n"; // End message
    }
};

// Main program entry point
int main() {
    VendingMachine vm; // Create a vending machine object
    vm.run();          // Run the vending machine
    return 0;          // Exit program
}

