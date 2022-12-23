#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include <gtest/gtest.h>

void fillGraph(IGraph *graph) {
    graph->AddEdge(1, 3);
    graph->AddEdge(2, 1);
    graph->AddEdge(2, 3);
    graph->AddEdge(2, 4);
    graph->AddEdge(3, 4);
    graph->AddEdge(4, 5);
    graph->AddEdge(5, 3);
    graph->AddEdge(5, 4);
}

TEST(TestListGraph, tests) {
    IGraph *listGraph = new ListGraph(6);
    fillGraph(listGraph);

    EXPECT_TRUE(listGraph->GetNextVertices(0) == std::vector<int>());
    EXPECT_TRUE(listGraph->GetPrevVertices(0) == std::vector<int>());

    EXPECT_TRUE(listGraph->GetNextVertices(1) == std::vector<int>({3}));
    EXPECT_TRUE(listGraph->GetNextVertices(2) == std::vector<int>({1, 3, 4}));
    EXPECT_TRUE(listGraph->GetNextVertices(3) == std::vector<int>({4}));
    EXPECT_TRUE(listGraph->GetNextVertices(4) == std::vector<int>({5}));
    EXPECT_TRUE(listGraph->GetNextVertices(5) == std::vector<int>({3, 4}));

    EXPECT_TRUE(listGraph->GetPrevVertices(1) == std::vector<int>({2}));
    EXPECT_TRUE(listGraph->GetPrevVertices(2) == std::vector<int>());
    EXPECT_TRUE(listGraph->GetPrevVertices(3) == std::vector<int>({1, 2, 5}));
    EXPECT_TRUE(listGraph->GetPrevVertices(4) == std::vector<int>({2, 3, 5}));
    EXPECT_TRUE(listGraph->GetPrevVertices(5) == std::vector<int>({4}));

    delete listGraph;
}

TEST(TestMatrixGraph, tests) {
    IGraph *matrixGraph = new MatrixGraph(6);
    fillGraph(matrixGraph);

    EXPECT_TRUE(matrixGraph->GetNextVertices(0) == std::vector<int>());
    EXPECT_TRUE(matrixGraph->GetPrevVertices(0) == std::vector<int>());

    EXPECT_TRUE(matrixGraph->GetNextVertices(1) == std::vector<int>({3}));
    EXPECT_TRUE(matrixGraph->GetNextVertices(2) == std::vector<int>({1, 3, 4}));
    EXPECT_TRUE(matrixGraph->GetNextVertices(3) == std::vector<int>({4}));
    EXPECT_TRUE(matrixGraph->GetNextVertices(4) == std::vector<int>({5}));
    EXPECT_TRUE(matrixGraph->GetNextVertices(5) == std::vector<int>({3, 4}));

    EXPECT_TRUE(matrixGraph->GetPrevVertices(1) == std::vector<int>({2}));
    EXPECT_TRUE(matrixGraph->GetPrevVertices(2) == std::vector<int>());
    EXPECT_TRUE(matrixGraph->GetPrevVertices(3) == std::vector<int>({1, 2, 5}));
    EXPECT_TRUE(matrixGraph->GetPrevVertices(4) == std::vector<int>({2, 3, 5}));
    EXPECT_TRUE(matrixGraph->GetPrevVertices(5) == std::vector<int>({4}));

    delete matrixGraph;
}

TEST(TestSetGraph, tests) {
    IGraph *setGraph = new SetGraph(6);
    fillGraph(setGraph);

    EXPECT_TRUE(setGraph->GetNextVertices(0) == std::vector<int>());
    EXPECT_TRUE(setGraph->GetPrevVertices(0) == std::vector<int>());

    EXPECT_TRUE(setGraph->GetNextVertices(1) == std::vector<int>({3}));
    EXPECT_TRUE(setGraph->GetNextVertices(2) == std::vector<int>({4, 3, 1}));
    EXPECT_TRUE(setGraph->GetNextVertices(3) == std::vector<int>({4}));
    EXPECT_TRUE(setGraph->GetNextVertices(4) == std::vector<int>({5}));
    EXPECT_TRUE(setGraph->GetNextVertices(5) == std::vector<int>({4, 3}));

    EXPECT_TRUE(setGraph->GetPrevVertices(1) == std::vector<int>({2}));
    EXPECT_TRUE(setGraph->GetPrevVertices(2) == std::vector<int>());
    EXPECT_TRUE(setGraph->GetPrevVertices(3) == std::vector<int>({1, 2, 5}));
    EXPECT_TRUE(setGraph->GetPrevVertices(4) == std::vector<int>({2, 3, 5}));
    EXPECT_TRUE(setGraph->GetPrevVertices(5) == std::vector<int>({4}));

    delete setGraph;
}


TEST(TestArcGraph, tests) {
    IGraph *arcGraph = new ArcGraph(6);
    fillGraph(arcGraph);

    EXPECT_TRUE(arcGraph->GetNextVertices(0) == std::vector<int>());
    EXPECT_TRUE(arcGraph->GetPrevVertices(0) == std::vector<int>());
    EXPECT_TRUE(arcGraph->GetNextVertices(1) == std::vector<int>({3}));
    EXPECT_TRUE(arcGraph->GetNextVertices(2) == std::vector<int>({1, 3, 4}));
    EXPECT_TRUE(arcGraph->GetNextVertices(3) == std::vector<int>({4}));
    EXPECT_TRUE(arcGraph->GetNextVertices(4) == std::vector<int>({5}));
    EXPECT_TRUE(arcGraph->GetNextVertices(5) == std::vector<int>({3, 4}));
    EXPECT_TRUE(arcGraph->GetPrevVertices(1) == std::vector<int>({2}));
    EXPECT_TRUE(arcGraph->GetPrevVertices(2) == std::vector<int>());
    EXPECT_TRUE(arcGraph->GetPrevVertices(3) == std::vector<int>({1, 2, 5}));
    EXPECT_TRUE(arcGraph->GetPrevVertices(4) == std::vector<int>({2, 3, 5}));
    EXPECT_TRUE(arcGraph->GetPrevVertices(5) == std::vector<int>({4}));

    delete arcGraph;
}