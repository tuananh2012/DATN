#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int length = 1e6;// length of the road
const int width = 25000;// width of the road
const int r = 50000; // R_0
const double lambda = 0.000000005;
const double PI = 3.141592654;
const int k_max = 50;
double dientichcungtron(int x){
    if(x >= r) return 0;
    double alpha = acos((double)x/r);
    return alpha * r * r - sin(alpha) * x * r;
}
double calculateArea(int x){
   if(x <= 0 && x+r < width) return dientichcungtron(-x);
   else if( x <= 0 && x + r >= width) return dientichcungtron(-x) - dientichcungtron(width-x);
   else if(x > 0)  return PI * r * r - dientichcungtron(x) - dientichcungtron(width - x);
}
double calculateProbability(double p, int x){
   double base = lambda * calculateArea(x);
   double ans = exp(-base);
   double cur = ans;   
   for(int k = 1;k < k_max;k++){
       cur = cur * (base * (1-p))/k;
       ans += cur;
   }
   cout << ans << endl;
   return ans;
}
double integral(double p){
    double ans = 0;
    for(int x = - r + 1; x <= width/2;x++){
        ans += (1- calculateProbability(p,x));
    }
    return 2 * ans/(2*r + width);
}
double check(double p, int numOfPoints){
    int ans = 0, totalPoint = 0;
    vector<pair<ll,ll>> points(numOfPoints);
    srand(time(NULL));
    for(int i = 0; i < numOfPoints;i++){
        int x = rand() % ((r<<1)+width);
        x-=r;
        int y = rand() % (length);
        points[i]={x,y};
    }
    freopen("data.txt","r",stdin);
    int numOfTest;
    cin >> numOfTest;
    while (numOfTest--)
    {
        vector<bool> inside(numOfPoints,0);
        int numOfPointsInRoad ;
        auto temp = points;
        cin >> numOfPointsInRoad;
        totalPoint += numOfPoints;
        while (numOfPointsInRoad--)
        {
            long long x,y;
            cin >> x >> y;
            double f = (double)rand() / RAND_MAX;
            if(f > p) continue;
            for (int i = 0; i < numOfPoints; i++)
            {
                if(!inside[i]){
                    if((x-points[i].first) * (x - points[i].first) + (y-points[i].second) * (y-points[i].second) <= (ll) r * r ){
                        ans++;
                        inside[i]  = true;
                    }
                }
            }  
        }
    }
    return (double)ans/totalPoint;
}
int main(){
    // cout << calculateArea(10000);
    cout << integral(1) << endl << check(1,1000);


}