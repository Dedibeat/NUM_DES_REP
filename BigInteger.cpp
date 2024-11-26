#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
class BigInteger {
    std::vector<int> digits;
    bool isNegative;
    void trim() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0) isNegative = false;
    }
public:
    BigInteger() : isNegative(false) { digits.push_back(0); }
    BigInteger(const std::string& num) {
        isNegative = false; size_t start = 0;
        if (num[0] == '-') { isNegative = true; start = 1; }
        else if (num[0] == '+') { start = 1; }
        for (size_t i = num.size(); i > start; --i) digits.push_back(num[i - 1] - '0');
        trim();
    }
    BigInteger operator+(const BigInteger& other) const {
        if (isNegative == other.isNegative) {
            BigInteger result = addAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else {
            if (compareAbs(*this, other) >= 0) {
                BigInteger result = subtractAbs(*this, other);
                result.isNegative = isNegative;
                return result;
            } else {
                BigInteger result = subtractAbs(other, *this);
                result.isNegative = other.isNegative;
                return result;
            }
        }
    }
    BigInteger operator-(const BigInteger& other) const {
        if (isNegative != other.isNegative) {
            BigInteger result = addAbs(*this, other);
            result.isNegative = isNegative;
            return result;
        } else {
            if (compareAbs(*this, other) >= 0) {
                BigInteger result = subtractAbs(*this, other);
                result.isNegative = isNegative;
                return result;
            } else {
                BigInteger result = subtractAbs(other, *this);
                result.isNegative = !other.isNegative;
                return result;
            }
        }
    }
    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        result.isNegative = isNegative != other.isNegative;
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long current = result.digits[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = current % 10;
                carry = current / 10;
            }
        }
        result.trim();
        return result;
    }
    bool operator<(const BigInteger& other) const {
        if (isNegative != other.isNegative) return isNegative;
        int cmp = compareAbs(*this, other);
        return isNegative ? cmp > 0 : cmp < 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
        if (num.isNegative) os << '-';
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) os << *it;
        return os;
    }
private:
    static int compareAbs(const BigInteger& a, const BigInteger& b) {
        if (a.digits.size() != b.digits.size()) return a.digits.size() > b.digits.size() ? 1 : -1;
        for (size_t i = a.digits.size(); i > 0; --i)
            if (a.digits[i - 1] != b.digits[i - 1])
                return a.digits[i - 1] > b.digits[i - 1] ? 1 : -1;
        return 0;
    }
    static BigInteger addAbs(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        result.digits.clear();
        int carry = 0; size_t maxSize = std::max(a.digits.size(), b.digits.size());
        for (size_t i = 0; i < maxSize || carry; ++i) {
            int sum = carry;
            if (i < a.digits.size()) sum += a.digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        return result;
    }
    static BigInteger subtractAbs(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        result.digits.clear();
        int carry = 0;
        for (size_t i = 0; i < a.digits.size(); ++i) {
            int diff = a.digits[i] - carry - (i < b.digits.size() ? b.digits[i] : 0);
            if (diff < 0) { diff += 10; carry = 1; } else carry = 0;
            result.digits.push_back(diff);
        }
        result.trim();
        return result;
    }
};
