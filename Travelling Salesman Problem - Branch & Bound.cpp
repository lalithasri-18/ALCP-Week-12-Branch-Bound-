#include <bits/stdc++.h>
using namespace std;

const int INF = 100000000;

struct Node {
    vector<vector<int> > mat;
    vector<int> path;
    int city, cost;

    bool operator<(const Node &a) const {
        return cost > a.cost;
    }
};

int reduce(vector<vector<int> > &a, int n) {
    int sum = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int mn = INF;
        for (int j = 0; j < n; j++)
            mn = min(mn, a[i][j]);

        if (mn == INF) continue;

        sum += mn;
        for (int j = 0; j < n; j++)
            if (a[i][j] != INF)
                a[i][j] -= mn;
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int mn = INF;
        for (int i = 0; i < n; i++)
            mn = min(mn, a[i][j]);

        if (mn == INF) continue;

        sum += mn;
        for (int i = 0; i < n; i++)
            if (a[i][j] != INF)
                a[i][j] -= mn;
    }

    return sum;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    if (n < 2) return 0;

    vector<vector<int> > a(n, vector<int>(n));

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (i == j)
                a[i][j] = INF;
        }
    }

    priority_queue<Node> q;

    Node root;
    root.mat = a;
    root.city = 0;
    root.path.push_back(0);
    root.cost = reduce(root.mat, n);
    q.push(root);

    while (!q.empty()) {
        Node u = q.top();
        q.pop();

        if ((int)u.path.size() == n) {
            cout << "Minimum Cost = " << u.cost;
            cout << "\nPath: ";

            for (int i = 0; i < n; i++)
                cout << u.path[i] << " -> ";

            cout << 0;
            return 0;
        }

        for (int j = 0; j < n; j++) {
            if (u.mat[u.city][j] == INF)
                continue;

            Node v = u;
            v.path.push_back(j);

            for (int k = 0; k < n; k++) {
                v.mat[u.city][k] = INF;
                v.mat[k][j] = INF;
            }

            v.mat[j][0] = INF;
            v.city = j;

            v.cost = u.cost +
                     u.mat[u.city][j] +
                     reduce(v.mat, n);

            q.push(v);
        }
    }

    cout << "No tour found";
    return 0;
}
