#include "the5.h"

// do not add extra libraries here

using namespace std;

void StronglyConnectedComponent(int &node, const vector<vector<int>> &dependencyGraph, vector<char> &nodeStatus, vector<int> &result) {
    
    int graphSize = dependencyGraph.size();
    nodeStatus[node] = 'G';
    
    for (int adjacentNode = 0; adjacentNode < graphSize; adjacentNode++) {
        
        if (dependencyGraph[node][adjacentNode] == 0) continue;
        
        if (nodeStatus[adjacentNode] == 'W')
            StronglyConnectedComponent(adjacentNode, dependencyGraph, nodeStatus, result);
        
    }
    
    nodeStatus[node] = 'B';
    result.push_back(node);
    
}

void DFSVisit(int &node, const vector<vector<int>> &dependencyGraph, vector<char> &nodeStatus, vector<int> &result, bool &hasCycles) {
    
    int graphSize = dependencyGraph.size();
    nodeStatus[node] = 'G';
    
    for (int adjacentNode = 0; adjacentNode < graphSize; adjacentNode++) {
        
        if (dependencyGraph[adjacentNode][node] == 0) continue;
        
        if (nodeStatus[adjacentNode] == 'W')
            DFSVisit(adjacentNode, dependencyGraph, nodeStatus, result, hasCycles);
        
        else if (nodeStatus[adjacentNode] == 'G')
            hasCycles = false;
        
    }
    
    nodeStatus[node] = 'B';
    result.push_back(node);
    
}

void DFS(const vector<vector<int>> &dependencyGraph, vector<int> &result, bool &hasCycles) {
    
    int graphSize = dependencyGraph.size();
    vector<char> nodeStatus(graphSize, 'W');

    for (int node = 0; node < graphSize; node++)
        if (nodeStatus[node] == 'W')
            DFSVisit(node, dependencyGraph, nodeStatus, result, hasCycles);
    
}

void run(const std::vector<std::vector<int>>& dependencyMatrix, 
                         bool& isCompilable,
                         std::vector<int>& compileOrder, 
                         std::vector<std::vector<int>>& cyclicDependencies) {
    
    isCompilable = true;
    
    DFS(dependencyMatrix, compileOrder, isCompilable);
    
    if (isCompilable) return;
    
    else {
        
        int nodeCount = dependencyMatrix.size();
        
        vector<char> nodeStatus(nodeCount, 'W');
        vector<int> temp;
        
        for (int node = nodeCount - 1; node >= 0; node--) {
            temp.clear();
            
            if (nodeStatus[compileOrder[node]] == 'W') {
                StronglyConnectedComponent(compileOrder[node], dependencyMatrix, nodeStatus, temp);
                if (temp.size() > 1 || (temp.size() == 1 && dependencyMatrix[compileOrder[node]][compileOrder[node]]))
                    cyclicDependencies.push_back(temp);
            }
            
        }
        
    }
    
}
