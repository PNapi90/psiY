import numpy as np
import pylab as py

data0 = np.loadtxt("Histograms/EGamma_661/d0_40/d12_120")
data1 = np.loadtxt("Histograms/EGamma_661/d0_60/d12_120")
data2 = np.loadtxt("Histograms/EGamma_661/d0_80/d12_120")
data3 = np.loadtxt("Histograms/EGamma_661/d0_100/d12_120")
data4 = np.loadtxt("Histograms/EGamma_661/d0_120/d12_120")

from matplotlib.colors import LogNorm

py.figure(1,figsize=(5,4))
py.clf()
py.imshow(data0, cmap=py.cm.jet, origin='lower', interpolation='none', extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")

py.figure(2,figsize=(5,4))
py.clf()
py.imshow(data1, cmap=py.cm.jet, origin='lower', interpolation='none', extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")

py.figure(3,figsize=(5,4))
py.clf()
py.imshow(data2, cmap=py.cm.jet, origin='lower', interpolation='none', extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")

py.figure(4, figsize=(5, 4))
py.clf()
py.imshow(data3, cmap=py.cm.jet, origin='lower', interpolation='none',
          extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")

py.figure(5, figsize=(5, 4))
py.clf()
py.imshow(data4, cmap=py.cm.jet, origin='lower', interpolation='none',
          extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")

xbins = [i for i in range(len(data0[0]))]
print(len(data0),len(data0[0]))

colors = py.cm.jet(np.linspace(0,1,len(data0)))

py.figure(6,figsize=(5,4))
py.clf()
for i in range(len(data0)):
    if i % 5 != 0:
        continue
    py.plot(xbins,data0[i,:],color=colors[i],ls=':')