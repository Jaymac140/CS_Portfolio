// Developer: James Marcano
// Date: 02/23/2025

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>  // For text alignment in output
using namespace std;

/*
 * Class: GroceryTracker
 * Purpose: Tracks the frequency of grocery items from an input file.
 *          It stores item frequencies in a map, writes them to a backup file,
 *          and provides functions to display the data.
 */
class GroceryTracker {
private:
    map<string, int> itemFrequency;  // Stores item names as keys and their count as values

    /*
     * Method: readInputFile
     * Reads each line from the input file and updates the item frequency map.
     */
    void readInputFile(const string& filename) {
        ifstream inFile(filename);  // Open file for reading
        if (!inFile.is_open()) {
            cerr << "Error: Could not open file \"" << filename << "\"." << endl;
            return;
        }

        string item;
        while (getline(inFile, item)) {  // Read each line (one item per line)
            if (!item.empty()) {
                itemFrequency[item]++;  // Increment count for the item
            }
        }
        inFile.close();  // Close file after reading
    }

    /*
     * Method: writeBackupFile
     * Saves the contents of the item frequency map into a backup file (frequency.dat).
     */
    void writeBackupFile(const string& backupFilename) {
        ofstream outFile(backupFilename);  // Open file for writing
        if (!outFile.is_open()) {
            cerr << "Error: Could not create file \"" << backupFilename << "\"." << endl;
            return;
        }

        for (const auto& pair : itemFrequency) {  // Iterate over the map and write to file
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();  // Close file after writing
    }

public:
    /*
     * Constructor: GroceryTracker
     * Reads grocery data from the input file and writes the frequencies to a backup file.
     */
    GroceryTracker(const string& inputFilename, const string& backupFilename) {
        readInputFile(inputFilename);   // Load item frequencies
        writeBackupFile(backupFilename);  // Save item frequencies to a backup file
    }

    /*
     * Method: getFrequencyOfItem
     * Returns the frequency of a specific grocery item. If not found, returns 0.
     */
    int getFrequencyOfItem(const string& item) const {
        auto it = itemFrequency.find(item);  // Look up item in the map
        if (it != itemFrequency.end()) {
            return it->second;  // Return the count of the item
        }
        return 0;  // Item not found
    }

    /*
     * Method: printAllFrequencies
     * Prints all grocery items and their corresponding purchase counts.
     */
    void printAllFrequencies() const {
        cout << "\n=== Frequency of All Items ===" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

    /*
     * Method: printHistogram
     * Displays a histogram using asterisks (*) to represent item purchase counts.
     */
    void printHistogram() const {
        cout << "\n=== Histogram of Item Frequencies ===" << endl;
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first << " ";  // Align item name
            for (int i = 0; i < pair.second; i++) {
                cout << "*";  // Print one '*' per purchase
            }
            cout << endl;
        }
    }
};

/*
 * Function: main
 * The main menu for user interaction.
 * - Allows searching for an item’s frequency.
 * - Prints all item frequencies.
 * - Displays a histogram.
 * - Provides an option to exit.
 */
int main() {
    const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";  // Input file name
    const string BACKUP_FILE = "frequency.dat";  // Backup file name

    // Create GroceryTracker object (loads data from input file automatically)
    GroceryTracker tracker(INPUT_FILE, BACKUP_FILE);

    int userChoice;
    while (true) {
        // Display main menu
        cout << "\n===================================" << endl;
        cout << "    Corner Grocer: Item Tracker   " << endl;
        cout << "===================================" << endl;
        cout << "1. Search for a specific item’s frequency" << endl;
        cout << "2. Print all item frequencies" << endl;
        cout << "3. Print histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        // Validate input (check for invalid characters)
        if (cin.fail()) {
            cin.clear();  // Clear error flag
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << "Invalid input. Please enter a number (1-4).\n";
            continue;
        }

        if (userChoice == 1) {
            // Search for a specific item's frequency
            cout << "Enter item name: ";
            string item;
            cin >> ws;
            getline(cin, item);  // Read item name (handles spaces)
            cout << item << " was purchased " << tracker.getFrequencyOfItem(item) << " time(s).\n";

        } else if (userChoice == 2) {
            // Print all item frequencies
            tracker.printAllFrequencies();

        } else if (userChoice == 3) {
            // Print histogram
            tracker.printHistogram();

        } else if (userChoice == 4) {
            // Exit program
            cout << "Exiting program. Goodbye!" << endl;
            break;

        } else {
            // Handle invalid choices
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;  // End program
}