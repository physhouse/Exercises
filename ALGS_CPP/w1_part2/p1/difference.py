import numpy as np

data = np.loadtxt("data.txt")
weights = data[:,0]
duration = data[:,1]

#scores = weights / duration
scores = weights - duration
ids = np.arange(0,10000)

D = np.zeros((10000,2))

D[:,0] = ids
D[:,1] = (scores)*10000+weights

B = D[D[:,1].argsort()]
rids = B[:,0].astype(int)

print(B)
print(rids)

ids = rids[::-1]
print(ids)

result = 0
time = 0
for k in range(0,10000):
	time = time + duration[ids[k]]
	result = result + weights[ids[k]] * time

print(result)

