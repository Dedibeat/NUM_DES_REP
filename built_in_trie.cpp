#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using Trie = trie<
    string,                  // Key type (strin, deque, vector)
    null_type,               // Mapped type(any type)
    trie_string_access_traits<>, // Access traits for strings
    pat_trie_tag,            // Use a Patricia Trie
    trie_prefix_search_node_update>; // Enables prefix search
int main() {
    Trie t;
    // Insert words
    t.insert("apple");
    t.insert("app");
    t.insert("banana");
    
    // Search
    cout << boolalpha << (t.find("app") != t.end()) << "\n"; // true
    cout << (t.find("banana") != t.end()) << "\n";           // true
    cout << (t.find("band") != t.end()) << "\n";             // false
    
    // Prefix search
    auto range = t.prefix_range("app");
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << "\n";
    }
    return 0;
}
