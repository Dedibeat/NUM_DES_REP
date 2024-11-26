#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5; // Maximum size of the input array
int t[4 * N];      // Segment tree array
int lazy[4 * N];   // Lazy propagation array
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl]; // Leaf node
    } else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);         // Build left child
        build(a, v * 2 + 1, tm + 1, tr); // Build right child
        t[v] = t[v * 2] + t[v * 2 + 1];  // Sum of left and right children
    }
}
void push(int v, int tl, int tr) {
    if (lazy[v] != 0) {
        int tm = (tl + tr) / 2;
        // Update left child
        t[v * 2] += (tm - tl + 1) * lazy[v];
        lazy[v * 2] += lazy[v];
        // Update right child
        t[v * 2 + 1] += (tr - tm) * lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        // Clear the lazy value at current node
        lazy[v] = 0;
    }
}
void updateRange(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v] += (tr - tl + 1) * addend;
        lazy[v] += addend;
    } else {
        push(v, tl, tr); // Push the lazy updates
        int tm = (tl + tr) / 2;
        updateRange(v * 2, tl, tm, l, min(r, tm), addend);
        updateRange(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
        t[v] = t[v * 2] + t[v * 2 + 1]; // Update current node
    }
}
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0; // If the range is invalid
    if (l == tl && r == tr) {
        return t[v]; // Exact segment matches the query range
    }
    push(v, tl, tr); // Push the lazy updates
    int tm = (tl + tr) / 2;
    // Recurse on both children
    return sum(v * 2, tl, tm, l, min(r, tm)) +
           sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}