#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm> // For std::transform

using namespace std;

// Constants for the alphabet and reflector definitions
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Rotor configurations for the Enigma I machine
const map<string, pair<string, char>> ROTORS = {
    {"I", {"EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q'}},  // Rotor I wiring and notch
    {"II", {"AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E'}}, // Rotor II wiring and notch
    {"III", {"BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V'}}, // Rotor III wiring and notch
    {"IV", {"ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J'}}, // Rotor IV wiring and notch
    {"V", {"VZBRGITYUPSDNHLXAWMJQOFECK", 'Z'}}   // Rotor V wiring and notch
};

// Reflector configurations for the Enigma I machine
const map<char, string> REFLECTORS = {
    {'B', "YRUHQSLDPXNGOKIIZWFMTVEA"}, // Reflector B wiring
    {'C', "FVPJIAOYEDRZXWGCTKUQNMHS"}  // Reflector C wiring
};

// Class representing a single rotor
class Rotor {
public:
    Rotor(const string& wiring, char notch, char ring_setting, int position)
        : wiring(wiring), notch(notch), ring_setting(ring_setting), position(position) {}

    // Encrypt a letter using the rotor
    char encrypt(char letter) {
        // Placeholder for rotor encryption logic
        return letter; // This should be replaced with actual encryption logic
    }

private:
    string wiring;  // Wiring of the rotor
    char notch;     // Notch position of the rotor
    char ring_setting; // Ring setting for the rotor
    int position;   // Current position of the rotor
};

// Class representing the plugboard
class Plugboard {
public:
    Plugboard(const map<char, char>& connections) : connections(connections) {}

    // Encrypt a letter using the plugboard
    char encrypt(char letter) {
        return connections.count(letter) ? connections.at(letter) : letter;
    }

private:
    map<char, char> connections; // Connections for the plugboard
};

// Class representing the reflector
class Reflector {
public:
    Reflector(const string& wiring) : wiring(wiring) {}

    // Encrypt a letter using the reflector
    char reflect(char letter) {
        return wiring[letter - 'A']; // Assuming 'A' is 0, 'B' is 1, etc.
    }

private:
    string wiring; // Wiring for the reflector
};

// Class representing the Enigma machine
class EnigmaMachine {
public:
    EnigmaMachine(const vector<Rotor>& rotors, const Reflector& reflector, const Plugboard& plugboard)
        : rotors(rotors), reflector(reflector), plugboard(plugboard) {}

    // Encrypt a message
    string encrypt_message(const string& message) {
        string encrypted_message;
        for (char letter : message) {
            if (isalpha(letter)) {
                letter = toupper(letter); // Ensure the letter is uppercase
                letter = plugboard.encrypt(letter); // First, pass through the plugboard
                // Pass through the rotors and reflector (not implemented here)
                letter = reflector.reflect(letter); // Then, pass through the reflector
                encrypted_message += letter; // Add encrypted letter to the message
            } else {
                encrypted_message += letter; // Non-alphabetic characters remain unchanged
            }
        }
        return encrypted_message; // Return the final encrypted message
    }

private:
    vector<Rotor> rotors; // Rotors in the machine
    Reflector reflector;   // Reflector in the machine
    Plugboard plugboard;   // Plugboard in the machine
};

// Function to configure the plugboard based on user input
Plugboard configure_plugboard() {
    map<char, char> connections; // Initialize a map for the plugboard connections
    set<char> available_letters(ALPHABET.begin(), ALPHABET.end()); // Set of available letters for connections

    while (available_letters.size() > 1) { // Continue until no letters are left to connect
        cout << "Available letters: ";
        for (char letter : available_letters) {
            cout << letter << " "; // Display available letters
        }
        cout << endl;

        string pair; // Initialize a string to hold the user input for a connection pair
        cout << "Enter a pair of letters to connect (or 'done' to finish): ";
        cin >> pair; // Read user input

        // Convert input to uppercase for uniformity
        std::transform(pair.begin(), pair.end(), pair.begin(), ::toupper);

        if (pair == "DONE") { // Exit if the user indicates they are done
            break; // Exit the loop
        } else if (pair.size() == 2 && available_letters.count(pair[0]) && available_letters.count(pair[1])) {
            connections[pair[0]] = pair[1]; // Add connection from first letter to second
            connections[pair[1]] = pair[0]; // Add connection from second letter to first (bidirectional)
            available_letters.erase(pair[0]); // Remove used letters from available letters
            available_letters.erase(pair[1]); // Remove used letters from available letters
        } else {
            cout << "Invalid input. Please enter two different letters from the available letters." << endl; // Error message for invalid input
        }
    }

    return Plugboard(connections); // Return the configured plugboard
}

// Function to select rotors from the available options
vector<Rotor> select_rotors() {
    vector<Rotor> selected_rotors; // Vector to hold selected rotors
    set<string> available_rotors = {"I", "II", "III", "IV", "V"}; // Set of available rotors

    while (selected_rotors.size() < 3) { // Require exactly three rotors
        cout << "Available rotors: ";
        for (const string& rotor : available_rotors) {
            cout << rotor << " "; // Display available rotors
        }
        cout << endl;

        string rotor_choice; // Initialize a string to hold the user's rotor choice
        cout << "Select rotor (I, II, III, IV, V): ";
        cin >> rotor_choice; // Read user input

        std::transform(rotor_choice.begin(), rotor_choice.end(), rotor_choice.begin(), ::toupper); // Convert to uppercase

        if (available_rotors.count(rotor_choice)) { // If the rotor choice is valid
            // Prompt for initial position (1-26)
            int position;
            cout << "Enter initial position (1-26) for rotor " << rotor_choice << ": ";
            cin >> position;
            while (position < 1 || position > 26) { // Validate position input
                cout << "Invalid position. Please enter a number between 1 and 26: ";
                cin >> position;
            }

            // Prompt for ring setting
            char ring_setting;
            cout << "Enter ring setting (A-Z) for rotor " << rotor_choice << ": ";
            cin >> ring_setting;
            ring_setting = toupper(ring_setting); // Convert to uppercase
            while (ring_setting < 'A' || ring_setting > 'Z') { // Validate ring setting input
                cout << "Invalid ring setting. Please enter a letter between A and Z: ";
                cin >> ring_setting;
                ring_setting = toupper(ring_setting);
            }

            selected_rotors.emplace_back(ROTORS.at(rotor_choice).first, ROTORS.at(rotor_choice).second, ring_setting, position); // Add selected rotor
            available_rotors.erase(rotor_choice); // Remove selected rotor from available options
        } else {
            cout << "Invalid rotor selection. Please choose from the available options." << endl; // Error message for invalid selection
        }
    }

    return selected_rotors; // Return the selected rotors
}

int main() {
    cout << "Welcome to the Enigma Machine!" << endl;

    // Configure plugboard
    Plugboard plugboard = configure_plugboard();

    // Select rotors
    vector<Rotor> rotors = select_rotors();

    // Select reflector
    char reflector_choice;
    cout << "Select reflector (B or C): ";
    cin >> reflector_choice;
    reflector_choice = toupper(reflector_choice); // Convert to uppercase
    while (reflector_choice != 'B' && reflector_choice != 'C') { // Validate reflector input
        cout << "Invalid reflector choice. Please choose B or C: ";
        cin >> reflector_choice;
        reflector_choice = toupper(reflector_choice);
    }

    Reflector reflector(REFLECTORS.at(reflector_choice)); // Create reflector

    // Create Enigma machine
    EnigmaMachine enigma(rotors, reflector, plugboard);

    // Example encryption
    string message;
    cout << "Enter message to encrypt: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, message); // Read the entire line as a message

    string encrypted_message = enigma.encrypt_message(message); // Encrypt the message
    cout << "Encrypted message: " << encrypted_message << endl;

    return 0;
}
