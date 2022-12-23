#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#define VISITED 1
#define NOT_VISITED 0

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

int bfs(const IGraph &graph, int from, int to) {
    std::vector<std::pair<int, int>> visited(graph.VerticesCount(), std::pair<int, int>(NOT_VISITED, 0));
    std::queue<int> q;

    q.push(from);
    visited[from] = std::pair<int, int>(0, 1);

    while (!q.empty()) {
        int cur = q.front();

        if (cur == to) {
            break;
        }

        q.pop();
        std::vector<int> next = graph.GetNextVertices(cur);

        for (int i = 0; i < next.size(); ++i) {
            if (visited[next[i]].first == NOT_VISITED) {
                q.push(next[i]);
                visited[next[i]].first = visited[cur].first + 1;
                visited[next[i]].second = visited[cur].second;
            } else if (visited[next[i]].first >= 0) {
                if (visited[next[i]].first == visited[cur].first + 1) {
                    visited[next[i]].second += visited[cur].second;
                } else if (visited[next[i]].first > visited[cur].first + 1) {
                    visited[next[i]].first = visited[cur].first + 1;
                    visited[next[i]].second += visited[cur].second;
                }
            }
        }

        visited[cur].first = VISITED;
    }

    return visited[to].second;
}

void task(std::istream &input, std::ostream &output) {
    int v = 0, n = 0;
    input >> v;
    input >> n;

    IGraph *graph = new ListGraph(v);

    for (int i = 0; i < n; ++i) {
        int from = 0, to = 0;

        input >> from >> to;

        graph->AddEdge(from, to);
        graph->AddEdge(to, from);
    }

    int u = 0, w = 0;
    input >> u >> w;

    std::cout << bfs(*graph, u, w) << std::endl;
    delete graph;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}