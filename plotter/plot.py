import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt
import numpy as np

data = []
convergence = []
cc = 1
fn = input()

with open('../outputs/' + fn, 'r') as f:
    for line in f:
        if line == '#\n':
            fig, ax = plt.subplots()
            ax.plot(data, linewidth=0.1)
            plt.savefig('result_' + fn + '-' + str(cc) + '.png')
            cc +=1
            convergence.append(data[-1])
            data = []
            continue
        for i in line.split():
            data.append(int(i))

fig, ax = plt.subplots()
ax.plot(convergence, linewidth=0.3)
plt.savefig('convergence_' + fn + '.png')
