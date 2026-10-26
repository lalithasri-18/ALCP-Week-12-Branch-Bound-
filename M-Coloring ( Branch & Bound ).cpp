#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int> > graph(n, vector<int>(n));

    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    cout << "Enter number of colors: ";
    cin >> m;

    queue<vector<int> > q;
    vector<int> root;
    q.push(root);

    while (!q.empty()) {
        vector<int> color = q.front();
        q.pop();

        int v = color.size();

        if (v == n) {
            cout << "Coloring possible\n";

            for (int i = 0; i < n; i++)
                cout << "Vertex " << i
                     << " -> Color " << color[i] << endl;

            return 0;
        }

        for (int c = 1; c <= m; c++) {
            bool safe = true;

            for (int i = 0; i < v; i++) {
                if (graph[v][i] == 1 &&
                    color[i] == c) {
                    safe = false;
                    break;
                }
            }

            if (graph[v][v] == 1)
                safe = false;

            if (safe) {
                vector<int> next = color;
                next.push_back(c);
                q.push(next);
            }
        }
    }

    cout << "Coloring not possible";
    return 0;
}
