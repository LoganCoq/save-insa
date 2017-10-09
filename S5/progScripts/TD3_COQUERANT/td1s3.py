# TD1 Sceance 3

# 3.1

# 3.1.1

def isqrt_hard(n):
	"""
	This function search which value is the square root of the value n by trying each int
		( 0,1,2,3,....)
	If the square root isn't an int, it will return the closer root below

	CU : n is a natural integer
	"""
	val = 0
	while (val * val) < n and (val * val) != n:
		val += 1
	return val if (val * val) == n else val-1

print("test isqrt_hard")
print(isqrt_hard(10))
print(isqrt_hard(100))
print(isqrt_hard(24))

# 3.1.2

#    2*1-1 + 2*2-1 + 2*3-1 + 2*4-1 = 16
#    2*1-1 + 2*2-1 + 2*3-1 + 2*4-1 + 2*5-1 = 25

def isqrt_sum(n):
	"""
	This function search the closer square root of n by computing each odd number.
	ex : 2*1-1 + 2*2-1 + ...
	It will return the square root the closer to sqrt(n)

	CU : n is a natural integer
	"""
	val = 1
	res = 0
	while res < n:
		res += 2*val-1
		val += 1
	return (val-1) if res ==  n else val - 2

print("test isqrt_sum")
print(isqrt_sum(10))
print(isqrt_sum(100))
print(isqrt_sum(24))


# 3.1.3

def isqrt_dicho(n):
	"""
	This function compute the square root of n using the dichotomy search

	CU : n is a natural integer
	"""
	debut = 0
	milieu = n // 2
	fin = n
	while not ( milieu*milieu < n < (milieu+1)*(milieu+1) ):
		if milieu*milieu > n:
			fin = milieu
			milieu = debut + (fin-debut)//2
		elif milieu*milieu == n:
			return milieu
		else:
			debut = milieu
			milieu = debut + (fin-debut)//2
	return milieu
print("test isqrt_dicho")
print(isqrt_dicho(10))
print(isqrt_dicho(100))
print(isqrt_dicho(24))


# 3.1.4
import math

def isqrt_builtin(n):
	return math.floor(math.sqrt(n))

#affichage courbes temps mis par function en fonction de n

#l'affichage est réaliser uniquement jusqu'à 10 car les calculs mettaient du temps


import timeit

#import matplotlib.pyplot as plt

#n = 10
#x = []
#y_hard = []
#y_sum = []
#y_dicho = []
#y_builtin = []
# for i in range(2, n+1):
# 	print(i)
# 	x.append(i)
# 	y_hard.append(timeit.timeit(stmt='isqrt_hard('+str(i)+')', setup="from __main__ import isqrt_hard"))
# 	y_sum.append(timeit.timeit(stmt='isqrt_sum('+str(i)+')', setup="from __main__ import isqrt_sum"))
# 	y_dicho.append(timeit.timeit(stmt='isqrt_dicho('+str(i)+')', setup="from __main__ import isqrt_dicho"))
# 	y_builtin.append(timeit.timeit(stmt='isqrt_builtin('+str(i)+')', setup="from __main__ import isqrt_builtin"))
#
# plt.plot(x, y_hard)
# plt.axis([1,10,0,2])
# plt.ylabel('Time')
# plt.xlabel('n')
# plt.show()
# plt.plot(x, y_sum)
# plt.axis([1,10,0,2])
# plt.ylabel('Time')
# plt.xlabel('n')
# plt.show()
# plt.plot(x, y_dicho)
# plt.axis([1,10,0,2])
# plt.ylabel('Time')
# plt.xlabel('n')
# plt.show()
# plt.plot(x, y_builtin)
# plt.axis([1,10,0,2])
# plt.ylabel('Time')
# plt.xlabel('n')
# plt.show()




print("timeit for isqrt_hard : ")
#print(timeit.timeit(stmt='isqrt_hard(1000)', setup="from __main__ import isqrt_hard"))
print("timeit for isqrt_sum : ")
#print(timeit.timeit(stmt='isqrt_sum(1000)', setup="from __main__ import isqrt_sum"))
print("timeit for isqrt_dicho : " )
#print(timeit.timeit(stmt='isqrt_dicho(1000)', setup="from __main__ import isqrt_dicho"))
print("timeit for isqrt_builtin : " )
#print(timeit.timeit(stmt='isqrt_builtin(1000)', setup="from __main__ import isqrt_builtin"))



#On peut remarquer que la fonction la plus lente est la fonction isqrt_hard ainsi que
#la fonction isqrt_sum qui ont peut une légère différence sur n=1000
#Tandis que les fonction isqrt_dicho et isqrt_builtin sont elles bien plus rapide,
#ce qui est cohérent car la recherche dichotomique réalise moins de test et d'opération
#que hard et sum
