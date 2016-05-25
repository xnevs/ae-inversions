#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <ostream>
#include <algorithm>

enum class Alg {
    bf,
    is1,
    is2,
    ms1,
    ms2,
    ms3,
    bf_idx,
    is1_idx,
    is2_idx,
    ms1_idx,
    ms2_idx,
    ms3_idx
};

enum class Seq {
    inc,
    dec,
    rnd
};

inline std::ostream &operator<<(std::ostream &out, std::vector<int> const & v) {
    out << "{";
    for(auto const i : v) {
        out << " " << i;
    }
    out << " }";
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

#include <memory>

template <typename URNG>
std::unique_ptr<int[]> generate_a(size_t n, Seq seq, URNG && gen) {
    auto v = std::make_unique<int[]>(n);

    for(size_t i=0; i<n; i++)
        v[i] = i;

    switch(seq) {
    case Seq::inc:
        break;
    case Seq::dec:
        std::reverse(v.get(),v.get()+n);
        break;
    case Seq::rnd:
        std::shuffle(v.get(),v.get()+n,gen);
        break;
    }

    return v;
}
#endif
