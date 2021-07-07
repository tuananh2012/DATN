#include <bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0, 80000, 200000, 250000, 370000}, ri{20000, 105000, 215000, 280000, 400000}, lambda{0.0000000008, 0.0000000002, 0.0000000005, 0.00000003, 0.00000000004};
double val;
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
double f(vector<double> p, double step)
{
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration::squareIntegral(low, high, calcProbability, p, step) / (2 * radius + *ri.rbegin() - le[0]);
}
double f1(vector<double> p, double step)
{
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration::trapezoidIntegral(low, high, calcProbability, p, step) / (2 * radius + *ri.rbegin() - le[0]);
}
double f2(vector<double> p, double step)
{
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration::simpsonIntergral(low, high, calcProbability, p, step) / (2 * radius + *ri.rbegin() - le[0]);
}
int main()
{
    for (int i = 1; i < 100000; i *= 10)
    {
        cout << setprecision(15) << "Tong Reimann giua voi delta x = " << i << ": " << f({1, 1, 1, 1, 1}, i) << endl;
        cout << setprecision(15) << "Luat hinh thang voi delta x = " << i << ":" << f1({1, 1, 1, 1, 1}, i) << endl;
        cout << setprecision(15) << "Luat Simpson voi delta x = " << i << ":" << f2({1, 1, 1, 1, 1}, i) << endl;
    }
}