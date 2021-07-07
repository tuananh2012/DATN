import matplotlib.pyplot as plt
import numpy as np
with open('plot_pso_2.txt') as f:
    data = [[float(line.split()[0]), int(line.split()[1])] for line in f.readlines()]
fig = plt.figure(dpi=150)
ax = fig.add_subplot(111)
# plt.xticks(np.arange(len(data) + 90, 100), np.arange(len(data) + 90, 100))
plt.xlabel('iteration')
plt.ylabel('result')
ax.plot(np.asarray([i[1] for i in data[100:1000]]), np.asarray([i[0] for i in data[100:1000]]))
plt.show()
