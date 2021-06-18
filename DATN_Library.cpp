#include "DATN_Library.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <bits/stdc++.h>

#define PI 3.141592654

#define rand_01 ((float)rand() / (float)RAND_MAX)

#define rand_range(x, y) ((rand() % (y - x + 1)) + x)

namespace DATN
{
    double calculateDiversity(vector<vector<double>> swarm)
    {
        int num = swarm.size();
        int dimension = swarm[0].size();
        vector<double> mean(dimension, 0);
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                mean[j] += swarm[i][j];
            }
        }
        for (int i = 0; i < dimension; i++)
        {
            mean[i] /= num;
        }
        double ans = 0;
        for (auto i : swarm)
        {
            double temp = 0;
            for (int j = 0; j < dimension; j++)
            {
                temp += (mean[j] - i[j]) * (mean[j] - i[j]);
            }
            temp /= dimension;
            ans += temp;
        }
        ans /= num;
        return ans;
    }

    double Basic_computation ::arcArea(double disToCenter, double radius)
    {
        if (disToCenter >= radius)
            return 0;
        double alpha = acos((double)disToCenter / radius);
        return (alpha * radius - sin(alpha) * disToCenter) * radius;
    }

    double Basic_computation ::calculateAreaInRoad(double distance1, double distance2, double radius, double width)
    {
        if (distance1 + distance2 > width)
            return arcArea(distance1, radius) - arcArea(distance1 + width, radius);
        else
            return (PI * radius * radius - arcArea(distance1, radius) - arcArea(distance2, radius));
    }

    double Integration::squareIntegral(double low, double high, double f(double, vector<double>), vector<double> p, double step)
    {
        double ans = 0;
        int cnt = 0;
        for (double cur = low; cur + step <= high; cur += step)
        {
            double mid = cur + step / 2;
            ans += f(mid, p);
            // cnt ++;
            // if(cnt < 10) cout << mid << " "  << f(mid,p) << endl;
        }
        return ans * step;
    }
    double Integration ::trapezoidIntegral(double low, double high, double f(double, vector<double>), vector<double> p, double step)
    {
        double ans = 0;
        for (double cur = low; cur + step <= high; cur += step)
        {
            double mid = (f(cur, p) + f(cur + step, p)) / 2;
            ans += mid;
        }
        return ans * step;
    }
    double Integration ::simpsonIntergral(double low, double high, double f(double, vector<double>), vector<double> p, double step)
    {
        double ans = 0;
        int cnt = 0;
        for (double cur = low; cur + step <= high; cur += step)
        {
            if (cnt & 1)
            {
                ans += (f(cur, p) * 4);
            }
            else
                ans += (f(cur, p) * 2);
            cnt++;
        }
        ans -= (f(low, p) + f(high, p));
        ans *= step / 3;
        return ans;
    }

    ABC1 ::ABC1(int x, int y, int z, int t, function<double(vector<double>)> fi)
    {
        time_t ti;
        srand((unsigned)time(&ti));
        nbFoodSource = x;
        nbDimensions = y;
        nbIterations = z;
        maxTrials = t;
        f = fi;
        ans = 0;
        vector<foodSource> res(nbFoodSource);
        vector<double> temp(nbDimensions);
        for (int i = 0; i < nbFoodSource; i++)
        {
            for (int j = 0; j < nbDimensions; j++)
            {
                temp[j] = rand_01;
            }
            res[i].pos = temp;
            res[i].objFxValue = f(temp);
            res[i].fitness = fitnessFunction(res[i].objFxValue);
            res[i].prob = 0;
            res[i].trials = 0;
            if (res[i].objFxValue > ans)
            {
                ans = res[i].objFxValue;
                globalBest = temp;
            }
        }
        food_source = res;
    }

    void ABC1::calcFitness()
    {
        for (int i = 0; i < nbFoodSource; i++)
        {
            food_source[i].fitness = fitnessFunction(food_source[i].objFxValue);
        }
    }

    void ABC1 ::calcProb()
    {
        double cur = 0;
        for (int i = 0; i < nbFoodSource; i++)
        {
            cur += food_source[i].fitness;
        }
        for (int i = 0; i < nbFoodSource; i++)
        {
            food_source[i].prob = food_source[i].fitness / cur;
        }
    }

    double ABC1 ::fitnessFunction(double x)
    {
        if (x >= 0)
            return 1.0 / (1 + x);
        else
            return 1 - x;
    }
    void ABC1 ::sendEmployee1(int i)
    {
        int neibor = i;
        while (neibor == i)
        {
            neibor = rand_range(0, nbFoodSource - 1);
        }
        int paramToChange = rand_range(0, nbDimensions - 1);
        auto curPos = food_source[i].pos[paramToChange];
        auto neiborPos = food_source[neibor].pos[paramToChange];
        while (true)
        {
            double newPos = globalBest[paramToChange] + 2 * (rand_01 - 0.5) * (curPos - neiborPos);
            if (newPos > 0.0 && newPos < 1.0)
            {
                food_source[i].pos[paramToChange] = newPos;
                break;
            }
        }

        auto newValue = this->f(food_source[i].pos);
        auto fitness = fitnessFunction(newValue);
        if (newValue < food_source[i].objFxValue)
        {
            food_source[i].fitness = fitness;
            food_source[i].objFxValue = newValue;
            food_source[i].trials = 0;
            if (food_source[i].objFxValue < ans)
            {
                ans = food_source[i].objFxValue;
                globalBest = food_source[i].pos;
            }
        }
        else
        {
            food_source[i].trials++;
            sendScout(i);
        }
    }
    void ABC1 ::sendEmployee(int i)
    {
        int neibor = i;
        while (neibor == i)
        {
            neibor = rand_range(0, nbFoodSource - 1);
        }
        int paramToChange = rand_range(0, nbDimensions - 1);
        auto curPos = food_source[i].pos[paramToChange];
        auto neiborPos = food_source[neibor].pos[paramToChange];
        while (true)
        {
            double newPos = curPos + 2 * (rand_01 - 0.5) * (curPos - neiborPos);
            if (newPos > 0.0 && newPos < 1.0)
            {
                food_source[i].pos[paramToChange] = newPos;
                break;
            }
        }

        auto newValue = this->f(food_source[i].pos);
        auto fitness = fitnessFunction(newValue);
        if (newValue < food_source[i].objFxValue)
        {
            food_source[i].fitness = fitness;
            food_source[i].objFxValue = newValue;
            food_source[i].trials = 0;
            if (food_source[i].objFxValue < ans)
            {
                ans = food_source[i].objFxValue;
                globalBest = food_source[i].pos;
            }
        }
        else
        {
            food_source[i].trials++;
            sendScout(i);
        }
    }

    void ABC1 ::sendOnlookers()
    {
        calcProb();
        int foodIndex = 0, onlookerIndex = 0;
        while (onlookerIndex < nbFoodSource)
        {
            if (rand_01 < food_source[foodIndex].prob)
            {
                onlookerIndex++;
                sendEmployee(foodIndex);
            }
            else
            {
                foodIndex++;
                foodIndex %= nbFoodSource;
            }
        }
    }

    void ABC1 ::sendScout(int i)
    {
        if (food_source[i].trials > maxTrials)
        {
            for (int j = 0; j < nbDimensions; j++)
            {
                food_source[i].pos[j] = rand_01;
            }
            food_source[i].objFxValue = this->f(food_source[i].pos);
            food_source[i].fitness = fitnessFunction(food_source[i].objFxValue);
            food_source[i].trials = 0;
            if (food_source[i].objFxValue < ans)
            {
                ans = food_source[i].objFxValue;
                globalBest = food_source[i].pos;
            }
        }
    }

    void ABC1 ::optimizer()
    {
        const clock_t begin_time = clock();
        for (int t = 0; t < nbIterations; t++)
        {
            for (int i = 0; i < nbFoodSource; i++)
            {
                sendEmployee(i);
            }
            sendOnlookers();
            cout << -ans << " " << t + 1 << endl;
        }
        // cout << "best value :" << ans << endl;
        // cout << "best params: " ;
        // for (int i = 0; i < nbDimensions; i++)
        // {
        //     cout << globalBest[i] << " ";
        // }
        // cout << endl;
        // std::cout <<"time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    }

    PSO ::PSO(int nParticles, int nDimensions, int nIteration, double xmax, double xmin, double vmax, double vmin, double ww, double cc1, double cc2, function<double(vector<double>)> fii)
    {
        nbParticles = nParticles;
        nbDimensions = nDimensions;
        nbIterations = nIteration;
        xMax = xmax;
        xMin = xmin;
        vMax = vmax;
        vMin = vmin;
        w = ww;
        c1 = cc1;
        c2 = cc2;
        f = fii;
        gBestValue = -1e9;
        vector<particle> sw(nbParticles);
        vector<double> pos(nbDimensions), vel(nbDimensions, 0);
        for (int i = 0; i < nbParticles; i++)
        {
            for (int j = 0; j < nbDimensions; j++)
            {
                pos[j] = (rand_01 * (xMax - xMin) + xMin);
            }
            sw[i].pos = pos;
            // for(auto ss : sw[i].pos) cout << ss << endl;
            sw[i].velocity = vel;
            sw[i].pBest = pos;
            sw[i].pBestValue = f(pos);
            if (sw[i].pBestValue > gBestValue)
            {
                gBestValue = sw[i].pBestValue;
                gBest = pos;
            }
        }
        swarm = sw;
    }

    void PSO ::optimizer()
    {
        int ii = 0;
        const clock_t begin_time = clock();
        int tt = nbIterations;
        while (nbIterations--)
        {
            double ww = w - (0.8 * w) * ii / tt;
            ii++;
            for (int i = 0; i < nbParticles; i++)
            {
                for (int j = 0; j < nbDimensions; j++)
                {
                    auto x = swarm[i].pos[j], v = swarm[i].velocity[j];
                    v = ww * v + rand_01 * c1 * (swarm[i].pBest[j] - x) + rand_01 * c2 * (gBest[j] - x);
                    swarm[i].velocity[j] = min(max(v, vMin), vMax);
                    swarm[i].pos[j] = min(max(x + swarm[i].velocity[j], xMin), xMax);
                }
                auto val = this->f(swarm[i].pos);
                if (val > swarm[i].pBestValue)
                {
                    swarm[i].pBestValue = val;
                    swarm[i].pBest = swarm[i].pos;
                    if (val > gBestValue)
                    {
                        gBestValue = val;
                        gBest = swarm[i].pos;
                    }
                }
            }
            cout << setprecision(10) << gBestValue << " " << ii + 1 << endl;
        }
        // cout << "fitness: " << gBestValue << endl;
        // cout << "params: "<< gBest.size();
        // for (auto i : gBest)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;
        // std::cout <<"time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    }
    void PSO ::optimizer1()
    {
        set<int> dim;
        for (int i = 0; i < nbDimensions; i++)
        {
            dim.insert(i);
        }
        int ii = 0;
        const clock_t begin_time = clock();
        int tt = nbIterations;
        while (nbIterations--)
        {
            if (nbIterations % 10 == 0)
            {
                for (int i = 0; i < nbParticles; i++)
                {
                    double vel = 0;
                    for (int j = 0; j < nbDimensions; j++)
                    {
                        vel += swarm[i].velocity[j] * swarm[i].velocity[j];
                    }
                    vel /= nbDimensions;
                    if (vel < 1e-8)
                    {
                        auto randd = (rand_01 * (vMax - vMin) + vMin);
                        int numberOfDimensionsToChange = rand_range(1, nbDimensions);
                        set<int> dims = dim;
                        vector<int> changeDim;
                        while (numberOfDimensionsToChange--)
                        {
                            int ra = rand_range(0, nbDimensions - 1);
                            while (dims.find(ra) == dims.end())
                            {
                                ra = rand_range(0, nbDimensions - 1);
                            }
                            changeDim.push_back(ra);
                            dims.erase(ra);
                        }
                        for (auto d : changeDim)
                        {
                            swarm[i].velocity[d] = randd;
                        }
                    }
                }
            }
            double ww = w - (0.8 * w) * ii / tt;
            ii++;
            for (int i = 0; i < nbParticles; i++)
            {
                for (int j = 0; j < nbDimensions; j++)
                {
                    auto x = swarm[i].pos[j], v = swarm[i].velocity[j];
                    v = ww * v + rand_01 * c1 * (swarm[i].pBest[j] - x) + rand_01 * c2 * (gBest[j] - x);
                    swarm[i].velocity[j] = min(max(v, vMin), vMax);
                    swarm[i].pos[j] = min(max(x + swarm[i].velocity[j], xMin), xMax);
                }
                auto val = this->f(swarm[i].pos);
                if (val > swarm[i].pBestValue)
                {
                    swarm[i].pBestValue = val;
                    swarm[i].pBest = swarm[i].pos;
                    if (val > gBestValue)
                    {
                        gBestValue = val;
                        gBest = swarm[i].pos;
                    }
                }
            }
            cout << setprecision(10) << gBestValue << " " << ii << endl;
        }

        for (auto i : gBest)
        {
            cout << i << " ";
        }
        cout << endl;
        // std::cout <<"time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    }
};
