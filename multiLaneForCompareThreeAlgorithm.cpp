#include <bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0, 80000, 200000, 250000, 340000, 460000, 540000, 670000}, ri{20000, 105000, 215000, 280000, 360000, 490000, 560000, 700000}, lambda{0.000000008, 0.0000000002, 0.0000000005, 0.000000003, 0.00000000004, 0.00000000007, 0.000000009, 0.0000000002};
double val;
double v;
double calcProbability(double x, vector<double> p)
{
    double ans = 0;
    for (int i = 0; i < le.size(); i++)
    {
        ans += p[i] * lambda[i] * Basic_computation::calculateAreaInRoad(abs(x - le[i]), abs(x - ri[i]), radius, ri[i] - le[i]);
    }
    // cout << ans << endl;
    return 1 - exp(-ans);
}
double costFunction(vector<double> p)
{
    double ans = 6;
    for (auto i : p)
        ans += i;
    for (auto i : p)
    {
        for (auto j : p)
        {
            ans += v * abs(i - j);
        }
    }
    //for(auto i : p) ans += sqrt(i);
    return ans/10000 ;
}
double f(vector<double> p)
{
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration::squareIntegral(low, high, calcProbability, p, 1000) / (2 * radius + *ri.rbegin() - le[0]) / costFunction(p);
}
double ff(vector<double> p)
{
    return (f(p) - val);
}
double f2(vector<double> p)
{
    return -(f(p) - val);
}
int main()
{
    // cout << Basic_computation :: arcArea(65000,100000) << endl;
    // cout << f({0.407117,0.246773,0.366436}) << endl;
    vector<double> xxx(le.size(), 0.35);
    val = 0;
    vector<double> xx = {0.01,0.05,0.1,0.3,0.5,1};
    xxx = {0.3};
    for (auto i : xx)
    {
        v = i;
        int time = 1;
        double x = 0, y = 0, z = 0;
        while (time--)
        {
           //freopen("outputrac.txt","w",stdout);
             auto obj = new ABC1(10, le.size(), 500, 30, f2);
            auto obj1 = new PSO(10, le.size(), 1000, 1, 0, 0.2, -0.2, 0.8, 2, 2, ff);
            auto obj2 = new PSO(10, le.size(), 1000, 1, 0, 0.2, -0.2, 0.8, 2, 2, ff);
            obj1->optimizer();//pso
            x += obj1->gBestValue;

            obj2->optimizer1();//pso-based
            y += obj2->gBestValue;
            obj->optimizer(); // abc-algorithm
           z -= obj->ans;
        }
       // freopen("output.txt","a",stdout);

        cout << x << "\t" << y << "\t" << z << endl;
        //fclose(stdout);
    }
}