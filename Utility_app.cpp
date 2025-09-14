#include <iostream>   // for input/output
#include <iomanip>    // for formatting numbers (e.g., setw, setfill)
#include <vector>     // for using dynamic arrays (vector)
#include <string>     // for using string type
#include <sstream>    // for string formatting (toMoney)
using namespace std;

struct Item {
    string code;   // Code used to identify the item (e.g., A1, B2)
    string name;   // Name of the product (e.g., Coca-Cola)
    int price;     // Price in cents (to avoid floating-point errors)
    int stock;     // Number of items available in stock
};

class VendingMachine {
    vector<Item> items;  // List of items in the vending machine

    // Helper function to convert cents into a formatted money string
    string toMoney(int cents) {
        ostringstream ss;  // Create a string stream for formatting
        ss << "£" << cents/100 << "."       // Pounds (integer part)
           << setw(2) << setfill('0')       // Always 2 digits after decimal
           << (cents % 100);                // Cents (remainder)
        return ss.str();  // Return formatted money string
    }

public:
    // Constructor: initialize vending machine with some default items
    VendingMachine() {
        items = {
            {"A1", "Coca-Cola", 125, 5},
            {"A2", "Water", 100, 5},
            {"B1", "Coffee", 150, 3},
            {"B2", "Hot Chocolate", 170, 2},
            {"C1", "Chocolate Bar", 85, 4},
            {"C2", "Crisps", 95, 4}
        };
    }

    // Function to display the vending machine menu
    void showMenu() {
        cout << "\n--- Vending Machine Menu ---\n";
        for (auto &it : items)  // Loop through all items
            cout << it.code << " | " << setw(15) << left << it.name
                 << " | " << toMoney(it.price)
                 << " | Stock: " << it.stock << "\n";
    }

    // Function to find an item by its code
    Item* findItem(string code) {
        for (auto &it : items) {
            if (it.code == code) return &it;  // Return pointer if match found
        }
        return nullptr;  // Return nullptr if not found
    }

    // Function to handle purchasing an item
    void buyItem(Item &it) {
        // Check if the item is out of stock
        if (it.stock <= 0) {
            cout << "Sorry, " << it.name << " is out of stock.\n";
            return;
        }

        int inserted = 0;  // Track amount of money inserted (in cents)
        cout << "Price of " << it.name << ": " << toMoney(it.price) << "\n";

        // Keep asking for money until enough is inserted
        while (inserted < it.price) {
            cout << "Insert money (e.g., 1.00) or type 0 to cancel: ";
            double val; 
            cin >> val;

            // If user enters 0, cancel transaction
            if (val == 0) {
                cout << "Transaction cancelled. Returning " << toMoney(inserted) << "\n";
                return;
            }

            // Convert entered value into cents and add to total
            inserted += int(val * 100 + 0.5);
            cout << "Total inserted: " << toMoney(inserted) << "\n";
        }

        // Reduce stock since item is purchased
        it.stock--;

        // Dispense the item
        cout << "Dispensing " << it.name << " ... Enjoy!\n";

      
        cout << "Change returned: " << toMoney(inserted - it.price) << "\n";   // Return change if any
    }

    // Main loop of the vending machine
    void run() {
        while (true) {
            // Show the menu
            showMenu();

            // Ask user for input
            cout << "\nEnter item code (or Q to quit): ";
            string code; 
            cin >> code;

            // Quit if user enters Q
            if (code == "Q" || code == "q") break;

            // Try to find the item
            Item* choice = findItem(code);

            // If invalid code, show error
            if (!choice) {
                cout << "Invalid code.\n";
            } else {
                // Process buying the item
                buyItem(*choice);

                // After purchase, ask if user wants another product
                cout << "Would you like another product to buy? (Y/N): ";
                char again; 
                cin >> again;

                // If user enters N, break loop
                if (again == 'N' || again == 'n') break;
            }
        }

        // Exit message
        cout << "Thank you. Goodbye!\n";
    }
};

// Main function: entry point of the program
int main() {
    VendingMachine vm;  // Create a vending machine object
    vm.run();           // Run the machine
    return 0;           // End program
}

