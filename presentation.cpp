#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>
using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;

void printHeader() {
    cout << "======================================" << endl;
    cout << "        🌟🌟🌟 MAGICAL FRACTIONS 🌟🌟🌟        " << endl;
    cout << "======================================" << endl;
}

void printFraction(const Fraction& fraction) {
    cout << "✨ Fraction: " << static_cast<string>(fraction) << endl;
}

void printResult(const string& operation, const Fraction& result) {
    cout << "✨ " << operation << ": " << static_cast<string>(result) << endl;
}

void animateLoading() {
    cout << "🔮 Calculating... ";
    cout.flush();
    for (int i = 0; i < 5; ++i) {
        this_thread::sleep_for(chrono::milliseconds(300));
        cout << ".";
        cout.flush();
    }
    cout << " Magic Happens!" << endl;
}

int main() {
    // Create two magnificent fractions
    Fraction f1(1, 2);
    Fraction f2(3, 4);

    // Perform extraordinary arithmetic operations
    Fraction sum = f1 + f2;
    Fraction difference = f1 - f2;
    Fraction product = f1 * f2;
    Fraction quotient = f1 / f2;

    // Display the majestic results
    printHeader();
    printFraction(f1);
    printFraction(f2);
    cout << "--------------------------------------" << endl;

    animateLoading(); // Add a loading animation

    printResult("Sum", sum);
    printResult("Difference", difference);
    printResult("Product", product);
    printResult("Quotient", quotient);
    cout << "======================================" << endl;

    return 0;
}
