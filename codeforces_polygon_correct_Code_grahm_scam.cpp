
#include <bits/stdc++.h>

using namespace std;

#define inti long long int
#define ld long double
#define F first
#define S second
#define P pair<int, int>
#define pb push_back

const inti N = 100005;

struct point
{
    inti x, y;
    bool operator<(point &O)
    {
        return (x < O.x) || (x == O.x && y < O.y);
    }
    bool operator==(point &O)
    {
        return (x == O.x && y == O.y);
    }
};

bool cw(point a, point b, point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

bool ccw(point a, point b, point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool collinear(point a, point b, point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) == 0;
}

void convex_hull(vector<point> &p)
{
    if (p.size() <= 2)
        return;
    sort(p.begin(), p.end());

    inti i, n = p.size();
    point p1 = p[0], p2 = p[n - 1];
    // up contains points of upper convex hull
    // down contains points of lower convex hull
    vector<point> up, down;
    up.pb(p1);
    down.pb(p1);

    for (i = 1; i < n; i++)
    {
        if (i == n - 1 || !ccw(p1, p[i], p2))
        {
            // upper half and last point considered
            while (up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], p[i]))
            {
                up.pop_back();
            }
            up.pb(p[i]);
        }
        if (i == n - 1 || !cw(p1, p[i], p2))
        {
            // lower half ans last point considered
            while (down.size() >= 2 && cw(down[down.size() - 2], down[down.size() - 1], p[i]))
            {
                down.pop_back();
            }
            down.pb(p[i]);
        }
    }
    // up and down vectors contains all the points of upper and lower conve hull
    // and including the points p1 and p2
    p.clear();
    for (i = 0; i < up.size(); i++)
    {
        p.pb(up[i]);
    }
    for (i = 0; i < down.size(); i++)
    {
        p.pb(down[i]);
    }
    // p contains all points (repeated included ) of convex hull
    sort(p.begin(), p.end());
    p.resize(unique(p.begin(), p.end()) - p.begin());
    // p contains all points of convex hull , collineaar included and no repeated
}

void solve()
{
    inti i, j, k, n, m, ans = 0, cnt = 0, sum = 0;
    cin >> n;
    vector<point> p(n);
    for (i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
    }
    cin >> m;
    map<pair<inti, inti>, inti> mp;
    for (i = 0; i < m; i++)
    {
        point temp;
        cin >> temp.x >> temp.y;
        mp[{temp.x, temp.y}]++;
        p.pb(temp);
    }
    // p vector cotains all n+m points
    // ie points of both the polygons
    convex_hull(p);
    // my vector p will contain all the points of convex hull only
    for (auto x : p)
    {
        // cout << x.x << " " << x.y << '\n';
        if (mp.count({x.x, x.y}))
        {
            cout << "NO";
            return;
        }
    }
    cout << "YES";
    return;
}
int main()
{
    //lets_do_it();
    // int t;cin>>t;while(t--)
    solve();
    return 0;
}
