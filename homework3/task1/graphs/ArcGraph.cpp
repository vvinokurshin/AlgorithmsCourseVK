#include "ArcGraph.h"

#include "ArcGraph.h"

ArcGraph::ArcGraph(int count) : count(count) {}

ArcGraph::ArcGraph(const IGraph &other) {
    count = other.VerticesCount();

    for (int i = 0; i < count; ++i) {
        for (const auto &elem : other.GetNextVertices(i)) {
            edges.push_back(std::pair<int, int>(i, elem));
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    edges.push_back(std::pair<int, int>(from, to));
}

int ArcGraph::VerticesCount() const { return count; }

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;

    for (const auto &elem : edges) {
        if (elem.first == vertex) {
            next.push_back(elem.second);
        }
    }

    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;

    for (const auto &elem : edges) {
        if (elem.second == vertex) {
            prev.push_back(elem.first);
        }
    }

    return prev;
}