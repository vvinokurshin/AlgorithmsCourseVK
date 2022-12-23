#include "SetGraph.h"

SetGraph::SetGraph(int count) { graph.resize(count); }

SetGraph::SetGraph(const IGraph &other) {
    graph.resize(other.VerticesCount());

    for (int i = 0; i < other.VerticesCount(); ++i) {
        std::vector<int> next = other.GetNextVertices(i);

        graph[i] = std::unordered_set<int>(next.begin(), next.end());
    }
}

void SetGraph::AddEdge(int from, int to) { graph[from].insert(to); }

int SetGraph::VerticesCount() const { return graph.size(); }

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    return std::vector<int>(graph[vertex].begin(), graph[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i].find(vertex) != graph[i].end()) {
            prev.push_back(i);
        }
    }

    return prev;
}