#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_bf_idx(std::vector<int> const & a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;
    for(size_type i=0; i<n-1; i++)
        for(size_type j=i+1; j<n; j++)
            if(comp(a[j], a[i]))
                ++count;
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_bf(std::vector<int> const & a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    size_type count = 0;
    for(auto i=std::begin(a); i!=prev(std::end(a)); ++i)
        for(auto j=next(i); j!=std::end(a); ++j)
            if(comp(*j, *i))
                ++count;
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_is1_idx(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;
    for(size_type i=1; i<n; ++i) {
        size_type j;
        for(j=i; j>0 && comp(a[j],a[j-1]); --j) {
            swap(a[j-1],a[j]);
        }
        count += i-j;
    }
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_is1(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    size_type count = 0;
    for(auto i=next(std::begin(a)); i!=std::end(a); ++i) {
        decltype(i) j;
        for(j=i; j!=std::begin(a) && comp(*j,*prev(j)); --j)
            swap(*prev(j), *j);
        count += distance(j, i);
    }
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_is2_idx(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;
    for(size_type i=1; i<n; ++i) {
        auto x = a[i];
        size_type j;
        for(j=i; j>0 && comp(x,a[j-1]); --j) {
            a[j] = a[j-1];
        }
        a[j] = x;
        count += i-j;
    }
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_is2(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    size_type count = 0;
    for(auto i=next(std::begin(a)); i!=std::end(a); ++i) {
        auto j = upper_bound(std::begin(a), i, *i, comp);
        rotate(j, i, next(i));
        count += distance(j, i);
    }
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type ms1_helper_idx(std::vector<int> &a, std::vector<int>::size_type first, std::vector<int>::size_type last, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = last-first;
    if(n < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms1_helper_idx(a,first,mid, comp, swap);
    auto count2 = ms1_helper_idx(a,mid,last, comp, swap);

    size_type count = 0;
    std::vector<int> b(n);
    auto k0=first, k1=mid;
    for(size_type k=0; k<n; k++) {
        if(k1 != last && (k0 == mid || comp(a[k1], a[k0]))) {
            b[k] = a[k1++];
            count += mid - k0;
        } else {
            b[k] = a[k0++];
        }
    }
    move(std::begin(b), std::end(b), std::begin(a)+first);

    return count + count1 + count2;
}
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms1_idx(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    return ms1_helper_idx(a, 0, a.size(), comp, swap);
}

template<typename Comp, typename Swap>
std::vector<int>::size_type ms1_helper(std::vector<int>::iterator first, std::vector<int>::iterator last, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = distance(first, last);
    if(n < 2)
        return 0;

    auto mid = first + n / 2;
    auto count1 = ms1_helper(first, mid, comp, swap);
    auto count2 = ms1_helper(mid, last, comp, swap);

    size_type count = 0;
    std::vector<int> b(n);
    auto k0=first, k1=mid;
    for(auto k=std::begin(b); k!=std::end(b); ++k) {
        if(k1 != last && (k0 == mid || comp(*k1, *k0))) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
        }
    }
    move(std::begin(b), std::end(b), first);

    return count + count1 + count2;
}
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms1(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    return ms1_helper(std::begin(a), std::end(a), comp, swap);
}

template<typename Comp, typename Swap>
std::vector<int>::size_type ms2_helper_idx(std::vector<int> & a, std::vector<int>::size_type first, std::vector<int>::size_type last, std::vector<int> & b, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    if(last - first < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms2_helper_idx(a,first,mid,b, comp, swap);
    auto count2 = ms2_helper_idx(a,mid,last,b, comp, swap);

    size_type count = 0;
    auto k0=first, k1=mid;
    for(auto k=first; k<last; k++) {
        if(k1 != last && (k0 == mid || comp(a[k1], a[k0]))) {
            b[k] = a[k1++];
            count += mid - k0;
        } else {
            b[k] = a[k0++];
        }
    }
    move(std::begin(b)+first, std::begin(b)+last, std::begin(a)+first);

    return count + count1 + count2;
}
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms2_idx(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    auto n = a.size();
    std::vector<int> b(n);
    return ms2_helper_idx(a,0,n,b, comp, swap);
}

template<typename Comp, typename Swap>
std::vector<int>::size_type ms2_helper(std::vector<int>::iterator first, std::vector<int>::iterator last, std::vector<int>::iterator bfirst, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = distance(first, last);
    if(n < 2)
        return 0;

    auto mid = first + n / 2;
    auto bmid = bfirst + n / 2;
    auto blast = bfirst + n;

    auto count1 = ms2_helper(first, mid, bfirst, comp, swap);
    auto count2 = ms2_helper(mid, last, bmid, comp, swap);

    size_type count = 0;
    auto k0=first, k1=mid;
    for(auto k=bfirst; k!=blast; ++k) {
        if(k1 != last && (k0 == mid || comp(*k1, *k0))) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
        }

    }
    move(bfirst, blast, first);

    return count + count1 + count2;
}
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms2(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    auto n = a.size();
    std::vector<int> b(n);
    return ms2_helper(std::begin(a), std::end(a), std::begin(b), comp, swap);
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms3_idx(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;
    std::vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        for(size_type first=0; first<n; first+=2*width) {
            auto mid = std::min(first+width, n);
            auto last = std::min(mid+width, n);
            auto k0=first, k1=mid;
            for(size_type k=first; k<last; ++k) {
                if(k1 != last && (k0 == mid || comp(a[k1], a[k0]))) {
                    b[k] = a[k1++];
                    count += mid - k0;
                } else {
                    b[k] = a[k0++];
                }
            }
        }
        move(std::begin(b), std::end(b), std::begin(a));
    }
    return count;
}

template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms3(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;
    std::vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        for(size_type i=0; i<n; i+=2*width) {
            auto m = std::min(width, n-i);
            auto l = std::min(m+width, n-i);
            auto first = std::begin(a)+i;
            auto mid = first + m;
            auto last = first + l;
            auto bfirst = std::begin(b) + i;
            auto blast = bfirst + l;
            auto k0=first, k1=mid;
            for(auto k=bfirst; k<blast; ++k) {
                if(k1 != last && (k0 == mid || comp(*k1, *k0))) {
                    *k = *(k1++);
                    count += distance(k0, mid);
                } else {
                    *k = *(k0++);
                }
            }
        }
        move(std::begin(b), std::end(b), std::begin(a));
    }
    return count;
}

#define MS2_CUTOFF 17 
template<typename Comp, typename Swap>
std::vector<int>::size_type ms2_is2_helper(std::vector<int>::iterator first, std::vector<int>::iterator last, std::vector<int>::iterator bfirst, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = distance(first, last);
    size_type count = 0;

    if(n < MS2_CUTOFF) {
        for(auto i=next(first); i!=last; ++i) {
            auto j = upper_bound(first, i, *i, comp);
            rotate(j, i, next(i));
            count += distance(j, i);
        }
        return count;
    }

    auto mid = first + n / 2;
    auto bmid = bfirst + n / 2;
    auto blast = bfirst + n;

    auto count1 = ms2_is2_helper(first, mid, bfirst, comp, swap);
    auto count2 = ms2_is2_helper(mid, last, bmid, comp, swap);

    auto k0=first, k1=mid;
    for(auto k=bfirst; k!=blast; ++k) {
        if(k1 != last && (k0 == mid || comp(*k1, *k0))) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
        }

    }
    move(bfirst, blast, first);

    return count + count1 + count2;
}
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms2_is2(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    auto n = a.size();
    std::vector<int> b(n);
    return ms2_is2_helper(std::begin(a), std::end(a), std::begin(b), comp, swap);
}

#define MS3_CUTOFF 17
template<typename Comp, typename Swap>
std::vector<int>::size_type inversions_ms3_is2(std::vector<int> a, Comp comp = Comp(), Swap swap = Swap()) {
    using size_type = std::vector<int>::size_type;
    auto n = a.size();
    size_type count = 0;

    // is2 algorithm
    for(auto first=std::begin(a); first<std::end(a); first+=MS3_CUTOFF) {
        auto last = std::min(first+MS3_CUTOFF,std::end(a));
        for(auto i=next(first); i!=last; ++i) {
            auto j = upper_bound(first, i, *i, comp);
            rotate(j, i, next(i));
            count += distance(j, i);
        }
    }

    // ms3 algorithm
    std::vector<int> b(n);
    for(size_type width = MS3_CUTOFF; width < n; width *= 2) {
        for(size_type i=0; i<n; i+=2*width) {
            auto m = std::min(width, n-i);
            auto l = std::min(m+width, n-i);
            auto first = std::begin(a)+i;
            auto mid = first + m;
            auto last = first + l;
            auto bfirst = std::begin(b) + i;
            auto blast = bfirst + l;
            auto k0=first, k1=mid;
            for(auto k=bfirst; k<blast; ++k) {
                if(k1 != last && (k0 == mid || comp(*k1, *k0))) {
                    *k = *(k1++);
                    count += distance(k0, mid);
                } else {
                    *k = *(k0++);
                }
            }
        }
        move(std::begin(b), std::end(b), std::begin(a));
    }
    return count;
}
