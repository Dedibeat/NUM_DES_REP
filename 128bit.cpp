#include <iostream>

void printInt128(__int128 x) {
    if (x == 0) {
        std::cout << "0";
        return;
    }

    std::string s;
    bool neg = (x < 0);
    if (neg) x = -x;

    while (x) {
        s += '0' + (x % 10);
        x /= 10;
    }

    if (neg) s += '-';
    std::reverse(s.begin(), s.end());
    std::cout << s;
}

int main() {
    __int128 a = 1234567890123456789, b = 9876543210987654321;
    __int128 sum = a + b;
    printInt128(sum);
    return 0;
}
