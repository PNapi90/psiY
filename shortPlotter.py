import numpy as np
import pylab as py

py.close("all")

data0 = np.loadtxt("Histograms/EGamma_661/d0_120/d12_40")

from matplotlib.colors import LogNorm

py.figure(1,figsize=(5,4))
py.clf()
py.imshow(data0, cmap=py.cm.jet, origin='lower', interpolation='none', extent=[0, 180, 0, 700], norm=LogNorm(), aspect="auto")



xbins = [i for i in range(len(data0[0]))]
print(len(data0),len(data0[0]))

colors = py.cm.jet(np.linspace(0,1,len(data0)))

py.figure(6,figsize=(5,4))
py.clf()
for i in range(len(data0)):
    if i % 5 != 0:
        continue
    py.plot(xbins,data0[i,:],color=colors[i],ls=':')