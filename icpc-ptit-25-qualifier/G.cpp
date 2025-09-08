#include <bits/stdc++.h>
using namespace std;

const bool MULTI_TEST = false;

const int MAX_N = 2e5 + 5;
int n, m, k;
pair<int, int> p[MAX_N];
int lim_row[MAX_N], lim_col[MAX_N];
vector<int> block[MAX_N];

struct TSegmentTree
{
    int L[4 * MAX_N], H[4 * MAX_N], sum[4 * MAX_N];
    int leaf[MAX_N];

    void Build(int x, int low, int high)
    {
        L[x] = low;
        H[x] = high;
        if (low == high)
        {
            sum[x] = 0;
            leaf[low] = x;
        }
        else
        {
            int mid = (low + high) / 2;
            Build(2 * x, low, mid);
            Build(2 * x + 1, mid + 1, high);
            sum[x] = sum[2 * x] + sum[2 * x + 1];
        }
    }

    void Update(int k, int w)
    {
        int x = leaf[k];
        sum[x] = w;
        for (x /= 2; x > 0; x /= 2)
            sum[x] = sum[2 * x] + sum[2 * x + 1];
    }

    int qi, qj;
    int Request(int x)
    {
        if (H[x] < qi || L[x] > qj)
            return 0;
        if (qi <= L[x] && H[x] <= qj)
            return sum[x];
        return Request(2 * x) + Request(2 * x + 1);
    }

    int Query(int i, int j)
    {
        qi = i;
        qj = j;
        return Request(1);
    }
} ST;

void Input()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        lim_row[i] = m + 1;
        block[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        lim_col[i] = n + 1;
    }
    for (int i = 1; i <= k; i++) {
        cin >> p[i].first >> p[i].second;
        lim_row[p[i].first] = min(lim_row[p[i].first], p[i].second);
        lim_col[p[i].second] = min(lim_col[p[i].second], p[i].first);
        block[p[i].first].push_back(p[i].second);
    }
}

void Solve()
{
    ST.Build(1, 1, m);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (long long) (lim_row[i] - 1);
        if (lim_row[i] == 1) break;
    }

    int limc = m + 1;
    for (int i = 1; i <= m; i++) {
        ans += (long long) (lim_col[i] - 1);
        if (lim_col[i] == 1) {
            limc = i;
            break;
        }
    }

    long long intersect = 0;
    for (int i = 1; i <= n; i++) {
        int x = min(lim_row[i] - 1, limc - 1);
        if (lim_row[i] == 1) break;
        intersect += (long long) (x - ST.Query(1, x));
        for (int y : block[i]) {
            ST.Update(y, 1);
        }
    }
    ans -= intersect;
    cout << ans << '\n';
}

void Main()
{
    Input();
    Solve();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    if (fopen("input.txt", "r"))
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    if (MULTI_TEST)
    {
        int t;
        cin >> t;
        while (t--)
            Main();
    }
    else
        Main();
}
