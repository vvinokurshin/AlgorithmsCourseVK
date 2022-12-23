#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int count) { 
    graph.resize(count);

    for (int i = 0; i < count; ++i) {
        graph[i].resize(count, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph &other) {
    graph.resize(other.VerticesCount());

    for (int i = 0; i < other.VerticesCount(); ++i) {
        graph[i] = other.GetNextVertices(i);

        for (const auto &elem: other.GetNextVertices(i)) {
            graph[i][elem] = 1;
        } 
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i]) {
            next.push_back(i);
        }
    }

    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][vertex]) {
            prev.push_back(i);
        }
    }

    return prev;
}