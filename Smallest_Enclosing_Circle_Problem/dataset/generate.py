from random import randint as rint
N = input("number of points: ")
Xmin = input("min value of X: ")
Xmax = input("max value of X: ")
Ymin = input("min value of Y: ")
Ymax = input("max value of Y: ")

filename = raw_input("enter filename: ")
f = open(filename, "w+")
f.write(str(N) + '\n')
for i in range(N):
	x = rint(Xmin, Xmax)
	y = rint(Ymin, Ymax)
	f.write(str(x) + ' ' + str(y) + '\n')
f.close()
