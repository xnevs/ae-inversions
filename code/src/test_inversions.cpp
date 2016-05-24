#include <iostream>

#include <string>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

#include "utilities.hpp"
#include "inversions.hpp"

#define TEST(f, rep, a) {                                                          \
    std::chrono::time_point<std::chrono::steady_clock> _TEST_start, _TEST_end;     \
    _TEST_start = std::chrono::steady_clock::now();                                \
    for(int _TEST_i=0; _TEST_i<rep; _TEST_i++) {                                   \
        (f)((a));                                                                  \
    }                                                                              \
    _TEST_end = std::chrono::steady_clock::now();                                  \
    std::chrono::duration<double> _TEST_elapsed_seconds = _TEST_end - _TEST_start; \
    cout << #f"\t" << _TEST_elapsed_seconds.count() << " s" << endl;               \
}


using namespace std;

//using Algorithm = function<vector<int>::size_type(vector<int> const &)>;
//using Algorithm = vector<int>::size_type (*)(vector<int>);

Alg alg;
int n;
Seq seq;
int rep;

bool parse_args(int argc, char *argv[]) {
    if(argc != 5)
        return false;

    string alg_{argv[1]};
    string n_{argv[2]};
    string seq_{argv[3]};
    string rep_{argv[4]};
   
    if(alg_ == "bf") {
        alg = Alg::bf;
    } else if(alg_ == "is1") {
        alg = Alg::is1;
    } else if(alg_ == "is2") {
        alg = Alg::is2;
    } else if(alg_ == "ms1") {
        alg = Alg::ms1;
    } else if(alg_ == "ms2") {
        alg = Alg::ms2;
    } else if(alg_ == "ms3") {
        alg = Alg::ms3;
    } else {
        return false;
    }

    try {
        n = stoi(n_);
    } catch(...) {
        return false;
    }

    if(seq_ == "inc") {
        seq = Seq::inc;
    } else if(seq_ == "dec") {
        seq = Seq::dec;
    } else if(seq_ == "rnd") {
        seq = Seq::rnd;
    } else {
        return false;
    }

    try {
        rep = stoi(rep_);
    } catch(...) {
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    
    if(!parse_args(argc,argv)) {
        cout << "napaka z argumenti" << endl;
        return -1;
    }

    random_device rd;
    default_random_engine random{rd()};

    auto a = generate(n,seq,random);

    //cout << " bf: " << inversions_bf(a) << endl;
    //cout << "alg: " << alg(a) << endl;

    switch(alg) {
    case Alg::bf:
        TEST(inversions_bf , rep, a);
        break;
    case Alg::is1:
        TEST(inversions_is1, rep, a);
        break;
    case Alg::is2:
        TEST(inversions_is2, rep, a);
        break;
    case Alg::ms1:
        TEST(inversions_ms1, rep, a);
        break;
    case Alg::ms2:
        TEST(inversions_ms2, rep, a);
        break;
    case Alg::ms3:
        TEST(inversions_ms3, rep, a);
        break;
    }
}
