#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib.tri as tri
from matplotlib.lines import Line2D
from matplotlib.patches import Circle
import numpy as np

file_p = '../data/p_grob.dat'
p = np.loadtxt(file_p, 'double')

file_b = '../data/b_grob.dat'
b = np.loadtxt(file_b, 'int')

file_t = '../data/t_grob.dat'
t = np.loadtxt(file_t, 'int')

fig = plt.figure()

ax = fig.add_subplot(111, aspect='equal')

#circle1 = Circle( (0.8,1.7), radius=0.2, color='red' )
#ax.add_patch(circle1)
#circle2 = Circle( (1.9, 1.7), radius=0.2, color='red' )
#ax.add_patch(circle2)
#circle3 = Circle( (3.0, 1.7), radius=0.2, color='red' )
#ax.add_patch(circle3)
#circle4 = Circle( (4.1, 1.7), radius=0.2, color='red' )
#ax.add_patch(circle4)

x = p[:,0]
y = p[:,1]
plt.triplot(x, y, t-1, '-')

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
	line = Line2D([x1, x2], [y1, y2], color=col, lw=4)
	ax.add_line(line)

ax.set_xlim(-0.2,5.2)
ax.set_ylim(-0.1,2.1)

#plt.savefig('Gitter_grob.pdf')
plt.show()
