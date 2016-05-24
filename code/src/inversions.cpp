#include "inversions.hpp"

#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

#include "utilities.hpp"

using namespace std;

using size_type = vector<int>::size_type;

size_type inversions_bf(vector<int> const &a) {
    //auto n = a.size();
    size_type count = 0;
    /*
    for(size_type i=0; i<n-1; i++)
        for(size_type j=i+1; j<n; j++)
            if(a[i] > a[j])
                count++;
    */
    for(auto i=begin(a); i!=prev(end(a)); i++)
        for(auto j=next(i); j!=end(a); j++)
            if(*i > *j)
                count++;
    return count;
}

size_type inversions_is1(vector<int> a) {
    size_type count = 0;
    /*
    for(size_type i=1; i<n; i++) {
        size_type j;
        for(j=i; j>0 && a[j-1]>a[j]; j--) {
            swap(a[j-1],a[j]);
        }
        count += i-j;
    }
    */
    for(auto i=next(begin(a)); i!=end(a); i++) {
        decltype(i) j;
        for(j=i; j!=begin(a) && *prev(j)>*j; j--)
            swap(*prev(j),*j);
        count += distance(j, i);
    }

    return count;
}

size_type inversions_is2(vector<int> a) {
    size_type count = 0;
    for(auto i=next(begin(a)); i!=end(a); i++) {
        auto first = upper_bound(begin(a), i, *i);
        rotate(first,i,next(i));
        count += distance(first, i);
    }
    return count;
}

size_type ms1_helper(vector<int> &a, size_type first, size_type last) {
    auto n = last-first;
    if(n < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms1_helper(a,first,mid);
    auto count2 = ms1_helper(a,mid,last);

    size_type count = 0;
    vector<int> b(n);
    auto k0=first, k1=mid;
    for(size_type k=0; k<n; k++) {
        if(k0 < mid && (k1 >= last || a[k0] <= a[k1])) {
            b[k] = a[k0++];
        } else {
            b[k] = a[k1++];
            count += mid-k0;
        }
    }

    copy(b.begin(), b.end(), a.begin()+first);

    return count + count1 + count2;
}
size_type inversions_ms1(vector<int> a) {
    return ms1_helper(a,0,a.size());
}

size_type ms2_helper(vector<int> &a, size_type first, size_type last, vector<int> &b) {
    if(last - first < 2)
        return 0;

    auto mid = (first + last) / 2;

    auto count1 = ms2_helper(a,first,mid,b);
    auto count2 = ms2_helper(a,mid,last,b);

    size_type count = 0;
    auto k0=first, k1=mid;
    for(auto k=first; k<last; k++) {
        if(k0 < mid && (k1 >= last || a[k0] <= a[k1])) {
            b[k] = a[k0++];
        } else {
            b[k] = a[k1++];
            count += mid-k0;
        }
    }

    copy(b.begin()+first, b.begin()+last, a.begin()+first);

    return count + count1 + count2;
}
size_type inversions_ms2(vector<int> a) {
    auto n = a.size();
    vector<int> b(n);
    return ms2_helper(a,0,n,b);
}

size_type inversions_ms3(vector<int> a) {
    auto n = a.size();

    size_type count = 0;
    vector<int> b(n);
    for(size_type width = 1; width < n; width *= 2) {
        size_type first,last;
        for(first=0,last=min(2*width,n); first<n; first=last,last=min(last+2*width,n)) {
            auto mid = min(first+width,n);
            size_type k0=first, k1=mid;
            for(auto k=first; k<last; k++) {
                if(k0 < mid && (k1 >= last || a[k0] <= a[k1])) {
                    b[k] = a[k0++];
                } else {
                    b[k] = a[k1++];
                    count += mid-k0;
                }
            }
        }
        copy(b.begin(), b.end(), a.begin());
    }

    return count;
}

size_t inversions_ms3_a(int a[], size_t n) {
    size_t count = 0;
    int *b = new int[n];
    for(size_t width = 1; width < n; width *= 2) {
        size_t first,last;
        for(first=0,last=min(2*width,n); first<n; first=last,last=min(last+2*width,n)) {
            auto mid = min(first+width,n);
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
