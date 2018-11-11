#!/bin/bash

N=60
M=$1
LEDAROOT="/home/raghukul/github/CS648/Smallest_Enclosing_Circle_Problem/LEDA"
export LEDAROOT
LD_LIBRARY_PATH=$LEDAROOT
export LD_LIBRARY_PATH
rm -rf "failed" "out"
mkdir -p "out"
mkdir -p "failed"

until [ $N -lt 10 ];do
	python generate.py $M
	(./binaries/random < "test") >> "./out/rand_out"
	(./binaries/trivia_3 < "test") >> "./out/tri_3_out"
	(./binaries/trivia_4 < "test") >> "./out/tri_4_out"
	let N-=1
done
rm "test"
python compute_avg.py

