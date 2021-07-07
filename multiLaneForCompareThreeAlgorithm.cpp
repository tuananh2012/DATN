#include <bits/stdc++.h>
#include "DATN_Library.cpp"
using namespace std;
using namespace DATN;
const int radius = 100000;
vector<double> le{0, 80000, 200000, 250000, 340000, 460000, 540000, 670000}, ri{20000, 105000, 215000, 280000, 360000, 490000, 560000, 700000}, lambda{0.000000008, 0.0000000002, 0.0000000005, 0.000000003, 0.00000000004, 0.000000007, 0.000000009, 0.0000000002};
double val;
double v;
vector<double> cij;

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
    double ans = 0.2;
    for (auto i : p)
        ans += i;
    int index = 0;
    for (auto i : p)
    {
        for (auto j : p)
        {
            ans += cij[index] * abs(i - j);
            index++;
        }
    }
    //for(auto i : p) ans += sqrt(i);
    return ans;
}
double f(vector<double> p)
{
    double low = le[0] - radius;
    double high = *ri.rbegin() + radius;
    return Integration::squareIntegral(low, high, calcProbability, p, 1000) /(2*radius+*ri.rbegin() -le[0]);// costFunction(p);
}
double ff(vector<double> p)
{
    return (f(p) - val);
}
double f2(vector<double> p)
{
    return val - f(p);
}
int main()
{
    srand(time(NULL));
    vector<double> xxx = {0.1019226278, 0, 0, 0.1292817577, 0, 0.07039011182, 0.04943516092, 1};
    cout << f(xxx) << endl;
    val = 0;
    vector<double> test = {0.05};
    for (auto rand_seed : test)
    {
        cij.clear();
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                auto x = rand_seed * rand_01;
                cij.push_back(x);
            }
        }
        int time = 1;
        int old_time = time;
        double x = 0, y = 0, z = 0;
        while (time--)
        {
            // FILE *fp = freopen("outputrac.txt","w",stdout);
            auto obj = new ABC1(10, le.size(), 500, 30, f2);
            auto obj1 = new PSO(10, le.size(), 1000, 1, 0, 0.2, -0.2, 0.8, 2, 2, ff);
            auto obj2 = new PSO(10, le.size(), 1000, 1, 0, 0.2, -0.2, 0.8, 0, 2, ff);
            obj1->optimizer(); //pso
            x += obj1->gBestValue;
            obj2->optimizer1(); //pso-based
            y += obj2->gBestValue;
            // obj->optimizer(); // abc-algorithm
            // z -= obj->ans;

            //    freopen("output.txt","a",stdout);
            // fclose(fp);
        }
        // FILE *fp = freopen("output.txt","a",stdout);
        cout << "ket qua 3 thuat toan voi cij = "<<rand_seed << "*rand(0,1)" << endl;
        cout << "PSO" << "            " << "PSO-Based" << "           " << "ABC" << endl;
        cout << x / old_time << "\t" << y / old_time << "\t" << z / old_time << endl;
        // fclose(fp);
    }
}