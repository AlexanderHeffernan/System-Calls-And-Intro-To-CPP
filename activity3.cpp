#include <iostream>

namespace Complex {
    class complex {
    private:
        int a, b;
    
    public:
        // Constructor with zero arguments and default values set to 1
        complex() : a(1), b(1) {}

        // Constructor with two arguments to initialize a and b
        complex(int a_val, int b_val) : a(a_val), b(b_val) {}

        // Member functions to return the values of a and b
        int geta() { return a; }
        int getb() { return b; }
    };
}

int main() {
    using namespace Complex;

    // Declare a complex number using the default constructor
    complex c1;

    // Declare a complex number using the parameterized constructor
    complex c2(5, 10);

    // Display the values of both complex numbers
    std::cout << "Complex number 1: " << c1.geta() << " + " << c1.getb() << "i\n";
    std::cout << "Complex number 2: " << c2.geta() << " + " << c2.getb() << "i\n";

    return 0;
}