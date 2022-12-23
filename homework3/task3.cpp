#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const = 0;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
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

int dijkstra(const IGraph &graph, int from, int to) {
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
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(std::pair<int, int>(cur.first + elem.first, elem.second));
            } else if (distances[elem.second] > cur.first + elem.first) {
                priorityQueue.erase(std::pair<int, int>(distances[elem.second], elem.second));
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(std::pair<int, int>(cur.first + elem.first, elem.second));
            }
        }
    }

    return priorityQueue.begin()->first;
}

void task(std::istream &input, std::ostream &output) {
    int n = 0, m = 0;
    input >> n;
    input >> m;

    IGraph *graph = new ListGraph(n);

    for (int i = 0; i < m; ++i) {
        int from = 0, to = 0, weight = 0;

        input >> from >> to >> weight;

        graph->AddEdge(from, to, weight);
        graph->AddEdge(to, from, weight);
    }

    int from = 0, to = 0;
    input >> from >> to;

    std::cout << dijkstra(*graph, from, to) << std::endl;
    delete graph;
}

int main(void) {
    task(std::cin, std::cout);
    return 0;
}