// C++ STL <complex> Cheat Sheet
// ================================
// This header provides the std::complex<T> class template and related functions
// to work with complex numbers in C++.

#ifndef CPP_COMPLEX_CHEATS_H
#define CPP_COMPLEX_CHEATS_H

#include <complex>
#include <iostream>
#include <cmath>

using std::complex;
using std::abs;
using std::arg;
using std::norm;
using std::conj;
using std::real;
using std::imag;
using std::polar;

// --- Type aliases for convenience ---
using cd = complex<double>;
using cf = complex<float>;
using cld = complex<long double>;

// --- Constructors ---
// complex<T> z;            // 0 + 0i
// complex<T> z(x, y);      // x + yi
// complex<T> z(x);         // x + 0i
// complex<T> z = {x, y};   // C++11 initializer-list

// --- Member functions & accessors ---
// z.real()   -> T  (real part)
// z.imag()   -> T  (imaginary part)
// z.operator=(...)
// z +=, z -=, z *=, z /= overloads

// --- Common free functions ---
// abs(z)     -> magnitude (sqrt(x^2 + y^2))
// norm(z)    -> squared magnitude (x^2 + y^2)
// arg(z)     -> phase/angle (atan2(y, x))
// conj(z)    -> complex conjugate (x - yi)
// real(z)    -> T (real part)
// imag(z)    -> T (imag part)
// polar(r, theta) -> complex number from magnitude and angle
// std::exp, std::log, std::pow, std::sin, std::cos, std::tan, ... all overloaded for complex

// --- Examples ---
// Creating and printing
// cd z1(3, 4);
// std::cout << "z1 = " << z1 << '\n';           // (3,4)

// Accessors
// double x = real(z1);       // 3
// double y = imag(z1);       // 4

// Magnitude & phase
// double r = abs(z1);        // 5
// double theta = arg(z1);    // atan2(4,3)

// Conjugate
// cd z2 = conj(z1);          // (3,-4)

// Polar form
// cd z3 = polar(5.0, theta); // (3,4)

// Arithmetic
// cd a(1,2), b(2, -1);
// cd sum = a + b;            // (3,1)
// cd prod = a * b;           // (4,3)

// Advanced complex math
// cd e = exp(z1);
// cd l = log(z1);
// cd p = pow(z1, 2);
// cd s = sin(z1);
// cd c = cos(z1);

// --- Integration with algorithms ---
// You can store complex numbers in STL containers:
// std::vector<cd> vec = {z1, z2, z3};
// std::sort(vec.begin(), vec.end(), [](const cd &a, const cd &b) {
//     return abs(a) < abs(b); // sort by magnitude
// });

#endif // CPP_COMPLEX_CHEATS_H
