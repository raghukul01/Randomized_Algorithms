#!/bin/bash

N=100
LEDAROOT="/home/raghukul/github/CS648/Smallest_Enclosing_Circle_Problem/LEDA"
export LEDAROOT
LD_LIBRARY_PATH=$LEDAROOT
export LD_LIBRARY_PATH

mkdir -p "out"
mkdir -p "failed"

until [ $N -lt 10 ];do
	python generate.py $N
	(./binaries/random < "test") > "./out/rand_out"
	(./binaries/trivia_3 < "test") > "./out/tri_3_out"
	if diff "./out/rand_out" "./out/tri_3_out" > /dev/null
	then
		echo "Files are same"
	else
		echo "Files are not same"
		(cat "test") > "./failed/failed$N.txt"
	fi
	let N-=1
done
rm -rf "./out"
rm "test"

