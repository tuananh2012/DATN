import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
 
#Simulation window parameters
xMin=[0, 80000, 200000, 250000, 340000, 460000, 540000, 670000];xMax=[20000, 105000, 215000, 280000, 360000, 490000, 560000, 700000]
lambda_array = [0.000000008, 0.0000000002, 0.0000000005, 0.000000003, 0.00000000004, 0.000000007, 0.000000009, 0.0000000002]
test_pso = [0.1019226278, 0, 0, 0.1292817577, 0, 0.07039011182, 0.04943516092, 1]
test_pso_based = [0.04782553116, 0, 0, 0.04782553173, 0, 0.03518855532, 0.03518859092, 0]
yMin=0;yMax=10000000
for i in range(0,8,1):
    xDelta=xMax[i]-xMin[i];yDelta=yMax-yMin #rectangle dimensions
    areaTotal=xDelta*yDelta
 
#Point process parameters
    lambda0=lambda_array[i] * test_pso[i] #intensity (ie mean density) of the Poisson process./
 
#Simulate Poisson point process
    f = open("data_pso.txt", "a")
    numbPoints = scipy.stats.poisson( lambda0*areaTotal ).rvs()#Poisson number of points
    xx = xDelta*scipy.stats.uniform.rvs(0,1,((numbPoints,1)))+xMin[i]#x coordinates of Poisson points
    yy = yDelta*scipy.stats.uniform.rvs(0,1,((numbPoints,1)))+yMin#y coordinates of Poisson points
    #Plotting

    # f.write(str(numbPoints) + "\n")
    for i in range(0,len(xx)):
        f.write(str(int(xx[i])) + " " + str(int(yy[i])) + "\n")
