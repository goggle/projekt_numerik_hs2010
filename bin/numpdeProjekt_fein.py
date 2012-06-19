#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from matplotlib.patches import CirclePolygon
from matplotlib.lines import Line2D

class DraggableCircle:
	def __init__(self, circle):
		self.circle = circle
		self.press = None

	def connect(self):
		self.cidpress = self.circle.figure.canvas.mpl_connect('button_press_event', self.on_press)
		self.cidrelease = self.circle.figure.canvas.mpl_connect('button_release_event', self.on_release)
		self.cidmotion = self.circle.figure.canvas.mpl_connect('motion_notify_event', self.on_motion)

	def on_press(self, event):
		if event.inaxes != self.circle.axes: return

		contains, attrd = self.circle.contains(event)
		if not contains: return
		x0, y0 = self.circle.xy
		self.press = x0, y0, event.xdata, event.ydata

	def on_motion(self, event):
		if self.press is None: return
		if event.inaxes != self.circle.axes: return
		x0, y0, xpress, ypress = self.press
		dx = event.xdata - xpress
		dy = event.ydata - ypress
		self.circle.xy=(x0+dx, y0+dy)
		self.circle.figure.canvas.draw()


	def on_release(self, event):
		self.press = None
		#x0, y0 = self.circle.xy
		self.circle.figure.canvas.draw()

	def disconnect(self):
		self.circle.figure.canvas.mpl_disconnect(self.cidpress)
		self.circle.figure.canvas.mpl_disconnect(self.cidrelease)
		self.circle.figure.canvas.mpl_disconnect(self.cidmotion)

# Create plots of the solution:
def plotSolution():
	plt.savefig('../movie/positions.png')
	plt.close()
	file_u = '../data/u_fein.dat'
	u = np.loadtxt(file_u, 'double')
	time = 0.0
	dt = 0.2
	length = len(u[:,0])
	movie = ''
	for i in range(0, length):
		plot_file = '../movie/plot%.3d.png' %(i)
		f = plt.figure(figsize=(9,4))
		f.subplots_adjust(left=0.05)
		f.subplots_adjust(right=1.1)
		f.subplots_adjust(bottom=0.05)
		f.subplots_adjust(top=0.90)
		a = f.add_subplot(111)
		a.set_xlim(-0.1, 5.1)
		a.set_ylim(-0.5, 2.1)
		print "Plotting image %d of %d..." %(i+1, length)
		img = plt.imread(plot_file)
		con = plt.imshow(img, cmap=cm.jet, extent=[0,5,0,2], vmin=14.0, vmax=28.0)
		cbar = plt.colorbar(con, ticks=range(14,29))
		a.text(0.0, -0.3, 'Zeit: %.1f'%(time), fontsize=15)
		mean = np.mean(u[i,:])
		a.text(1.0, -0.3, 'Durchschnittstemperatur: %.1f' %(mean), fontsize=15)
		plt.title(unicode('Temperaturverteilung im grossen H\366rsaal', 'latin-1'), fontsize=16)
		plt.savefig('../movie/movie%.3d.png' %(i+1))
		movie += '../movie/movie%.3d.png ' %(i+1)
		time += dt
	# Show the movie:
	print "Creating movie..."
	os.system('animate -delay 50 ' + movie)



# Start the numerical simulation when a key is pressed:
def on_keypress(event):
	os.system("rm -f ../movie/movie*.png")
	os.system("rm -f ../movie/plot*.png")
	x1, y1 = circle1.xy
	x2, y2 = circle2.xy
	x3, y3 = circle3.xy
	x4, y4 = circle4.xy
	print 'Radiator 1: (%.2f, %.2f)' %(x1, y1)
	print 'Radiator 2: (%.2f, %.2f)' %(x2, y2)
	print 'Radiator 3: (%.2f, %.2f)' %(x3, y3)
	print 'Radiator 4: (%.2f, %.2f)' %(x4, y4)
	print 'Performing numerical simulation...'
	os.system('./numSimulation_fein %f %f %f %f %f %f %f %f' %(x1, y1, x2, y2, x3, y3, x4, y4))
	plotSolution()


# Read in the Points and Triangles:
file_p = '../data/p_fein.dat'
p = np.loadtxt(file_p, 'double')
file_t = '../data/t_fein.dat'
triangles = np.loadtxt(file_t, 'int') - 1
x = p[:,0]
y = p[:,1]


fig = plt.figure(figsize=(9,4))
ax = fig.add_subplot(111)
ax.set_xlim(-0.1, 5.1)
ax.set_ylim(-0.1, 2.1)

# Draw the circles:
circle1 = CirclePolygon( (0.8, 1.7), radius=0.2, color='darkred')
circle2 = CirclePolygon( (1.9, 1.7), radius=0.2, color='darkred')
circle3 = CirclePolygon( (3.0, 1.7), radius=0.2, color='darkred')
circle4 = CirclePolygon( (4.1, 1.7), radius=0.2, color='darkred')
circles = [ax.add_patch(circle1), ax.add_patch(circle2), ax.add_patch(circle3), ax.add_patch(circle4)]
drs = []

#Draw the walls:
line = Line2D([0, 5], [0, 0], color='black', lw=6) 
ax.add_line(line)
line = Line2D([0, 5], [2, 2], color='black', lw=6) 
ax.add_line(line)
line = Line2D([0, 0], [0, 2], color='black', lw=6) 
ax.add_line(line)
line = Line2D([5, 5], [0, 2], color='black', lw=6) 
ax.add_line(line)
line = Line2D([0.75, 1.5], [0, 0], color='green', lw=6) 
ax.add_line(line)
line = Line2D([3.5, 4.25], [0, 0], color='green', lw=6) 
ax.add_line(line)
line = Line2D([0.5, 1.1], [2, 2], color='blue', lw=6) 
ax.add_line(line)
line = Line2D([1.6, 2.2], [2, 2], color='blue', lw=6) 
ax.add_line(line)
line = Line2D([2.7, 3.3], [2, 2], color='blue', lw=6) 
ax.add_line(line)
line = Line2D([3.8, 4.4], [2, 2], color='blue', lw=6) 
ax.add_line(line)

# Connect the circles to the event handlers:
for circle in circles:
	dr = DraggableCircle(circle)
	dr.connect()
	drs.append(dr)

plt.title('Simulation mit Tastendruck starten')

cid = fig.canvas.mpl_connect('key_press_event', on_keypress)
plt.show()
