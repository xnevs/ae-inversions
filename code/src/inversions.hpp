#ifndef INVERSIONS_HPP
#define INVERSIONS_HPP

#include <vector>

std::vector<int>::size_type inversions_bf(std::vector<int> const &a);

std::vector<int>::size_type inversions_is1(std::vector<int> a);

std::vector<int>::size_type inversions_is2(std::vector<int> a);

std::vector<int>::size_type inversions_ms1(std::vector<int> a);

std::vector<int>::size_type inversions_ms2(std::vector<int> a);

std::vector<int>::size_type inversions_ms3(std::vector<int> a);

#include <cstddef>
size_t inversions_ms3_a(int a[], size_t n);

#endif
