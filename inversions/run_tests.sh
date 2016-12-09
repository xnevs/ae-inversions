#!/bin/bash

slow_algs='bf,bf_idx,is1,is1_idx,is2,is2a,is2_idx'
fast_algs='ms1,ms1_idx,ms2,ms2_idx,ms2_is2,ms2_is2a,ms3,ms3_idx,ms3_is2'
all_algs=$slow_algs,$fast_algs

tiny_ns=$(seq 10 10 200)
small_ns=$(seq 1000 1000 9000)
med_ns=$(seq 10000 10000 90000)
large_ns="$(seq 100000 100000 900000) $(seq 1000000 1000000 10000000)"

function run_all_type {
    for size in $tiny_ns
    do
        ./inversions $all_algs $size $1 1000000
    done

    for size in $small_ns
    do
        ./inversions $all_algs $size $1 100
    done

    for size in $med_ns
    do
        ./inversions $slow_algs $size $1 1
    done
    for size in $med_ns
    do
        ./inversions $fast_algs $size $1 100
    done

    for size in $large_ns
    do
        ./inversions $fast_algs $size $1 1
    done
}

for seq in inc dec rnd
do
    run_all_type $seq
done
