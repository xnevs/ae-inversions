# ae-inversions

A benchmark of different inversion counting algorithms. Created as part of an Algorithm Engineering class.

## Inversions

Given an integer sequence a = a_1, a_2, ..., a_n we define an inversion as a pair of indices i < j, such that a_i > a_j.

## The Problem

Count the number of inversions in a given sequence.

## The Algorithms

Several algorithms (and their variations) are implemented and benchmarked:
  * Brute force
  * Inversion counting by insertion sort
  * Inversion counting by merge sort
  * Hybrid algorithms

## Building and Running
  Run `make` in the `code` directory.
  The result of building is the `inversions` executable, that benchmarks different algorithms.
  
  Example of running can be found in the `run_tests.sh` script.
