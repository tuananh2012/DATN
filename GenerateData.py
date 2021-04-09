import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
 
#Simulation window parameters
xMin=0;xMax=25000
yMin=0;yMax=1000000
xDelta=xMax-xMin;yDelta=yMax-yMin #rectangle dimensions
areaTotal=xDelta*yDelta
 
#Point process parameters
lambda0=0.000000005 #intensity (ie mean density) of the Poisson process
 
#Simulate Poisson point process
f = open("data.txt", "w")
numOfTest = 1000
f.write(str(numOfTest) + "\n")
while numOfTest >= 0 :
    numOfTest = numOfTest - 1
    numbPoints = scipy.stats.poisson( lambda0*areaTotal ).rvs()#Poisson number of points
    xx = xDelta*scipy.stats.uniform.rvs(0,1,((numbPoints,1)))+xMin#x coordinates of Poisson points
    yy = yDelta*scipy.stats.uniform.rvs(0,1,((numbPoints,1)))+yMin#y coordinates of Poisson points
    #Plotting

    f.write(str(numbPoints) + "\n")
    for i in range(0,len(xx)):
        f.write(str(int(xx[i])) + " " + str(int(yy[i])) + "\n")
