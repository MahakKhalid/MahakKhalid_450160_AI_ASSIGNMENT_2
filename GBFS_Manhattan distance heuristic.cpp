#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > goal_state{ {0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

bool nodes_visited(const vector<vector<int>> &c, map<vector<vector<int>>, bool> &checked_nodes) {
    return checked_nodes.count(c) && checked_nodes[c];
}

int manhattan(const vector<vector<int>> &c) {
    int distance = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (c[i][j] != 0) {
                int target_i = c[i][j] / 3;
                int target_j = c[i][j] % 3;
                distance += abs(i - target_i) + abs(j - target_j);
            }
        }
    }
    return distance;
}

bool within_bounds(int i, int j) {
    return i >= 0 && i <= 2 && j >= 0 && j <= 2;
}

vector<vector<vector<int>>> neighbours(const vector<vector<int>> &c) {
    pair<int, int> position;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (c[i][j] == 0) {
                position = {i, j};
                break;
            }
        }
    }

    vector<vector<vector<int>>> answer;

    for (int k = 0; k < 4; k++) {
        int rx = position.first + (k == 0) - (k == 1);
        int ry = position.second + (k == 2) - (k == 3);

        if (within_bounds(rx, ry)) {
            vector<vector<int>> n = c;
            swap(n[position.first][position.second], n[rx][ry]);
            answer.push_back(n);
        }
    }

    return answer;
}

typedef pair<vector<vector<int>>, int> state;

struct compare {
    bool operator()(const state &v, const state &b) const {
        return manhattan(v.first) > manhattan(b.first);
    }
};

void print(const vector<vector<int>> &p) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", p[i][j]);
        }
        cout << endl;
    }
}

void path_print(vector<vector<int>> p, map<vector<vector<int>>, vector<vector<int>>> &parent) {
    vector<vector<vector<int>>> path;
    while (parent.count(p)) {
        path.push_back(p);
        p = parent[p];
    }
    path.push_back(p);

    cout << "Printing Path:" << endl;
    for (int i = path.size() - 1; i >= 0; --i) {
        print(path[i]);
        cout << endl;
    }
    cout << endl;
}

void greedy_best_first_search(const vector<vector<int>> &initial_state) {
    priority_queue<state, vector<state>, compare> que;
    que.push({initial_state, 0});

    map<vector<vector<int>>, bool> visited;
    map<vector<vector<int>>, vector<vector<int>>> parent;

    while (!que.empty()) {
        vector<vector<int>> current_state = que.top().first;
        que.pop();

        if (visited[current_state]) {
            continue;
        }

        visited[current_state] = true;

        if (current_state == goal_state) {
            cout << "Goal State Reached!\n\n";
            path_print(current_state, parent);
            break;
        }

        vector<vector<vector<int>>> neighbors = neighbours(current_state);

        for (auto &neighbor : neighbors) {
            if (!visited[neighbor]) {
                parent[neighbor] = current_state;
                que.push({neighbor, 0});
            }
        }
    }
}

int main() {
    vector<vector<int>> initial_state;
    int elements = 0;

    cout << "Enter the initial state of the puzzle:" << endl;
    for (int i = 0; i < 3; i++) {
        vector<int> i_state;
        for (int j = 0; j < 3; j++) {
            cout << " [" << i << "][" << j << "] ";
            cin >> elements;
            i_state.push_back(elements);
        }
        initial_state.push_back(i_state);
    }

    cout << "Initial Puzzle state:" << endl;
    for (auto &it : initial_state) {
        for (auto &i : it) {
            cout << i << " ";
        }
        cout << endl;
    }
    
    cout<<"\n\nImplementing Greedy Best First Search using Manhattan distance heuristic\n\n";

    greedy_best_first_search(initial_state);

    return 0;
}

