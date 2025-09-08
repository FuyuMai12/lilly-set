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

    int n;
    vector<int> a;
    
    void Preprocess() {
        
    }

    void Input(int testcase) {
        cin >> n;
        read1d(a, n);
    }

    void Solve(int testcase) {
        map<i64, vector<pair<int, int>>> mp;
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                mp[a[i]+a[j]].emplace_back(make_pair(i, j));
            }
        }

        map<i64, vector<int>> common_indices;
        for (auto it=mp.begin(); it!=mp.end(); it++) {
            i64 val = it->first;
            common_indices[val].emplace_back(mp[val][0].first);
            common_indices[val].emplace_back(mp[val][0].second);
            if (mp[val].size() > 1) {
                for (int i=1; i<mp[val].size(); i++) {
                    if (common_indices[val].size() > 1 && 
                        common_indices[val][1] != mp[val][i].first &&
                        common_indices[val][1] != mp[val][i].second) {
                        common_indices[val].erase(common_indices[val].begin()+1);
                    }
                    if (common_indices[val].size() > 0 && 
                        common_indices[val][0] != mp[val][i].first &&
                        common_indices[val][0] != mp[val][i].second) {
                        common_indices[val].erase(common_indices[val].begin());
                    }
                }
            }
        }

        int ans = 0;
        for (int p=0; p<n; p++) {
            i64 sum = 3LL * a[p];
            for (int i=0; i<n; i++) {
                i64 demanded = sum - a[i];
                if (mp.find(demanded) == mp.end()) continue;
                
                if (find(common_indices[demanded].begin(), common_indices[demanded].end(), i) != common_indices[demanded].end()) {
                    continue;
                }

                ans++; break;
            }
        }
        cout << ans << endl;
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
