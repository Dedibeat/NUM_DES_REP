#include <iostream>
#include <unordered_map>
#include <chrono>

using namespace std;

struct CustomHash {
    // Splitmix64 hash function
    static uint64_t splitmix64(uint64_t x) {
        // Constants are from the SplitMix64 algorithm
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    // For uint64_t keys
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    // For pair keys
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& p) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t hash1 = splitmix64(hash<T>()(p.first) + FIXED_RANDOM);
        uint64_t hash2 = splitmix64(hash<U>()(p.second) + FIXED_RANDOM + 1);
        return hash1 ^ (hash2 << 1);
    }
};

int main() {
    // Unordered map with pair<int, int> keys and custom hash function
    unordered_map<pair<int, int>, int, CustomHash> my_map;

    // Insert elements
    my_map[{1, 2}] = 100;
    my_map[{3, 4}] = 200;
    my_map[{5, 6}] = 300;

    // Access elements
    cout << "Value at key {1, 2}: " << my_map[{1, 2}] << endl;
    cout << "Value at key {3, 4}: " << my_map[{3, 4}] << endl;
    cout << "Value at key {5, 6}: " << my_map[{5, 6}] << endl;

    return 0;
}
