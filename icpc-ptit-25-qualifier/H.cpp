// #Team4T's full template, by AkiLotus+iristran911.
// Powered by Alice Engine, credited to chocological.

/******************************************** [  APPENDIXES  ] *********************************************/
#pragma GCC optimize("Ofast,unroll-loops")
#include <string>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using i128 = __int128_t;
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
    int hasMultipleTests = 0;
    int interactive = 0;
    
    // Wake up, "Celia".
    // [homu]lilly::set().

    string s;
    
    void Preprocess() {
        
    }

    void Input(int testcase) {
        cin >> s;
    }

    void Solve(int testcase) {
        set<tuple<int, int, int>> prefixes;
        prefixes.insert(make_tuple(0, 0, 0));

        int n = s.size();
        int pxs = 0;
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i=0; i<n; i++) {
            pxs ^= (1 << (s[i] - 'a'));

            if (pxs == 0) dp[i + 1] = 1;

            for (int x=0; x<26; x++) {
                int demandedMask = pxs ^ (1 << x);
                auto it = prefixes.lower_bound(make_tuple(demandedMask, -1, -1));
                if (it == prefixes.end()) continue;
                if (get<0>(*it) != demandedMask) continue;

                int j = get<2>(*it);
                dp[i+1] = min(dp[i+1], dp[j] + 1);
            }

            prefixes.insert(make_tuple(pxs, dp[i+1], i+1));
        }
        cout << dp[n] << endl;
    }
}
/***********************************************************************************************************/

/***************************************** [        MAIN         ] *****************************************/
int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    if (!solution::interactive) cin.tie(NULL);

    #ifdef Alice
    solution::interactive *= -1;
    #endif
    
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
    for (auto &z: vec) cout << z << " ";
    cout << endl;
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
