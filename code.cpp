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

int parent[4000005];
int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

void solve() {
    int n = read();
    if (n == -1) return;
    vector<Constraint> constraints(n);
    vector<int> coords;
    coords.reserve(2 * n);
    for (int k = 0; k < n; ++k) {
        constraints[k].i = read();
        constraints[k].j = read();
        constraints[k].e = read();
        coords.push_back(constraints[k].i);
        coords.push_back(constraints[k].j);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    auto get_coord = [&](int x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin() + 1;
    };

    int m = coords.size();
    for (int i = 1; i <= m; ++i) parent[i] = i;

    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 1) {
            int u = get_coord(constraints[k].i);
            int v = get_coord(constraints[k].j);
            int root_u = find(u);
            int root_v = find(v);
            if (root_u != root_v) {
                parent[root_u] = root_v;
            }
        }
    }

    bool possible = true;
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 0) {
            int u = get_coord(constraints[k].i);
            int v = get_coord(constraints[k].j);
            if (find(u) == find(v)) {
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
    while (t--) {
        solve();
    }
    return 0;
}
