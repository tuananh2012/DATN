#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int length = 10000000;// length of the road
const int width = 25000;// width of the road
const int radius = 100000; // R_0
double lambda1 = 0.000000002;
double lambda2 = 0.0000000005;
const double PI = 3.141592654;
const int k_max = 100;
const int distanceBetweenRoads = 100000;
double S(int x){
    if(x >= radius) return 0;
    double alpha = acos((double)x/radius);
    return (alpha * radius  - sin(alpha) * x )* radius;
}
pair<double,double> calculateArea(int x){
    double s1 = S(width-x);
    double s2 = S(abs(x));
    double s3 = S(width + distanceBetweenRoads - x);
    double s4 = S(2 * width + distanceBetweenRoads - x);
    if(x<=0){
        return {s2 - s1,s3 - s4};
    }
    else if(x <= width && x > 0){
        return {PI * radius * radius - s1 - s2,s3 - s4};
    }
    else if( x > width && x < width + distanceBetweenRoads){
        return {s1 - s2,s3 - s4};
    }
    else{
        auto ans = calculateArea(x - 2 * (x- width - distanceBetweenRoads/2));
        return {ans.second,ans.first};
    }
}
double calculateProb(double p1,double p2, int x){
    auto val = calculateArea(x);
    double base1 = p1 * val.first * lambda1, base2 = p2 * val.second * lambda2;
    return 1 - exp(-base1) * exp(-base2);
}
double integral(double p1, double p2){
    double ans = 0;
    for (int i = 1-radius; i < radius + 2 * width + distanceBetweenRoads; i++)
    {
        ans += calculateProb(p1,p2,i);
    }
    return ans;
}
double costFunction(double p1, double p2){
    return sqrt(sqrt(p1)) + sqrt(sqrt(p2)) + abs(p1-p2)/20;
}
void twopath(){
    double area = S(radius/sqrt(2));
    area = (double)radius * radius - area;
    double res =(double) (2 * width + 2 * radius + distanceBetweenRoads) * (length + 2 * radius);
    res = res - 4 * area;
    double curans = 0, bestp1=0,bestp2=0;
    for(double p1 = 0.1; p1 < 1.0;p1 += 0.1){
        for(double p2 = 0.1; p2 < 1.0;p2 += 0.1){
            double candidate = integral(p1,p2)/costFunction(p1,p2);
            if(curans < candidate){
                curans = candidate;
                bestp1 = p1;
                bestp2 = p2;
            }
        }
    }
    cout << bestp1 << " " << bestp2 << " " << integral(bestp1,bestp2)*length/res;

}
int main(){
    twopath();
}