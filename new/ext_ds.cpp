#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<
    T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset = tree<
    pair<T, int>, null_type, less<pair<T, int>>,
    rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V>
using indexed_map = tree<
    K, V, less<K>,
    rb_tree_tag, tree_order_statistics_node_update>;

gp_hash_table<Key, Mapped> mp;
using IntSeqTrie = trie<
    vector<int>,        // key type
    int,                // mapped value
    trie_string_access_traits< // must define how to access the sequence
        vector<int>,           // same as key type
        null_type>,            // no hash
    pat_trie_tag,              // use Patricia trie
    trie_prefix_search_node_update>;
