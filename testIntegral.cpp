#include<bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0,100000},ri{25000,125000},lambda{0.0000000008,0.000000002};
double val;
double calcProbability(double x, vector<double> p){
    double ans = 0;
    for(int i = 0; i < le.size();i++){
        ans += p[i] * lambda[i] * Basic_computation::calculateAreaInRoad(abs(x-le[i]),abs(x-ri[i]),radius,ri[i]-le[i]);
    }
   // cout << ans << endl;
    return 1-exp(-ans);
}
double f(vector<double>p, double step){
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration:: squareIntegral(low,high,calcProbability,p,step)/(2 * radius + *ri.rbegin() - le[0]);
}
double f1(vector<double>p, double step){
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration:: trapezoidIntegral(low,high,calcProbability,p,step)/(2 * radius + *ri.rbegin() - le[0]);
}
double f2(vector<double>p, double step){
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration:: simpsonIntergral(low,high,calcProbability,p,step)/(2 * radius + *ri.rbegin() - le[0]);
}
int main(){
    cout << setprecision(15) << f({1,1},1) << endl;
    cout <<  setprecision(15) << f({1,1},1000) << endl;
    cout <<  setprecision(15) << f1({1,1},1000) << endl;
    cout <<  setprecision(15) << f2({1,1},1000) << endl;
}