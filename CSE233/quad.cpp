
#include <iostream>
#include <cmath>
#include <cassert>

bool isQuadratic(double a);
// you need to implement the following functions
bool isLinear(double b);
double calcLinearRoot(double b, double c);
double calcDiscriminant(double a, double b, double c);
double calcSingleRoot(double a, double b);
double calcPlusRoot(double a, double b, double c);
double calcMinusRoot(double a, double b, double c);

// test fuctions
// you need to implement these
void test_isQuadratic();
void test_isLinear();
void test_calcLinearRoot();
void test_calcDiscriminant();
void test_calcSingleRoot();
void test_calcPlusRoot();
void test_calcMinusRoot();

// helper function
bool areDoublesEqual(double testValue, double referenceValue);

int main() {
    std::cout << "Beginning unit tests...\n";
    test_isQuadratic();
    test_isLinear();
    test_calcLinearRoot();
    test_calcDiscriminant();
    test_calcSingleRoot();
    test_calcPlusRoot();
    test_calcMinusRoot();
    std::cout << "All unit tests passed.\n";

    double a, b, c, x1, x2;
    std::cout << "Enter values for a, b, and c\n";
    std::cin >> a >> b >> c;
    if (isQuadratic(a) == false) {
        std::cout << "a is 0. this is not quadratic\n";
        if (isLinear(b) == false) {
            std::cout << "b is 0. this is not a valid equation\n";
            return 0;
        }
        else {
            std::cout << "b is 0. this equation is linear.\n";
            x1 = calcLinearRoot(b, c);
            std::cout << "there is one root. x = " << x1 << "\n";
            return 0;
        }
    }
    else {
        std::cout << "a is not 0. this is quadratic\n";
        double d = calcDiscriminant(a, b, c);
        if (d > 0) {
            std::cout << "d is positive. we have 2 roots\n";
            x1 = calcPlusRoot(a, b, c);
            x2 = calcMinusRoot(a, b, c);
            std::cout << "x1 = " << x1 << "\n";
            std::cout << "x2 = " << x2 << "\n";
        }
        else if (d == 0) {
            std::cout << "d is 0. we have 1 root\n";
            x1 = calcSingleRoot(a, b);
            std::cout << "x = " << x1 << "\n";
        }
        else {
            std::cout << "d is negative. we have 0 roots\n";
        }
    }
    return 0;
}

bool areDoublesEqual(double testValue, double referenceValue) {
    return std::fabs(testValue - referenceValue) < 0.0001;
}

bool isQuadratic(double a) {
    if (a == 0) return false;
    else return true;
}

void test_isQuadratic() {
    assert(isQuadratic(0) == false);
    assert(isQuadratic(0) == false);
    assert(isQuadratic(2) == true);
    assert(isQuadratic(63) == true);
    assert(isQuadratic(-2343) == true);
    assert(isQuadratic(0.0000000000000000001) == true);
}
