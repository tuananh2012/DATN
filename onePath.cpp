#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int length = 10000000;// length of the road
const int width = 25000;// width of the road
const int radius = 100000; // R_0
double lambda = 0.000000003;
const double PI = 3.141592654;
const int k_max = 100;
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
   return  (double)1 - ans;
}
double test(double p,int x){
    double base = lambda * calculateArea(x);
    if(p==1.0) return 1-exp(-base);
    else return 1-exp(-base*p);
}
 
double integral(double p){
    double ans = 0;
    for(int x = -radius + 1; x <= width/2;x++){
        ans += test(p,x);
    }
 //   cout << ans << endl;
    return 2 * ans /(width + 2 * radius);
}
double costFunction(double p){
    return sqrt(sqrt(p));
}
double cal(double l){
    return integral(l)/costFunction(l);
    //2*l + sqrt(l) + sqrt(sqrt(l)) +
}
double findBestProb(){
    double l= 0.00001,r=0.9999;
    double derivatestep = 0.0000001;
    double lans = cal(l);
    double rans = cal(r);   
    int time = 20;
    while (time--)
    {
        auto mid = (l+r)/2;
        double midans = cal(mid);
        if(midans < cal(mid + derivatestep)){
            lans = midans;
            l = mid;
        }
        else{
            rans = midans;
            r = mid;
        }
    }
    return r;
}
void onePath(){
    double area = dientichcungtron(radius/sqrt(2));
    area = (double)radius * radius - area;
    double res =(double) (width + 2 * radius) * (length - 2 * radius);
    res = res/(res - 4 * area);
    //freopen("output.txt","w",stdout);
    for(double numCar = 100; numCar < 4000; numCar+=50){
        lambda = numCar/length/width;
        double ans = findBestProb();
        cout << numCar << " " << ans * numCar << " " << integral(ans) * res << endl; 
    }
}
int main(){
    cout << integral(1) << endl;
}