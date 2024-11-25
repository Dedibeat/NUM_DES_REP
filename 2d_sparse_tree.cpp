#include <iostream>
typedef long long ll;
struct NodeY {
    ll val;       // Aggregated value of the segment
    NodeY *left;  // Left child in Y-axis
    NodeY *right; // Right child in Y-axis
    NodeY() : val(0), left(nullptr), right(nullptr) {}
};
struct NodeX {
    ll x_left, x_right; // Range represented by this node on X-axis
    NodeX *left;        // Left child in X-axis
    NodeX *right;       // Right child in X-axis
    NodeY *segTreeY;    // Y-axis segment tree rooted at this node
    NodeX(ll x_left, ll x_right) : x_left(x_left), x_right(x_right), left(nullptr), right(nullptr), segTreeY(nullptr) {}
};
class DynamicSegmentTree2D {
private:
    NodeX* root;
    ll x_l_bound, x_r_bound;
    ll y_l_bound, y_r_bound;
    void updateY(NodeY*& node, ll y_l, ll y_r, ll y_idx, ll value) {
        if (!node) node = new NodeY();
        if (y_l == y_r) {
            node->val += value;
            return;
        }
        ll y_mid = y_l + (y_r - y_l) / 2;
        if (y_idx <= y_mid) {
            updateY(node->left, y_l, y_mid, y_idx, value);
        } else {
            updateY(node->right, y_mid + 1, y_r, y_idx, value);
        }
        node->val = getValue(node->left) + getValue(node->right);
    }
    ll queryY(NodeY* node, ll y_l, ll y_r, ll qy_l, ll qy_r) {
        if (!node || qy_r < y_l || qy_l > y_r) return 0;
        if (qy_l <= y_l && y_r <= qy_r) {
            return node->val;
        }
        ll y_mid = y_l + (y_r - y_l) / 2;
        return queryY(node->left, y_l, y_mid, qy_l, qy_r) + queryY(node->right, y_mid + 1, y_r, qy_l, qy_r);
    }
    void updateX(NodeX*& node, ll x_l, ll x_r, ll x_idx, ll y_idx, ll value) {
        if (!node) node = new NodeX(x_l, x_r);
        updateY(node->segTreeY, y_l_bound, y_r_bound, y_idx, value);
        if (x_l == x_r) return;
        ll x_mid = x_l + (x_r - x_l) / 2;
        if (x_idx <= x_mid) {
            updateX(node->left, x_l, x_mid, x_idx, y_idx, value);
        } else {
            updateX(node->right, x_mid + 1, x_r, x_idx, y_idx, value);
        }
    }
    ll queryX(NodeX* node, ll x_l, ll x_r, ll qx_l, ll qx_r, ll qy_l, ll qy_r) {
        if (!node || qx_r < x_l || qx_l > x_r) return 0;
        if (qx_l <= x_l && x_r <= qx_r) {
            return queryY(node->segTreeY, y_l_bound, y_r_bound, qy_l, qy_r);
        }
        ll x_mid = x_l + (x_r - x_l) / 2;
        return queryX(node->left, x_l, x_mid, qx_l, qx_r, qy_l, qy_r) +
               queryX(node->right, x_mid + 1, x_r, qx_l, qx_r, qy_l, qy_r);
    }
    ll getValue(NodeY* node) {
        return node ? node->val : 0;
    }

public:
    DynamicSegmentTree2D(ll x_l_bound, ll x_r_bound, ll y_l_bound, ll y_r_bound)
        : x_l_bound(x_l_bound), x_r_bound(x_r_bound),
          y_l_bound(y_l_bound), y_r_bound(y_r_bound), root(nullptr) {}

    void update(ll x_idx, ll y_idx, ll value) {
        updateX(root, x_l_bound, x_r_bound, x_idx, y_idx, value);
    }

    ll query(ll qx_l, ll qx_r, ll qy_l, ll qy_r) {
        return queryX(root, x_l_bound, x_r_bound, qx_l, qx_r, qy_l, qy_r);
    }
};
int main() {
    ll x_l_bound = -1e9, x_r_bound = 1e9;
    ll y_l_bound = -1e9, y_r_bound = 1e9;
    DynamicSegmentTree2D segTree2D(x_l_bound, x_r_bound, y_l_bound, y_r_bound);

    segTree2D.update(5, 5, 10);           // Add 10 at point (5, 5)
    segTree2D.update(100, 100, 5);        // Add 5 at point (100, 100)
    segTree2D.update(-50, -50, 7);        // Add 7 at point (-50, -50)

    std::cout << "Sum in rectangle [(0, 0), (10, 10)]: "
              << segTree2D.query(0, 10, 0, 10) << std::endl;

    std::cout << "Sum in rectangle [(-100, -100), (100, 100)]: "
              << segTree2D.query(-100, 100, -100, 100) << std::endl;

    return 0;
}
