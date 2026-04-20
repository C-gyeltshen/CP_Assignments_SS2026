#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

static const long long INF = 1e18;   // "infinity" sentinel

// ── Floyd-Warshall ────────────────────────────────────────────
// dist[i][j] = shortest path weight from i to j.
// Returns true if NO negative cycle exists.
bool floydWarshall(int V, std::vector<std::vector<long long>>& dist)
{
    // Core triple-nested loop
    for (int k = 0; k < V; ++k)            // intermediate vertex
        for (int i = 0; i < V; ++i)        // source
            for (int j = 0; j < V; ++j)    // destination
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = std::min(dist[i][j],
                                          dist[i][k] + dist[k][j]);

    // Negative cycle: if any dist[i][i] < 0, a negative cycle
    // passes through vertex i.
    for (int i = 0; i < V; ++i)
        if (dist[i][i] < 0) return false;

    return true;
}

// ── Print the distance matrix ─────────────────────────────────
void printMatrix(int V,
                 const std::vector<std::vector<long long>>& dist)
{
    const int W = 12;   // column width
    std::cout << "\nDistance matrix (INF = unreachable):\n\n";

    // Header row
    std::cout << std::setw(W) << " ";
    for (int j = 0; j < V; ++j)
        std::cout << std::setw(W) << ("v" + std::to_string(j));
    std::cout << '\n' << std::string(W * (V + 1), '-') << '\n';

    for (int i = 0; i < V; ++i) {
        std::cout << std::setw(W) << ("v" + std::to_string(i));
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] >= INF / 2) std::cout << std::setw(W) << "INF";
            else                        std::cout << std::setw(W) << dist[i][j];
        }
        std::cout << '\n';
    }
}

// ── main ──────────────────────────────────────────────────────
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int V, E;
    std::cout << "Enter V (vertices) and E (edges): ";
    std::cin >> V >> E;

    // Initialise distance matrix
    std::vector<std::vector<long long>> dist(V,
        std::vector<long long>(V, INF));

    for (int i = 0; i < V; ++i) dist[i][i] = 0;   // self-distance = 0

    std::cout << "Enter each edge as: u v w\n";
    for (int i = 0; i < E; ++i) {
        int u, v; long long w;
        std::cin >> u >> v >> w;
        // Keep minimum weight for parallel edges
        dist[u][v] = std::min(dist[u][v], w);
    }

    bool ok = floydWarshall(V, dist);

    printMatrix(V, dist);

    if (!ok)
        std::cout << "\n[WARNING] Negative-weight cycle DETECTED. "
                     "Some distances are invalid.\n";
    else
        std::cout << "\nNo negative-weight cycle detected.\n";

    return 0;
}
