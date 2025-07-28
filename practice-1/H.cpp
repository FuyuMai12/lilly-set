// re:Re::set ~ [homu]lilly::set

/******************************************** [  APPENDIXES  ] *********************************************/
#pragma GCC optimize("O3,unroll-loops")
#include <string>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using i64  = long long;
using f64  = long double;
const long double PI   = 3.141592653589793116L;
const long double EPS  = 0.000000000001L;
const long double GOLD = ((1.0L+sqrt(5.0L))/2.0L);
mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void readadj(vector<vector<int>> &adj, int vertex, int edge);
template <typename T> void readwadj(vector<vector<pair<int, T>>> &adj, int vertex, int edge);
template <typename T> void read1d(vector<T> &vec, int dim);
template <typename T> void read2d(vector<vector<T>> &vec, int dim1, int dim2);
template <typename T> void write1d(vector<T> &vec);
template <typename T> void write2d(vector<vector<T>> &vec);
/***********************************************************************************************************/

/***************************************** [      SOLUTION       ] *****************************************/
namespace solution {
    int hasMultipleTests = 1;

    int a, b;
    
    void Preprocess() {
        
    }

    void Input(int testcase) {
        cin >> a >> b;
    }

    void Solve(int testcase) {
        int d = abs(a - b);

        for (int k=0; k<=45000; k++) {
            int s = k * (k + 1) / 2;
            
            if (s < d) continue;

            if ((s & 1) == (d & 1)) {cout << k << endl; return;}
        }

        exit(2226);
    }
}
/***********************************************************************************************************/

/***************************************** [        MAIN         ] *****************************************/
int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solution::Preprocess();
    
    int T = 1;
    if (solution::hasMultipleTests) {cin >> T; cin.ignore();}
    for (int testcase=1; testcase<=T; testcase++) {
        solution::Input(testcase); solution::Solve(testcase);
    }
    
    return 0;
}
/***********************************************************************************************************/

template <typename T> void read1d(vector<T> &vec, int dim) {
    vec.clear(); vec.resize(dim);
    for (auto &z: vec) cin >> z;
}

template <typename T> void read2d(vector<vector<T>> &vec, int dim1, int dim2) {
    vec.clear(); vec.resize(dim1, vector<T>(dim2));
    for (auto &row: vec) for (auto &z: row) cin >> z;
}

template <typename T> void write1d(vector<T> &vec) {
    for (auto &z: vec) cout << z << " "; cout << endl;
}

template <typename T> void write2d(vector<vector<T>> &vec) {
    for (auto &row: vec) write1d(row);
}

void readadj(vector<vector<int>> &adj, int vertex, int edge) {
    adj.clear(); adj.resize(vertex);
    for (int i=0; i<edge; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
}

template <typename T> void readwadj(vector<vector<pair<int, T>>> &adj, int vertex, int edge) {
    adj.clear(); adj.resize(vertex);
    for (int i=0; i<edge; i++) {
        int u, v; T w;
        cin >> u >> v >> w; u--; v--;
        adj[u].emplace_back(make_pair(v, w));
        adj[v].emplace_back(make_pair(u, w));
    }
}
