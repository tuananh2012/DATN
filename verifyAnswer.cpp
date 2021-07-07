#include<bits/stdc++.h>
#include"DATN_Library.cpp"
using namespace std;
using namespace DATN;
#define ll long long

const ll length = 10000000;// length of the road
const ll width = 25000;// width of the road
const ll radius = 100000; // R_0
const int k_max = 50;
vector<double> le{0},ri{25000},lambda{0.0000000001};
vector<pair<ll,ll>> generateRandom(int numOfPoints){
    vector<pair<ll,ll>> ans(numOfPoints);
    random_device rd;
  /* Random number generator */
  default_random_engine generator(rd());
  /* Distribution on which to apply the generator */
  uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    for (int i = 0; i < numOfPoints; i++) {
      int x = distribution(generator) % (radius * 2 + width);
      int y = distribution(generator) % (length  - 2 * radius);
      x -= radius;
      y += radius;
      ans[i] = {x,y};
  }
  return ans;
}

double calcProbability(double x, vector<double> p){
    double ans = 0;
    for(int i = 0; i < le.size();i++){
        ans += p[i] * lambda[i] * Basic_computation::calculateAreaInRoad(abs(x-le[i]),abs(x-ri[i]),radius,ri[i]-le[i]);
    }
   // cout << ans << endl;
    return 1-exp(-ans);
}
double f(vector<double> p)
{
    double low = -100000;
    double high = 125000;
    return Integration::squareIntegral(low, high, calcProbability, p, 1) / (2 * radius + width);
}
int main(){
    srand(time(NULL));
    int num = 500;
    ll ans = 0;
    auto p = generateRandom(num);
    freopen("data.txt","r",stdin);
    int test;
    
    cin >> test;
    ll res = num * test;
    while (test--)  
    {
        int n;
        vector<bool> vis(num,0);
        cin >> n;
        while (n--)
        {
            ll x,y;
            cin >> x >> y;
            for(int i = 0; i < num;i++){
                if((x-p[i].first) * (x-p[i].first) + (y-p[i].second) * (y-p[i].second) <= radius * radius){
                    vis[i] = 1;
                }
            }
        }
        int cur = 0;
        for (int i = 0; i < num; i++)
        {
            if(vis[i]) cur++;
        }
        // cout << cur << endl;
        ans += cur;
    }
    
    cout << (double) ans/res << endl;
    cout << f({1}) << endl;
}