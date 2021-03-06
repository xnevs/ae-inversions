#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <algorithm>
#include <type_traits>
#include <chrono>
#include <iostream>
#include <ostream>

enum class Alg {
    bf,
    is1,
    is2,
    is2a,
    ms1,
    ms2,
    ms3,
    ms2_is2,
    ms2_is2a,
    ms3_is2,
    bf_idx,
    is1_idx,
    is2_idx,
    ms1_idx,
    ms2_idx,
    ms3_idx,
};

constexpr auto NUM_ALGS = static_cast<typename std::underlying_type<Alg>::type>(Alg::ms3_idx) + 1;

class AlgFlags : std::bitset<NUM_ALGS> {
  public:
    std::bitset<NUM_ALGS> & set(Alg pos, bool value = true) {
        return std::bitset<NUM_ALGS>::set(static_cast<std::underlying_type<Alg>::type>(pos), value);
    }
    constexpr bool operator[](Alg pos) const {
        return std::bitset<NUM_ALGS>::operator[](static_cast<std::underlying_type<Alg>::type>(pos));
    }
};

enum class Seq {
    inc,
    dec,
    rnd
};

inline std::ostream & operator<<(std::ostream & out, Seq seq) {
    switch(seq) {
      case Seq::inc:
        out << "inc";
        break;
      case Seq::dec:
        out << "dec";
        break;
      case Seq::rnd:
        out << "rnd";
        break;
    }
    return out;
}

template <typename URNG>
std::vector<int> generate(std::vector<int>::size_type n, Seq seq, URNG && gen) {
    std::vector<int> v(n);

    for(std::vector<int>::size_type i=0; i<n; i++)
        v[i] = i;

    switch(seq) {
      case Seq::inc:
        break;
      case Seq::dec:
        std::reverse(v.begin(),v.end());
        break;
      case Seq::rnd:
        std::shuffle(v.begin(),v.end(),gen);
        break;
    }

    return v;
}

#define TEST(f, test_cases) \
do {                                                                           \
    decltype((f)((test_cases).front())) _TEST_count = 0;                       \
    std::chrono::time_point<std::chrono::steady_clock> _TEST_start, _TEST_end; \
    _TEST_start = std::chrono::steady_clock::now();                            \
    for(auto const & _TEST_a : (test_cases)) {                                 \
        _TEST_count += (f)((_TEST_a));                                         \
    }                                                                          \
    _TEST_end = std::chrono::steady_clock::now();                              \
    auto _TEST_elapsed = std::chrono::duration_cast<std::chrono::milliseconds> \
                                                   (_TEST_end - _TEST_start);  \
    std::cout << #f+11 << "," << n << "," << seq << "," << rep << ","          \
         << _TEST_count << "," << _TEST_elapsed.count() << endl;               \
} while(0)
    //std::chrono::duration<double> _TEST_elapsed = _TEST_end - _TEST_start; 

inline std::ostream & operator<<(std::ostream & out, std::vector<int> const & v) {
    out << "{";
    for(auto const i : v) {
        out << " " << i;
    }
    out << " }";
    return out;
}

#endif
