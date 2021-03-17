#include "bits/stdc++.h"

using namespace std;
#define inti long long
#define ll long long
const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t mod = 1e9 + 7;
const int32_t MM = 998244353;

struct pt
{
    inti x;
    inti y;
    bool operator<(pt &p)
    {
        if (p.x == x)
        {
            return y < p.y;
        }
        return x < p.x;
    }
    bool operator==(pt &p)
    {
        return p.x == x and p.y == y;
    }
};

int direc(pt a, pt b, pt c)
{
    //alpha-beta=0
    //alpha-beeta>0 clockwise move karega
    //alpha-beta<0 anticlockwise move karega
    inti alpha_minus_beeta = a.x * (b.y - c.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y);

    return alpha_minus_beeta == 0 ? 0 : (alpha_minus_beeta > 0) ? 1
                                                                : -1;
}
void convex_hull_grahm_scan(vector<pt> &v)
{
    if (v.size() <= 2)
    {
        return;
    }
    sort(v.begin(), v.end()); // O(NLOGN)
    inti n = v.size();
    pt p1, p2;
    p1 = v[0];
    p2 = v[n - 1];

    vector<pt> upper, down;
    upper.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)v.size(); i++) //O(N)
    {
        int check = direc(p1, v[i], p2); //O(1)
        if (check != -1)
        {
            //upper half;
            inti sz = upper.size();
            while (sz >= 2 and direc(upper[sz - 2], upper[sz - 1], v[i]) == -1)
            {
                upper.pop_back();
                sz = upper.size();
            }
            upper.push_back(v[i]);
        }
        else if (check != 1)
        {
            //lower half;
            inti sz = down.size();
            while (sz >= 2 and direc(down[sz - 2], down[sz - 1], v[i]) == 1)
            {
                down.pop_back();
                sz = down.size();
            }
            down.push_back(v[i]);
        }
    }
    v.clear();
    for (int i = 0; i < upper.size(); i++)
    {
        v.push_back(upper[i]);
    }
    for (int i = 0; i < down.size(); i++)
    {
        v.push_back(down[i]);
    }
    //remove redundency;
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // memset(prime, true, sizeof(prime));
    //primes(); // primes under 1lakh

    /*
  #ifdef NCR
        init();
    #endif
*/

    //take total number of point
    inti n;
    cin >> n;
    vector<pt> v_of_points(n);
    //take values;
    for (int i = 0; i < n; i++)
    {
        inti x, y;
        cin >> x;
        cin >> y;
        v_of_points[i].x = x;
        v_of_points[i].y = y;
    }
    convex_hull_grahm_scan(v_of_points);
    for (int i = 0; i < v_of_points.size(); i++)
    {
        cout << v_of_points[i].x << " " << v_of_points[i].y << endl;
    }
    cout << endl;
}
//time complexity O(Nlog(N));