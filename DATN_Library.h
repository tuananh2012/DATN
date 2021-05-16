#include <bits/stdc++.h>
using namespace std;
namespace DATN
{
    struct foodSource
        {
            vector<double> pos; // dim[0] = length of link L1, dim[1] = length of link L2, dim[2] = angle THETA
            double objFxValue;         // Sum of Square Errors (Beta_actual - Beta_theoritical)
            double fitness;
            double trials;
            double prob;
        };
    struct particle{
        vector<double> pos;
        vector<double> velocity;
        vector<double> pBest;
        double pBestValue; 
    };
    class Basic_computation
    {
    public:
        static double arcArea(double disToCenter, double radius);
        static double calculateAreaInRoad(double distance1, double distance2, double radius, double width);
    };
    class Integration
    {
    public:
        static double squareIntegral(double low, double high, double f(double,vector<double>), vector<double> p, double step);
        static double trapezoidIntegral(double low, double high, double f(double,vector<double>), vector<double> p, double step);
        static double simpsonIntergral(double low, double high, double f(double,vector<double>), vector<double> p, double step);
    };
    class ABC
    {

    public:
        int nbFoodSource;
        int nbDimensions;
        int nbIterations;
        int maxTrials;
        vector<double> globalBest;
        double ans;
        function<double(vector<double>)> f;
        vector<foodSource> food_source;
        ABC(int x,int y,int z,int t,std:: function<double(vector<double>)> f);
        void calcFitness();
        void calcProb();
        void sendEmployee(int index);
        void sendOnlookers();
        void sendScout(int index);
        void optimizer();
        double fitnessFunction(double x);
    };
    class PSO{
        public:
        int nbParticles;
        int nbDimensions;
        int nbIterations;
        double gBestValue;
        vector<double> gBest;
        double xMax,xMin,vMax,vMin,w,c1,c2;
        function < double (vector<double>)> f;
        vector<particle> swarm;
        PSO(int nbParticles, int nbDimensions, int nbIteration, double xMax,double xMin, double vMax, double vMin , double w,double c1,double c2, function < double (vector<double>)> f);
        void optimizer();
    };

} // namespace DATN
