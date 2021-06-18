import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from pylab import *
import json
import os
import pdb
import re


def get_data(file_path):
    output = []
    with open(file_path, 'r') as f:
        for line in f.readlines():
            k = []
            line = line.split()
            for j in line:
                k.append(float(j)/10000)
            output.append(k)
    return np.asarray(output).T


def line_chart(models, data_matrix, x_label, y_label, title, xpoints, higher_models=[], name=None, maxx=10000):
    styles = ['o', 's', 'd', '^', 'x', '*', 'v', '<']
    #styles = ['o', 's', 'v', '*']
    line_styles = ['-', '--', '-', '-.', ':', '-', '--']
    # styles = ['o-', '>--', 's-', 'd-.', '^:', 'x-', '*-', 'v-']

    colors = ['#003300', '#009933', '#33cc33',
              '#66ff66', '#99ff99', '#ffffff', '#0033ff']
    barwith = 0.1
    ax1 = plt.subplot(111)

    num_models = data_matrix.shape[0]
    num_x_levels = data_matrix.shape[1]\

    assert num_models == len(
        models), "Number of model must equal to data matrix shape 0"

    lns1 = []
    for i, model in enumerate(models):
        if model not in higher_models:
            line = data_matrix[i]
            x = np.arange(num_x_levels)
            fillstyle = 'none'
            if i > 3:
                fillstyle = 'full'
            lni, = ax1.plot(x, line, marker=styles[i % len(
                styles)], markersize=8, color='k', label=models[i], markevery=1, fillstyle=fillstyle)
            lns1.append(lni)

    ax1.set_xlabel(x_label, fontsize=15, fontweight='bold')
    ax1.set_ylabel(y_label, fontsize=15, fontweight='bold')

    plt.xticks(np.arange(len(xpoints)), xpoints, fontsize=16)
#     plt.yticks(np.arange(0, 1.1, step=0.2), fontsize = 16)
    ax1.set_xlim(-0.3, len(xpoints) + .3 - 1)
    ax1.set_ylim(0, maxx + .32)
    # ypoints = np.arange(0, 1.1, 0.2)
    # plt.yticks(np.arange(len(ypoints)), ypoints, fontsize = 16)

    ax1.grid(True)
    box = ax1.get_position()
    ax1.set_position([box.x0 + 0.02, box.y0 + 0.04, box.width, box.height])

    # plt.legend(ncol = 4,borderaxespad = 0.3, fontsize=10.7)
    plt.legend(ncol=4, fontsize=11.5, loc=1, columnspacing=4.22)
    plt.show()
models = ['PSO', 'PSO-Based','ABC']


xpoint_del_nodes = {"xp": ["01", "0.15",
                           "0.2"], "xlabel": "Train ratio"}
ylabel = "Optimal Result"
maxx = 0.9

file_names = ['data/xtest.txt']
for index, file_name in enumerate(file_names):
    accs = get_data(file_name)
    name = 'yyy'
    xticks =["0.01", "0.05", "0.1","0.3","0.5","1"]
    if index == 0:
        xlabel = 'x'
    else:
        xlabel = 'x'
    line_chart(models=models, data_matrix=accs,
               x_label=xlabel, y_label=ylabel, title=name, xpoints=xticks, higher_models=[], name='{}.png'.format(file_name), maxx=maxx)

