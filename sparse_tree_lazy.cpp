#include <iostream>

typedef long long ll;

struct Node {
    ll val;       // Aggregated value of the segment
    ll lazy;      // Lazy propagation value
    Node *left;   // Left child
    Node *right;  // Right child
    Node() : val(0), lazy(0), left(nullptr), right(nullptr) {}
};
class DynamicSegmentTree {
private:
    Node* root;
    ll l_bound, r_bound;
    void push(Node* node, ll l, ll r) {
        if (node->lazy != 0) {
            node->val += node->lazy * (r - l + 1);
            if (l != r) {
                if (!node->left) node->left = new Node();
                if (!node->right) node->right = new Node();
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy;
            }
            node->lazy = 0;
        }
    }
    void update(Node*& node, ll l, ll r, ll ql, ll qr, ll value) {
        if (!node) node = new Node();
        push(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            node->lazy += value;
            push(node, l, r);
            return;
        }
        ll mid = l + (r - l) / 2;
        update(node->left, l, mid, ql, qr, value);
        update(node->right, mid + 1, r, ql, qr, value);
        node->val = getValue(node->left) + getValue(node->right);
    }
    ll query(Node* node, ll l, ll r, ll ql, ll qr) {
        if (!node || ql > r || qr < l) return 0;
        push(node, l, r);
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
    void update(ll ql, ll qr, ll value) {
        update(root, l_bound, r_bound, ql, qr, value);
    }
    ll query(ll ql, ll qr) {
        return query(root, l_bound, r_bound, ql, qr);
    }
};

int main() {
    ll l_bound = -1e9, r_bound = 1e9;
    DynamicSegmentTree segTree(l_bound, r_bound);
    segTree.update(1, 100, 5);      // Add 5 to range [1, 100]
    segTree.update(50, 150, 3);     // Add 3 to range [50, 150]
    std::cout << "Sum in range [1, 100]: " << segTree.query(1, 100) << std::endl;
    std::cout << "Sum in range [50, 150]: " << segTree.query(50, 150) << std::endl;
    std::cout << "Sum in range [1, 150]: " << segTree.query(1, 150) << std::endl;
    return 0;
}
