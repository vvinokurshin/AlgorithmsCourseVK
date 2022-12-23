#pragma once

#include "IGraph.h"

class ListGraph : public IGraph {
 public:
    ListGraph(int count);
    ListGraph(const IGraph &other);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<int>> graph;
};