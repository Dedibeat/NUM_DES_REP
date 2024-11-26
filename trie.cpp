#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    static const int ALPHABET_SIZE = 26; // Assuming lowercase English letters
    TrieNode* children[ALPHABET_SIZE];
    int countEnd;   // Number of words that end at this node
    int countPrefix; // Number of words that have the prefix up to this node
    TrieNode() {
        countEnd = 0;
        countPrefix = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a'; // Assuming lowercase letters
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
            node->countPrefix += 1;
        }
        node->countEnd += 1;
    }
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node->countEnd > 0;
    }
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node->countPrefix > 0;
    }
    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index])
                return 0;
            node = node->children[index];
        }
        return node->countEnd;
    }

    int countWordsStartingWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index])
                return 0;
            node = node->children[index];
        }
        return node->countPrefix;
    }

    void erase(const string& word) {
        if (search(word))
            eraseHelper(root, word, 0);
    }

private:
    bool eraseHelper(TrieNode* node, const string& word, int depth) {
        if (!node)
            return false;
        if (depth == word.size()) {
            node->countEnd -= 1;
            node->countPrefix -= 1;
            // If node has no children, we can delete it
            return isLeafNode(node);
        } else {
            int index = word[depth] - 'a';
            if (eraseHelper(node->children[index], word, depth + 1)) {
                delete node->children[index];
                node->children[index] = nullptr;
            }
            node->countPrefix -= 1;
            // If node is not end of another word and has no children
            return !node->countEnd && isLeafNode(node);
        }
    }

    // Checks if the node is a leaf node (no children)
    bool isLeafNode(TrieNode* node) {
        for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
            if (node->children[i])
                return false;
        }
        return true;
    }
};
