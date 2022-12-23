#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    ListGraph(int count);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;

 private:
    std::vector<std::vector<int>> graph;
};

ListGraph::ListGraph(int count) { graph.resize(count); }

void ListGraph::AddEdge(int from, int to) { graph[from].push_back(to); }

int ListGraph::VerticesCount() const { return graph.size(); }

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return graph[vertex];
}

int dfs_recur(const IGraph &gr, int vertex, std::vector<bool> &visited) {
    visited[vertex] = true;
    int count = 1;

    std::vector<int> next = gr.GetNextVertices(vertex);

    for (const auto &cur : next) {
        if (!visited[cur]) {
            count += dfs_recur(gr, cur, visited);
        }
    }

    return count;
}

bool dfs(const IGraph &gr) {
    int vertices = gr.VerticesCount();
    std::vector<bool> visited(vertices, false);

    return dfs_recur(gr, 0, visited) == vertices;
}

void task(std::istream &input, std::ostream &output) {
    int n = 0, m = 0;
    input >> n;
    input >> m;

    if (m != n - 1) {
        std::cout << 0 << std::endl;
        return;
    }

    IGraph *graph = new ListGraph(n);

    for (int i = 0; i < m; ++i) {
        int from = 0, to = 0;

        input >> from >> to;

        graph->AddEdge(from, to);
        graph->AddEdge(to, from);
    }

    std::cout << dfs(*graph) << std::endl;
    delete graph;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}