import numpy as np
import random

inputs = [ ([1,2,4],1), ([2,5,1],0) ]

def perceptron(inputs):
	weights = [1,1,1]
	delta_weight = [0,0,0]
	n = 0.1
	mal_classe = 1
	while mal_classe != 0:
		mal_classe = 0
		for i in range(1,len(inputs)):
			if inputs[i][1]*np.transpose(inputs[i][0])*weights >= 0:
				mal_classe += 1
				delta_weight += (-inputs[i][1])*inputs[i][0]
		weights -= n*delta_weight
		tau += 1
	return weights


import numpy as np
import random

inputs = np.ndarray( [[1,2,4], [2,5,1]])
targets = np.ndarray( [1,0] )

def perceptron(inputs, targets):
        weights = np.array([random.random(),random.random(),random.random()])
        delta_weight = np.array([[0,0,0]])
        n = 0.1
        mal_classe = 1
        tau = 0
        while mal_classe != 0:
                mal_classe = 0
                for i in range(0,np.size(inputs)-1):
                        if targets[i]*np.dot(np.transpose(weights[tau]),inputs[i]) <= 0:
                                mal_classe += 1
                                delta_weight += (-targets[i])*inputs[i]
                weights[tau+1] = weights[tau] - n*delta_weight
                tau += 1
        return weights


print(perceptron(inputs, targets))

