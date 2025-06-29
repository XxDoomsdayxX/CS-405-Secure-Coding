// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    const std::string account_number = "CharlieBrown42";
    char user_input[20]; // 19 characters + null terminator

    std::string temp_input;
    std::cout << "Enter a value (max 19 characters): ";

    // Read the full line to ensure we capture all input
    std::getline(std::cin, temp_input);

    // Warn the user if they exceeded the buffer limit
    if (temp_input.length() > 19) {
        std::cout << "Too many characters entered! Only the first 19 will be used." << std::endl;
    }

    // Use strncpy_s which is secure and avoids Visual Studio warnings
    strncpy_s(user_input, sizeof(user_input), temp_input.c_str(), sizeof(user_input) - 1);
    user_input[19] = '\0'; // Ensure null termination

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
