#include<bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0,80000,200000,250000,370000},ri{20000,105000,215000,280000,400000},lambda{0.0000000008,0.000000002,0.0000000005,0.000000003,0.0000000004};
double val;
double calcProbability(double x, vector<double> p){
    double ans = 0;
    for(int i = 0; i < le.size();i++){
        ans += p[i] * lambda[i] * Basic_computation::calculateAreaInRoad(abs(x-le[i]),abs(x-ri[i]),radius,ri[i]-le[i]);
    }
   // cout << ans << endl;
    return 1-exp(-ans);
}
double costFunction(vector<double> p){
    double ans = 5.1;
    for(auto i : p) ans += sin(i*PI * 1000);
    return ans;
}
double f(vector<double>p){
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration:: squareIntegral(low,high,calcProbability,p,20)/(2 * radius + *ri.rbegin() - le[0])/costFunction(p);
}
double ff(vector<double> p){
    return  (f(p) - val);
}
double f2(vector<double> p){
    return -(f(p) - val);
}
int main(){
   // cout << Basic_computation :: arcArea(65000,100000) << endl;
   // cout << f({0.407117,0.246773,0.366436}) << endl;
    vector<double> xxx(le.size(),0.5);
    val = f(xxx);
    freopen("plotabc.txt","w",stdout);
    auto obj = new ABC(15,le.size(),300,60,f2);
    // const clock_t begin_time = clock();
    obj->optimizer();
    fclose(stdout);
    // std::cout <<"time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    freopen("plotpso.txt","w",stdout);
    auto obj1 = new PSO(30,le.size(),300,1,0,0.2,-0.2,0.9,0.5,0.5,ff);
    obj1->optimizer();
    fclose(stdout);
    // double ans =0,x,y,z;
    // for(double p1 = 0.1;p1<=1;p1+=0.05){
    //     for(double p2 = 0.1;p2 <= 1;p2 += 0.05){
    //         for(double p3 = 0.1;p3 <= 1;p3+=0.05){
    //             if(ans < ff({p1,p2,p3})) {
    //                 ans = ff({p1,p2,p3});
    //                 x = p1; y = p2; z = p3;
    //             }
    //         }
    //     }
    // }
    // cout << x << " " << y << " " << z << " " << ans << endl;
    // cout << 2 * radius + *ri.rbegin() - le[0] << endl;
    // double low = le[0] - radius;
    // double high = *ri.rbegin() + radius;
    // cout << Integration:: squareIntegral(low+1,high-1,calcProbability,{0.5,0.5},10)/(2 * radius + *ri.rbegin() - le[0]);
}