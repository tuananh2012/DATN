#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> point;
vector<pair<int, double>> adj[10000];
long long radius = 100000;
long long EuclidDistance(pair<int, int> x, pair<int, int> y)
{
    return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}
double dientichcungtron(double x)
{
    if (x >= radius)
        return 0;
    double alpha = acos((double)x / radius);
    return (alpha * radius - sin(alpha) * x) * radius;
}
void clear(int nbPoint)
{
    point.clear();
    for (int i = 0; i < nbPoint; i++)
    {
        adj[i].clear();
    }
}
set<int> solve(int nbPoint, double threshold){
    set<int> ans;
    bool ok = 0;
    double cur = 0;
    for (int i = 0; i < nbPoint; i++)
    {
        if(adj[i].size() == 0 || (adj[i].size() == 1 && adj[adj[i][0].first].size() > 1)){
            ans.insert(i);
            cur += 1;
        }
    }
    


}
int main()
{
    long long radius2 = radius * radius;
    freopen("dataServer.txt", "r", stdin);
    int test;
    cin >> test;
    while (test--)
    {
        int numOfPoint;
        cin >> numOfPoint;
        for (int i = 0; i < numOfPoint; i++)
        {
            int x, y;
            cin >> x >> y;
            point.push_back({x, y});
        }
        for (int i = 0; i < numOfPoint; i++)
        {
            for (int j = 0; j < numOfPoint; j++)
            {
                if (i != j)
                {
                    long long dis = EuclidDistance(point[i], point[j]);
                    if (dis < radius2)
                    {
                        adj[i].push_back({j, dientichcungtron(sqrt(dis) / 2)});
                        adj[j].push_back({i, dientichcungtron(sqrt(dis) / 2)});
                    }
                }
            }
        }
    }
}