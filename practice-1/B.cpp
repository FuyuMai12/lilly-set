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
    int hasMultipleTests = 0;

    const int MOD = 1000000007;

    string s;
    int k;
    vector<string> a;
    
    void Preprocess() {
        
    }

    void Input(int testcase) {
        cin >> s >> k;
        read1d(a, k);
    }

    void Solve(int testcase) {
        const i64 BASELL = 31LL;
        const int HASH_MOD = MOD;

        k = 0;
        int n = s.size();
        vector<int> hash_vals[n+1];
        for (auto &t: a) {
            if (t.size() > n) continue;
            int hash_val = 0;
            for (auto &c: t) {
                hash_val = (BASELL * hash_val + (c - 'a')) % HASH_MOD;
            }

            hash_vals[t.size()].emplace_back(hash_val);
        }

        for (int i=1; i<=n; i++) sort(hash_vals[i].begin(), hash_vals[i].end());

        vector<int> dp(n+1, 0);
        dp[0] = 1;

        for (int i=0; i<n; i++) {

            int hash_val = 0;

            for (int len=1; i+len<=n; len++) {
                int j = i + len;
                hash_val = (BASELL * hash_val + (s[i+len-1] - 'a')) % HASH_MOD;

                auto it = lower_bound(hash_vals[len].begin(), hash_vals[len].end(), hash_val);

                if (it == hash_vals[len].end()) continue;
                if (*it != hash_val) continue;
                dp[j] = (dp[i] + dp[j]) % MOD;
            }
        }

        cout << dp[n] << endl;
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
