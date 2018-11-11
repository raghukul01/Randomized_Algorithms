import sys

filename = ["./out/rand_out"]
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
	sd = 0
	for i in range(N):
		tmp[i] -= avg
		sd += tmp[i]*tmp[i]

	sd /= N
	sd = sd**0.5
	print avg, mx, mn, sd