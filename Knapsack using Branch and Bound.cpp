#include <bits/stdc++.h>
using namespace std;

struct Item {
    int w, p;
    double ratio;
};

struct Node {
    int level, weight, profit;
    double bound;

    bool operator<(const Node &a) const {
        return bound < a.bound;
    }
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double getBound(Node u, vector<Item> &a,
                int n, int W) {
    if (u.weight > W)
        return 0;

    double b = u.profit;
    int weight = u.weight;

    for (int i = u.level + 1; i < n; i++) {
        if (weight + a[i].w <= W) {
            weight += a[i].w;
            b += a[i].p;
        } else {
            b += (W - weight) * a[i].ratio;
            break;
        }
    }
    return b;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> a(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter weight and profit: ";
        cin >> a[i].w >> a[i].p;
        if (a[i].w <= 0 || a[i].p < 0) {
            cout << "Invalid item";
            return 0;
        }
        a[i].ratio = (double)a[i].p / a[i].w;
    }

    cout << "Enter capacity: ";
    cin >> W;

    if (W < 0) return 0;

    sort(a.begin(), a.end(), compare);

    priority_queue<Node> q;

    Node root;
    root.level = -1;
    root.weight = 0;
    root.profit = 0;
    root.bound = getBound(root, a, n, W);

    q.push(root);
    int best = 0;

    while (!q.empty()) {
        Node u = q.top();
        q.pop();

        if (u.bound <= best || u.level == n - 1)
            continue;

        Node v;
        v.level = u.level + 1;

        v.weight = u.weight + a[v.level].w;
        v.profit = u.profit + a[v.level].p;

        if (v.weight <= W) {
            best = max(best, v.profit);
            v.bound = getBound(v, a, n, W);

            if (v.bound > best)
                q.push(v);
   		}
    
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = getBound(v, a, n, W);

        if (v.bound > best)
            q.push(v);
    }

    cout << "Maximum Profit = " << best;
    return 0;
}
