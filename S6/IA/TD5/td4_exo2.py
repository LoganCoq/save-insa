import numpy as np
import matplotlib.pyplot as plt


X = np.loadtxt("iris_a.txt", usecols=(0,1,2,3), delimiters=",", dtype=float)

Y = np.loadtxt("iris_a.txt", usecols=(4,), delimiters=",", dtype=int)

plt.scatter(X[0:50,1], X[0:50,2], color="b")

plt.scatter(X[50:100,1], X[50:100,2], color="r")

plt.show()
