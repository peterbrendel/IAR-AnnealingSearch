import numpy as np
import matplotlib.pyplot as plt

data = []

with open('../outputs/uf250-01.out', 'r') as f:
    for line in f:
        for i in line.split():
            data.append(int(i))

fig, ax = plt.subplots()

ax.plot(data, linewidth=0.1)

plt.show()
