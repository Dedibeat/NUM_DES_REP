#include <iostream>
typedef long long ll;
struct Node {
    ll val;       // Value of the segment (e.g., sum)
    Node *left;   // Left child
    Node *right;  // Right child aa
    Node() : val(0), left(nullptr), right(nullptr) {}
};
class DynamicSegmentTree {
private:
    Node* root;
    ll l_bound, r_bound;
    void update(Node*& node, ll l, ll r, ll idx, ll value) {
        if (!node) node = new Node();
        if (l == r) {
            node->val += value;
            return;
        }
        ll mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(node->left, l, mid, idx, value);
        } else {
            update(node->right, mid + 1, r, idx, value);
        }
        node->val = getValue(node->left) + getValue(node->right);
    }
    ll query(Node* node, ll l, ll r, ll ql, ll qr) {
        if (!node || ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) {
            return node->val;
        }
        ll mid = l + (r - l) / 2;
        return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
    }
    ll getValue(Node* node) {
        return node ? node->val : 0;
    }
public:
    DynamicSegmentTree(ll l_bound, ll r_bound) : l_bound(l_bound), r_bound(r_bound), root(nullptr) {}
    void update(ll idx, ll value) {
        update(root, l_bound, r_bound, idx, value);
    }
    ll query(ll ql, ll qr) {
        return query(root, l_bound, r_bound, ql, qr);
    }
};
int main() {
    ll l_bound = -1e9, r_bound = 1e9;
    DynamicSegmentTree segTree(l_bound, r_bound);
    segTree.update(5, 10);          // Add 10 at index 5
    segTree.update(1000000000, 5);  // Add 5 at index 1e9
    std::cout << "Sum in range [0, 10]: " << segTree.query(0, 10) << std::endl;
    std::cout << "Sum in range [0, 1e9]: " << segTree.query(0, 1000000000) << std::endl;
    return 0;
}
