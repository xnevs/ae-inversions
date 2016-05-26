#include "inversions.hpp"

#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

using namespace std;

using size_type = vector<int>::size_type;

size_type inversions_bf_idx(vector<int> const & a) {
    auto n = a.size();
    size_type count = 0;
    for(size_type i=0; i<n-1; i++)
        for(size_type j=i+1; j<n; j++)
            if(a[j] < a[i])
                ++count;
    return count;
}

size_type inversions_bf(vector<int> const & a) {
    size_type count = 0;
    for(auto i=begin(a); i!=prev(end(a)); ++i)
        for(auto j=next(i); j!=end(a); ++j)
            if(*j < *i)
                ++count;
    return count;
}

size_type inversions_is1_idx(vector<int> a) {
    auto n = a.size();
    size_type count = 0;
    for(size_type i=1; i<n; ++i) {
        size_type j;
        for(j=i; j>0 && a[j]<a[j-1]; --j) {
            swap(a[j-1],a[j]);
        }
        count += i-j;
    }
    return count;
}

size_type inversions_is1(vector<int> a) {
    size_type count = 0;
    for(auto i=next(begin(a)); i!=end(a); ++i) {
        decltype(i) j;
        for(j=i; j!=begin(a) && *j<*prev(j); --j)
            swap(*prev(j), *j);
        count += distance(j, i);
    }
    return count;
}

size_type inversions_is2_idx(vector<int> a) {
    auto n = a.size();
    size_type count = 0;
    for(size_type i=1; i<n; ++i) {
        auto x = a[i];
        size_type j;
        for(j=i; j>0 && x<a[j-1]; --j) {
            a[j] = a[j-1];
        }
        a[j] = x;
        count += i-j;
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

size_type ms1_helper_idx(vector<int> &a, size_type first, size_type last) {
    auto n = last-first;
    if(n < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms1_helper_idx(a,first,mid);
    auto count2 = ms1_helper_idx(a,mid,last);

    size_type count = 0;
    vector<int> b(n);
    auto k0=first, k1=mid;
    for(size_type k=0; k<n; k++) {
        if(k1 != last && (k0 == mid || a[k1] < a[k0])) {
            b[k] = a[k1++];
            count += mid - k0;
        } else {
            b[k] = a[k0++];
        }
    }
    move(b.begin(), b.end(), a.begin()+first);

    return count + count1 + count2;
}
size_type inversions_ms1_idx(vector<int> a) {
    return ms1_helper_idx(a,0,a.size());
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
        if(k1 != last && (k0 == mid || *k1 < *k0)) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
        }
    }
    move(begin(b), end(b), first);

    return count + count1 + count2;
}
size_type inversions_ms1(vector<int> a) {
    return ms1_helper(begin(a), end(a));
}

size_type ms2_helper_idx(vector<int> & a, size_type first, size_type last, vector<int> & b) {
    if(last - first < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms2_helper_idx(a,first,mid,b);
    auto count2 = ms2_helper_idx(a,mid,last,b);

    size_type count = 0;
    auto k0=first, k1=mid;
    for(auto k=first; k<last; k++) {
        if(k1 != last && (k0 == mid || a[k1] < a[k0])) {
            b[k] = a[k1++];
            count += mid - k0;
        } else {
            b[k] = a[k0++];
        }
    }
    move(b.begin()+first, b.begin()+last, a.begin()+first);

    return count + count1 + count2;
}
size_type inversions_ms2_idx(vector<int> a) {
    auto n = a.size();
    vector<int> b(n);
    return ms2_helper_idx(a,0,n,b);
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
        if(k1 != last && (k0 == mid || *k1 < *k0)) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
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

size_type inversions_ms3_idx(vector<int> a) {
    auto n = a.size();
    size_type count = 0;
    vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        size_type first, last;
        for(first=0, last=min(2*width, n); first<n; first=last, last=min(last+2*width, n)) {
            auto mid = min(first+width, n);
            size_type k0=first, k1=mid;
            for(auto k=first; k<last; ++k) {
                if(k1 != last && (k0 == mid || a[k1] < a[k0])) {
                    b[k] = a[k1++];
                    count += mid - k0;
                } else {
                    b[k] = a[k0++];
                }
            }
        }
        move(begin(b), end(b), begin(a));
    }
    return count;
}

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
                if(k1 != last && (k0 == mid || *k1 < *k0)) {
                    *k = *(k1++);
                    count += distance(k0, mid);
                } else {
                    *k = *(k0++);
                }
            }
        }
        move(begin(b), end(b), begin(a));
    }
    return count;
}

#define MS2_CUTOFF 13
size_type ms2_is2_helper(vector<int>::iterator first, vector<int>::iterator last, vector<int>::iterator bfirst) {
    auto n = distance(first, last);
    size_type count = 0;

    if(n < MS2_CUTOFF) {
        for(auto i=next(first); i!=last; ++i) {
            auto j = upper_bound(first, i, *i);
            rotate(j, i, next(i));
            count += distance(j, i);
        }
        return count;
    }

    auto mid = first + n / 2;
    auto bmid = bfirst + n / 2;
    auto blast = bfirst + n;

    auto count1 = ms2_is2_helper(first, mid, bfirst);
    auto count2 = ms2_is2_helper(mid, last, bmid);

    auto k0=first, k1=mid;
    for(auto k=bfirst; k!=blast; ++k) {
        if(k1 != last && (k0 == mid || *k1 < *k0)) {
            *k = *(k1++);
            count += distance(k0, mid);
        } else {
            *k = *(k0++);
        }

    }
    move(bfirst, blast, first);

    return count + count1 + count2;
}
size_type inversions_ms2_is2(vector<int> a) {
    auto n = a.size();
    vector<int> b(n);
    return ms2_is2_helper(begin(a), end(a), begin(b));
}

#define MS3_CUTOFF 13
size_type inversions_ms3_is2(vector<int> a) {
    auto n = a.size();
    size_type count = 0;

    // is2 algorithm
    for(auto first=begin(a); first<end(a); first+=MS3_CUTOFF) {
        auto last = min(first+MS3_CUTOFF,end(a));
        for(auto i=next(first); i!=last; ++i) {
            auto j = upper_bound(first, i, *i);
            rotate(j, i, next(i));
            count += distance(j, i);
        }
    }

    // ms3 algorithm
    vector<int> b(n);
    for(size_type width = MS3_CUTOFF; width < n; width *= 2) {
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
                if(k1 != last && (k0 == mid || *k1 < *k0)) {
                    *k = *(k1++);
                    count += distance(k0, mid);
                } else {
                    *k = *(k0++);
                }
            }
        }
        move(begin(b), end(b), begin(a));
    }
    return count;
}
