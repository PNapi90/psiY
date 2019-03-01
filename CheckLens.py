import numpy as np

data = np.loadtxt("d0_Hists/d0s_5_4/d0_0/d12_0")
data2 = np.loadtxt("ComptonHists/ComptonHist_661")
data3 = np.loadtxt("ComptonHists/ComptonHist_661_Merge")
print(len(data),len(data[0]))
print(len(data2), len(data2[0]))
print(len(data3), len(data3[0]))
