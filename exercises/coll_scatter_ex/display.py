import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import os

d1 = np.loadtxt('ex1')
d2 = np.loadtxt('ex2')
d3 = np.loadtxt('ex3')
d4 = np.loadtxt('ex4')

d1 = d1[::-1]
d2 = d2[::-1]
d3 = d3[::-1]
d4 = d4[::-1]

plt.figure(figsize=(15,15))
plt.subplot(221)
plt.imshow(d1, extent=[-2.0, 1.0, -1.5, 1.5])
plt.subplot(222)
plt.imshow(d2, extent=[-0.749, -0.750, -0.0605, -0.0615])
plt.subplot(223)
plt.imshow(d3, extent=[-1.45, -1.35, -0.05, 0.05])
plt.subplot(224)
plt.imshow(d4, extent=[-1.30, -1.15, 0.25, 0.40])
plt.savefig('mandelbrot.png')
print(os.listdir('.'))
print('TECHIO> open --static-dir /project/target/coll_scatter_ex mandelbrot.pngpneu')
print('TECHIO> success true')
