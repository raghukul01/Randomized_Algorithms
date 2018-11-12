#!/bin/bash

N=250
M=$1
LEDAROOT="$(pwd)/LEDA"
export LEDAROOT
LD_LIBRARY_PATH=$LEDAROOT
export LD_LIBRARY_PATH
rm -rf "failed" "out"
mkdir -p "out"
mkdir -p "failed"

until [ $N -lt 10 ];do
	python generate.py $M
	(./binaries/random < "test") >> "./out/rand_out"
	let N-=1
done
rm "test"
python compute_avg.py

