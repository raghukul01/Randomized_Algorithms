import sys

filename = ["./out/rand_out", "./out/tri_3_out", "./out/tri_4_out"]
for file in filename:
	f = open(file)
	tmp = list(map(float, f.read().split()))

	N = len(tmp)
	sm = 0
	mx = -1
	for i in range(N):
		sm += tmp[i]
		mx = max(mx, tmp[i])
	avg = sm / N
	sd = 0
	for i in range(N):
		tmp[i] -= avg
		sd += tmp[i]*tmp[i]

	sd /= N
	sd = sd**0.5
	print avg, sd, mx