#include<bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0,80000,200000,250000,370000},ri{20000,105000,215000,280000,400000},lambda{0.000000008,0.000000002,0.000000005,0.000000003,0.0000000004};
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
    double ans = 0.1;
    for(auto i : p) ans += i;
    for(auto i : p){
        for(auto j : p){
            ans += 0.35 * abs(i-j);
        }
    }
    //for(auto i : p) ans += sqrt(i);
    return ans/10000;
}
double f(vector<double>p){
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration:: squareIntegral(low,high,calcProbability,p,1000)/(2 * radius + *ri.rbegin() - le[0])/costFunction(p);
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
    vector<double> xxx(le.size(),0.35);
    val = f(xxx);
    // cout << val << endl;
    //freopen("plotabc.txt","w",stdout);
    auto obj = new ABC1(10,le.size(),1000,30,f2);
    // const clock_t begin_time = clock();
   //obj->optimizer();
    //fclose(stdout);
    // std::cout <<"time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
   // freopen("plot_6_0.25.txt","w",stdout);
    auto obj1 = new PSO(10,le.size(),1000,1,0,0.2,-0.2,0.8,2,2,ff);
    obj1->optimizer();

    // for(auto i : obj1->swarm){ 5.323067557 6.398218843 7.571627184  4.777248751 4.101984475
    // 5.55178235  7.557415157 5.616465112 3.426880523 7.112705674
    // 7.157579149 6.795042283 5.658620734 7.116068464  7.216317625
    // 7.581799259 7.257661456 7.462641679  6.92994234 6.206881385
    // 6.596695751 5.450629562 6.686236731 5.518026612 5.900866004
    // abc 2.02376 -3.71055 0.732994 0.0653282 -3.26678 1.70733 -1.29914 0.021867 -1.83501 1.33911
    // pso 6.895428033 7.374452905 7.266720608 5.946160965 7.289114927 6.339800882
    // TA-PSO 7.593395678 7.593285707 7.592508206  7.593219689 7.593071948 7.593439111 7.593381124 7.589426576 7.593353833 7.592501434
    //     for(auto j : i.velocity){
    //         cout << j << " " ;
    //     }
    //     cout << endl;
    // }
    auto obj2 = new PSO(10,le.size(),1000,1,0,0.2,-0.2,0.8,0,2,ff);
    obj2 -> optimizer1();
    // 5.9251
   //fclose(stdout);
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