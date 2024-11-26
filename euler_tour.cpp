// euler tour
const int MAXN = 100005;
int values[MAXN];  // Original values at each node
int tin[MAXN], tout[MAXN];  // Entry and exit times
int flat_tree[2 * MAXN];  // Flattened tree
int timer = 0;
void dfs(int u, int p) {
    tin[u] = timer;
    flat_tree[timer++] = values[u];
    for (int v : tree[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer - 1;
}


