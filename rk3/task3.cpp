#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const = 0;
    virtual std::vector<std::pair<int, int>>
    GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    ListGraph(int count);

    void AddEdge(int from, int to, int weight) override;
    int VerticesCount() const override;
    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;

 private:
    std::vector<std::vector<std::pair<int, int>>> graph;
};

ListGraph::ListGraph(int count) { graph.resize(count); }

void ListGraph::AddEdge(int from, int to, int weight) {
    graph[from].push_back(std::pair<int, int>(weight, to));
}

int ListGraph::VerticesCount() const { return graph.size(); }

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    return graph[vertex];
}

int dijkstra(const IGraph &graph, int from, int to, int k) {
    std::vector<int> prices(graph.VerticesCount(), -1);
    std::vector<int> distances(graph.VerticesCount(), -1);
    std::set<std::pair<int, int>> priorityQueue;

    distances[from] = 0;
    priorityQueue.insert(std::pair<int, int>(0, from));

    while (!priorityQueue.empty()) {
        auto cur = *priorityQueue.begin();

        if (cur.second == to) {
            break;
        }

        priorityQueue.erase(cur);

        for (auto &elem : graph.GetNextVertices(cur.second)) {
            if (distances[elem.second] == -1) {
                prices[elem.second] = cur.second;
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(std::pair<int, int>(cur.first + elem.first, elem.second));
            } else if (distances[elem.second] > cur.first + elem.first) {
                prices[elem.second] = cur.second;
                priorityQueue.erase(std::pair<int, int>(distances[elem.second], elem.second));
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(std::pair<int, int>(cur.first + elem.first, elem.second));
            }
        }
    }

    int count = 0;
    int cur = to;
    while (cur != from && count < k) {
        cur = prices[cur];
        ++count;
    }

    if (cur != from) {
        return -1;
    }

    return priorityQueue.begin()->first;
}

void task(std::istream &input, std::ostream &output) {
    int n = 0, m = 0, k = 0, s = 0, f = 0;
    input >> n >> m >> k >> s >> f;

    IGraph *graph = new ListGraph(n);

    for (int i = 0; i < m; ++i) {
        int from = 0, to = 0, weight = 0;

        input >> from >> to >> weight;
        graph->AddEdge(from - 1, to - 1, weight);
    }

    std::cout << dijkstra(*graph, s - 1, f - 1, k) << std::endl;
    delete graph;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}