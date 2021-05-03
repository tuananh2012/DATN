#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int length = 10000000; // length of the road
const int width = 25000;     // width of the road
const int radius = 100000;   // R_0
double lambda1 = 0.0000000008;
double lambda2 = 0.000000002;
const double PI = 3.141592654;
const int k_max = 100;
const int distanceBetweenRoads = 100000;
double xxx;
#define rand_01 ((float)rand() / (float)RAND_MAX)

const int numofdims = 2;
const int numofparticles = 50;
double integral(double p1, double p2);
double costFunction(double p1, double p2);
void fitnessfunc(float X[numofparticles][numofdims], float fitnesses[numofparticles])
{
    memset(fitnesses, 0, sizeof (float) * numofparticles);
    for(int i = 0; i < numofparticles; i++)
    {
        fitnesses[i] = integral(X[i][0],X[i][1])/costFunction(X[i][0],X[i][1]);
    }
}
float mean(float inputval[], int vallength)
{
    int addvalue = 0;
    for(int i = 0; i < vallength; i++)
    {
        addvalue += inputval[i];
    }
    return (float)(addvalue / vallength);
}
void PSO(int numofiterations, float c1, float c2,
              float Xmin[numofdims], float Xmax[numofdims], float initialpop[numofparticles][numofdims],
              float worsts[], float meanfits[], float bests[], float *gbestfit, float gbest[numofdims])
{
    float V[numofparticles][numofdims] = {0};
    float X[numofparticles][numofdims];
    float Vmax[numofdims];
    float Vmin[numofdims];
    float pbests[numofparticles][numofdims];
    float pbestfits[numofparticles];
    float fitnesses[numofparticles];
    float w;
    float minfit;
    int   minfitidx;

    memcpy(X, initialpop, sizeof(float) * numofparticles * numofdims);
    fitnessfunc(X, fitnesses);
    minfit = *max_element(fitnesses, fitnesses + numofparticles);
    minfitidx = max_element(fitnesses, fitnesses + numofparticles) - fitnesses;
    *gbestfit = minfit;
    memcpy(gbest, X[minfitidx], sizeof(float) * numofdims);

    for(int i = 0; i < numofdims; i++)
    {
        Vmax[i] = 0.2 * (Xmax[i] - Xmin[i]);
        Vmin[i] = -Vmax[i];
    }

    for(int t = 0; t < numofiterations; t++)
    {
        w = 0.9 - 0.7 * t / numofiterations;

        for(int i = 0; i < numofparticles; i++)
        {
            if(fitnesses[i] > pbestfits[i])
            {
                pbestfits[i] = fitnesses[i];
                memcpy(pbests[i], X[i], sizeof(float) * numofdims);
            }
        }
        for(int i = 0; i < numofparticles; i++)
        {
            for(int j = 0; j < numofdims; j++)
            {
                V[i][j] = min(max((w * V[i][j] + rand_01 * c1 * (pbests[i][j] - X[i][j])
                                   + rand_01 * c2 * (gbest[j] - X[i][j])), Vmin[j]), Vmax[j]);
                X[i][j] = min(max((X[i][j] + V[i][j]), Xmin[j]), Xmax[j]);
            }
        }

        fitnessfunc(X, fitnesses);
        minfit = *max_element(fitnesses, fitnesses + numofparticles);
        minfitidx = max_element(fitnesses, fitnesses + numofparticles) - fitnesses;
        if(minfit > *gbestfit)
        {
            *gbestfit = minfit;
            memcpy(gbest, X[minfitidx], sizeof(float) * numofdims);
        }

        //worsts[t] = *min_element(fitnesses, fitnesses + numofparticles);
        bests[t] = *gbestfit;
       // meanfits[t] = mean(fitnesses, numofparticles);
        cout << gbest[0] << " " << gbest[1] << endl;
    }


}
double S(int x)
{
    if (x >= radius)
        return 0;
    double alpha = acos((double)x / radius);
    return (alpha * radius - sin(alpha) * x) * radius;
}
pair<double, double> calculateArea(int x)
{
    double s1 = S(abs(width - x));
    double s2 = S(abs(x));
    double s3 = S(width + distanceBetweenRoads - x);
    double s4 = S(2 * width + distanceBetweenRoads - x);
    if (x <= 0)
    {
        return {s2 - s1, s3 - s4};
    }
    else if (x <= width && x > 0)
    {
        return {PI * radius * radius - s1 - s2, s3 - s4};
    }
    else if (x > width && x <= (width + (distanceBetweenRoads >> 1)))
    {
        return {s1 - s2, s3 - s4};
    }
    else
    {
        auto ans = calculateArea( 2 * width + distanceBetweenRoads - x);
        return {ans.second, ans.first};
    }
}
double calculateProb(double p1, double p2, int x)
{
    auto val = calculateArea(x);
    double base1 = p1 * val.first * lambda1, base2 = p2 * val.second * lambda2;
    return 1 - exp( -base1) * exp( -base2);
}
double integral(double p1, double p2)
{
    double ans = 0;
    for (int i = 1 - radius; i < radius + 2 * width + distanceBetweenRoads; i++)
    {
        ans += calculateProb(p1, p2, i);
    }
    return ans;
}
double costFunction(double p1, double p2)
{
    return sqrt(sqrt(p1)) + sqrt(sqrt(p2)) ;
}
double targetFunction(double p1,double p2){
    return integral(p1,p2)/costFunction(p1,p2);
}
void twopath()
{
    double curans = 0, bestp1 = 0, bestp2 = 0;
    for (double p1 = 0.1; p1 < 1.0; p1 += 0.1)
    {
        for (double p2 = 0.1; p2 < 1.0; p2 += 0.1)
        {
            double candidate = integral(p1, p2) / costFunction(p1, p2);
            if (curans < candidate)
            {
                curans = candidate;
                bestp1 = p1;
                bestp2 = p2;
            }
        }
    }
    cout << bestp1 << " " << bestp2 << " " << integral(bestp1, bestp2) * xxx;
}

int main()
{
    double area = S(radius / sqrt(2));
    area = (double)radius * radius - area;
    double res = (double)(2 * width + 2 * radius + distanceBetweenRoads) * (length - 2 * radius);
    res = res - 4 * area;
    xxx = (length - 2 * radius) / res;
    time_t t;
    srand((unsigned) time(&t));

    float xmin[numofdims], xmax[numofdims];
    float initpop[numofparticles][numofdims];
    float worsts[1000], bests[1000];
    float meanfits[1000];
    float gbestfit;
    float gbest[2];
    for(int i = 0; i < 2; i++)
    {
        xmax[i] = 1;
        xmin[i] = 0.1; 
    }
    for(int i = 0; i < numofparticles; i++)
        for(int j = 0; j < numofdims; j++)
        {
            initpop[i][j] = rand_01 * (xmax[i]-xmin[i]) + xmin[i];
        }

    PSO(100, 0.1, 0.1, xmin, xmax, initpop, worsts, meanfits, bests, &gbestfit, gbest);

    cout<<"fitness: "<< integral(gbest[0],gbest[1]) * xxx << " " << gbest[0] << " " << gbest[1] <<  endl;
    twopath();
    return 0;
}
