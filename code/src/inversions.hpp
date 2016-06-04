#ifndef INVERSIONS_HPP
#define INVERSIONS_HPP

#include <vector>

std::vector<int>::size_type inversions_bf(std::vector<int> const & a);
std::vector<int>::size_type inversions_is1(std::vector<int> a);
std::vector<int>::size_type inversions_is2(std::vector<int> a);
std::vector<int>::size_type inversions_is2a(std::vector<int> a);
std::vector<int>::size_type inversions_ms1(std::vector<int> a);
std::vector<int>::size_type inversions_ms2(std::vector<int> a);
std::vector<int>::size_type inversions_ms3(std::vector<int> a);

std::vector<int>::size_type inversions_ms3_is2(std::vector<int> a);
std::vector<int>::size_type inversions_ms2_is2(std::vector<int> a);

std::vector<int>::size_type inversions_bf_idx(std::vector<int> const & a);
std::vector<int>::size_type inversions_is1_idx(std::vector<int> a);
std::vector<int>::size_type inversions_is2_idx(std::vector<int> a);
std::vector<int>::size_type inversions_ms1_idx(std::vector<int> a);
std::vector<int>::size_type inversions_ms2_idx(std::vector<int> a);
std::vector<int>::size_type inversions_ms3_idx(std::vector<int> a);

#endif
