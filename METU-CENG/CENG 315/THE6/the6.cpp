#include "the6.h"

// do not add extra libraries here
using namespace std;

bool Comp(const pair<pair<int, int>, int> &EDGE_A, const pair<pair<int, int>, int> &EDGE_B) {
    return EDGE_A.second < EDGE_B.second;
}
int getParent(int x, vector<int> &parent) {
    if (parent[x] != x) {
        parent[x] = getParent(parent[x], parent);
    }
    return parent[x];
}
void SetUnion(int x, int y, vector<int> &parent, vector<int> &rank) {
    int parent_x = getParent(x, parent);
    int parent_y = getParent(y, parent);

    if (parent_x != parent_y) {
        if (rank[parent_x] > rank[parent_y]) {
            parent[parent_y] = parent_x;
        } else {
            parent[parent_x] = parent_y;
            if (rank[parent_x] == rank[parent_y]) {
                rank[parent_y]++;
            }
        }
    }
}



void DFS(int node, const vector<vector<pair<int, int>>> &molecule_structure, vector<int> &current_chain, vector<int> &chain, vector<bool> &visited) {
    visited[node] = true;
    current_chain.push_back(node);

    for (auto edge : molecule_structure[node]) {
        int neighbor = edge.first;

        if (!visited[neighbor]) {
            DFS(neighbor, molecule_structure, current_chain, chain, visited);
        }
    }

    if (current_chain.size() > chain.size()) {
        chain = current_chain;
    }
    visited[node] = false;
    current_chain.pop_back();
}

int find_structure(vector<vector<pair<int, int>>> &bond_energies, vector<vector<pair<int, int>>> &lowest_energy_structure) {
    int n = bond_energies.size();
    vector<pair<pair<int, int>, int>> EDGES;
    for (int i = 0; i < n; i++) {
        for (auto edge : bond_energies[i]) {
            int neighbor = edge.first;
            int w = edge.second;
            EDGES.push_back(make_pair(make_pair(i, neighbor), w));
        }
    }
    sort(EDGES.begin(), EDGES.end(), Comp);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int total_energy = 0;

    for (auto edge : EDGES) {
        int u1 = edge.first.first;
        int u2 = edge.first.second;
        int w = edge.second;
        int root1 = getParent(u1, parent);
        int root2 = getParent(u2, parent);
        if (root1 != root2) {
            lowest_energy_structure[u1].push_back(make_pair(u2, w));
            lowest_energy_structure[u2].push_back(make_pair(u1, w));
            SetUnion(u1, u2, parent, rank);
            total_energy += w;
        }
    }

    return total_energy;
}

int find_longest_chain(vector<vector<pair<int, int>>> &molecule_structure, vector<int> &chain) {
    int n = molecule_structure.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> current_chain;
            DFS(i, molecule_structure, current_chain, chain, visited);
        }
    }

    return chain.size();
}