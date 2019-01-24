import numpy as np

data = np.loadtxt("d0_Hists/d0s_5_4/d0_0/d12_0")

print(len(data),len(data[0]))

data2 = np.loadtxt("Histograms/EGamma_661/d0_0/d12_0")

print(len(data2), len(data2[0]))
