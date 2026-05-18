#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void add_edge(Graph& g, int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

std::vector<int> bfs(Graph& graph, int root, int goal) {
  std::queue<int> q;
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> parent(graph.size(), -1);
  q.push(root);
  visited[root] = true;
  while (q.size() != 0) {
    int v = q.front();
    if (v == goal) {
      break;
    }
    q.pop();

    for (auto e : graph[v]) {
      if (!visited[e]) {
        visited[e] = true;
        parent[e] = v;
        q.push(e);
      }
    }
  }

  if (!visited[goal]) {
    return {};
  }

  std::vector<int> path;

  for (int cur = goal; cur != -1; cur = parent[cur]) {
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());

  return path;
}

std::vector<int> dfs(Graph& graph, int root, int goal) {
  std::stack<int> st;
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> parent(graph.size(), -1);
  st.push(root);
  visited[root] = true;
  while (st.size() != 0) {
    int v = st.top();
    if (v == goal) {
      break;
    }
    st.pop();

    for (auto it = graph[v].rbegin(); it != graph[v].rend(); ++it) {
      int e = *it;

      if (!visited[e]) {
        visited[e] = true;
        parent[e] = v;
        st.push(e);
      }
    }
  }

  if (!visited[goal]) {
    return {};
  }

  std::vector<int> path;

  for (int cur = goal; cur != -1; cur = parent[cur]) {
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());

  return path;
}

void dfs_ts(Graph& graph, int root, int& current_label, std::vector<int>& s,
            std::vector<bool>& visited) {
  visited[root] = true;

  for (auto it = graph[root].rbegin(); it != graph[root].rend(); ++it) {
    int e = *it;
    if (!visited[e]) {
      dfs_ts(graph, e, current_label, s, visited);
    }
  }
  s[root] = current_label;
  current_label--;
}

std::vector<int> topological_sort(Graph& graph) {
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> s(graph.size());
  int current_label = graph.size() - 1;
  for (int i = 0; i < graph.size(); i++) {
    if (!visited[i]) {
      dfs_ts(graph, i, current_label, s, visited);
    }
  }

  std::vector<int> order(s.size());

  for (int v = 0; v < static_cast<int>(s.size()); ++v) {
    order[s[v]] = v;
  }

  return order;
}

template <typename T>
void print(const T& t) {
  if (t.size() == 0) {
    std::cout << "empty" << std::endl;
  }
  for (auto a : t) {
    std::cout << a << ' ';
  }
  std::cout << std::endl;
}

int main() {
  {
    int n = 4;
    Graph graph(n);

    add_edge(graph, 0, 1);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 0);
    bfs(graph, 0, 3);
    dfs(graph, 0, 3);
    // std::cout <<  << std::endl;
  }

  {
    Graph graph = {
        {1, 2},  // 0
        {3},     // 1
        {5},     // 2
        {5},     // 3
        {},      // 4
        {}       // 5
    };

    auto bfs_result = bfs(graph, 0, 5);
    auto dfs_result = dfs(graph, 0, 5);
    auto ts_result = topological_sort(graph);

    std::cout << "BFS path: " << std::endl << '\t';
    print(bfs_result);
    std::cout << "DFS path: " << std::endl << '\t';
    print(dfs_result);

    std::cout << "Topological sort: " << std::endl << '\t';
    print(ts_result);
  }
  return 0;
}