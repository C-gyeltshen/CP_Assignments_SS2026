#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

// Represents a directed weighted edge
struct Edge {
    int u, v, weight;
};

static const long long INF = std::numeric_limits<long long>::max();

// ── Bellman-Ford ──────────────────────────────────────────────

bool bellmanFord(int V,
                 const std::vector<Edge>& edges,
                 int src,
                 std::vector<long long>& dist)
{
    dist.assign(V, INF);
    dist[src] = 0;

    // ── Phase 1: Relax all edges V-1 times ───────────────────
    for (int iter = 0; iter < V - 1; ++iter) {
        bool updated = false;
        for (const auto& e : edges) {
            if (dist[e.u] != INF &&
                dist[e.u] + e.weight < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.weight;
                updated = true;
            }
        }
        // Early exit if no update in this pass
        if (!updated) break;
    }

    // ── Phase 2: Detect negative cycles ──────────────────────

    bool hasNegCycle = false;
    for (int iter = 0; iter < V; ++iter) {          // run V more times
        for (const auto& e : edges) {
            if (dist[e.u] != INF &&
                dist[e.u] + e.weight < dist[e.v])
            {
                dist[e.v] = -INF;   // mark as "negatively infinite"
                hasNegCycle = true;
            }
        }
    }

    return !hasNegCycle;
}

// ── main ──────────────────────────────────────────────────────
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int V, E;
    std::cout << "Enter V (vertices) and E (edges): ";
    std::cin >> V >> E;

    std::vector<Edge> edges(E);
    std::cout << "Enter each edge as: u v w\n";
    for (auto& e : edges) std::cin >> e.u >> e.v >> e.weight;

    int src;
    std::cout << "Enter source vertex (0-indexed): ";
    std::cin >> src;

    std::vector<long long> dist;
    bool noCycle = bellmanFord(V, edges, src, dist);

    // ── Output ────────────────────────────────────────────────
    std::cout << "\nShortest distances from vertex " << src << ":\n";
    std::cout << std::left << std::setw(10) << "Vertex"
              << std::setw(20) << "Distance" << '\n';
    std::cout << std::string(30, '-') << '\n';

    for (int i = 0; i < V; ++i) {
        std::cout << std::setw(10) << i;
        if (dist[i] == INF)       std::cout << "Unreachable\n";
        else if (dist[i] == -INF) std::cout << "-INF (negative cycle)\n";
        else                      std::cout << dist[i] << '\n';
    }

    if (!noCycle)
        std::cout << "\n[WARNING] Negative-weight cycle DETECTED "
                     "in the graph.\n";
    else
        std::cout << "\nNo negative-weight cycle detected.\n";

    return 0;
}

