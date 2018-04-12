def approximation(inputs,weights):
	res = weights[0]
	for i in range(len(inputs)-1):
		res += weights[i + 1] * inputs[i]
	return 1.0 if res >= 0.0 else 0.0

inputs = [
[1.145456,1.56023,1],
[2.560, 1.26,0]
]
weights = [ 1,1.03]

for inp in inputs:
	print("Prévu : %d, Calculé : %d", inp[2], approximation(inp, weights));

