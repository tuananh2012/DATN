#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> point;
vector<pair<int, long long>> adj[10000];
long long radius = 100000;
long long EuclidDistance(pair<int,int> x, pair<int,int> y){
    return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}
double dientichcungtron(int x){
    if(x >= radius) return 0;
    double alpha = acos((double)x/radius);
    return (alpha * radius  - sin(alpha) * x )* radius;
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
        for(int i = 0; i < numOfPoint;i++){
            for(int j = 0; j < numOfPoint;j++){
                if(i != j && EuclidDistance(point[i],point[j]) < radius * radius){
                    adj[i].push_back()
                }
            }
        }
    }
}