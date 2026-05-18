#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using graph = std::vector<std::vector<int>>;

void s_t(graph& list, int s, int t) {}

void add_edge(graph& g, int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

int count_active(const std::vector<bool>& active) {
  return std::count(active.cbegin(), active.cend(), true);
}

std::pair<int, int> random_edge(const graph& graph,
                                const std::vector<bool>& active,
                                std::mt19937& rng) {
  std::vector<std::pair<int, int>> edges;

  for (int u = 0; u < static_cast<int>(graph.size()); ++u) {
    if (!active[u]) {
      continue;
    }

    for (int v : graph[u]) {
      if (active[v]) {
        edges.push_back({u, v});
      }
    }
  }

  std::uniform_int_distribution<int> dist(0,
                                          static_cast<int>(edges.size()) - 1);
  return edges[dist(rng)];
}

int min_cut(graph list, std::mt19937& rng) {

  // Setup active list
  std::vector<bool> active(list.size());
  for (int i = 0; i < list.size(); i++) {
    if (list[i].size() > 0) {
      active[i] = true;
    }
  }

  while (count_active(active) > 2) {
    // 1. Choose cut
    auto [keep, remove] = random_edge(list, active, rng);

    // 2. Move from cutted to keep
    for (int i = 0; i < list[remove].size(); i++) {
      list[keep].push_back(list[remove][i]);
    }

    // 3. Change remove to keep
    for (int i = 0; i < list.size(); i++) {
      for (int j = 0; j < list[i].size(); j++) {
        if (active[i] == true) {
          if (list[i][j] == remove) {
            list[i][j] = keep;
          }
        }
      }
    }

    // 4. Remove duplicates
    auto& l = list[keep];
    l.erase(std::remove(l.begin(), l.end(), keep), l.end());

    active[remove] = false;
    list[remove].clear();
  }

  for (int u = 0; u < static_cast<int>(list.size()); ++u) {
    if (active[u]) {
      return static_cast<int>(list[u].size());
    }
  }

  return 0;
}

int min_cut_iter(graph& list, int iterations) {
    std::random_device rd;
    std::mt19937 rng(rd());
  int result = std::numeric_limits<int>::max();

  for (int i = 0; i < iterations; i++) {
    result = std::min(result, min_cut(list, rng));
    // std::cout << result << ' ';
  }
  //   std::cout << std::endl;
  return result;
}

graph read_graph_from_stdin(int n) {
  graph g(n);

  std::string line;

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }

    std::istringstream iss(line);

    int u;
    iss >> u;
    --u;  // labels 1..200 -> indexes 0..199

    int v;
    while (iss >> v) {
      --v;
      g[u].push_back(v);
    }
  }

  return g;
}

int main() {
  {
    int n = 200;
    graph graph = read_graph_from_stdin(n);
    std::cout << "Start" << std::endl;
    std::cout << min_cut_iter(graph, 1000) << std::endl;
    std::cout << "End" << std::endl;
  }

//   {
//     int n = 4;
//     graph graph(n);

//     add_edge(graph, 0, 1);
//     add_edge(graph, 1, 2);
//     add_edge(graph, 2, 3);
//     add_edge(graph, 3, 0);
//     std::cout << min_cut(graph) << std::endl;
//     std::cout << min_cut_iter(graph, 100) << std::endl;
//   }

//   {
//     int n = 4;
//     graph graph(n);

//     add_edge(graph, 0, 1);
//     add_edge(graph, 0, 2);
//     add_edge(graph, 1, 3);
//     std::cout << min_cut(graph) << std::endl;
//     std::cout << min_cut_iter(graph, 100) << std::endl;
//   }

//   {
//     int n = 16;
//     graph g(n);

//     // Left cluster: complete graph K8 on vertices 0..7
//     for (int u = 0; u <= 7; ++u) {
//       for (int v = u + 1; v <= 7; ++v) {
//         add_edge(g, u, v);
//       }
//     }

//     // Right cluster: complete graph K8 on vertices 8..15
//     for (int u = 8; u <= 15; ++u) {
//       for (int v = u + 1; v <= 15; ++v) {
//         add_edge(g, u, v);
//       }
//     }

//     // Only 3 edges between clusters
//     add_edge(g, 0, 8);
//     add_edge(g, 1, 9);
//     add_edge(g, 2, 10);

//     std::cout << min_cut_iter(g, 1000) << std::endl;
//   }

//   {
//     int n = 20;
//     graph g(n);

//     // First cluster: K10 on 0..9
//     for (int u = 0; u <= 9; ++u) {
//       for (int v = u + 1; v <= 9; ++v) {
//         add_edge(g, u, v);
//       }
//     }

//     // Second cluster: K10 on 10..19
//     for (int u = 10; u <= 19; ++u) {
//       for (int v = u + 1; v <= 19; ++v) {
//         add_edge(g, u, v);
//       }
//     }

//     // 5 bridge edges between clusters
//     add_edge(g, 0, 10);
//     add_edge(g, 1, 11);
//     add_edge(g, 2, 12);
//     add_edge(g, 3, 13);
//     add_edge(g, 4, 14);

//     std::cout << min_cut_iter(g, 5000) << std::endl;
//   }

  return 0;
}