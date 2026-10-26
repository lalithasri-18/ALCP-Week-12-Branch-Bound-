#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c;
    vector<int> path;
};

int main() {
    int rows, cols;

    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    if (rows <= 0 || cols <= 0) return 0;

    vector<string> board(rows);

    cout << "Enter board:\n";
    for (int i = 0; i < rows; i++) {
        cin >> board[i];
        if ((int)board[i].size() != cols)
            return 0;
    }

    string word;
    cout << "Enter word: ";
    cin >> word;

    // Check whether enough letters exist
    int have[256] = {0};
    int need[256] = {0};

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            have[(unsigned char)board[i][j]]++;

    for (int i = 0; i < (int)word.size(); i++)
        need[(unsigned char)word[i]]++;

    for (int i = 0; i < 256; i++) {
        if (need[i] > have[i]) {
            cout << "Word not found";
            return 0;
        }
    }

    queue<State> q;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == word[0]) {
                State s;
                s.r = i;
                s.c = j;
                s.path.push_back(i * cols + j);
                q.push(s);
            }
        }
    }

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        State s = q.front();
        q.pop();

        int len = s.path.size();

        if (len == (int)word.size()) {
            cout << "Word found";
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int x = s.r + dr[k];
            int y = s.c + dc[k];

            if (x < 0 || x >= rows ||
                y < 0 || y >= cols)
                continue;

            if (board[x][y] != word[len])
                continue;

            int id = x * cols + y;
            bool used = false;

            for (int i = 0; i < len; i++) {
                if (s.path[i] == id) {
                    used = true;
                    break;
                }
            }

            if (used) continue;

            State next = s;
            next.r = x;
            next.c = y;
            next.path.push_back(id);

            q.push(next);
        }
    }

    cout << "Word not found";
    return 0;
}
