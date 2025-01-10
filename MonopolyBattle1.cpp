#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 100;
const int INF = INT_MAX;

// Custom matrix multiplication using min-max operations
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, int N) {
    vector<vector<int>> C(N, vector<int>(N, INF));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (A[i][k] < INF && B[k][j] < INF) {
                    // Min-max operation: min for path, max for time
                    C[i][j] = min(C[i][j], max(A[i][k], B[k][j]));
                }
            }
        }
    }
    return C;
}

// Matrix exponentiation with custom min-max operations
vector<vector<int>> matrixExpo(vector<vector<int>>& mat, int exp, int N) {
    vector<vector<int>> result(N, vector<int>(N, INF));

    // Initialize the result as the identity matrix
    for (int i = 0; i < N; ++i) {
        result[i][i] = 0;
    }

    // Perform matrix exponentiation
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matrixMultiply(result, mat, N);
        }
        mat = matrixMultiply(mat, mat, N);
        exp /= 2;
    }
    return result;
}

int main() {
    int N, T, L;
    cin >> N >> T >> L;

    // Initialize the adjacency matrix with INF (no path)
    vector<vector<int>> adj(N, vector<int>(N, INF));

    // Process each turn and update the adjacency matrix
    for (int t = 1; t <= T; ++t) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Convert to 0-based indexing

        // Update the adjacency matrix with the minimum timestamp
        adj[u][v] = min(adj[u][v], t);
    }

    // Use matrix exponentiation to calculate the reachability matrix for exactly L steps
    vector<vector<int>> reach = matrixExpo(adj, L, N);

    // Output the results
    for (int i = 0; i < N; ++i) {
        if (reach[0][i] < INF) {
            cout << reach[0][i] << " ";
        } else {
            cout << -1 << " ";
        }
    }
    cout << endl;

    return 0;
}
