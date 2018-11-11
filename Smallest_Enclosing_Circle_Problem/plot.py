import math
import matplotlib.pyplot as plt

fname = 'test'
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

f2 = open('circle', "r")
tmp = map(float, f2.read().split())
N = len(tmp) / 3
C = []
for i in xrange(0,3*N,3):
	C.append([tmp[i], tmp[i+1], tmp[i+2]])

W = max(C[N-1][0] + C[N-1][2] + 1, C[N-1][1] + C[N-1][2] + 1)
Q = max(C[N-1][0] - C[N-1][2] - 1, C[N-1][1] - C[N-1][2] - 1)

for i in range(1,N):
	fig, ax = plt.subplots()
	ax.plot(Px[:i], Py[:i], "ro")
	# hack to scale the graph :P
	ax.plot([W], [Q], "wo")
	ax.plot([W], [W], "wo")
	ax.plot([Q], [W], "wo")
	ax.plot([Q], [Q], "wo")
	ax.plot([Px[i]], [Py[i]], "bo")
	ax.set_xlim(Q, W)
	ax.set_ylim(Q, W)
	ax.axis('scaled')
	C1 = plt.Circle((C[i-1][0], C[i-1][1]), C[i-1][2], color='blue', fill=False)
	ax.add_artist(C1)
	fig.savefig('./images/' + 'file' + str(i) + 'a')
	C1.remove()
	C1 = plt.Circle((C[i][0], C[i][1]), C[i][2], color='blue', fill=False)
	ax.add_artist(C1)
	fig.savefig('./images/' + 'file' + str(i) + 'b')
	# plt.show()
"""
	W = max(C[N-1][0] + C[N-1][2] + 1, C[N-1][1] + C[N-1][2] + 1)
	Q = max(C[N-1][0] - C[N-1][2] - 1, C[N-1][1] - C[][2] - 1)
W = max(C[N-1]+R+1, C[N-1]+R+1)
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
"""