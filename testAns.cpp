#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll length = 10000000;// length of the road
const ll width = 25000;// width of the road
const ll radius = 100000; // R_0
const ll PI = 3.141592654;
const int k_max = 50;

vector<pair<ll,ll>> generateRandom(int numOfPoints){
    vector<pair<ll,ll>> ans(numOfPoints);
    random_device rd;
  /* Random number generator */
  default_random_engine generator(rd());
  /* Distribution on which to apply the generator */
  uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    for (int i = 0; i < numOfPoints; i++) {
      int x = distribution(generator) % (radius * 2 + width);
      int y = distribution(generator) % (length  + 2 * radius);
      x -= radius;
      y-= radius;
      ans[i] = {x,y};
  }
  return ans;
}
int main(){
    int num = 1000;
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
    
    cout << (double) ans/res;
}