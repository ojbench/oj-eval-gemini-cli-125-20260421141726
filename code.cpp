#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define get_char() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
    int x = 0;
    char ch = get_char();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        ch = get_char();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = get_char();
    }
    return x;
}

struct Constraint {
    int i, j, e;
};

struct Node {
    int val;
    int* ptr;
};

bool compareNodes(const Node& a, const Node& b) {
    return a.val < b.val;
}

int parent[4000005];
int sz[4000005];

int find(int i) {
    int root = i;
    while (parent[root] != root) root = parent[root];
    while (parent[i] != root) {
        int next = parent[i];
        parent[i] = root;
        i = next;
    }
    return root;
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (sz[root_i] < sz[root_j]) {
            parent[root_i] = root_j;
            sz[root_j] += sz[root_i];
        } else {
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
}

vector<Constraint> constraints;
vector<Node> nodes;

void solve() {
    int n = read();
    if (n == -1) return;
    constraints.assign(n, {0, 0, 0});
    nodes.clear();
    nodes.reserve(2 * n);
    for (int k = 0; k < n; ++k) {
        constraints[k].i = read();
        constraints[k].j = read();
        constraints[k].e = read();
        nodes.push_back({constraints[k].i, &constraints[k].i});
        nodes.push_back({constraints[k].j, &constraints[k].j});
    }
    sort(nodes.begin(), nodes.end(), compareNodes);
    int rank = 0;
    for (int i = 0; i < (int)nodes.size(); ++i) {
        if (i == 0 || nodes[i].val != nodes[i - 1].val) {
            rank++;
        }
        *nodes[i].ptr = rank;
    }

    for (int i = 1; i <= rank; ++i) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 1) {
            unite(constraints[k].i, constraints[k].j);
        }
    }

    bool possible = true;
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 0) {
            if (find(constraints[k].i) == find(constraints[k].j)) {
                possible = false;
                break;
            }
        }
    }

    if (possible) printf("YES\n");
    else printf("NO\n");
}

int main() {
    int t = read();
    if (t == -1) return 0;
    constraints.reserve(2000000);
    nodes.reserve(4000000);
    while (t--) {
        solve();
    }
    return 0;
}
