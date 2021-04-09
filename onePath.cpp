#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int length = 10000000;// length of the road
const int width = 25000;// width of the road
const int radius = 100000; // R_0
double lambda = 0.000000005;
const double PI = 3.141592654;
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
      int y = distribution(generator) % (length +2 * radius);
      x -= radius;
      y-= radius;
      
      ans[i] = {x,y};
  }
  return ans;
}
double dientichcungtron(int x){
    if(x >= radius) return 0;
    double alpha = acos((double)x/radius);
    return (alpha * radius  - sin(alpha) * x )* radius;
}
double calculateArea(int x){
   if(x <= 0 && x + radius < width) return dientichcungtron(-x);
   else if( x <= 0 && x + radius >= width) return dientichcungtron(-x) - dientichcungtron(width-x);
   else if(x > 0)  return PI * radius * radius - dientichcungtron(x) - dientichcungtron(width - x);
}
double calculateProbability(double p, int x){
   double base = lambda * calculateArea(x);
   double ans = exp(-base);
   double cur = ans;
   for (int i = 1; i < k_max; i++)
   {
       cur *= (base * (1.0-p))/i;
       ans += cur;
   }
   
 //  cout << ans << endl;
   return  (double)1 - ans;
}
 
double integral(double p){
    double ans = 0;
    for(int x = -radius + 1; x <= width/2;x++){
        ans += calculateProbability(p,x);
    }
 //   cout << ans << endl;
    return 2 * ans/(2*radius + width) * ((double)length/(length+ 2 * radius));
}
double check(double p, int numOfPoints){
    int ans = 0, totalPoint = 0;
    vector<pair<ll,ll>> points = generateRandom(numOfPoints);
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
                    if((x-points[i].first) * (x - points[i].first) + (y-points[i].second) * (y-points[i].second) <= (ll) radius * radius ){
                        ans++;
                        inside[i]  = true;
                    }
                }
            }  
        }
    }
    return (double)ans/totalPoint;
}
double findBestProb(float expo){
    double best_ans = 0, best_prob = 0.01;
    for(double p = 0.01 ; p <= 1.0; p += 0.01){
        double cur = integral(p)/pow(p,expo);
        if(cur > best_ans){
            best_ans = cur;
            best_prob = p;
        }
    }
    return best_prob;
}
int main(){
    double area = dientichcungtron(radius/sqrt(2));
    area = (double)radius * radius - area;
    double res =(double) (width + 2 * radius) * (length + 2 * radius);
    res = res/(res - 4 * area);
    // cout << calculateArea(10000);
    freopen("output.txt","w",stdout);
    for(double numCar = 10; numCar < 3000; numCar++){
        lambda = numCar/length/width;
        double ans = findBestProb(0.3);
        cout << numCar << " " << ans << " " << integral(ans) * res << endl; 
    }
    

    
}