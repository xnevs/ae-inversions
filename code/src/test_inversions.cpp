#include <iostream>

#include <string>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

#include "utilities.hpp"
#include "inversions.hpp"

using namespace std;

using Algorithm = function<vector<int>::size_type(vector<int> const &)>;
//using Algorithm = vector<int>::size_type (*)(vector<int>);

Algorithm alg;
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
        alg = inversions_bf;
    } else if(alg_ == "is1") {
        alg = inversions_is1;
    } else if(alg_ == "is2") {
        alg = inversions_is2;
    } else if(alg_ == "ms1") {
        alg = inversions_ms1;
    } else if(alg_ == "ms2") {
        alg = inversions_ms2;
    } else if(alg_ == "ms3") {
        alg = inversions_ms3;
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
    //default_random_engine random{rd()};

    default_random_engine random;

    auto seed = rd();

    random.seed(seed);
    auto a = generate(n,seq,random);

    random.seed(seed);
    auto a_a = generate_a(n,seq,random);

    //cout << " bf: " << inversions_bf(a) << endl;
    //cout << "alg: " << alg(a) << endl;

    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();

    for(int i=0; i<rep; i++) {
        alg(a);
    }

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    cout << "time: " << elapsed_seconds.count() << " s" << endl;
}
