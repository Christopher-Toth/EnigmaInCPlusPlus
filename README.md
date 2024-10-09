# Enigma Machine Simulation

## Overview

This project simulates the Enigma machine, an encryption device used during World War II, written in C++. The program allows users to configure various settings, including the plugboard, rotors, and reflectors, to encrypt messages.

## Features

- **Plugboard Configuration**: Connect letters to enhance encryption complexity.
- **Rotor Selection**: Choose from five rotors (I, II, III, IV, V) with customizable initial positions (1-26) and ring settings (A-Z).
- **Reflector Options**: Select between two reflectors (B and C) to alter the encryption pattern.
- **Message Encryption**: Input plaintext messages and receive the encrypted output.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++)
- CMake (optional, for building with CMake)

### Installation

1. Clone the repository:
   ```
   git clone https://github.com/Christopher-Toth/enigma-machine.git
   cd enigma-machine
   ```
   
2. Compile the program:
   ```
   g++ enigma.cpp -o enigma
   ```
   
3. Run the simulation:
   ```
   ./enigma
   ```

## Usage

1. Configure the Plugboard: Enter pairs of letters to connect. Type "DONE" when finished.
2. Select Rotors: Choose the desired rotors, initial positions, and ring settings.
3. Select Reflector: Choose either reflector B or C.
4. Encrypt a Message: Input the message you wish to encrypt.

## Example
```
Welcome to the Enigma Machine!
Available letters: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
Enter a pair of letters to connect (or 'done' to finish): AB
...
Select reflector (B or C): B
Enter message to encrypt: HELLO
Encrypted message: XYZAB
```

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests for enhancements or bug fixes.

## License
This project is licensed under the MIT License.
