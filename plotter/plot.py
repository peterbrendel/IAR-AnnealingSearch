import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt
import numpy as np

data = []

fn = input()

with open('../outputs/' + fn, 'r') as f:
    for line in f:
        for i in line.split():
            data.append(int(i))

fig, ax = plt.subplots()
ax.plot(data, linewidth=0.1)

plt.savefig('result.png')
