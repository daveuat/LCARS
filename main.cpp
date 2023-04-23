#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Using the standard namespace to make things easier.
using namespace std;

// Class and program is named LCARS, Library Computer Access and Retrieval System (LCARS for short), after the computer from Star Trek The Next Generation
class LCARS {
public:
    // Constructor for taking a filename
    LCARS(const string& filename) : filename(filename) {
        createFile(); // Creates the file for the object is constructed
    }

    // function called 'store' for storing data to the file
    void store(const string& content, const string& rank) {
        ofstream file(filename, ios::app); // this creates an ofstream object and appends data in the file

        if (file.is_open()) { // check to see if the file is open
            file << content << endl; // write the user inputted data to the file
            file.close(); // closes file
            cout << "Thank you " << rank << ", data is now stored in my memory banks." << endl; // print confirmation message to user
        }
    }

    // Function for finding stored data based off a keyword or word
    void find(const string& keyword, const string& rank) {
        ifstream file(filename); // Create an ifstream object to read the file
        string line; // Declare a string variable to store each line read from the file
        bool found = false;

        if (file.is_open()) { // Check if the file is open
            while (getline(file, line)) { // Read each line from the file
                if (line.find(keyword) != string::npos) { // Check if the keyword is found in the current line
                    cout << rank << ", I have retrieved the following data: " << line << endl; // Print what was found to the screen
                    found = true;
                    break;
                }
            }
            file.close(); // Close the file
        }

        if (!found) {
            cout << rank << ", I am unable to locate the requested information. " << keyword << ", does not exist in my memory banks." << endl; // display message if request isn't found
        }
    }

    // function to find all data stored by the user
    void findAll(const string& rank) {
        ifstream file(filename); // Create a needed ifstream object for reading the file
        string line; // This declares a string variable to store each line that is read from the file

        cout << rank << ", ship memory banks contain the following data: " << endl; // This prints the a message for the found data
        if (file.is_open()) { // This checks if the file is open or not
            while (getline(file, line)) { // This will read each line from the data file
                cout << line << endl; // This prints every entry in the list to the screen
            }
            file.close(); // Closes the file when done.
        }
    }

private:
    string filename; // Declaring string variable to store the filename for all data

    // A function to create the file for stored data
    void createFile() {
        ifstream file_test(filename);
        if (!file_test.good()) { // Needed to add this because it kept overwriting the file. This checks to see if it already exists.
            ofstream file(filename);
            file.close(); // Now closes the file
        }
    }

    // Append data to the file function
    void appendToFile(const string& content) {
        ofstream file(filename, ios::app);

        if (file.is_open()) { // This checks if the file is open or not
            file << content << endl; // This writes the data to the file
            file.close(); // Now closes the file
        }
    }
};

int main() {
    LCARS lcars("lcars_data.txt"); // Data file name for stored data based off the star trek computer LCARS for short

    string input;
    string rank;
    string keyword;

    cout << "Welcome to ";
    // Prints welcome message to the screen, used https://patorjk.com/ ASCII Art Generator
    cout << R"(
  _      _____          _____   _____ 
 | |    / ____|   /\   |  __ \ / ____|
 | |   | |       /  \  | |__) | (___  
 | |   | |      / /\ \ |  _  / \___ \ 
 | |___| |____ / ____ \| | \ \ ____) |
 |______\_____/_/    \_\_|  \_\_____/ 
)" << '\n';
    cout << "Please verify if you are Commander or Higher rank of the Enterprise crew and login. " << '\n';
    cout << "Please enter your rank (Captain or Commander): ";
    getline(cin, rank);

    if (rank != "Captain" && rank != "Commander") {
        cout << "That rank is invalid. Contacting the Chief of Security. Please remain here. " << endl;
        return 0;
    }

    bool running = true;
    while (running) {
        cout << rank << ", specify a command when ready. (store/find/find_all/exit): ";
        getline(cin, input);

        if (input == "store") {
            cout << "Please enter the data you want to store: ";
            getline(cin, input);
            lcars.store(input, rank);
        }
        else if (input == "find") {
            cout << "Please enter the keyword you want to find: ";
            getline(cin, keyword);
            lcars.find(keyword, rank);
        }
        else if (input == "find_all") {
            lcars.findAll(rank);
        }
        else if (input == "exit") {
            running = false;
        }
        else {
            cout << "That is an Invalid command " << rank << ". Please try again. " << endl;
        }
    }

    return 0;
}