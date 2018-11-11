import sys

tmp = sys.argv[1:]

from random import randint as rint
N = int(tmp[0])
Xmin = -rint(1, N)
Xmax = rint(1,N)
Ymin = -rint(1,N)
Ymax = rint(1,N)
 
filename = "test"
f = open(filename, "w+")
f.write(str(N) + '\n')
for i in range(N):
	x = rint(Xmin, Xmax)
	y = rint(Ymin, Ymax)
	f.write(str(x) + ' ' + str(y) + '\n')
f.close()
