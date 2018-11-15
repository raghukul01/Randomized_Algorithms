import sys

filename = ["./out/rand_out"]
percent = [1.1, 1.2, 1.5, 2]
for file in filename:
	f = open(file)
	tmp = list(map(float, f.read().split()))

	N = len(tmp)
	sm = 0
	mx = -1
	mn = 1e10
	for i in range(N):
		sm += tmp[i]
		mx = max(mx, tmp[i])
		mn = min(mn, tmp[i])
	avg = sm / N
	for i in range(4):
		percent[i] *= avg
		cnt = 0
		for j in range(N):
			if tmp[j] > percent[i]:
				cnt+=1
		print round((cnt *100) / float(N) , 3), 