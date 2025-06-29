// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>

// Custom exception class derived from std::exception
class MyCustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "MyCustomException occurred!";
    }
};

// Function that throws a standard exception
bool do_even_more_custom_application_logic(){

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // Throwing a standard exception
    throw std::runtime_error("Standard runtime_error thrown!");

    return true; // This will not be reached
}
void do_custom_application_logic(){

    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Caught a std::exception in custom logic: " << e.what() << std::endl;
    }

    // Throwing a custom exception
    throw MyCustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl; // This will not be reached
}

float divide(float num, float den){

    if (den == 0.0f) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    return (num / den);
}

void do_division() noexcept{

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Division Error: " << e.what() << std::endl;
    }
}

int main(){

    std::cout << "Exceptions Tests!" << std::endl;

    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const MyCustomException& e) {
        std::cerr << "Caught MyCustomException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught an unknown exception!" << std::endl;
    }

    std::cout << "Program finished gracefully." << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu