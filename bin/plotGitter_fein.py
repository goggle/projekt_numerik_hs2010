#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib.tri as tri
from matplotlib.lines import Line2D
import numpy as np

file_p = '../data/p_fein.dat'
p = np.loadtxt(file_p, 'double')

file_b = '../data/b_fein.dat'
b = np.loadtxt(file_b, 'int')

file_t = '../data/t_fein.dat'
t = np.loadtxt(file_t, 'int')

fig = plt.figure()
ax = fig.add_subplot(111, aspect='equal')

x = p[:,0]
y = p[:,1]
plt.triplot(x, y, t-1, lw=0.6)

for i in b:
	x1 = p[i[0]-1, 0]
	y1 = p[i[0]-1, 1]
	x2 = p[i[1]-1, 0]
	y2 = p[i[1]-1, 1]
	if i[2] == 0:
		col = 'black'
	elif i[2] == 1:
		col = 'green'
	elif i[2] == 2:
		col = 'blue'
	line = Line2D([x1, x2], [y1, y2], color=col, lw=2.5)
	ax.add_line(line)

ax.set_xlim(-0.2,5.2)
ax.set_ylim(-0.1,2.1)

#plt.savefig('gitter/Gitter_fein.pdf')
plt.show()
