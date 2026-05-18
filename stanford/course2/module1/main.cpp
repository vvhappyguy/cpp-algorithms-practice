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

    std::cout << "BFS path: " << std::endl << '\t';
    print(bfs_result);
    std::cout << "DFS path: " << std::endl << '\t';
    print(dfs_result);
  }
  return 0;
}