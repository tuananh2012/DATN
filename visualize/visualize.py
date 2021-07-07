import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as patches
import numpy as np
from matplotlib import colors, rc
from pylab import *
def get_data(file_path):
    output = []
    with open(file_path, 'r') as f:
        for line in f.readlines():
            k = []
            line = line.split()
            for j in line:
                k.append(float(j))
            output.append(k)
    return np.asarray(output).T
fig = plt.figure(dpi=150)
rect1 = patches.Rectangle((10000, 0), 20000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect2 = patches.Rectangle((92500, 0), 25000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect3 = patches.Rectangle((207500, 0), 15000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect4 = patches.Rectangle((350000, 0), 20000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect5 = patches.Rectangle((475000, 0), 30000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect6 = patches.Rectangle((550000, 0), 20000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect7 = patches.Rectangle((685000, 0), 30000, 10000000, linewidth=1, color='r', alpha= 0.5)
rect8 = patches.Rectangle((265000, 0), 30000, 10000000, linewidth=1, color='r', alpha= 0.5)


ax = fig.add_subplot(111, aspect= 'equal')
ax.add_patch(rect1)
ax.add_patch(rect2)
ax.add_patch(rect3)
ax.add_patch(rect4)
ax.add_patch(rect5)
ax.add_patch(rect6)
ax.add_patch(rect7)
ax.add_patch(rect8)
ax.axes.get_xaxis().set_visible(False)
ax.axes.get_yaxis().set_visible(False)
ax.set_xlim(-100000,800000)
ax.set_ylim(0,1000000)
accs = get_data("data_pso.txt")

for i in range(0,len(accs[0])):
    print(accs[0][i],accs[1][i])
    circle1 = plt.Circle((accs[0][i], accs[1][i]), 100000, color='g', alpha=0.5)#, clip_on=False)
    ax.add_patch(circle1)
# plt.plot([0, 0], [10000, 0], 'k-', lw=1, color='blue', alpha=0.5)#, clip_on=False)
# circle1 = plt.Circle((100000, 100000), 100000, color='g', alpha=0.5)#, clip_on=False)
# ax.add_patch(circle1)
plt.show()