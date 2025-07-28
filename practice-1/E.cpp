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

    vector<i64> list_of_zeroes;
    vector<i64> index_diffs;

    i64 n;
    
    void Preprocess() {
        list_of_zeroes.emplace_back(0); index_diffs.emplace_back(0);
        list_of_zeroes.emplace_back(1); index_diffs.emplace_back(0);
        list_of_zeroes.emplace_back(2); index_diffs.emplace_back(0);
        list_of_zeroes.emplace_back(3); index_diffs.emplace_back(0);
        list_of_zeroes.emplace_back(5); index_diffs.emplace_back(1);
        list_of_zeroes.emplace_back(8); index_diffs.emplace_back(2);
        
        i64 last_anomaly = 7LL;
        int length = 6;
        while (list_of_zeroes.back() <= 1000000000000000LL) {
            index_diffs.emplace_back(index_diffs.back());
            list_of_zeroes.emplace_back(list_of_zeroes.back() + 1 + index_diffs.back());

            while (last_anomaly + 3 <= list_of_zeroes[length]) {
                i64 latest_anomaly = (list_of_zeroes[length] % 3 == 0 ? list_of_zeroes[length] - 2
                    : list_of_zeroes[length] - list_of_zeroes[length] % 3 + 1);
                if (latest_anomaly > list_of_zeroes[length]) latest_anomaly -= 3;
                
                i64 step_forward = (latest_anomaly - last_anomaly) / 3;
                list_of_zeroes[length] += step_forward;
                index_diffs[length] += step_forward;

                last_anomaly = latest_anomaly;
            }

            length++;
        }

        const int LIMIT_3 = 50000;
        vector<int> grundy(LIMIT_3, 0);
        for (int x=4; x<LIMIT_3; x++) {
            set<int> s;
            for (int i=1; i*3<x; i++) {
                s.insert(grundy[x-i]);
            }
            while (s.find(grundy[x]) != s.end()) grundy[x]++;
        }

        vector<i64> list3;
        for (int i=0; i<LIMIT_3; i++) {
            if (!grundy[i]) list3.emplace_back(i);
        }

        for (int i=0; i<list3.size(); i++) assert(list3[i] == list_of_zeroes[i]);

        // write1d(list_of_zeroes);
        // write1d(index_diffs);

        // vector<i64> list2;
        // // vector<i64> diff2;
        // list2.emplace_back(0); list2.emplace_back(1); list2.emplace_back(2); list2.emplace_back(3); list2.emplace_back(5);
        // // diff2.emplace_back(0); diff2.emplace_back(0); diff2.emplace_back(0); diff2.emplace_back(0); diff2.emplace_back(1);
        // while (list2.back() <= 1000000000000000LL) {
        //     i64 lo = 1, hi = list2.back(), diff = LLONG_MAX;
        //     while (lo <= hi) {
        //         i64 x = lo + hi >> 1;
        //         if (x * 3 >= list2.back() + x) {diff = x; hi = x - 1;}
        //         else lo = x + 1;
        //     }

        //     list2.emplace_back(list2.back() + diff);
        //     // diff2.emplace_back(diff);
        // }

        // write1d(list2);
        // // write1d(diff2);

        // assert(list_of_zeroes == list2);
    }

    void Input(int testcase) {
        // cin >> n;
        n = testcase;
    }

    void Solve(int testcase) {
        if (n < 4) {cout << n << endl; return;}

        int i = lower_bound(list_of_zeroes.begin(), list_of_zeroes.end(), n) - list_of_zeroes.begin();
        // cout << "i = " << i << " => ";
        if (list_of_zeroes[i] == n) cout << n << endl;
        else cout << n - list_of_zeroes[i-1] << endl;
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
