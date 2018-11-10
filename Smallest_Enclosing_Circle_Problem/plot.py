import math
import matplotlib.pyplot as plt

fname = 'dataset/test'
f1 = open(fname, "r")
temp = map(int, f1.read().split())
N = temp[0]
Px = []
Py = []
for i in range(1, len(temp)):
	if i%2 == 1:
		Px.append(temp[i])
	else:
		Py.append(temp[i])

f2 = open("circle.txt", "r")
temp = map(float, f2.read().split())
X, Y = temp[0], temp[1]
R = temp[2]
C = [X, Y]

C1 = plt.Circle(C, R, color='blue', fill=False)

fig, ax = plt.subplots()
ax.plot(Px, Py, "ro")
ax.axis('scaled')
ax.add_artist(C1)
W = max(C[0]+R+1, C[1]+R+1)
Q = min(C[0]-R-1,C[1]-R-1 )
ax.set_xlim(Q, W)
ax.set_ylim(Q, W)
# ax.gca().set_aspect('equal', adjustable='box')
plt.show()