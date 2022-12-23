#include "ListGraph.h"

ListGraph::ListGraph(int count) { graph.resize(count); }

ListGraph::ListGraph(const IGraph &other) {
    graph.resize(other.VerticesCount());

    for (int i = 0; i < other.VerticesCount(); ++i) {
        graph[i] = other.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return graph[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;

    for (int from = 0; from < graph.size(); ++from) {
        for (int i = 0; i < graph[from].size(); ++i) {
            if (graph[from][i] == vertex) {
                prev.push_back(from);
            }
        }
    }

    return prev;
}