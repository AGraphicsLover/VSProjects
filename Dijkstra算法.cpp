#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;
class Solution
{
public:
    vector<int> dijkstra(int src, vector<vector<int>>& graph, vector<int>& preNode)
    {
        ///initialization
        preNode = vector<int>(graph.size(), -1);
        vector<int> distToSrc(graph.size());
        unordered_set<int> visitedNodes;
        unordered_set<int> unvisitedNodes;
        for (int i = 0; i < graph.size(); i++)
        {
            unvisitedNodes.insert(i);
        }
        unvisitedNodes.erase(src);
        visitedNodes.insert(src);
        distToSrc[src] = 0;
        preNode[src] = -1;

        ///do greedy, find most closed node each turn
        while (!unvisitedNodes.empty())
        {
            int minNode = 0;
            int previousNode = 0;
            int minDistance = INT_MAX;
            ///traverse each v-u,v in visitedNodes, u in unvisitedNodes
            for (auto vNode : visitedNodes)
            {
                for (auto unNode : unvisitedNodes)
                {
                    if (graph[vNode][unNode] && distToSrc[vNode] + graph[vNode][unNode] < minDistance)
                    {
                        minDistance = distToSrc[vNode] + graph[vNode][unNode];
                        minNode = unNode;
                        previousNode = vNode;
                    }
                }
            }
            visitedNodes.insert(minNode);
            unvisitedNodes.erase(minNode);
            distToSrc[minNode] = minDistance;
            preNode[minNode] = previousNode;
        }
        return distToSrc;
    }

    int printPath()
    {
        vector<vector<int>> graph{ {0, 4, 0, 0, 0, 0, 0, 8, 0},
                                  {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                  {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                  {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                  {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                  {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                  {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                  {0, 0, 2, 0, 0, 0, 6, 7, 0} };

        vector<int> preNode;
        auto dists = dijkstra(0, graph, preNode);
        for (int i = 0; i < dists.size(); i++)
        {
            cout << i << " " << dists[i] << ": ";
            int node = i;
            stack<int> s;
            while (node != -1)
            {
                s.push(node);
                node = preNode[node];
            }
            while (!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
            cout << endl;
        }
        return 0;
    }
};

int main()
{
    return Solution().printPath();
}