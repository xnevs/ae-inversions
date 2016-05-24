#include "inversions.hpp"

#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

#include "utilities.hpp"

using namespace std;

using size_type = vector<int>::size_type;

size_type inversions_bf(vector<int> const &a) {
    size_type count = 0;
    for(auto i=begin(a); i!=prev(end(a)); ++i)
        for(auto j=next(i); j!=end(a); ++j)
            if(*i > *j)
                ++count;
    return count;
}

size_type inversions_is1(vector<int> a) {
    size_type count = 0;
    for(auto i=next(begin(a)); i!=end(a); ++i) {
        decltype(i) j;
        for(j=i; j!=begin(a) && *prev(j)>*j; --j)
            swap(*prev(j), *j);
        count += distance(j, i);
    }

    return count;
}

size_type inversions_is2(vector<int> a) {
    size_type count = 0;
    for(auto i=next(begin(a)); i!=end(a); ++i) {
        auto j = upper_bound(begin(a), i, *i);
        rotate(j, i, next(i));
        count += distance(j, i);
    }
    return count;
}

size_type ms1_helper(vector<int>::iterator first, vector<int>::iterator last) {
    auto n = distance(first, last);
    if(n < 2)
        return 0;

    auto mid = first + n / 2;
    auto count1 = ms1_helper(first, mid);
    auto count2 = ms1_helper(mid, last);

    size_type count = 0;
    vector<int> b(n);
    auto k0=first, k1=mid;
    for(auto k=begin(b); k!=end(b); ++k) {
        if(k0 != mid && (k1 == last || *k0 <= *k1)) {
            *k = *(k0++);
        } else {
            *k = *(k1++);
            count += distance(k0, mid);
        }
    }
    move(begin(b), end(b), first);

    return count + count1 + count2;
}
size_type inversions_ms1(vector<int> a) {
    return ms1_helper(begin(a), end(a));
}

size_type ms2_helper(vector<int>::iterator first, vector<int>::iterator last, vector<int>::iterator bfirst) {
    auto n = distance(first, last);
    if(n < 2)
        return 0;

    auto mid = first + n / 2;
    auto bmid = bfirst + n / 2;
    auto blast = bfirst + n;

    auto count1 = ms2_helper(first, mid, bfirst);
    auto count2 = ms2_helper(mid, last, bmid);

    size_type count = 0;
    auto k0=first, k1=mid;
    for(auto k=bfirst; k!=blast; ++k) {
        if(k0 != mid && (k1 == last || *k0 <= *k1)) {
            *k = *(k0++);
        } else {
            *k = *(k1++);
            count += distance(k0, mid);
        }
    }
    move(bfirst, blast, first);

    return count + count1 + count2;
}
size_type inversions_ms2(vector<int> a) {
    auto n = a.size();
    vector<int> b(n);
    return ms2_helper(begin(a), end(a), begin(b));
}

size_type inversions_ms3(vector<int> a) {
    auto n = a.size();

    size_type count = 0;
    vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        size_type first, last;
        for(first=0, last=min(2*width, n); first<n; first=last, last=min(last+2*width, n)) {
            auto mid = min(first+width, n);
            size_type k0=first, k1=mid;
            for(auto k=first; k<last; ++k) {
                if(k0 < mid && (k1 >= last || a[k0] <= a[k1])) {
                    b[k] = a[k0++];
                } else {
                    b[k] = a[k1++];
                    count += mid-k0;
                }
            }
        }
        move(begin(b), end(b), begin(a));
    }

    return count;
}
/*
size_type inversions_ms3(vector<int> a) {
    auto n = a.size();

    size_type count = 0;
    vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        for(size_type i=0; i<n; i+=2*width) {
            auto m = min(width, n-i);
            auto l = min(m+width, n-i);
            auto first = begin(a)+i;
            auto mid = first + m;
            auto last = first + l;
            auto bfirst = begin(b) + i;
            auto blast = bfirst + l;
            auto k0=first, k1=mid;
            for(auto k=bfirst; k<blast; ++k) {
                if(k0 != mid && (k1 == last || *k0 <= *k1)) {
                    *k = *(k0++);
                } else {
                    *k = *(k1++);
                    count += distance(k0, mid);
                }
            }
        }
        move(begin(b), end(b), begin(a));
    }

    return count;
}
*/

size_t inversions_ms3_a(int a[], size_t n) {
    size_t count = 0;
    int *b = new int[n];
    for(size_t width = 1; width < n; width *= 2) {
        size_t first, last;
        for(first=0, last=min(2*width, n); first<n; first=last, last=min(last+2*width, n)) {
            auto mid = min(first+width, n);
            size_t k0=first, k1=mid;
            for(auto k=first; k<last; k++) {
                if(k0 < mid && (k1 >= last || a[k0] <= a[k1])) {
                    b[k] = a[k0++];
                } else {
                    b[k] = a[k1++];
                    count += mid-k0;
                }
            }
        }
        copy(b, b+n, a);
    }
    delete[] b;

    return count;
}
