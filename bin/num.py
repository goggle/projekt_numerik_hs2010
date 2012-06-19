#!/usr/bin/python
# -*- coding:utf-8 -*-

import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

#delta = 0.025
#x = y = np.arange(-3.0, 3.0, delta)
#X, Y = np.meshgrid(x, y)
#Z1 = mlab.bivariate_normal(X, Y, 1.0, 1.0, 0.0, 0.0)
#Z2 = mlab.bivariate_normal(X, Y, 1.5, 0.5, 1, 1)
#Z = Z2-Z1  # difference of Gaussians

Z = plt.imread('../movie/plot012.png')

im = plt.imshow(Z, cmap=cm.jet, extent=[0,5,0,2], vmin=14.0, vmax=28.0)

plt.show()


